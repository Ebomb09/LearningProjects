#include "classes.h"
#include "video.h"

void RunApp(){

    bool Exit = false;

    int Controls[8] {0};

    /*
        0, Exit
        1 -> 4, Movement, Left - Right - Up - Down
        5, MouseX
        6, MouseY
        7, MouseLB
        8, MouseRB
    */

    while(!Exit){
        const int CurrentTick = SDL_GetTicks();

        Video::ClearScreen();

        Video::GetControls(Controls,8);

        //Handle Controls
        if(Controls[0] == 1){
            Exit = true;
        }

        Video::UpdateScreen();

        Video::FrameCap(CurrentTick);
    }

}

int main(int argc, char* argv[]){

    if(Video::Init("Game",640,480)){

        Video::SetFPS(60);
        RunApp();

    }

    return 0;
}