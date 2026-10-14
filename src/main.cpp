#include "raylib.h"
#include "minefield.h"


int main() {

    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib template window");
    Tile::loadTextures();

    SetTargetFPS(60);

    {
        Minefield mainField(10);

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            mainField.updateAll();

            EndDrawing();
        }
    }

    Tile::unloadTextures();
    CloseWindow();
    return 0;
}
