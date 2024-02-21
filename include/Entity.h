#ifndef ENTITY_H
#define ENTITY_H

struct GridPos{
    short x, y;
};

struct Tile{
    GridPos cordi;
    short Minecount = 0;
    bool revealed = false;
    bool isMine = false;
    bool flag = false;
};


#endif