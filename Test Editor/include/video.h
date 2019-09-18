#ifndef GAMEVIDEO_H
#define GAMEVIDEO_H

    #include "SDL.h"
    #include "SDL_image.h"
    #include "SDL_ttf.h"

    #include "geometry.h"

    #include <string>
    using std::string;

    namespace Video{

        SDL_Texture* GetTexture(string fname);
        SDL_Texture* GetText(string fname, string text, SDL_Renderer* rend = NULL);

        class Texture{
            public:
                SDL_Texture* Image = NULL;
                Area Size;
                string Name;

                Texture(string font, string text, Vector2 Dim, SDL_Renderer* rend = NULL) : Image(GetText(font, text, rend)), Size{Dim.X, Dim.Y}, Name{font} {}

                Texture(string fname, Vector2 Dim) : Image(GetTexture(fname)), Size{Dim.X,Dim.Y}, Name{fname} {}

                ~Texture();
        };

        bool Init(string Name, int Window_Width, int Window_Height);

        void DrawScreen(Texture& text, const float& X, const float& Y, const int& celX, const int& celY, SDL_Renderer* rend = NULL);

        void DrawRect(const int& x, const int& y, const int& w, const int& h);
        void DrawRect(Area ar);

        void SetDrawColor(const int& r, const int& g, const int& b, const int& a);

        void ClearScreen();
        void UpdateScreen();

        void GetControls(int* Controls);
        string GetTextInput(const string& Name, const int& Width, const int& Height);

        void FrameCap(int LastUpdate);
        void SetFPS(int _FPS);

        void Quit();

        enum Controls{
            sysExit,
            keyLeft,
            keyRight,
            keyUp,
            keyDown,
            mouseX,
            mouseY,
            mouseLDown,
            mouseLUp,
            mouseLHeld,
            mouseRDown,
            mouseRUp,
            mouseRHeld,
            key1,
            key2,
            NUM_OF_KEYS
        };

    }

#endif