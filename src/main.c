#include <stdio.h>
#include "raylib.h"

int main(void) {
    printf("Atlas: \n");
    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Atlas", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
