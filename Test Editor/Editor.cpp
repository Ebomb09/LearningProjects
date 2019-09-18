#include "classes.h"
#include "video.h"
#include "loader.h"

#include <iostream>
#include <math.h>

void RunApp(){

    bool Exit = false;

    int Controls[NUM_OF_KEYS] {0};

    vector<Object*> Objects;

    Map::LoadMap("Save.map",Objects);

    Vector2 mouseSelection[2];
    int selObj = 0;

    while(!Exit){
        const int CurrentTick = SDL_GetTicks();

        Video::SetDrawColor(0,0,0,0);
        Video::ClearScreen();

        Video::GetControls(Controls);

        //Handle Controls
        if(Controls[sysExit])
            Exit = true;    

        if(Controls[key1]){
            string file = Video::GetTextInput("Save File As...",256,64);
            if(file != ""){
                Map::SaveMap(file, Objects);
            }
        }

        if(Controls[key2])
            selObj = 1;

        //Draw Objects
        for(unsigned int i = 0;i < Objects.size();i ++){
            Objects[i]->Draw();
        }

        //Draw HUD
        Video::SetDrawColor(255,255,255,255);
        Video::DrawRect(Clamp(Controls[mouseX],32),Clamp(Controls[mouseY],32),32,32);

        if (Controls[mouseLDown]){
            mouseSelection[0] = {Controls[mouseX],Controls[mouseY]};
        }

        if (Controls[mouseLHeld]){
            mouseSelection[1] = {Controls[mouseX], Controls[mouseY]};
            Area rect = CreateArea(mouseSelection[0], mouseSelection[1]);
            rect.Snap(32);

            Video::DrawRect(rect);
        }

        if(Controls[mouseLUp]){
            Area rect = CreateArea(mouseSelection[0], mouseSelection[1]);
            rect.Snap(32);
            
            Object* _obj = new BackGround("Data/Images/BgDirt.png",32,32,rect.Width / 32,rect.Height / 32);
            _obj->Position = rect.Position;
            Objects.push_back(_obj);
        }

        Video::UpdateScreen();

        Video::FrameCap(CurrentTick);
    }

/*
    string f;
    getline(std::cin,f);
    Map::SaveMap(f,Objects);
*/

    for(unsigned int i = 0; i < Objects.size();i ++){
        delete Objects[i];
    }

}

int main(int argc, char* argv[]){

    if(Video::Init("Game",640,480)){

        Video::SetFPS(60);

        RunApp();

        Video::Quit();

    }

    return 0;
}