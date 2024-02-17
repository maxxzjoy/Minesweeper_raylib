#include "raylib.h"
#include "iostream"

using namespace std;

#define TILE_SIZE 28
#define COL 15
#define ROW 8
#define EDGEOFFSET 8
#define MENUHIEGHT 30
#define TABLEMAX 99


struct GridPos{
    short x, y;
};

struct Tile{
    GridPos cordi;
    bool revealed = false;
    bool isMine = false;
};

class Mouse_ev
{
private:
    
public:
    // Clicked tile position
    GridPos clicked_cordi;
    // Check mouse click inside the tiles
    bool Inside;

    // Initialization
    Mouse_ev() {
        clicked_cordi = {0};
        Inside = false;
    };
};

class Board
{
private:
    static Tile Mine_Table[TABLEMAX][TABLEMAX];
public:
    void GenerateMine(int seed);
};

void Board::GenerateMine(int seed){

}

void DrawBoard(void);
void MouseEvent(void);
