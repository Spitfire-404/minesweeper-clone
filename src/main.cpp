#include "raylib.h"
#include "minefield.h"
#include <cmath>
#include <vector>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib template window");
    Minefield mainField(10);


    SetTargetFPS(60);

    // Main game loop

    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();


        ClearBackground(RAYWHITE);

        EndDrawing();
    }


    CloseWindow();
    return 0;
}
