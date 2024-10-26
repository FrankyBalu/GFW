#include <Log.hpp>
#include "raylib.h"


const unsigned short FPS = 60;
const unsigned short WINDOWWIDTH = 800;
const unsigned short WINDOWHEIGHT = 600;
const Color BACKGROUNDCOLOR = WHITE;

int main() {

    INFO_LOG("TestApp für GFW");
    INFO_LOG("Hier werde ich die einzelnen Funktionen von GFW Testen und versuchen zu erklären");

    //Damit Raylib nicht so gesprächig ist
    SetTraceLogLevel(4);


    //Fenster erstellen ... muss in eine extra Klasse
    InitWindow(WINDOWWIDTH, WINDOWHEIGHT, "GFW Test");
    SetTargetFPS(FPS);

    Texture2D LOGO = LoadTexture("data/logo.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUNDCOLOR);

        DrawTexture(LOGO,208,108, BACKGROUNDCOLOR );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
