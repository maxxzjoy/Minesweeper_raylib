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
static Vector2 offset = {0};
Mouse_ev MousePos;

// Main entry point
int main()
{
    // Initialization
    offset.x = WIDTH%TILE_SIZE;
    offset.y = HEIGHT%TILE_SIZE;

    InitWindow(WIDTH, HEIGHT, "Minesweeper");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawGrid();

            MouseEvent();

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();                  // Close window and OpenGL context

    return 0;
}

void DrawGrid(void){

    // Vertical lines
    for(int i = 0; i <= WIDTH/TILE_SIZE; i++ )
        DrawLineV( (Vector2){TILE_SIZE*i + offset.x/2, offset.y/2}, (Vector2){TILE_SIZE*i + offset.x/2, HEIGHT - offset.y/2}, BLACK );

    // Horizontal lines
    for(int i = 0; i <= HEIGHT/TILE_SIZE; i++ )
        DrawLineV( (Vector2){offset.x/2, TILE_SIZE*i + offset.y/2}, (Vector2){WIDTH - offset.x/2, TILE_SIZE*i + offset.y/2}, BLACK );

}

void MouseEvent(void){

    // Check "Left" Mouse click event
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        Vector2 TmpPos = {0};
        TmpPos = GetMousePosition();
        if( TmpPos.x >= (WIDTH - offset.x/2) || TmpPos.x <= (offset.x/2) ||
        TmpPos.y >= (HEIGHT - offset.y/2) || TmpPos.y <= (offset.y/2)){
            MousePos.Clicked = false;
        }
        else{
            MousePos.Pos.x = TmpPos.x - offset.x/2;
            MousePos.Pos.y = TmpPos.y - offset.y/2;
            MousePos.Clicked = true;
        }
    }

    if(MousePos.Clicked){
        DrawRectangle( ((int)MousePos.Pos.x - (int)MousePos.Pos.x % TILE_SIZE + offset.x/2),
        ((int)MousePos.Pos.y - (int)MousePos.Pos.y % TILE_SIZE + offset.y/2 + 1),
        TILE_SIZE - 1, TILE_SIZE - 1, BLUE);
    }

}