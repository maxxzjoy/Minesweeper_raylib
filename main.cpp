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
static Vector2 offset = {0}, LTcorner = {0}, RBcorner = {0};
Mouse_ev MousePos;

// Main entry point
int main()
{
    // Calculating cordinates on the window
    offset.x = WIDTH%TILE_SIZE;
    offset.y = (HEIGHT - MENUHIEGHT)%TILE_SIZE;
    LTcorner.x = offset.x/2;
    LTcorner.y = offset.y/2 + MENUHIEGHT;
    RBcorner.x = WIDTH - LTcorner.x;
    RBcorner.y = HEIGHT - offset.y/2;

    // Initialization
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
        DrawLineV( (Vector2){TILE_SIZE*i + LTcorner.x, LTcorner.y}, (Vector2){TILE_SIZE*i + LTcorner.x, RBcorner.y}, BLACK );

    // Horizontal lines
    for(int i = 0; i <= (HEIGHT-MENUHIEGHT)/TILE_SIZE; i++ )
        DrawLineV( (Vector2){LTcorner.x, TILE_SIZE*i + LTcorner.y}, (Vector2){RBcorner.x, TILE_SIZE*i + LTcorner.y}, BLACK );

}

void MouseEvent(void){

    // Check "Left" Mouse click event
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        Vector2 TmpPos = {0};
        TmpPos = GetMousePosition();
        if( TmpPos.x >= RBcorner.x || TmpPos.x <= LTcorner.x ||
        TmpPos.y >= RBcorner.y || TmpPos.y <= LTcorner.y){
            MousePos.Pos = {0};
            MousePos.Clicked_GridPos = {0};
            MousePos.Inside = false;
        }
        else{
            MousePos.Pos = TmpPos;
            MousePos.Clicked_GridPos.x = (short)( MousePos.Pos.x / TILE_SIZE);
            MousePos.Clicked_GridPos.y = (short)( (MousePos.Pos.y - LTcorner.y)  / TILE_SIZE);
            MousePos.Inside = true;
        }
    }

    // For checking the clicked tile position
    DrawText( TextFormat("(%d, %d)", MousePos.Clicked_GridPos.x, MousePos.Clicked_GridPos.y), 30, 5, 20, BLACK);
    
    // Drawing part, gonna move later
    if(MousePos.Inside){
        DrawRectangle( (MousePos.Clicked_GridPos.x * TILE_SIZE + LTcorner.x),
        (MousePos.Clicked_GridPos.y * TILE_SIZE + LTcorner.y + 1),
        TILE_SIZE - 1, TILE_SIZE - 1, BLUE);
    }

}