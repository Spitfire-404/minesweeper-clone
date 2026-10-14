#pragma once

#include "raylib.h"
#include <functional>
#include <utility>


// current implementation: draws a black box and constantly checks for clicks and fires the according function : onLeft or onRight
class GUIbutton{
    private:
        std::function<void()> onLeft;
        std::function<void()> onRight;


    public:
        Vector2 position;
        Vector2 size;
        Texture2D tex{};
        Color tint = WHITE;

        GUIbutton(Vector2 p, Vector2 s, Texture2D texture, std::function<void()> left, std::function<void()> right)
            : onLeft(std::move(left)),
              onRight(std::move(right)),
              position(p),
              size(s),
              tex(texture)
        {}


        void update() {
            const Rectangle source{
                0.0f,
                0.0f,
                static_cast<float>(tex.width),
                static_cast<float>(tex.height)
            };
            const Rectangle destination{position.x, position.y, size.x, size.y};
            DrawTexturePro(tex, source, destination, Vector2{0.0f, 0.0f}, 0.0f, tint);

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

        bool isWithin(Vector2 in) const {
            if(position.x<=in.x && in.x<=position.x+size.x){
                if(position.y<=in.y && in.y<=position.y+size.y){
                    return true;
                }
            }

            return false;
        }

};
