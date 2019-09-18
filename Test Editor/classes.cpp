#include "classes.h"

void Object::SetDimensions(int w, int h){
    Width = w;
    Height = h;
}

bool Object::ContainsObject(Object& _Obj){
    bool success = false;

    Vector2& Pos = Position;
    Vector2& cPos = _Obj.Position;

    Vector2 dim = Vector2{ Width * Sprite.Size.Width, Height * Sprite.Size.Height};
    Vector2 cdim = Vector2{ _Obj.Width * _Obj.Sprite.Size.Width, _Obj.Height * _Obj.Sprite.Size.Height};

    if(Pos.X <= cPos.X && Pos.X + dim.X >= cPos.X + cdim.X)
        if(Pos.Y <= cPos.Y && Pos.Y + dim.Y >= cPos.Y + cdim.Y)
            success = true;

    return success;
}

bool Object::IntersectsObject(Object& _Obj){
    bool success = false;

    Vector2& Pos = Position;
    Vector2& cPos = _Obj.Position;

    Vector2 cdim = Vector2{ _Obj.Width * Sprite.Size.Width, _Obj.Height * Sprite.Size.Height};

    if(cPos.X <= Pos.X && cPos.X + cdim.X >= Pos.X)
        if(cPos.Y <= Pos.Y && cPos.Y + cdim.Y >= Pos.Y)
            success = true;

    return success;
}

void Object::Draw(){
    //Default Example Draw Method
    for(unsigned int i = 0;i < Width;i ++){
        for(unsigned int j = 0;j < Height;j ++){
            DrawScreen(Sprite,Position.X + Sprite.Size.Width * i,Position.Y + Sprite.Size.Height * j,0,0);
        }
    }

    //After Drawing Perform Object Specific Functions
    Step();
}

void Player::HandleInput(int Controls[]){
    if(Controls[1])
        Position.X --;

    if(Controls[2])
        Position.X ++;

    if(Controls[3])
        Position.Y --;

    if(Controls[4])
        Position.Y ++;    
}