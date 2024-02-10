#include "raylib.h"
#include "iostream"

#define TILE_SIZE 23
#define WIDTH 800
#define HEIGHT 450

class Mouse_ev
{
private:
    
public:
    Vector2 Pos = {0};
    bool Clicked = false;
};



void DrawGrid(void);
void MouseEvent(void);
