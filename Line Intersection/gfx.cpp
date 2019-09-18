#include "SDL.h"
#include "data.h"

SDL_Window* gWindow;

SDL_Renderer* gRenderer;

bool Vid_Init(){
    bool success = true;

    //Init SDL Video
    if(SDL_Init(SDL_INIT_VIDEO) == 0){

        gWindow = SDL_CreateWindow("Physics Test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,320,240,SDL_WINDOW_SHOWN);

        //Check if Window Created
        if(gWindow != NULL){

            gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);

            //Check if Renderer Created
            if(gRenderer == NULL){
                success = false;
            }

        }else{
            success = false;
        }

    }else{
        success = false;
    }

    return success;
}

void Vid_Reset(int* Controls){
    SDL_Event e;

    for(int i = 0;i < sizeof(*Controls) / sizeof(*(Controls + 1));i ++){
        *(Controls + i) = 0;
    }

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            *(Controls) = 1;
        }
    }
}

void Vid_Apply(){
    SDL_RenderPresent(gRenderer);
}

void Draw_Texture(){
    
}