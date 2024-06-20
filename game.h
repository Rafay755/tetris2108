#ifndef game_h
#define game_h

#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;
#include "color.h"
#include "grid.h"
#include <map>
#include "position.h"
#include "blocks.h"
#include "color.h"
//*********************************************************game class****************************************************************

// Defines an enumeration to improve readability for different  state of game
enum GameState
{
    RUNNING,
    PAUSED,
    GAME_OVER
};


class Game
{
private:
    vector<block> blocks; // vector to hold all blocks at all
    block nextBlock;      // next block that has to fall back

    block currentBlock; // current block
    bool isBlockOutside()
    {
        vector<position> tiles = currentBlock.GetCellPosition();
        // i can also simply used for(position item :tiles)
        for (int i = 0; i < tiles.size(); i++)
        {
            position item = tiles[i];
            if (grid.isOutsideGrid(item.getRows(), item.getCols())) // check if block cross bounds of grid at all
            {
                return true;
            }
        }
        return false;
    }
    void rotateBlock()
    {
        if (!gameOver) // check user pressessd end game window or not or cross
        {
            currentBlock.rotate(); // then rotate block
            if (isBlockOutside())  // if after rotating block cross limits turn back or undo rotation
            {
                currentBlock.undoRotation();
            }
        }
    }
    bool BlockFits()
    {
        vector<position> tiles = currentBlock.GetCellPosition();
        for (int i = 0; i < tiles.size(); i++)
        {
            position item = tiles[i];
            if (grid.isCellEmpty(item.getRows(), item.getCols()) == false) // check blocks id and dimensions set correectly or not
            {
                return false;
            }
        }
        return true;
    }
    void LockBlock() //  lockBlock function to lock block at bottom
    {
        vector<position> tiles = currentBlock.GetCellPosition(); // tiles position vector storing the all positions of current block
        for (int i = 0; i < tiles.size(); i++)
        {
            position item = tiles[i];
            grid.grid[item.getRows()][item.getCols()] = currentBlock.getId(); // it stores position of current block to grid and then assign block id to it
        }
        currentBlock = nextBlock; // assigning nxt block to it
        // means next block is unable to fit in grid at all
        if (BlockFits() == false)
        {
            gameOver = true;
        }
        nextBlock = getRandomBlock(); // for proper random behavior
        int rowClr = grid.clearFullRows();
        scoredUpdate(rowClr, 0); // how many rows are cleared at all
    }

    // this function is used to reset the whole game
    void reset()
    {
        grid.initialize();               // it will clear all grid by intializing each grid cell with 0
        blocks = getAllblocks();         // function to get blocks
        currentBlock = getRandomBlock(); // random blocks assigning
        nextBlock = getRandomBlock();    // random blocks assigning
        score = 0;                       // reset score to 0
    }
    Grid grid;

public:
    GameState currentState;
    bool gameOver;
    Music music;

    int score;
    // vector of block class that stores blocks at indexes
    vector<block> getAllblocks()
    {
        return {Iblock(), Jblock(), Lblock(), Oblock(), Sblock(), Tblock(), Zblock()};
    }
    // function used to get random blocks at all
    block getRandomBlock()
    {
        if (blocks.empty()) // if block vector is empty refill it
        {
            blocks = getAllblocks();
        }

        int randomIndex = rand() % blocks.size();   // to generate a block with in range of vectors at all
        block b = blocks[randomIndex];              // this  is a randomly selected block
        blocks.erase(blocks.begin() + randomIndex); // so that block will not appear for next tim,e to ensure that there is a random block generation i use it instead of bag theory

        return b; // return that random removed block
    }
    // default constructor
    Game()
    {
        blocks = getAllblocks();
        currentBlock = getRandomBlock();
        nextBlock = getRandomBlock();
        gameOver = false;
        score = 0;
        currentState = RUNNING; // using enum

       
    }
    // function to toggle or swing or swap states
    void togglePause()
    {
        if (currentState == RUNNING)
        {
            currentState = PAUSED;
        }
        else if (currentState == PAUSED)
        {
            currentState = RUNNING;
        }
    }
    // draw function of game class
    void Draw()
    {
        grid.draw();                    // use dtraw function of grid class
        currentBlock.drawBlock(11, 11); // dimensions to draw the block

        switch (nextBlock.getId())
        {
            // set dimensions for O block as it is not appearing good without setting it
        case 3:
            nextBlock.drawBlock(255, 290);
            break;
            // setting dimensions for s block at all
        case 4:
            nextBlock.drawBlock(250, 280);
            break;
            // default dimensions for remaining blocks
        default:
            nextBlock.drawBlock(270, 270);
            break;
        }
    }

