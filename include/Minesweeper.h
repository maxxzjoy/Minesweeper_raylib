#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "MineSSetting.h"
#include "Entity.h"
#include "raylib.h"
#include <time.h>
#include <cstdlib>


class Minesweeper
{
private:
    // Clicked tile position
    GridPos clicked_cordi;

    // Checking first time click on tile
    bool first_left_click;

    // Check mouse click inside the tiles
    bool Inside;

    bool game_end;

    Vector2 LTcorner, RBcorner;
    Vector2 TmpPos;

    Tile GameTable[COL][ROW];

    void LeftMouseEvent(void);
    void RightMouseEvent(void);
    void PlaceMines(int minecount);
    void Reveal8Tile(GridPos cor);
    void AddOne2Tiles(short x, short y);
    bool ClickedInside(Vector2 click, Vector2 LT, int width, int hieght);
    bool InsideRange(int a, int b);
    bool ClosedtoClick(GridPos c);
    bool CompareFlagcounts(GridPos c);
    
public:
    // Initialization
    Minesweeper(Vector2 LT) {
        clicked_cordi = {0};
        first_left_click = true;
        Inside = false;
        game_end = false;
        LTcorner = LT;
        TmpPos = {0};
        RBcorner.x = LTcorner.x + COL * TILE_SIZE;
        RBcorner.y = LTcorner.y + ROW * TILE_SIZE;
    };

    // Main functions
    void InitGame(void);
    void MouseEvent(void);

    /*-------------------------*/
    /*     Info functions      */
    /*-------------------------*/
    
    GridPos GetClickedCordi(void);              // Get the last clicked cordinate on tile
    bool GetEndGameFlag(void);                  // Get ...
    bool GetTileRevealState(int x, int y);      // Get (x, y) tile (bool) reveal state
    bool GetTileMineState(int x, int y);        // Get (x, y) tile (bool) isMine state
    bool GetTileFlagState(int x, int y);        // Get (x, y) tile (bool) flag state
    int GetTileMineCount(int x, int y);         // Get (x, y) tile (int) minecount state
};

#endif