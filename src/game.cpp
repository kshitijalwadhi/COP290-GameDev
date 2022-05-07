#include "game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Spawnable.h"
#include "Map.h"
#include "Menu.h"

GameObject* player1;
GameObject* player2;

std::vector<Enemy*> enemies;

std::vector<Spawnable*> spawnables;
Spawnable* temp;

Map* map;

Menu* menu;

SDL_Renderer* Game::renderer = nullptr;

Mix_Music *gMenuMusic = NULL;

Uint32 lastSpawn=0;
Uint32 lastStatusTime=0;

SDL_Rect statusRect = {750, 35*16, 350, 3*16};
SDL_Texture* statusTexture = nullptr;
std::string statusText = "";

SDL_Rect dstRect_ToMenu = {685, 20, 50, 50};
SDL_Texture* menuTex = nullptr;

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
        isMultiplayer = false;

        map = new Map();

        player1 = new GameObject("../assets/sprites/characters.png", 128, 48, 1, 1, startTime);
        player2 = new GameObject("../assets/sprites/characters.png", 128, 19*16, 2, 3, startTime);

        menu = new Menu();
        startTime = 0;
        numEnemies = 0;
        numSpawnables = 0;
        gameOver = true;
    }
    else{
        isRunning = false;
    }
}

bool checkInsideRect(int x, int y, SDL_Rect rect)
{
    if(x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    {
        return true;
    }
    return false;
}

void Game::handleEvents()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    SDL_PollEvent(&event);
    int x, y;
    SDL_GetMouseState(&x, &y);

    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(checkInsideRect(x, y, dstRect_ToMenu))
            {
                isMenuScreen = true;
            }
        default:
            break;
    }
    player1->updatePos(event, state, map->map_mat,1);
    if(isMultiplayer)
        player2->updatePos(event, state, map->map_mat,2);
            
}

void Game::spawnableSpawnHelper()
{
    if(SDL_GetTicks() - lastSpawn > globals::spawnDelay)
    {
        std::pair<int,int> valSpawn = map->validPos();
        int potion_type = rand() % 4;
        int capacity = rand()%3 + 1;
        temp = new Spawnable("../assets/collectibles/potions-tileset.png",valSpawn.first*16, valSpawn.second*16, potion_type, capacity);
        temp->potion_type = potion_type;
        temp->capacity = capacity;
        spawnables.push_back(temp);
        lastSpawn = SDL_GetTicks();
        numSpawnables++;
    }
}

void Game::enemySpawnHelper()
{
    int rnd = rand()%globals::enemySpawnRate;
    if (rnd==0){
        std::pair<int,int> spawnLoc = map->validPos();
        Enemy* temp = new Enemy("../assets/sprites/characters.png", spawnLoc.first*16, spawnLoc.second*16, 7, startTime);
        enemies.push_back(temp);
        numEnemies++;
    }
}

void Game::checkSpawnableIntersection()
{
    bool intersect_1, intersect_2;
    for(int i=0; i<spawnables.size(); i++)
    {
        intersect_1 = false;
        intersect_2 = false;
        int xpos_spawn = spawnables[i]->getX();
        int ypos_spawn = spawnables[i]->getY();
        intersect_1 = player1->checkAndHandleSpawnableIntersection(xpos_spawn, ypos_spawn, spawnables[i]->getPotionType(), spawnables[i]->getCapacity());
        if(isMultiplayer)
            intersect_2 = player2->checkAndHandleSpawnableIntersection(xpos_spawn, ypos_spawn, spawnables[i]->getPotionType(), spawnables[i]->getCapacity());
        if(intersect_1 && !intersect_2)
            statusText = "P1 potion";
        if(intersect_2 && !intersect_1)
            statusText = "P2 potion";
        if(intersect_1 && intersect_2)
            statusText = "P1,P2 potion";

        lastStatusTime = SDL_GetTicks();

        if(intersect_1 || intersect_2)
        {
            spawnables[i]->~Spawnable();
            spawnables.erase(spawnables.begin()+i);
            i--;
            numSpawnables--;
        }
    }
}

