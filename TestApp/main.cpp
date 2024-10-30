#include <Log.hpp>
#include <Settings.hpp>
#include "raylib.h"

#include <iostream>

const Color BACKGROUNDCOLOR = WHITE;

int main() {

    INFO_LOG("TestApp für GFW");
    INFO_LOG("Hier werde ich die einzelnen Funktionen von GFW Testen und versuchen zu erklären");

    //Damit Raylib nicht so gesprächig ist
#ifdef DEBUG
    SetTraceLogLevel(4);
    GFW::Log::Instance()->SetLogLevel(GFW::LogLevel::LOG_TRACE);
#else
    SetTraceLogLevel(4);
    GFW::Log::Instance()->SetLogLevel(GFW::LogLevel::LOG_WARNING);
#endif

    GFW::Settings::Instance()->Load("data/settings.lua");
    GFW::Settings::Instance()->Save("data/settings_new.lua");
    //GFW::Log::Instance()->SetLogLevel(GFW::Settings::Instance()->LogLevel());

    GFW::Settings::Instance()->MusicVolume(3.0);
    GFW::Settings::Instance()->EffectVolume(0.25);

    //Fenster erstellen ... muss in eine extra Klasse
    InitWindow(GFW::Settings::Instance()->WindowWidth(), GFW::Settings::Instance()->WindowHeight(), "GFW Test");
    SetTargetFPS(GFW::Settings::Instance()->FPS());
    SetExitKey(GFW::Settings::Instance()->ExitKey());

    Texture2D LOGO = LoadTexture("data/logo.png");

    int texX = (GFW::Settings::Instance()->WindowWidth() - LOGO.width) / 2;
    int texY = (GFW::Settings::Instance()->WindowHeight() - LOGO.height) / 2;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUNDCOLOR);

        DrawTexture(LOGO,texX,texY, BACKGROUNDCOLOR );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
