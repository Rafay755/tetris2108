#ifndef blocks_h
#define blocks_h

#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#include "color.h"
#include "grid.h"
#include <map>
#include "position.h"

//*******************************************Block Clazss***********************************************************
class block
{
private:
    int cellSize;         // size of each cell of block
    int rotationState;    // current rotation state
    vector<Color> colors; // again it is a vector for collors pof block
    int rowOffset;        // offset positions dimensions
    int colOffset;

protected:
    int id;                           // block id
    map<int, vector<position>> cells; // Map storing the positions of individual cells for each rotation state basically it is frequencing the position values for each cell
public:
    block()
    {
        cellSize = 30; // set the cell size
        rotationState = 0;
        colors = getCellColors(); // from color.h
        rowOffset = 0;
        colOffset = 0;
    }
    // to detrmine new position
    vector<position> GetCellPosition()
    {
        vector<position> tiles = cells[rotationState]; // tiles is a vector of position class or vector object of position class and cell is a map that associates each rotation state of block to position object vector tiles
        vector<position> movedTiles;
        for (int i = 0; i < tiles.size(); i++)
        {
            position item = tiles[i];                                                           // just for covinience i did it so this is each position in tiles vector
            position newPos = position(item.getRows() + rowOffset, item.getCols() + colOffset); // calculates the new position for the current item by adding the rowOffset to its row index and the colOffset to its column index. It creates a new position object with these adjusted coordinates and assigns it to newPos.
            movedTiles.push_back(newPos);                                                       // adds the newPos to the movedTiles vector, effectively storing the adjusted position.
        }
        return movedTiles;
    }
    void drawBlock(int offsetX, int offsetY) // This  function drawBlock which takes two integer parameters offsetX and offsetY. These parameters represent the horizontal and vertical offsets from the top-left corner where the block will be drawn.
    {
        vector<position> tiles = GetCellPosition(); // initializes a vector called tiles with the positions of the block cells after adjusting for the row and column offsets

        for (int i = 0; i < tiles.size(); i++) // iterate for each position
        {
            position item = tiles[i]; // same as above i dit it
            // use raylib function to draw rectangle at all
            DrawRectangle(item.getCols() * cellSize + offsetX, item.getRows() * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
        }
    }
    void moveBlock(int rows, int cols) // this function adjust the row offsets and col offsets while moving the block
    {
        rowOffset += rows;
        colOffset += cols;
    }

    void rotate()
    {
        rotationState++;                        // take record of rotation state
        if (rotationState == (int)cells.size()) // there is a  frequency for each rotation state in cell map so it checks when it reached max rotation satte comes back to 0
        {
            rotationState = 0; // so it does not exceed max val in map
        }
    }
    void undoRotation()
    {
        rotationState--;
        if (rotationState == -1) // this chedck is there to ensure that iof a block is at initial state and then someone rotates it back i.e undo rotation then rotattion state will set to -1 so set roatation state to mx with in map
        {
            rotationState = cells.size() - 1;
        }
    }
    int getId() const // to get id
    {
        return id;
    }
};
//********************************88Inherited Blocks/Tetriminos*************************************************
/*
1.All of these blocks are inherited from block class
2.each block has its own id as well
3.each block has dimensions at all

*/
class Lblock : public block
{
public:
    Lblock()
    {
        id = 1;
        cells[0] = {position(0, 2), position(1, 0), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 1), position(1, 1), position(2, 1), position(2, 2)};
        cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 0)};
        cells[3] = {position(0, 0), position(0, 1), position(1, 1), position(2, 1)};
        moveBlock(0, 3);
    }
};
class Jblock : public block
{
public:
    Jblock()
    {
        id = 2;
        cells[0] = {position(0, 0), position(1, 0), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 1), position(0, 2), position(1, 1), position(2, 1)};
        cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 2)};
        cells[3] = {position(0, 1), position(1, 1), position(2, 0), position(2, 1)};
        moveBlock(0, 3);
    }
};
class Iblock : public block
{
public:
    Iblock()
    {
        id = 3;
        cells[0] = {position(1, 0), position(1, 1), position(1, 2), position(1, 3)};
        cells[1] = {position(0, 2), position(1, 2), position(2, 2), position(3, 2)};
        cells[2] = {position(2, 0), position(2, 1), position(2, 2), position(2, 3)};
        cells[3] = {position(0, 1), position(1, 1), position(2, 1), position(3, 1)};
        moveBlock(-1, 3);
    }
};
class Oblock : public block
{
public:
    Oblock()
    {
        id = 4;
        cells[0] = {position(0, 0), position(0, 1), position(1, 0), position(1, 1)};
        cells[1] = {position(0, 0), position(0, 1), position(1, 0), position(1, 1)};
        cells[2] = {position(0, 0), position(0, 1), position(1, 0), position(1, 1)};
        cells[3] = {position(0, 0), position(0, 1), position(1, 0), position(1, 1)};
        moveBlock(0, 4);
    }
};
class Sblock : public block
{
public:
    Sblock()
    {
        id = 5;
        cells[0] = {position(0, 1), position(0, 2), position(1, 0), position(1, 1)};
        cells[1] = {position(0, 1), position(1, 1), position(1, 2), position(2, 2)};
        cells[2] = {position(1, 1), position(1, 2), position(2, 0), position(2, 1)};
        cells[3] = {position(0, 0), position(1, 0), position(1, 1), position(2, 1)};
        moveBlock(0, 3);
    }
};

class Tblock : public block
{
public:
    Tblock()
    {
        id = 6;
        cells[0] = {position(1, 1), position(1, 0), position(1, 2), position(0, 1)};
        cells[1] = {position(1, 1), position(0, 1), position(2, 1), position(1, 0)};
        cells[2] = {position(1, 1), position(1, 0), position(1, 2), position(2, 1)};
        cells[3] = {position(1, 1), position(0, 1), position(2, 1), position(1, 2)};
        moveBlock(0, 3);
    }
};
class Zblock : public block
{
public:
    Zblock()
    {
        id = 7;
        // Define dimensions for each rotation
        cells[0] = {position(0, 0), position(0, 1), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 2), position(1, 1), position(1, 2), position(2, 1)};
        cells[2] = {position(1, 0), position(1, 1), position(2, 1), position(2, 2)};
        cells[3] = {position(0, 1), position(1, 0), position(1, 1), position(2, 0)};

        moveBlock(0, 3); // Initial movement of the block
    }
};
//****************************************************************End**************************************************************************************
#endif
