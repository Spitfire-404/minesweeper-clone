#pragma once

#include "GUIbutton.h"
#include "raylib.h"

struct Tile{
    static Texture2D textures[12];

    static void loadTextures();
    static void unloadTextures();
    enum State{unknown,cleared,flagged};
    State state;
    GUIbutton button;
    int nearMines = 0;
    bool isMine = false;
    int id;

    void click(){
        changeState(cleared);

        if(isMine){
            button.tex = textures[11];
            //button.tint = RED;

        }
        else
        {
            button.tex = textures[nearMines];

        }

    }
    void flag(){
        changeState(flagged);
    }

    Tile(bool mine = false)
        : button(
              Vector2{0, 0},
              Vector2{20, 20},
              textures[0],
              [this]{click();},
              [this]{flag();}
          ),
          isMine(mine)
    {this->changeState(unknown);}


    void changeState(State in){
        state =in;
        button.tint = WHITE;
        switch (state) {
            case cleared:
                this->button.tex = textures[0];
                break;
            case unknown:
                this->button.tex = textures[0];
                this->button.tint = GRAY;
                break;
            case flagged:
                this->button.tex = textures[10];

        }
    }


};
