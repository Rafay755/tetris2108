/*
Tetris game by:
Rafay Ahmad Hussain


*/




#include "raylib.h" // Include the raylib library
#include "game.h"   // Include the custom game header

int main()
{
    Color darkBlue = {44, 44, 127, 255};   // Define a color for the grid background
    InitWindow(500, 620, "raylib Tetris"); // Initialize the window with width 500, height 620, and title "raylib Tetris"

    SetTargetFPS(60);                                    // Set the frame rate to 60 frames per second
    Font font = LoadFontEx("Font/ThaleahFat", 64, 0, 0); // Load a custom font from file

  
    Game game;          // Create a Game object
    InitAudioDevice();  // Initialize the audio device

    // Load music from file and check if it was successfully loaded
    Music music = LoadMusicStream("music2.mp3");
    if (music.stream.buffer == NULL)
    {
        cout << "Failed to load music stream." << endl; // Print an error message if the music file failed to load
    }
    else
    {
        PlayMusicStream(music); // Play the music if it loaded successfully
    }

    //**************************************Game Loop***********************************************************
    while (!WindowShouldClose()) // Main game loop, runs until the window should close
    {
        UpdateMusicStream(music); // Update the music stream to keep it playing

        BeginDrawing();            // Begin drawing to the screen
        ClearBackground(darkBlue); // Clear the screen with the dark blue color

        // Draw the score and next on user interface
        DrawTextEx(font, "score", {365, 15}, 38, 2, WHITE); // Draw the "score" label
        DrawTextEx(font, "next", {370, 175}, 38, 2, WHITE); // Draw the "next" label

        if (game.gameOver)
        {
            DrawTextEx(font, "Game Over", {320, 450}, 38, 2, WHITE); // Draw "Game Over" message if the game is over
        }

        // Draw the score background box
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        char scoreText[10];
        sprintf_s(scoreText, "%d", game.score);                   // Convert the score to a string
        Vector2 textsize = MeasureTextEx(font, scoreText, 38, 2); // Measure the text size

        // Draw the score centered in the background box
        DrawTextEx(font, scoreText, {320 + (170 - textsize.x) / 2, 65}, 38, 2, WHITE); // this is a built in function of raylib

        // Draw the "next block" background box
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        // If the game state is RUNNING, update game logic
        if (game.currentState == RUNNING)
        {
            double speed = game.calculateSpeed(game.getScore()); // Calculate the drop speed based on the score
            if (game.eventTriggered(speed))                      // thats why we use triggering instead of continuous behaviour
            {
                game.moveBlockDown(); // Move the block down if the speed interval has passed
            }
        }

        game.Draw();        // Draw the game elements
        game.handleInput(); // Handle user input

        // If the game state is PAUSED, draw a pause screen overlay
        if (game.currentState == PAUSED)
        {
            const int fontSize = 40;
            const char *pauseText = "PAUSED";
            int textWidth = MeasureText(pauseText, fontSize); // Measure the pause text width
            int posX = (GetScreenWidth() - textWidth) / 2;    // Calculate horizontal center position
            int posY = GetScreenHeight() / 2 - fontSize / 2;  // Calculate vertical center position
            DrawText(pauseText, posX, posY, fontSize, WHITE); // Draw the pause text
        }

        EndDrawing(); // End drawing to the screen
    }

    CloseWindow(); // Close the window when the game loop ends

    return 0; // Return 0 to indicate successful execution
}
