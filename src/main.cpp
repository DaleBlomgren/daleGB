/**************************
 * Clock Speed: 4.194304 MHz
 * Sound: 4 Channels
 * Total Memory Bank: 64KB
 * 
***************************/


#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "GameBoy.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv){
    if (argc < 2) {
        printf("Usage: daleGB.exe GameboyFile.GB\n\n");
        return 1;
    }
    else if (argc > 2) {
        printf("Usage: daleGB.exe GameboyFile.GB\n\n");
        return 1;
    }

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init_Video Error: " << std::endl;
		return 2;
	}

    window = SDL_CreateWindow("DaleGB",
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN );

    if (window == NULL){
        std::cout << "SDL_Createwindow points to null" << std::endl;
        return 3;
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
    SDL_UpdateWindowSurface( window );
    
    ROM gameRom(argv[1]);
    GameBoy GB(gameRom);
    SDL_Event event; 
    GB.run(event);

    SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}