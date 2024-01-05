#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "raylib.h"

#define MAX_INPUT_CHARS 300

// Linux
/* #define FILE_URL "/home/x/Desktop/atlas.rec"  */
// Mac
#define FILE_URL "/Users/muga/Desktop/atlas.rec"


void addTask(Font* font, char* task, float inputPosX, int inputPosY) {
	Vector2 taskVector = { inputPosX, (float)inputPosY };
	DrawTextEx(*font, task, taskVector, font->baseSize, 1, DARKGRAY);
}

// Program main entry point
int main(void)
{
	time_t t;
	time(&t);

	struct tm *timePtr;
	timePtr = localtime(&t);

	char currentDate[12];


	strftime(currentDate, sizeof(currentDate), "%d/%m/%Y", timePtr);
	
    // Initialization
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Atlas");

    char taskName[MAX_INPUT_CHARS + 1] = "\0"; // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

	// Set font
	Font appFont = LoadFontEx("roboto.ttf", 20, 0, 250);

    Rectangle textBox = { 0, 44, screenWidth, 25 };

	// Keep track of item textbox locations on the X Axis
	int itemPosY = textBox.y + 5;

    bool focusOnInput = false;

    int framesCounter = 0;

    SetTargetFPS(120);

	// File to Store records
	FILE *file_ptr;

	file_ptr = fopen(FILE_URL, "a");

	char tasks[1000][301];
	int c = 0;

    // Main game loop
    while (!WindowShouldClose()){
		focusOnInput = true;

        if (focusOnInput)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();
			bool deleteInput = IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE);

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {				
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                    taskName[letterCount] = (char)key;
                    taskName[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }
                key = GetCharPressed();  // Check next character in the queue

            }

			if (deleteInput) {
				letterCount-=1;
				if (letterCount < 0) letterCount = 0;
				taskName[letterCount] = '\0';
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

		Vector2 labelVector = { (float)2, (float)0 };
		DrawTextEx(appFont, "Enter Task...", labelVector, appFont.baseSize, 1, GRAY);
		
		Vector2 currentDateLabelVector = {(float)(screenWidth - 120), (float)22};
		DrawTextEx(appFont, currentDate, currentDateLabelVector, appFont.baseSize, 1, MAROON);

		DrawRectangleRec(textBox, RAYWHITE);
		
		DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
		
		Vector2 textBoxVector = {(float)textBox.x + 5, (float)(textBox.y + 2.5)};
		DrawTextEx(appFont, taskName, textBoxVector, appFont.baseSize, 1, DARKGRAY);

		if (focusOnInput) {
			if (letterCount < MAX_INPUT_CHARS) {
				// Draw blinking underscore char
				if (((framesCounter/appFont.baseSize)%2) == 0){ 
					Vector2 cursorVector = { 
						(float)(textBox.x + 5 + MeasureTextEx(appFont, taskName, appFont.baseSize, 1).x), 
						(float)(textBox.y + 2.5) 
					};

					DrawTextEx(appFont, "_", cursorVector, appFont.baseSize, 1, DARKGRAY);
				}
			}

		}

		bool submitInput = IsKeyPressedRepeat(KEY_ENTER) || IsKeyPressed(KEY_ENTER);
		if (submitInput) {
			strcpy(tasks[c], taskName);

			letterCount = 0;
			taskName[0] = '\0';
			itemPosY += 25;

			c++;
		}

		for(int i=0; i < c + 1; i++){
			addTask(&appFont, tasks[i], (int)textBox.x + 5, (int)textBox.y + 28.5 + (appFont.baseSize + 2) * i + 1);
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
