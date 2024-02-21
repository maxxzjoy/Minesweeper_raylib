#include "raylib.h"
#include "iostream"

#include "MineSSetting.h"
#include "Entity.h"
#include "Minesweeper.h"




void DrawBoard(void);
void MouseEvent(void);
void PlaceMines(int minecount);
void Reveal8Tile(GridPos cor);
void InitGame(void);