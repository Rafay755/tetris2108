#ifndef grid_h
#define grid_h

#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#include "color.h"

// **************************************************Grid class**************************************************************8
class Grid
{
private:
    int rows; // rows of grid
    int cols; // cols of grid

    int cellSize;         // cell size
    vector<Color> colors; // this is a vector of type color

    bool isRowFull(int r)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] == 0) // there is a zero numeral when there is no color on grid cell so it means grid line is not filled
            {
                return false;
            }
        }
        return true; // it means if every cell owns non zero numeral then rows is full
    }
    void clearRow(int r)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c] = 0; // set all columns elements of that row to 0
        }
    }
    void moveRowDown(int r, int nR) // r is the row that has to be moved and nR is num of rows that we have to move down
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r + nR][c] = grid[r][c]; // suppose r is 0 and nR is 2 then it replaces all elemnts of row-2 with row-0 and set them to 0 so it will move down and cleared
            grid[r][c] = 0;
        }
    }

public:
    int **grid;
    // Default constructor
    Grid() : rows(20), cols(10), cellSize(30) // these are default dimensions for my grid
    {
        grid = new int *[rows];
        for (int i = 0; i < rows; i++)
        {
            grid[i] = new int[cols]; // Initialize each row with 0s
        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                grid[i][j] = 0;
            }
        }

        colors = getCellColors(); // copying vector color from color.h function
    }
    void initialize() // this fuincvtion is used to set grid to 0 means no color
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                grid[i][j] = 0;
            }
        }
    }
    // Parameterized constructor
    Grid(int r, int c, int cS) : rows(r), cols(c), cellSize(cS), grid(nullptr)
    {
        grid = new int *[rows];
        for (int i = 0; i < rows; i++)
        {
            grid[i] = new int[cols](); // Initialize each row with 0s
        }
        colors = getCellColors();
    }

    // Destructor
    ~Grid()
    {
        if (grid != nullptr)
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] grid[i]; // de allocating heapo location
            }
            delete[] grid;
        }
    }

    // Function to draw the grid
    void draw()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                int cellVal = grid[i][j];
                // Draw a square
                //DrawRectangle(int posX,int posY,int width,int height color)
                DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellVal]); // this is a function from raylib liberarry
            }
        }
    }
    // to print the numeric values of grid
    void printGrid()
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                cout << grid[i][j] << " "; // just to show numeric values of grid but dont need it now
            }
            cout << endl;
        }
    }
    bool isOutsideGrid(int r, int c)
    {
        if ((r >= 0 && r < rows) && (c >= 0 && c < cols)) // to check block is outside the grid or not
        {
            return false;
        }

        return true;
    }
    bool isCellEmpty(int r, int c) // to check cell is empty or not
    {
        if (grid[r][c] == 0)
        {
            return true;
        }
        return false;
    }
    int clearFullRows()
    {
        int completed = 0;
        for (int r = rows - 1; r >= 0; r--) // check rows from bottom
        {
            if (isRowFull(r)) // if it returns true
            {
                clearRow(r); // clear it by setting all to 0
                completed++; // increment in completeed
            }
            else if (completed > 0) // set the position of above rows like if it is 1 then it moves above rows by 1
            {
                moveRowDown(r, completed); // here completeed replaces nR that is num of rows to move down
            }
        }
        return completed; // return total rows that have cleared
    }
};
//*****************************************************End************************************************
#endif
