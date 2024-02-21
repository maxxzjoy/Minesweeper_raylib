#include "Minesweeper.h"

//------------------------------------------------------------------------
//  Main functions
//------------------------------------------------------------------------

void Minesweeper::InitGame(void){
    for(short i = 0; i < COL; i++ ){
        for(short j = 0; j < ROW; j++ ){
            GameTable[i][j].cordi = (GridPos){.x = i, .y = j};
            GameTable[i][j].flag = false;
            GameTable[i][j].isMine = false;
            GameTable[i][j].Minecount = 0;
            GameTable[i][j].revealed = false;
        }
    }
    first_left_click = true;
    game_end = false;
}

void Minesweeper::MouseEvent(void){

    LeftMouseEvent();

    RightMouseEvent();

}


//------------------------------------------------------------------------
//  Private functions
//------------------------------------------------------------------------

// Check mouse left click event
void Minesweeper::LeftMouseEvent(void){

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        TmpPos = GetMousePosition();
        Inside = false;
        clicked_cordi = {0};

        // Check if click on tile
        if( ClickedInside(TmpPos, LTcorner, COL*TILE_SIZE, ROW*TILE_SIZE ) ){
            clicked_cordi.x = (short)( (TmpPos.x - LTcorner.x) / TILE_SIZE);
            clicked_cordi.y = (short)( (TmpPos.y - LTcorner.y) / TILE_SIZE);
            Inside = true;

            // Generate mines
            if(first_left_click){
                PlaceMines(MINECOUNTS);
                first_left_click = false;
            }

            if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)){
                if(CompareFlagcounts(clicked_cordi) && GameTable[clicked_cordi.x][clicked_cordi.y].revealed)
                    Reveal8Tile(clicked_cordi);
            }else{
                GameTable[clicked_cordi.x][clicked_cordi.y].revealed = true;

                if(GameTable[clicked_cordi.x][clicked_cordi.y].isMine)
                    game_end = true;
            }

            // Reveal all con tiles if Minecount = 0
            if(GameTable[clicked_cordi.x][clicked_cordi.y].Minecount == 0)
                Reveal8Tile(clicked_cordi);
        }
    }

}


// Check mouse right click event
void Minesweeper::RightMouseEvent(void){

    if(IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)){
        TmpPos = GetMousePosition();
        Inside = false;
        clicked_cordi = {0};

        // Check if click on tile
        if( ClickedInside(TmpPos, LTcorner, COL*TILE_SIZE, ROW*TILE_SIZE ) ){
            clicked_cordi.x = (short)( (TmpPos.x - LTcorner.x) / TILE_SIZE) ;
            clicked_cordi.y = (short)( (TmpPos.y - LTcorner.y) / TILE_SIZE);
            Inside = true;
            if(!GameTable[clicked_cordi.x][clicked_cordi.y].revealed)
                GameTable[clicked_cordi.x][clicked_cordi.y].flag = !GameTable[clicked_cordi.x][clicked_cordi.y].flag;
        }
    }

}

bool Minesweeper::CompareFlagcounts(GridPos c){
    short counts = 0;
    for(int i = -1; i < 2; i++){
        if( InsideRange((c.x+i), COL) )
            for(int j = -1; j < 2; j++){  
                if( InsideRange((c.x+j), ROW) )
                    if(GameTable[c.x+i][c.y+j].flag)  counts++;
                
            }
    }

    return (counts == GameTable[c.x][c.y].Minecount)?true:false;
}

// Add 1 minecount to all tiles are connected to (x, y)
void Minesweeper::AddOne2Tiles(short x, short y){
    for(int i = -1; i < 2; i++){
        if( InsideRange((x+i), COL) )
            for(int j = -1; j < 2; j++){  
                if( InsideRange((y+j), ROW) )
                    GameTable[x+i][y+j].Minecount++;  
                
            }
    }
}


void Minesweeper::PlaceMines(int minecount = 1){
    srand(time(0));
    short r = rand() % (ROW);
    
    while(minecount > 0){
        short seeds = rand() % (COL);

        if(!GameTable[seeds][r].isMine && !ClosedtoClick((GridPos){seeds, r})){
            GameTable[seeds][r].isMine = true;
            AddOne2Tiles(seeds, r);
            minecount--;
        }
        r++;
        if(r == ROW)    r=0;
    }
}

void Minesweeper::Reveal8Tile(GridPos cor){
    GameTable[cor.x][cor.y].revealed = true;
    for(int i = -1; i < 2; i++)
        if( InsideRange((cor.x+i), COL) )
            for(int j = -1; j < 2; j++)
                if( InsideRange((cor.y+j), ROW) ){
                    if(!GameTable[cor.x+i][cor.y+j].revealed && !GameTable[cor.x+i][cor.y+j].flag){
                        GameTable[cor.x+i][cor.y+j].revealed = true;

                        if(GameTable[cor.x+i][cor.y+j].isMine)  game_end = true;

                        if(!GameTable[cor.x+i][cor.y+j].Minecount)
                            Reveal8Tile( (GridPos){ (short)(cor.x+i), (short)(cor.y+j)} );  
                    }  
                }
}

bool Minesweeper::ClickedInside(Vector2 click, Vector2 LT, int width, int hieght){
    if( click.x <= LT.x || click.x >= LT.x + width ||
    click.y <= LT.y || click.y >= LT.y + hieght)
        return false;
    else
        return true;
}

bool Minesweeper::InsideRange(int a, int b){
    return ( (a>=0) && (a < b))?true:false;
}

bool Minesweeper::ClosedtoClick(GridPos c){
    return (  ( abs(c.x-clicked_cordi.x) < 2 ) && ( abs(c.y-clicked_cordi.y) < 2 ));
}


//------------------------------------------------------------------------
//  Public functions for getting info from class
//------------------------------------------------------------------------

/** 
 * @brief Get the last clicked cordinate on tile 
 * 
 * @param none
 * @return
*/
GridPos Minesweeper::GetClickedCordi(void){
    return clicked_cordi;
}

/** 
 * @brief Get the last clicked cordinate on tile 
 * 
 * @param none
 * @return
*/
bool Minesweeper::GetEndGameFlag(void){
    return game_end;
}


/** 
 * @brief Get the last clicked cordinate on tile 
 * 
 * @param
 * @return
*/
bool Minesweeper::GetTileRevealState(int x, int y){
    return GameTable[x][y].revealed;
}

/** 
 * @brief Get the last clicked cordinate on tile 
 * 
 * @param
 * @return
*/
bool Minesweeper::GetTileMineState(int x, int y){
    return GameTable[x][y].isMine;
}

/** 
 * @brief Get the last clicked cordinate on tile 
 * 
 * @param
 * @return 
*/
bool Minesweeper::GetTileFlagState(int x, int y){
    return GameTable[x][y].flag;
}

/** 
 * @brief Get the mines number within range
 * 
 * @param
 * @return
*/
int Minesweeper::GetTileMineCount(int x, int y){
    return GameTable[x][y].Minecount;
}

