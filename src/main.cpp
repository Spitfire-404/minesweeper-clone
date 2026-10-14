// Application entry point and raylib resource-lifecycle coordination.

#include "raylib.h"
#include "minefield.h"


int main() {

    // Create the graphics context before loading textures or constructing the board.
    const int screenWidth = 1400;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib template window");
    Tile::loadTextures();

    // Limit the draw/input loop to a stable, CPU-friendly update rate.
    SetTargetFPS(60);

    {
        // Keep the board in a nested scope so its tiles are destroyed before
        // their shared textures and the graphics context are released.
        Minefield mainField(40,20,25);

        // raylib reports true when the user closes the window or presses Escape.
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(Color{0, 74, 100});// nice blue I like

            // Each tile is drawn and handles any mouse release from this frame.
            mainField.updateAll();

            EndDrawing();
        }
    }

    // GPU resources must be unloaded while the raylib context is still valid.
    Tile::unloadTextures();
    CloseWindow();
    return 0;
}
