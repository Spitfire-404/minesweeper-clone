#pragma once

#include "GUIbutton.h"
#include "raylib.h"

struct Tile{
    public:
    enum State{unknown,cleared,flagged};
    State state = unknown;
    GUIbutton button;
    int nearMines = 0;
    bool isMine = false;
    int id;

    void click(){
        changeState(cleared);

        if(isMine)
            button.color = RED;
        else
            button.color = GREEN;
    }
    void flag(){
        changeState(flagged);
    }

    Tile(bool mine = false)
        : button(
              Vector2{0, 0},
              Vector2{20, 20},
              [this](int in) { changeState((State)in); }
          ),
          isMine(mine)
    {}


    void changeState(State in){
        state =in;
        switch (state) {
            case cleared:
                this->button.color = GREEN;
                break;
            case unknown:
                this->button.color = GRAY;
                break;
            case flagged:
                this->button.color = BLUE;

        }
    }

};
