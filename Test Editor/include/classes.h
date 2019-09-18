#ifndef GAMEDATA_H
#define GAMEDATA_H

    #include "video.h"
    using namespace Video;

    #include <vector>
    using std::vector;

    #include <string>
    using std::string;

    class Object{
        public:
            bool Active = true;

            int Width = 1;
            int Height = 1;

            Vector2 Position;

            Texture Sprite;

            Object(string fname, const int& w, const int& h) : Sprite(Texture( fname, Vector2 {w,h}) ) {}

            void Draw();
            virtual void Step() {};

            void SetDimensions(int w, int h);
            bool ContainsObject(Object& _Obj);
            bool IntersectsObject(Object& _Obj);
    };

    class Player : public Object{
        public:
            Player() : Object("/Data/Images/Mario.png", 16, 16 ) {}
        
            void HandleInput(int Controls[]);
    };

    class ForeGround : public Object{
        public:

            ForeGround(string fname, const int& w, const int& h, int _w, int _h) : Object(fname,w,h) {
                SetDimensions(_w,_h);
            }
            
    };

    class BackGround : public Object{
        public:

            BackGround(string fname, const int& w, const int& h, int _w, int _h) : Object(fname,w,h) {
                SetDimensions(_w,_h);
            }

    };

    class Button : public Object{
        //string Name;

    };

#endif