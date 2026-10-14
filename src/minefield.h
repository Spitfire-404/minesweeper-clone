#pragma once


#include "Tile.h"
#include "raylib.h"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>

class Minefield{
  private:
      const int margin = 100;
      const int spacing = 2;
      const int sizeX;
      const int sizeY;

      // this is a [sizeX][sizeY] matrix
      Tile* field;
  public:

      Minefield(const Minefield&) = delete;
      Minefield& operator=(const Minefield&) = delete;

      Minefield(int size): Minefield(size,size) {}
      Minefield(int X, int Y)
          : sizeX(X),
            sizeY(Y),
            field(new Tile[static_cast<std::size_t>(X) * Y]) {

          for(int i=0;i<sizeX*sizeY; i++){
              field[i].isMine = GetRandomValue(0, 1);
              field[i].id = i;
              field[i].button.size = (((float)(GetScreenWidth()>GetScreenHeight()? GetScreenHeight(): GetScreenWidth())-margin)/sizeX);
              field[i].button.size -= spacing;
          }

          for(int y=0; y<sizeY;y++){
              for(int x=0; x<sizeX;x++){
                  Tile& current = at(x,y);
                  //std::cout << current.id << "\n";
                  current.button.position.x = (current.button.size.x*x)+(x*spacing)+ GetScreenWidth()/2.0f- (current.button.size.x*sizeX+(spacing*sizeX))/2;
                  current.button.position.y = (current.button.size.y*y)+(y*spacing)+ GetScreenHeight()/2.0f-(current.button.size.y*sizeY+(spacing*sizeY))/2;


                  int i=0;
                  for(int sy=y-1;sy<=y+1;sy++){
                      for(int sx=x-1;sx<=x+1;sx++){
                          try {
                              if (at(sx, sy).isMine) {
                                  i++;
                              }

                          } catch (std::range_error e) {

                              //ignore error because it is expected on edges and corners
                          }
                      }
                  }
                  current.nearMines = i;



                  current.click();

              }
          }
      }
      ~Minefield(){
          delete [] field;
      }

      Tile& at(int X, int Y){

          //error checking
          if(X>sizeX-1 || Y>sizeY-1){
              throw std::range_error("out of bounds read attempt: "+std::to_string(X)+','+std::to_string(Y));
          }
          if(X<0 || Y<0){
              throw std::range_error("out of bounds: negative read");
          }

          return field[(Y*sizeX) + X];

      }

      void updateAll(){
          for(int y=0; y<sizeY;y++){
              for(int x=0; x<sizeX;x++){
                  at(x, y).button.update();
              }
          }
      }
};
