

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <sys/types.h>
struct Tile{
    enum State{unknown,cleared,flagged};
    State state;
    uint nearMines = 1;
    bool isMine = false;

    Tile(State s, uint m): state(s), nearMines(m){}
    Tile(bool is): isMine(is){}
    Tile(){}


};


class Minefield{
  private:
      const int sizeX;
      const int sizeY;
      Tile* field;
  public:
      Minefield(int size): Minefield(size,size) {}
      Minefield(int X, int Y):  sizeX(X), sizeY(Y) {
          field = new Tile[sizeX*sizeY];

          for(int i=0;i<sizeX*sizeY; i++){
              field[i] = Tile(Tile::unknown, 10);
          }
      }
      ~Minefield(){
          delete [] field;
      }

      Tile& at(int X, int Y){

          //error checking
          if(X>sizeX || Y>sizeY){
              throw std::range_error("out of bounds read attempt");
          }
          if(X<0 || Y<0){
              throw std::range_error("out of bounds: negative read");
          }

          return field[X*Y];

      }

};
