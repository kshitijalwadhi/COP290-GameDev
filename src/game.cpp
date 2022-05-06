#include "game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Map.h"
#include "Menu.h"

GameObject* player1;
GameObject* player2;

std::vector<Enemy*> enemies;

Map* map;

Menu* menu;

SDL_Renderer* Game::renderer = nullptr;

Mix_Music *gMenuMusic = NULL;

Game::Game()
{
    isRunning = false;
    window = NULL;
    renderer = NULL;
}

Game::~Game()
{
    clean();
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    // check if init proper
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<<"SDL init success"<<std::endl;

        if(fullscreen)
            window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_FULLSCREEN);
        else
            window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        
        if(window)
        {
            std::cout<<"Window created"<<std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer)
        {
            // placeholder for now
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout<<"Renderer created"<<std::endl;
        }

        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            return;
        }

        int flags = MIX_INIT_MP3;
        
        Mix_Init(flags);

        if( Mix_OpenAudio( 22050, AUDIO_S16SYS, 2, 640 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            return;
        }

        gMenuMusic = Mix_LoadMUS("../assets/audio/menu.mp3");

        if(gMenuMusic == NULL)
        {
            printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
            return;
        }
        bgMusicPlaying = true;
        Mix_PlayMusic(gMenuMusic, 1);

        isRunning = true;
        isMenuScreen = true;

        map = new Map();

        player1 = new GameObject("../assets/sprites/characters.png", 128, 48, 1, 1, startTime);
        player2 = new GameObject("../assets/sprites/characters.png", 128, 19*16, 2, 3, startTime);

        menu = new Menu();
        startTime = 0;
        numEnemies = 0;
    }
    else{
        isRunning = false;
    }
}

void Game::handleEvents()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        case SDL_KEYDOWN:
            player1->updatePos(event, state, map->map_mat,1);
            player2->updatePos(event, state, map->map_mat,2);
            break;
        
        default:
            break;
    }
}

void Game::enemySpawnHelper()
{
    int rnd = rand()%globals::enemySpawnRate;
    if (rnd==0){
        std::pair<int,int> spawnLoc = map->validPos();
        //GameObject* temp = new GameObject("../assets/sprites/characters.png", spawnLoc.first*16, spawnLoc.second*16, 1, 7, startTime, true);
        Enemy* temp = new Enemy("../assets/sprites/characters.png", spawnLoc.first*16, spawnLoc.second*16, 7, startTime);
        enemies.push_back(temp);
        numEnemies++;
    }
}

void Game::update()
{
    // handle game logic here
    player1->update();
    player2->update();
    if(numEnemies<globals::maxEnemies){
        enemySpawnHelper();
    }
    for(auto enemy : enemies)
    {
        enemy->update();
        enemy->updatePosEnemy(map->map_mat);
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // rendering done here
    map->drawMap();
    player1->render();
    player2->render();
    for(auto enemy : enemies)
    {
        enemy->render();
    }
    SDL_RenderPresent(renderer);
}

void Game::handleMenuEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        case SDL_MOUSEBUTTONDOWN:
        {  
            int button_idx = menu->handleClick(event);
            switch (button_idx)
            {
                case 1:
                    isMenuScreen = false;
                    break;
                case 2:
                    isRunning = false;
                    break;
                case 3:
                    {
                        if(bgMusicPlaying)
                        {
                            Mix_PauseMusic();
                            bgMusicPlaying = false;
                        }
                        else
                        {
                            Mix_ResumeMusic();
                            bgMusicPlaying = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        default:
            break;
    }
}



void Game::updateMenu()
{
    menu->update();
}

void Game::renderMenu()
{
    SDL_RenderClear(renderer);
    menu->render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    Mix_FreeMusic( gMenuMusic );
    gMenuMusic = NULL;
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Game cleaned"<<std::endl;
}