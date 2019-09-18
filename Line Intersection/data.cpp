#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include "data.h"

using std::string;

void Body::Step(){
    Position = Vector2{ Position.X + Velocity.X, Position.Y + Velocity.Y};
}
void Body::ApplyForce(Vector2 Force){
    Vector2 Acceleration = Vector2{ Force.X / Mass, Force.Y / Mass};
    Velocity = Vector2{ Velocity.X + Acceleration.X, Velocity.Y + Acceleration.Y};
}

float PointDistance(Vector2 Point, Vector2 Point2){
    return (float)sqrt( pow( Point.X - Point2.X, 2) + pow( Point.Y - Point2.Y, 2));
}

bool WithinRange(float Num, float Av, float Dif){
    return (Num > (Av - Dif) && Num < (Av + Dif));
}

bool Line_HasIntersection(Line A, Line B){
    bool success = false;

    //Using Formula y = mx + b
    short typeA = 0;
    short typeB = 0;

    if(A.Point.X - A.Point2.X == 0){
        //Vertical Line
        typeA = 1;
    }else if(A.Point.Y - A.Point2.Y == 0){
        //Horizontal Line
        typeA = 2;
    }

    if(B.Point.X - B.Point2.X == 0){
        typeB = 1;
    }else if(B.Point.Y - B.Point2.Y == 0){
        typeB = 2;
    }

    //Slope, mx
    float mA;
    float mB;

    //Height, b
    float bA;
    float bB;

    //Find Line Type
    switch(typeA){
        case 0:
            mA = A.Point.X - A.Point2.X;
            bA = A.Point.Y - (mA) * A.Point.X;
        break;
        case 1:
            mA = 0;
            bA = A.Point.X;
        break;
        case 2:
            mA = 0;
            bA = A.Point.Y;
        break;
    }

    switch(typeB){
        case 0:
            mB= B.Point.X - B.Point2.X;
            bB = B.Point.Y - (mB) * B.Point.X;
        break;
        case 1:
            mB = 0;
            bB = B.Point.X;
        break;
        case 2:
            mB = 0;
            bB = B.Point.Y;
        break;
    }

    //std::cout<< "1. y = " << mA << "x + " << bA << " \n";
    //std::cout<< "2. y = " << mB << "x + " << bB << " \n";

    //Use Slope Forumlas -- mx + b = mx + b
    //Subsitute In Values-- mA + bA = mB + bB 
    //Move Similar Values-- mA - mB = bB - bA

    Vector2 Position;

    if(typeA == 0 && typeB == 0){
        float mX = mA - mB;
        float bX = bB - bA;

        //Find Intersect Location
        float x = bX / mX;
        float y = mA * x + bA;
        Position = Vector2{ x, y};
    }else{
        //1 Line With Slope / 1 Without
        if(typeA == 0){ 
            if(typeB == 1){
                Position = Vector2{ (B.Point.Y - bA) / mA, B.Point.Y};
            }
            if(typeB == 2){
                Position = Vector2{ B.Point.X, mA * B.Point.X + bA};
            }
        }
        if(typeB == 0){
            if(typeA == 1){
                Position = Vector2{ (A.Point.Y - bB) / mB, A.Point.Y};
            }
            if(typeA == 2){
                Position = Vector2{ A.Point.X, mB * A.Point.X + bB};
            }
        }
        //No Slope
        if(typeA != 0 && typeB != 0){
            if(typeA == 1 && typeB == 2){
                Position = Vector2{ A.Point.X, B.Point.Y};
            }
            if(typeA == 2 && typeB == 1){
                Position = Vector2{ B.Point.X, A.Point.Y};
            }
            //Both Same
            if(typeA == typeB){
                return (bA == bB);
            }
        }
    }

    //Debug Show Intersect Location
    std::cout<< "Intersection At {" << Position.X << "," << Position.Y << "} \n";

    //Find If Intersection Is In Lines By Distance To Points 
    if(WithinRange(PointDistance(Position,A.Point) + PointDistance(Position,A.Point2) - PointDistance(A.Point,A.Point2),0,0.05f)){

        if(WithinRange(PointDistance(Position,B.Point) + PointDistance(Position,B.Point2) - PointDistance(B.Point,B.Point2),0,0.05f)){

            success = true;
            std::cout<< "Point Within Bounds \n";
        }
    }

    return success;
}

bool SaveMap(string Fname,Body* Objects){
    bool success = true;

    //Initialize File
    std::fstream file;
    file.open(Fname, std::fstream::out | std::fstream::binary);
    file.seekp(0,file.beg);

    //Set Data
    char lData[] = {'a','b','c'};
    file.write(lData, sizeof(lData) / sizeof(lData[0]));

    //Free Resources
    file.close();

    return success;
}

bool LoadMap(string Fname,Body* Objects){
    bool success = true;

    //Initialize File
    std::fstream file;
    file.open(Fname, std::fstream::in | std::fstream::binary);

    //Find Size of File
    file.seekg(0,file.end);
    int size = file.tellg();
    file.seekg(0,file.beg);

    //Create Char For Data Handling
    char* lData = new char[size];

    //Get Data
    file.read(lData, size);

    //Handle Data
    for(int i = 0;i < size; i ++){
        std::cout<<*(lData + i);
    }

    //Free Resources
    file.close();


    return success;
}