    // to handle inpuit from key Board
    void moveBlockLeft()
    {
        if (!gameOver) // if game is not overed
        {
            currentBlock.moveBlock(0, -1);                // move left
            if (isBlockOutside() || BlockFits() == false) // if block is not in bounds of grid
            {
                currentBlock.moveBlock(0, 1); // Revert the movement
            }
        }
    }

    void moveBlockRight()
    {
        if (!gameOver)
        {
            currentBlock.moveBlock(0, 1);                 // move right
            if (isBlockOutside() || BlockFits() == false) // if block crosses the bounds
            {
                currentBlock.moveBlock(0, -1); // Revert the movement
            }
        }
    }

    void moveBlockDown()
    {
        if (!gameOver)
        {
            currentBlock.moveBlock(1, 0);                 // move 1 block along y axis
            if (isBlockOutside() || BlockFits() == false) // if block crosses bounds
            {
                currentBlock.moveBlock(-1, 0); // Revert the movement
                LockBlock();                   // when it reach bottom lock block
            }
        }
    }
    void handleInput()
    {
        int keyPressed = GetKeyPressed(); // use raylib func to find which key was pressed
        // press space key to reset the game
        if (keyPressed == KEY_SPACE && gameOver)
        {
            gameOver = false;
            reset();
        }
        // press P key to pause and resume
        if (keyPressed == KEY_P)
        { // Assuming 'P' is the pause key
            togglePause();
        }
        // if game is running
        if (currentState == RUNNING&&!gameOver)
        {
            // cases for pressed key
            /*
           1.move left while pressing left key
           2.move right while pressing right navigation key
           3.move down navigation key to move down and then score incremented by 1
           4.move up while pressing up navugation key
            */

            switch (keyPressed)
            {
            case KEY_LEFT:
                moveBlockLeft();
                break;

            case KEY_RIGHT:
                moveBlockRight();
                break;

            case KEY_DOWN:
                moveBlockDown();
                scoredUpdate(0, 1);
                break;

            case KEY_UP:
                rotateBlock();

            default:
                break;
            }
        }
    }
    // To update the scores
    void scoredUpdate(int linesCleared, int moveDownpoints)
    {
        switch (linesCleared)
        {
        case 1:
            score += 100; // 100 score while clearing 1 line
            break;
        case 2:
            score += 300; // 300 score while clearing 2 line
            break;
        case 3:
            score += 500; // 500 score while clearing 3 line
            break;

        default:
            break;
        }
        score += moveDownpoints; // it is one for each move down
    }
    int getScore() const
    {
        return score;
    }
    // we use this function manage speed with scores
    double calculateSpeed(int score)
    {
        if (score < 500) // if marks is less tahn 500 speed returns to 0.8 fps
        {
            return 0.8;
        }
        else
        {
            return max(0.1, 0.8 - (score / 5000.0)); // it causes slight or gradual increase in speed after increase in marks above 500
        }
    }
    // Function to manage time at intervals bcz we want actions at regular intervals not continuousl
    double lastUpddateTime = 0;
    bool eventTriggered(double interval)
    {
        double currentTime = GetTime(); // function of raylib to get the time in seconds when program starts
        if (currentTime - lastUpddateTime >= interval)
        {
            lastUpddateTime = currentTime;
            return true;
        }
        return false;
    }

    ~Game()
    {
        UnloadMusicStream(music); // close that openeed music stream
        CloseAudioDevice();
    }
};
//********************************************************End***********************************************************
#endif
