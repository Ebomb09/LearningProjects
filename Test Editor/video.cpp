#include <iostream>

#include "video.h"

SDL_Window*     Window      = NULL;
SDL_Renderer*   Renderer    = NULL;

int FPS_MAX = 0;
int FPS = 0;

namespace Video{

    bool Init(string Name, int Window_Width, int Window_Height){

        bool success = false;

        if(SDL_Init(SDL_INIT_VIDEO) == 0){

            Window = SDL_CreateWindow( Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Window_Width, Window_Height, SDL_WINDOW_SHOWN);

            if(Window != NULL){

                Renderer = SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED);

                if(Renderer != NULL){
                    
                    if(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG){

                        if(TTF_Init() != -1){
                            success = true;
                        }

                    }

                }

            }

        }

        return success;
    }

    void SetFPS(int _FPS){
        //Set Max
        FPS_MAX = _FPS;

        //Set Timer Per Frame
        FPS = 1000 / FPS_MAX;
    }

    void Quit(){
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(Window);

        SDL_Quit();
    }

    void DrawScreen(Texture& text, const float& X, const float& Y, const int& celX, const int& celY, SDL_Renderer* rend){
        if(!rend)
            rend = Renderer;

        //Get Source Sprite From Sheet
        SDL_Rect srcSpot { celX * text.Size.Width, celY * text.Size.Height, text.Size.Width, text.Size.Height};

        //Get Placement
        SDL_Rect rSpot { X, Y, text.Size.Width, text.Size.Height};
        
        //Draw To Screen
        SDL_RenderCopy(rend,text.Image,&srcSpot,&rSpot);
    }

    void DrawRect(const int& x, const int& y, const int& w, const int& h){
        SDL_Rect rect = {x,y,w,h};

        SDL_RenderDrawRect(Renderer, &rect);
    }

    void DrawRect(Area ar){
        SDL_Rect rect = {ar.Position.X,ar.Position.Y,ar.Width,ar.Height};

        SDL_RenderDrawRect(Renderer, &rect);
    }

    void SetDrawColor(const int& r, const int& g, const int& b, const int& a){
        SDL_SetRenderDrawColor(Renderer,r,g,b,a);
    }

    void ClearScreen(){
        //SDL_SetRenderDrawColor(Renderer,255,255,255,255);
        SDL_RenderClear(Renderer);
    }

    void UpdateScreen(){
        SDL_RenderPresent(Renderer);
    }

    void FrameCap(int LastTick){
        int CurrentTick = SDL_GetTicks();

        //Time Needed To Render Screen < Second Per Frame
        if(CurrentTick - LastTick < FPS){
            //Delay Time(ms) Extra Frames
            SDL_Delay(FPS - (CurrentTick - LastTick));
        }
    }

    void GetControls(int* Controls){

        for(unsigned int i = 0;i < NUM_OF_KEYS;i ++){
            if (i != mouseLHeld && i != mouseRHeld)
                Controls[i] = 0;
        }

        //Get SDL Events
        SDL_Event e;
        while(SDL_PollEvent(&e)){

            if(e.type == SDL_QUIT){
                Controls[sysExit] = 1;
            }

            if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                Controls[mouseLDown] = 1;
                Controls[mouseLHeld] = 1;
            }

            if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT){
                Controls[mouseLUp] = 1;
                Controls[mouseLHeld] = 0;
            }

            if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT){
                Controls[mouseRDown] = 1;
                Controls[mouseRHeld] = 1;
            }

            if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT){
                Controls[mouseRUp] = 1;
                Controls[mouseRHeld] = 0;
            }
            
        }

        //Get Keyboard States, SDL_SCANCODE(s)
        const Uint8* States = SDL_GetKeyboardState(NULL);

        Controls[keyLeft] = States[SDL_SCANCODE_A];
        Controls[keyRight] = States[SDL_SCANCODE_D];
        Controls[keyUp] = States[SDL_SCANCODE_W];
        Controls[keyDown] = States[SDL_SCANCODE_S];

        Controls[key1] = States[SDL_SCANCODE_1];
        Controls[key2] = States[SDL_SCANCODE_2];

        SDL_GetMouseState(&Controls[mouseX], &Controls[mouseY]);
    }

    string GetTextInput(const string& Name, const int& Width, const int& Height){

        string input = "";

        SDL_Window* _Window;
        SDL_Renderer* _Renderer;

        _Window = SDL_CreateWindow(Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);

        if(_Window != NULL){

             _Renderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_ACCELERATED);

            if(_Renderer != NULL){

                int WinID = SDL_GetWindowID(_Window);

                SDL_StartTextInput();

                bool Wait = true;
                while(Wait){
                    SDL_SetRenderDrawColor(_Renderer,85,85,85,255);
                    SDL_RenderClear(_Renderer);

                    //SDL_RaiseWindow(_Window);

                    SDL_Event e;
                    while(SDL_PollEvent(&e)){
                        if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                            Wait = false;
                        }
                        if(e.type == SDL_KEYDOWN){
                            if(e.key.keysym.sym == SDLK_BACKSPACE){
                                if(input.length() > 0){
                                    input.pop_back();
                                }
                            }
                            
                        }
                        if(e.type == SDL_TEXTINPUT){
                            input += e.text.text;      
                        }
                    }

                    Texture rendText = Texture("Data/Fonts/8Bit.ttf", input, Vector2 {0,0}, _Renderer );
                    int w = 0;
                    int h = 0;
                    SDL_QueryTexture(rendText.Image,NULL,NULL,&w, &h);
                    rendText.Size = Area{w,h};
                    DrawScreen(rendText, 0, 0, 0, 0, _Renderer);

                    SDL_RenderPresent(_Renderer);
                }

                SDL_StopTextInput();

            }

        }

        SDL_DestroyRenderer(_Renderer);
        SDL_DestroyWindow(_Window);

        return input;
    }

    SDL_Texture* GetTexture(string fname){
        SDL_Surface* surf = IMG_Load(fname.c_str());
        
        SDL_Texture* text = SDL_CreateTextureFromSurface(Renderer,surf);

        SDL_FreeSurface(surf);

        return text;
    }

    SDL_Texture* GetText(string fname, string text, SDL_Renderer* rend){
        if(!rend)
            rend = Renderer;

        TTF_Font* font = TTF_OpenFont(fname.c_str(),24);

        SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), SDL_Color {0,0,0,255});

        SDL_Texture* texture = SDL_CreateTextureFromSurface(rend,surf);

        SDL_FreeSurface(surf);
        TTF_CloseFont(font);

        return texture;
    }

    Texture::~Texture(){
        SDL_DestroyTexture(Image);
    }
}