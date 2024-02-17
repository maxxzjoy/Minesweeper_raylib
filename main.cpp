/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/


#include "header.h"

// Global variables
static Vector2 LTcorner = {0}, RBcorner = {0};
Mouse_ev MousePos;
Tile GameTable[COL][ROW];

// Main entry point
int main()
{
    // Calculating cordinates on the window
    LTcorner.x = EDGEOFFSET;
    LTcorner.y = EDGEOFFSET + MENUHIEGHT;
    RBcorner.x = LTcorner.x + COL * TILE_SIZE;
    RBcorner.y = LTcorner.y + ROW * TILE_SIZE;

    for(short i = 0; i < COL; i++ ){
        for(short j = 0; j < ROW; j++ ){
            GameTable[i][j].cordi = (GridPos){.x = i, .y = j};
        }
    }

    // Initialization
    InitWindow(RBcorner.x + EDGEOFFSET, RBcorner.y + EDGEOFFSET, "Minesweeper");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawBoard();

            MouseEvent();

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();                  // Close window and OpenGL context

    return 0;
}

void DrawBoard(void){

    // For checking the clicked tile position
    DrawText( TextFormat("(%d, %d)", MousePos.clicked_cordi.x, MousePos.clicked_cordi.y), 30, 5, 20, BLACK);

    // Draw Board outline
    DrawRectangleLines(LTcorner.x-1, LTcorner.y-1, (RBcorner.x-LTcorner.x+2), (RBcorner.y-LTcorner.y+2), BLACK);
    
    // Draw Board inside
    for(int i = 0; i < COL; i++ ){
        for(int j = 0; j < ROW; j++ ){
            DrawRectangleLines(TILE_SIZE*i + LTcorner.x, TILE_SIZE*j + LTcorner.y, TILE_SIZE, TILE_SIZE, BLACK);
            if(GameTable[i][j].revealed)
                DrawRectangle(TILE_SIZE*i + LTcorner.x + 1, TILE_SIZE*j + LTcorner.y + 1, TILE_SIZE-2, TILE_SIZE-2, VIOLET);
        }
    }

    // Showing the last clicked tile
    if(MousePos.Inside){
        DrawRectangle( (MousePos.clicked_cordi.x * TILE_SIZE + LTcorner.x + 1),
        (MousePos.clicked_cordi.y * TILE_SIZE + LTcorner.y + 1),
        TILE_SIZE - 2, TILE_SIZE - 2, BLUE);
    }
}

void MouseEvent(void){

    // Check "Left" Mouse click event
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        Vector2 TmpPos = {0};
        TmpPos = GetMousePosition();

        // Check if click on tile
        if( TmpPos.x >= RBcorner.x || TmpPos.x <= LTcorner.x ||
        TmpPos.y >= RBcorner.y || TmpPos.y <= LTcorner.y){
            MousePos.clicked_cordi = {0};
            MousePos.Inside = false;
        }
        else{
            MousePos.clicked_cordi.x = (short)( (TmpPos.x - LTcorner.x) / TILE_SIZE);
            MousePos.clicked_cordi.y = (short)( (TmpPos.y - LTcorner.y) / TILE_SIZE);
            MousePos.Inside = true;
            GameTable[MousePos.clicked_cordi.x][MousePos.clicked_cordi.y].revealed = true;
        }
    }
}

void PlaceMines(){

}