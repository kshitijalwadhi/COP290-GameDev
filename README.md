# IIT-D Mazetries

## SYSTEM REQUIREMENTS

Operating System used: Ubuntu (22.04)

Resolution: 1280x640 or higher

Refresh Rate of Monitor used during development: 60 Hz
***

## INSTALLATION INSTRUCTIONS

Run the shell script for installing the dependencies. 

`./run.sh`

Note that this will work only on UNIX systems. For windows refer to the guides available online for installing SDL, SDL_image, SDL_ttf, SDL_mixer, SDL_net.

## RUNNING THE GAME

- cd to the _src_ directory
- on terminal, run the following commands
    - `make` for compiling the client side executable
    - `make server` for compiling the server side executable

- For playing locally, just run the client side executable by running the command `./mygame`
- For playing on two systems, first set up the server by running the command `./server`. Then run the clients on two systems/terminals by running the command `./mygame`. 

## FEATURES

- 2D Maze game based on IIT Delhi campus. 
- Networking (Can play with friends on different systems; tested on LAN).
- Local Multiplayer (Can use WASD and arrow keys for multiplayer action).
- Can play solo as well.
- Four different healthbars (Energy, Fitness, Nerdiness, Social Quotient).
- They can be increased by visiting specific locations on campus.
- Potions spawned every now and then at random on the map. Go pick them before your opponent.
- Modelled professors as ghosts which take away your energy but increase your nerdiness. Decide accordingly whether you want to meet them or not :P
- The player that lasts the longest wins. 


## REFERENCES USED DURING DEVELOPMENT

The following references were used during the development of this project:

- SDL, SDL_image, SDL_mixer, SDL_ttf: [LazyFoo](https://lazyfoo.net/tutorials/SDL/index.php), [YouTube Playlist](https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx), [Github Repo](https://github.com/Limeoats/cavestory-development)
- SDL_net: [Docs](https://www.libsdl.org/projects/SDL_net/docs/SDL_net.pdf), [Github Repo](https://github.com/ArnavT005/Maze_Engine/blob/main/PacmanPro/src/server.cpp)

Images and Fonts:

- Open source resources were used for this project. They can be found at the following links:
    - https://opengameart.org/content/tiny-16-basic
    - https://fonts.google.com/specimen/Raleway