#pragma once

#include "raylib.h"
#include <functional>
#include <thread>


// current implementation: draws a black box and constantly checks for clicks and fires the according function : onLeft or onRight
class GUIbutton{
    private:
        std::function<void()> onLeft;
        std::function<void()> onRight;


    public:
        Vector2 position;
        Vector2 size;
        Color color = BLACK;

        GUIbutton(Vector2 p, Vector2 s, std::function<void()> L, std::function<void()> R): position(p), size(s){
            onLeft = L;
            onRight = R;

        }


        void update() {
            DrawRectangleV(position, size, color);


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

        bool isWithin(Vector2 in){
            if(position.x<=in.x && in.x<=position.x+size.x){
                if(position.y<=in.y && in.y<=position.y+size.y){
                    return true;
                }
            }

            return false;
        }

};
