#pragma once

// Owns, lays out, and updates the rectangular collection of game tiles.

#include "Tile.h"
#include "raylib.h"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>

/// Owns a row-major grid of tiles and positions it in the application window.
///
/// Construction relies on an initialized raylib window because the dimensions
/// returned by GetScreenWidth() and GetScreenHeight() determine tile geometry.
class Minefield{
  private:
      const int margin = 20; ///< Minimum space reserved around the board.
      const int spacing = 2;  ///< Gap in pixels between neighboring tiles.
      const int sizeX;
      const int sizeY;

      // Contiguous row-major storage: element (x, y) is at y * sizeX + x.
      Tile* field;
  public:

      // The class uniquely owns field, and each Tile callback captures its address.
      Minefield(const Minefield&) = delete;
      Minefield& operator=(const Minefield&) = delete;

      /// Constructs a square board.
      Minefield(int size): Minefield(size,size) {}

      /// Constructs a board with X columns and Y rows.
      Minefield(int X, int Y)
          : sizeX(X),
            sizeY(Y),
            field(new Tile[static_cast<std::size_t>(X) * Y]) {

          // Initialize cell contents and choose a square tile size that fits the
          // board along the window's shorter axis while preserving the margin.
          for(int i=0;i<sizeX*sizeY; i++){
              field[i].isMine = GetRandomValue(0, 1);
              field[i].id = i;

              // scale based off of the smallest dimention
              const float availableWidth = static_cast<float>(GetScreenWidth() - margin);
              const float availableHeight = static_cast<float>(GetScreenHeight() - margin);
              field[i].button.size = (availableWidth / sizeX < availableHeight / sizeY)
                                           ? availableWidth / sizeX
                                           : availableHeight / sizeY;


              field[i].button.size -= spacing;
          }

          // Convert each row/column coordinate into a centered screen position.
          for(int y=0; y<sizeY;y++){
              for(int x=0; x<sizeX;x++){
                  Tile& current = at(x,y);
                  current.button.position.x = (current.button.size.x*x)+(x*spacing)+ GetScreenWidth()/2.0f- (current.button.size.x*sizeX+(spacing*sizeX))/2;
                  current.button.position.y = (current.button.size.y*y)+(y*spacing)+ GetScreenHeight()/2.0f-(current.button.size.y*sizeY+(spacing*sizeY))/2;


                  // Inspect the surrounding 3x3 region. Out-of-range positions
                  // are expected at board edges and are ignored below.
                  int i=0;
                  for(int sy=y-1;sy<=y+1;sy++){
                      for(int sx=x-1;sx<=x+1;sx++){
                          try {
                              if (at(sx, sy).isMine) {
                                  i++;
                              }

                          } catch (std::range_error e) {
                              // Edges and corners have neighbors outside the board.
                          }
                      }
                  }
                  current.nearMines = i;
              }
          }
      }

      /// Releases the contiguous tile array owned by this board.
      ~Minefield(){
          delete [] field;
      }

      /// Returns the tile at (X, Y), throwing when the coordinate is invalid.
      Tile& at(int X, int Y){

          // Validate before calculating the row-major offset.
          if(X>sizeX-1 || Y>sizeY-1){
              throw std::range_error("out of bounds read attempt: "+std::to_string(X)+','+std::to_string(Y));
          }
          if(X<0 || Y<0){
              throw std::range_error("out of bounds: negative read");
          }

          return field[(Y*sizeX) + X];

      }

      /// Draws every tile and processes its input for the current frame.
      void updateAll(){
          for(int y=0; y<sizeY;y++){
              for(int x=0; x<sizeX;x++){
                  at(x, y).button.update();
              }
          }
      }
};
