#include "Tile.h"
#include "minefield.h"



void Tile::click()
{
    if(hasBeenClicked){
        return;
    }

    hasBeenClicked = true;
    changeState(cleared);

    if (isMine) {
        button.tex = textures[11];

        if (parent != nullptr) {
            static_cast<Minefield*>(parent)->gameOver();
        }
    } else {
        button.tex = textures[nearMines];
        if(nearMines == 0){
            static_cast<Minefield*>(parent)->clickNeighbors(this->id);
        }
    }

}


// Shared by every tile so the image resources are loaded only once.
Texture2D Tile::textures[12]{};

void Tile::loadTextures()
{
    // This order is part of the Tile rendering contract: indices 0-9 are the
    // blank/number faces, index 10 is the flag, and index 11 is the mine.
    static const char* paths[12] = {
        "src/images/Tile-blank.png",
        "src/images/Tile-1.png",
        "src/images/Tile-2.png",
        "src/images/Tile-3.png",
        "src/images/Tile-4.png",
        "src/images/Tile-5.png",
        "src/images/Tile-6.png",
        "src/images/Tile-7.png",
        "src/images/Tile-8.png",
        "src/images/Tile-9.png",
        "src/images/Tile-flag.png",
        "src/images/Tile-mine.png"
    };

    // A raylib window must exist before these GPU-backed textures are loaded.
    for (int i = 0; i < 12; ++i) {
        textures[i] = LoadTexture(paths[i]);
    }
}

void Tile::unloadTextures()
{
    // Reset each handle after releasing it, making repeated cleanup harmless.
    for (Texture2D& texture : textures) {
        if (texture.id != 0) {
            UnloadTexture(texture);
            texture = Texture2D{};
        }
    }
}
