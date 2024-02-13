#include "raylib.h"
#include "iostream"

using namespace std;

#define TILE_SIZE 23
#define WIDTH 800
#define HEIGHT 450

class Mouse_ev
{
private:
    
public:
    // Real mouse click position
    Vector2 Pos;
    // Clicked tile position
    Vector2 Clicked_GridPos;
    // Check mouse click inside the tiles
    bool Inside;

    // Initialization
    Mouse_ev() {
        Pos = {0};
        Clicked_GridPos = {0};
        Inside = false;
    };
};



void DrawGrid(void);
void MouseEvent(void);
