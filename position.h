#ifndef position_h
#define position_h

#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#include "color.h"

//************************************************************Poasition class*****************************************************************************
// this class is used to adjust the position of blocks and grid its each object has to parameters row and col
class position
{
private:
    int rows;
    int cols;

public:
    position() : rows(0), cols(0)
    {
    }
    position(int r, int c) : rows(r), cols(c)
    {
    }
    void setRows(int r)
    {
        rows = r;
    }
    void setCols(int c)
    {
        cols = c;
    }
    int getRows() const
    {
        return rows;
    }
    int getCols() const
    {
        return cols;
    }
    ~position()
    {
    }
};
//*******************************************************End*****************************************************************
#endif
