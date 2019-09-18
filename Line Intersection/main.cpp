#include <iostream>
#include <vector>

#include "data.h"
#include "gfx.h"

int main(){

    std::cout<<"Starting Simulation \n";

    //Run Simulation
    if(Vid_Init()){

        bool mainLoop = true;

        int Controls[2];

        Body* Objects;

        //LoadMap("MyLevel",Objects);

        while(mainLoop){
            Vid_Reset(Controls);
            
            if(Controls[0] == 1){
                mainLoop = false;
            }

            Vid_Apply();
        }

    }else{
        std::cout<<"Failed To Initialize Video";
    }

    std::cout<<"Press Enter To Exit";
    std::cin.ignore();

    return 0;
}