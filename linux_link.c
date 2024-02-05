#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PSXMSFS.h"

#define UNUSED(X) (void)((X))

#define SCREENWIDTH 410
#define SCREENHEIGHT 520
#define FPSTARGET 60

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_LAYOUT_NAME_IMPLEMENTATION
#include "gui.h"

#include <stdint.h>

#define NB_LOGS 20

int printLogBuffer(void *Param, GuiLayoutNameState *gui)
{

    logMessage *D = (logMessage *)Param;

    static uint64_t printedLogs = 0;

    uint64_t ID;
    char mess[128];

    for (int i = 0; i < NB_LOGS; i++) {
        ID = getLogID(D, i);
        if (ID > printedLogs) {
            strncpy(mess, getLogMessage(D, i), 128);
            printf("Debug Id: %lu\tLog: %s\n", ID, mess);
            strncpy(gui->TE_LOG, mess, 128);
            printedLogs++;
        }
    }
    return 0;
}
int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    bool exitWindow = false;
    bool showExit = false;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "PSXMSFS GUI interface");
    SetExitKey(0);

    SetTargetFPS(FPSTARGET);
    logMessage *D = initLogBuffer();

    GuiLayoutNameState state = InitGuiLayoutName();
    bool launched = false;

    while (!exitWindow) // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_ESCAPE))
            showExit = !showExit;

        exitWindow = WindowShouldClose();
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    //    printLogBuffer(D, &state);
        GuiLayoutName(&state, &showExit);

        if (state.Connected) {
            if (!launched) {
                initialize("127.0.0.1", "127.0.0.1", 10747, "127.0.0.1", 10749);
                connectPSXMSFS();
                main_launch();
                launched = !launched;
            }
        } else {
            launched = false;
        }

        if (showExit) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
            int result = GuiMessageBox((Rectangle){(float)GetScreenWidth() / 2 - 125, (float)GetScreenHeight() / 2 - 50, 250, 100}, GuiIconText(ICON_EXIT, "Close Window"), "Do you really want to exit?", "YES;NO");
            if ((result == 0) || (result == 2))
                showExit = false;
            else if (result == 1)
                cleanup();
            state.Connected = false;
            exitWindow = true;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
