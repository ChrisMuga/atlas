#include <stdio.h>
#include "raylib.h"

int main(void) {
    printf("Atlas: \n");
    InitWindow(800, 450, "Atlas");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("Atlas", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
