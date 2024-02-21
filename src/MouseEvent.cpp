#include "MouseEvent.h"


bool Minesweeper::ClickedInside(Vector2 click, Vector2 LT, int width, int hieght){
    if( click.x <= LT.x || click.x >= LT.x + width ||
    click.y <= LT.y || click.y >= LT.y + hieght)
        return false;
    else
        return true;
}


bool Minesweeper::MouseEvent(void){

    TmpPos = GetMousePosition();

    // Check mouse left click event
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        Inside = false;
        clicked_cordi = {0};

        // Check if click on tile
        if( ClickedInside(TmpPos, LTcorner, COL*TILE_SIZE, ROW*TILE_SIZE ) ){
            clicked_cordi.x = (short)( (TmpPos.x - LTcorner.x) / TILE_SIZE);
            clicked_cordi.y = (short)( (TmpPos.y - LTcorner.y) / TILE_SIZE);
            GameTable[clicked_cordi.x][clicked_cordi.y].revealed = true;
            Inside = true;

            // Generate mines
            if(first_left_click){
                PlaceMines(MINECOUNTS);
                first_left_click = false;
            }

            // Reveal all con tiles if Minecount = 0
            if(GameTable[clicked_cordi.x][clicked_cordi.y].Minecount == 0)
                Reveal8Tile(clicked_cordi);
        }
    }

    // Check mouse right click event
    if(IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)){
        Inside = false;
        clicked_cordi = {0};

        // Check if click on tile
        if( ClickedInside(TmpPos, LTcorner, COL*TILE_SIZE, ROW*TILE_SIZE ) ){
            clicked_cordi.x = (short)( (TmpPos.x - LTcorner.x) / TILE_SIZE) ;
            clicked_cordi.y = (short)( (TmpPos.y - LTcorner.y) / TILE_SIZE);
            Inside = true;
            GameTable[clicked_cordi.x][clicked_cordi.y].flag = !GameTable[clicked_cordi.x][clicked_cordi.y].flag;
        }
    }
    
    return true;
}



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
}

bool Minesweeper::insideRange(int a, int b){
    return ( (a>=0) && (a < b))?true:false;
}

void Minesweeper::AddOne2Tiles(short x, short y){
    for(int i = -1; i < 2; i++){
        if( insideRange((x+i), COL) )
            for(int j = -1; j < 2; j++){  
                if( insideRange((y+j), ROW) )
                    if(!GameTable[x+i][y+j].isMine)  GameTable[x+i][y+j].Minecount++;  
                
            }
    }
}

bool Minesweeper::ClosedtoClick(GridPos c){
    return (  ( abs(c.x-clicked_cordi.x) < 2 ) && ( abs(c.y-clicked_cordi.y) < 2 ));
}

void Minesweeper::PlaceMines(int minecount = 1){
    srand(time(0));
    short r = rand() % (ROW);
    
    while(minecount > 0){
        short seeds = rand() % (COL);

        if(!GameTable[seeds][r].isMine && !ClosedtoClick((GridPos){seeds, r})){
            GameTable[seeds][r].isMine = true;
            AddOne2Tiles(seeds, r);
            GameTable[seeds][r].Minecount = 0;
            minecount--;
        }
        r++;
        if(r == ROW)    r=0;
    }
}

void Minesweeper::Reveal8Tile(GridPos cor){
    GameTable[cor.x][cor.y].revealed = true;
    for(int i = -1; i < 2; i++)
        if( insideRange((cor.x+i), COL) )
            for(int j = -1; j < 2; j++)
                if( insideRange((cor.y+j), ROW) ){
                    if(!GameTable[cor.x+i][cor.y+j].revealed){
                        GameTable[cor.x+i][cor.y+j].revealed = true;
                        if(!GameTable[cor.x+i][cor.y+j].Minecount)
                            Reveal8Tile( (GridPos){ (short)(cor.x+i), (short)(cor.y+j)} );  
                    }  
                }
}


bool Minesweeper::GetInsideTable(void){
    return Inside;
}

bool Minesweeper::GetFirstClick(void){
    return first_left_click;
}

bool Minesweeper::GetTileRevealState(int x, int y){
    return GameTable[x][y].revealed;
}

bool Minesweeper::GetTileMineState(int x, int y){
    return GameTable[x][y].isMine;
}

bool Minesweeper::GetTileFlagState(int x, int y){
    return GameTable[x][y].flag;
}

int Minesweeper::GetTileMineCount(int x, int y){
    return GameTable[x][y].Minecount;
}

GridPos Minesweeper::GetClickedCordi(void){
    return clicked_cordi;
}

