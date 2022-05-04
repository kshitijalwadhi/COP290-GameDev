#include "game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Menu.h"

GameObject* player;

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

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            return;
        }

        gMenuMusic = Mix_LoadMUS("../assets/audio/menu.wav");

        if(gMenuMusic == NULL)
        {
            printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
            return;
        }
        bgMusicPlaying = true;
        Mix_PlayMusic(gMenuMusic, -1);

        isRunning = true;
        isMenuScreen = true;

        player = new GameObject("../assets/sprites/MyChar.png", 100, 100);
        map = new Map();

        menu = new Menu();
    }
    else{
        isRunning = false;
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        case SDL_KEYDOWN:
            player->updatePos(event, map->map);
            break;
        
        default:
            break;
    }
}

void Game::update()
{
    // handle game logic here
    player->update();

    // add code to load map from .txt file from here
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // rendering done here
    map->drawMap();
    player->render();
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
    //player->update();
}

void Game::renderMenu()
{
    SDL_RenderClear(renderer);
    menu->render();
    //player->render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    Mix_FreeMusic( gMenuMusic );
    gMenuMusic = NULL;
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Game cleaned"<<std::endl;
}