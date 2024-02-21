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
static Vector2 LTcorner = {EDGEOFFSET, EDGEOFFSET + MENUHIEGHT}, RBcorner = {0};

Minesweeper MineSweeperGame(LTcorner);


// Main entry point
int main()
{
    

    // Calculating cordinates on the window
    RBcorner.x = LTcorner.x + COL * TILE_SIZE;
    RBcorner.y = LTcorner.y + ROW * TILE_SIZE;

    // Initialization
    InitWindow(RBcorner.x + EDGEOFFSET, RBcorner.y + EDGEOFFSET, "Minesweeper");
    
    MineSweeperGame.InitGame();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        MineSweeperGame.MouseEvent();

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawBoard();
    
        EndDrawing(); 
    }

    // De-Initialization
    CloseWindow();                  // Close window and OpenGL context

    return 0;
}

void DrawBoard(void){
    GridPos i = MineSweeperGame.GetClickedCordi();

    // For checking the clicked tile position
    DrawText( TextFormat("(%d, %d)", i.x, i.y), 30, 5, 20, BLACK);

    // Draw Board outline
    DrawRectangleLines(LTcorner.x-1, LTcorner.y-1, (RBcorner.x-LTcorner.x+2), (RBcorner.y-LTcorner.y+2), BLACK);

    // Draw Board inside
    for(int i = 0; i < COL; i++ ){
        for(int j = 0; j < ROW; j++ ){
            DrawRectangleLines(TILE_SIZE*i + LTcorner.x, TILE_SIZE*j + LTcorner.y, TILE_SIZE, TILE_SIZE, BLACK);
            if(MineSweeperGame.GetTileRevealState(i,j)){
                DrawRectangle(TILE_SIZE*i + LTcorner.x + 1, TILE_SIZE*j + LTcorner.y + 1, TILE_SIZE-2, TILE_SIZE-2, (!MineSweeperGame.GetTileMineState(i, j))?VIOLET:RED);
                if(!MineSweeperGame.GetTileMineState(i, j))
                    DrawText( TextFormat("%d", MineSweeperGame.GetTileMineCount(i, j)), TILE_SIZE*(i+0.3) + LTcorner.x, TILE_SIZE*(j+0.3) + LTcorner.y, 18, BLACK);
            }
            if(MineSweeperGame.GetTileFlagState(i, j)){
                DrawRectangle(TILE_SIZE*i + LTcorner.x + 1, TILE_SIZE*j + LTcorner.y + 1, TILE_SIZE-2, TILE_SIZE-2, DARKGREEN);
            }
                
        }
    }

}

