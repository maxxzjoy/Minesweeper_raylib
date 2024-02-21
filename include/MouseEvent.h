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

    Vector2 LTcorner, RBcorner;
    Vector2 TmpPos;

    Tile GameTable[COL][ROW];

    bool ClosedtoClick(GridPos c);
    void PlaceMines(int minecount);
    void Reveal8Tile(GridPos cor);
    void AddOne2Tiles(short x, short y);
    bool ClickedInside(Vector2 click, Vector2 LT, int width, int hieght);
    bool insideRange(int a, int b);

public:
    // Initialization
    Minesweeper(Vector2 LT) {
        clicked_cordi = {0};
        first_left_click = true;
        Inside = false;
        LTcorner = LT;
        TmpPos = {0};
        RBcorner.x = LTcorner.x + COL * TILE_SIZE;
        RBcorner.y = LTcorner.y + ROW * TILE_SIZE;
    };

    void InitGame(void);
    bool MouseEvent(void);

    GridPos GetClickedCordi(void);
    bool GetInsideTable(void);
    bool GetFirstClick(void);
    bool GetTileRevealState(int x, int y);
    bool GetTileMineState(int x, int y);
    bool GetTileFlagState(int x, int y);
    int GetTileMineCount(int x, int y);
};

#endif