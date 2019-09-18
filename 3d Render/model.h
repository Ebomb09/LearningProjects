#ifndef 3D_DATA
#define 3D_DATA

    struct Vector2{
        float X;
        float Y;
    }

    struct Vector3{
        float X;
        float Y;
        float Z;
    };

    struct Vertex{
        Vector2 Position;
    };

    struct Face{
        Vertex Points[3];
    };

#endif