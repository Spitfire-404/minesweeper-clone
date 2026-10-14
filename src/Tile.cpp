#include "Tile.h"

Texture2D Tile::textures[12]{};

void Tile::loadTextures()
{
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

    for (int i = 0; i < 12; ++i) {
        textures[i] = LoadTexture(paths[i]);
    }
}

void Tile::unloadTextures()
{
    for (Texture2D& texture : textures) {
        if (texture.id != 0) {
            UnloadTexture(texture);
            texture = Texture2D{};
        }
    }
}
