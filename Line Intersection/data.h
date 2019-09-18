#ifndef DATA_H
#define DATA_H

#include <string>
using std::string;

namespace World{
    extern float Gravity;
}

struct Vector2{
    float X;
    float Y;
};

struct Body{
    float Mass;
    Vector2 Position;
    Vector2 Velocity;

    void Step();
    void ApplyForce(Vector2 Force);
};

struct Line{
    Vector2 Point;
    Vector2 Point2;
};

bool Line_HasIntersection(Line A, Line B);
float PointDistance(Vector2 A, Vector2 B);

bool LoadMap(string Fname, Body* Objects);
bool SaveMap(string Fname, Body* Objects);

#endif