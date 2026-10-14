#pragma once


#include "GUIbutton.h"
#include "raylib.h"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
struct Tile{
    enum State{unknown,cleared,flagged};
    State state = unknown;
    GUIbutton button;
    uint nearMines = 0;
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
              [this] { click(); },
              [this] { flag();  }
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
      Minefield(int X, int Y):  sizeX(X), sizeY(Y) {
          field = new Tile[sizeX*sizeY];

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
                  current.button.position.x = (current.button.size.x*x)+(x*spacing)+ GetScreenWidth()/2- (current.button.size.x*sizeX+(spacing*sizeX))/2;
                  current.button.position.y = (current.button.size.y*y)+(y*spacing)+ GetScreenHeight()/2-(current.button.size.y*sizeY+(spacing*sizeY))/2;
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
