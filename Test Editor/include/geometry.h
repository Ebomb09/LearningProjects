#ifndef GEOM_H
#define GEOM_H

    #include "SDL.h"

    #include <math.h>

    int Clamp(float Value, int Grid);
    int Raise(float Value, int Grid);

    struct Vector2{
        float X;
        float Y;
    };

    struct Area{
        int Width;
        int Height;
        Vector2 Position;

        SDL_Rect GetSDLRect();
        void Snap(int Grid);
    };

    Area CreateArea(Vector2 Pos, Vector2 Pos2);

#endif