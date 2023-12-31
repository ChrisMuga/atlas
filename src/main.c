#include <stdio.h>
#include <time.h>

#include "raylib.h"

#define MAX_INPUT_CHARS 300

// Program main entry point
int main(void)
{
	time_t t;
	time(&t);

	struct tm *time_ptr;
	time_ptr = localtime(&t);

	char current_date[12];

	strftime(current_date, sizeof(current_date), "%d/%m/%Y", time_ptr);
	
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Atlas");

    char name[MAX_INPUT_CHARS + 1] = "\0"; // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    Rectangle textBox = { 0, 44, screenWidth, 25 };
    bool focusOnInput = false;

	// File to Store records
	FILE *file_ptr;

    int framesCounter = 0;

    SetTargetFPS(120);

    // Main game loop
    while (!WindowShouldClose()){
        // Update
        /* if (CheckCollisionPointRec(GetMousePosition(), textBox)) focusOnInput = true; */
        /* else focusOnInput = false; */
		focusOnInput = true;

        if (focusOnInput)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();
			bool deleteInput = IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE);
			bool submitInput = IsKeyPressedRepeat(KEY_ENTER) || IsKeyPressed(KEY_ENTER);

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {				
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }
                key = GetCharPressed();  // Check next character in the queue

            }

			if (deleteInput) {
				letterCount-=1;
				if (letterCount < 0) letterCount = 0;
				name[letterCount] = '\0';
			}

			if (submitInput) {
				return 0;
			}

        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (focusOnInput){
			framesCounter++;
		} else { 
			framesCounter = 0; 
		}

        BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("Enter Task...", 2, 0, 20, GRAY);
		DrawText(current_date, screenWidth - 120, 22, 20, MAROON);
		DrawRectangleRec(textBox, RAYWHITE);
		DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
		DrawText(name, (int)textBox.x + 5, (int)textBox.y + 2.5, 20, DARKGRAY);

		if (focusOnInput)
		{
			if (letterCount < MAX_INPUT_CHARS)
			{
				// Draw blinking underscore char
				if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 20), (int)textBox.y + 2.5, 20, DARKGRAY);
			}
		}

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

