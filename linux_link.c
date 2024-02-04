#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "raylib.h"

#define UNUSED(X) (void)((X))

#define SCREENWIDTH 410
#define SCREENHEIGHT 520
#define FPSTARGET 60

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_LAYOUT_NAME_IMPLEMENTATION
#include "gui.h"

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    bool exitWindow = false;
    bool Bcheck = false;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "PSXMSFS GUI interface");
    SetExitKey(0);

    SetTargetFPS(FPSTARGET);
    GuiLayoutNameState state = InitGuiLayoutName();
    while (!exitWindow) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        exitWindow = WindowShouldClose();
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        GuiLayoutName(&state,&exitWindow);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