void Game::checkEnemyInteraction()
{
    for(int i=0; i<enemies.size(); i++)
    {
        int xpos_enemy = enemies[i]->getX();
        int ypos_enemy = enemies[i]->getY();
        player1->checkAndHandleEnemyIntersection(xpos_enemy, ypos_enemy);
        if(isMultiplayer)
            player2->checkAndHandleEnemyIntersection(xpos_enemy, ypos_enemy);
    }
}

void Game::updateStatusText()
{
    if(isMultiplayer)
    {
        bool player1_alive;
        bool player2_alive;
        player1_alive = player1->isAlive();
        player2_alive = player2->isAlive();

        if(player1_alive && !player2_alive)
            statusText = "Player 1 Wins!";
        else if(!player1_alive && player2_alive)
            statusText = "Player 2 Wins!";
        else if(!player1_alive && !player2_alive)
            statusText = "Draw!";
        
        gameOver = !(player1_alive && player2_alive);
    }
    else{
        if(!player1->isAlive())
            statusText = "You lose!";
        
        gameOver = !player1->isAlive();
    }
    if(!gameOver && statusText!="")
    {
        if(SDL_GetTicks() - lastStatusTime > 5000)
            statusText = "";
    }
}

void Game::update()
{
    // handle game logic here
    if(!gameOver & !isMenuScreen)
    {
        player1->update(map->map_mat);
        if(isMultiplayer)
            player2->update(map->map_mat);
        if(numEnemies<globals::maxEnemies){
            enemySpawnHelper();
        }
        if(numSpawnables<globals::maxSpawnables){
            spawnableSpawnHelper();
        }
        for(auto enemy : enemies)
        {
            enemy->update();
            enemy->updatePosEnemy(map->map_mat);
        }
        checkSpawnableIntersection();
        checkEnemyInteraction();
    }
    updateStatusText();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // rendering done here
    map->drawMap();
    player1->render();
    if(isMultiplayer)
        player2->render();
    for(auto spawnable : spawnables)
    {
        spawnable->render();
    }
    for(auto enemy : enemies)
    {
        enemy->render();
    }
    if(statusText != "")
    {
        statusTexture = TextureManager::loadTextureFromText(statusText,"../assets/fonts/Raleway-Medium.ttf", 32, {255, 255, 255});
        TextureManager::drawText(statusTexture, statusRect);
        SDL_DestroyTexture(statusTexture);
    }
    menuTex = TextureManager::loadTextureFromText("Menu","../assets/fonts/Raleway-Medium.ttf", 32, {255, 255, 255});
    TextureManager::drawText(menuTex, dstRect_ToMenu);
    SDL_DestroyTexture(menuTex);
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
                    player1->~GameObject();
                    player2->~GameObject();
                    map->~Map();
                    isMenuScreen = false;
                    isMultiplayer = false;
                    map = new Map();

                    player1 = new GameObject("../assets/sprites/characters.png", 128, 48, 1, 1, startTime);
                    player2 = new GameObject("../assets/sprites/characters.png", 128, 19*16, 2, 3, startTime);

                    startTime = 0;
                    numEnemies = 0;
                    numSpawnables = 0;
                    gameOver = false;

                    statusText = "";
                    lastSpawn=0;
                    enemies.clear();
                    spawnables.clear();
                    break;
                case 2:
                    player1->~GameObject();
                    player2->~GameObject();
                    map->~Map();
                    isMenuScreen = false;
                    isMultiplayer = true;
                    map = new Map();

                    player1 = new GameObject("../assets/sprites/characters.png", 128, 48, 1, 1, startTime);
                    player2 = new GameObject("../assets/sprites/characters.png", 128, 19*16, 2, 3, startTime);

                    startTime = 0;
                    numEnemies = 0;
                    numSpawnables = 0;
                    gameOver = false;

                    statusText = "";
                    lastSpawn=0;
                    enemies.clear();
                    spawnables.clear();
                    break;
                case 3:
                    isRunning = false;
                    break;
                case 4:
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
                case 5:
                {
                    isMenuScreen = false;
                }
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
    menu->update(gameOver);
    menu->isPaused = gameOver;
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