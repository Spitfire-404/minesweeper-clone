#pragma once

// Declares the state and visual behavior of one cell in the minefield.

#include "GUIbutton.h"
#include "raylib.h"

/// A single Minesweeper cell and the GUI control used to display it.
struct Tile{
    // All tiles share the same texture set; see Tile.cpp for the index layout.
    static Texture2D textures[12];

    /// Loads the shared tile textures. Call only after raylib initializes a window.
    static void loadTextures();

    /// Releases all shared textures before the raylib window is closed.
    static void unloadTextures();

    /// Logical visibility/marking state of the cell.
    enum State{
        unknown, ///< Covered and available for interaction.
        cleared, ///< Revealed by a left click.
        flagged  ///< Marked as a suspected mine by a right click.
    };

    State state;
    GUIbutton button;
    int nearMines = 0; ///< Number of mines in the surrounding 3x3 region.
    bool isMine = false;
    bool hasBeenClicked = false;
    int id;            ///< Row-major index assigned by Minefield.
<<<<<<< HEAD
    void* parent = nullptr;/// this needs to be a void pointer annoyingly
=======
    void* parent = nullptr;
>>>>>>> 3e4c7b7cb328de7559666475e2279016789ad876

    /// Reveals the cell and selects either its mine or adjacent-count texture.
    void click();
    void clear(){
        changeState(cleared);

        button.tex = textures[nearMines];
    }

    /// Marks the cell with the flag texture.
    void flag(){
        if (state == flagged){
            if(hasBeenClicked){
                clear();
            }else{

                changeState(unknown);
            }
        }
        else
        changeState(flagged);
    }

    /// Creates a cell and wires its mouse callbacks to this tile's actions.
    Tile(bool mine = false)
        : button(
              Vector2{0, 0},
              Vector2{20, 20},
              textures[0],
              [this]{click();},
              [this]{flag();}
          ),
          isMine(mine)
    {
        // Begin covered regardless of whether the tile contains a mine.
        this->changeState(unknown);
    }


    /// Updates the logical state and its corresponding covered/flagged visual.
    void changeState(State in){
        state =in;
        // State-specific tinting below starts from the normal texture color.
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
