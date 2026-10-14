#pragma once

// Defines the small textured button abstraction used by each Minesweeper tile.

#include "raylib.h"
#include <functional>
#include <utility>


/// A rectangular, textured control with independent left- and right-click actions.
///
/// Calling update() once per frame both renders the control and dispatches mouse
/// releases that occur while the cursor is inside its bounds.
class GUIbutton{
    private:
        // Actions are kept private so callers cannot invoke them without input handling.
        std::function<void()> onLeft;
        std::function<void()> onRight;


    public:
        // Screen-space bounds and rendering properties can be adjusted by the owner.
        Vector2 position;
        Vector2 size;
        Texture2D tex{};
        Color tint = WHITE;

        /// Creates a button with its geometry, texture, and mouse-release actions.
        GUIbutton(Vector2 p, Vector2 s, Texture2D texture, std::function<void()> left, std::function<void()> right)
            : onLeft(std::move(left)),
              onRight(std::move(right)),
              position(p),
              size(s),
              tex(texture)
        {}


        /// Draws the button and handles mouse releases for the current frame.
        void update() {
            // DrawTexturePro scales the complete texture into the button's bounds.
            const Rectangle source{
                0.0f,
                0.0f,
                static_cast<float>(tex.width),
                static_cast<float>(tex.height)
            };
            const Rectangle destination{position.x, position.y, size.x, size.y};
            DrawTexturePro(tex, source, destination, Vector2{0.0f, 0.0f}, 0.0f, tint);

            // Input outside the control must not trigger either callback.
            if (!isWithin(GetMousePosition())) {
                return;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                onLeft();
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
                onRight();
            }
        }

        /// Returns whether a screen-space point lies within the inclusive bounds.
        bool isWithin(Vector2 in) const {
            if(position.x<=in.x && in.x<=position.x+size.x){
                if(position.y<=in.y && in.y<=position.y+size.y){
                    return true;
                }
            }

            return false;
        }

};
