#include "geometry.h"
#include <iostream>

inline int Clamp(float Value, int Grid){
    return floor(Value / Grid) * Grid;
}

inline int Raise(float Value, int Grid){
    return ceil(Value / Grid) * Grid;
}

void Area::Snap(int Grid){
	Vector2 BR = {Position.X + Width, Position.Y + Height};
	
    Position.X = Clamp(Position.X, Grid);
    Position.Y = Clamp(Position.Y, Grid);
	
	BR.X = Raise(BR.X, Grid);
	BR.Y = Raise(BR.Y, Grid);
	
	Width = BR.X - Position.X;
	Height = BR.Y - Position.Y;
}

SDL_Rect Area::GetSDLRect(){
    SDL_Rect rect {0,0,Width,Height};

    return rect;
}

Area CreateArea(Vector2 Pos, Vector2 Pos2){
    int X = (Pos.X < Pos2.X) ? Pos.X : Pos2.X;
    int Y = (Pos.Y < Pos2.Y) ? Pos.Y : Pos2.Y;

    int X2 = (Pos.X > Pos2.X) ? Pos.X : Pos2.X;
    int Y2 = (Pos.Y > Pos2.Y) ? Pos.Y : Pos2.Y;

    Vector2 newPos = {X,Y};
    Vector2 newPos2 = {X2,Y2};

    int Width = X2 - X;
    int Height = Y2 - Y;

    Area dim = {Width,Height,newPos};

    return dim;
}