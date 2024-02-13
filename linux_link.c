#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "PSXMSFS.h"
#include "mock.h"

#ifdef _WIN32
#define NOGDI
#define NOUSER
#include <windows.h>
DWORD T;
HANDLE H;
#else
#include <pthread.h>
#define DWORD int
#define WINAPI
#endif

#define UNUSED(X) (void)((X))

#define SCREENWIDTH 410
#define SCREENHEIGHT 520
#define FPSTARGET 60

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "gui.h"

#include "style_dark.h"
#include <stdint.h>
#define NB_LOGS 8
#define MAXLEN_DEBUG_MSG 8192

char messages[NB_LOGS][MAXLEN_DEBUG_MSG];

FLAGS *flags;

DWORD WINAPI launchthread(void *Param)
{
    FLAGS *f = (FLAGS *)Param;
    int connected;
    connected = connectPSXMSFS(f);
    return connected;
}

void printLogBuffer(void *Param, GuiLayoutNameState *gui)
{

    logMessage *D = (logMessage *)Param;

    static uint64_t oldLogID = 0;
    static uint64_t count = 0;
    uint64_t ID;
    char *mess;
    char buffer[4192] = {0};


    for (int i = 0; i < NB_LOGS; i++) {

        int level = getLogLevel(D, i);
        ID = getLogID(D, i);
        mess = getLogMessage(D, i);
        if (oldLogID < ID) {               // there is a potential new log
            if (level >= gui->LOG_VALUE) { // is it below our verbosity level ?
                if (count < NB_LOGS) {
                    strcpy(messages[count], mess);
                } else {
                    memmove(messages, messages + 1, (NB_LOGS - 1) * MAXLEN_DEBUG_MSG);
                    strcpy(messages[NB_LOGS - 1], mess);
                }
                oldLogID = ID;
                count++;
            }
        }
    }
    if (count) {
        gui->TE_LOG[0] = 0;
        for (int i = 0; i < NB_LOGS; i++) {
            if (messages[i]) {
                if (i == 0)
                    strncpy(buffer, messages[i], strlen(messages[i]));
                else
                    strncat(buffer, messages[i], strlen(messages[i]));
                buffer[strlen(buffer)] = 10;
            }
        }
        strncpy(gui->TE_LOG, buffer, 4191);
    }
}

servers populateInfo(GuiLayoutNameState *state)
{

    servers S;
    strncpy(S.PSXIP, state->TE_PSXMAIN, IP_LENGTH);
    S.PSXPORT = strtol(state->TE_PSXPORT, NULL, 10);
    strncpy(S.BOOSTIP, state->TE_PSXBOOST, IP_LENGTH);
    S.BOOSTPORT = strtol(state->TE_BOOSTPORT, NULL, 10);
    strncpy(S.MSFSIP, state->TE_MSFS, IP_LENGTH);

    return S;
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    bool exitWindow = false;
    bool showExit = false;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "PSXMSFS GUI interface");
    SetExitKey(0);
    GuiLoadStyleDark();

    SetTargetFPS(FPSTARGET);
    logMessage *D = getLogBuffer(NB_LOGS);

    bool connecting = false;
    bool connected = false;
    bool launched = false;


    /*----------------------------
     * Trying to read the ini file
     *--------------------------*/

    flags = initFlags();  // Fills in default values for the flags
    updateFromIni(flags); // update values from INI file if present

    /*----------------------------------------------
     * Once we have the init flags, update the layout
     *--------------------------------------------*/

    GuiLayoutNameState state = InitGuiLayout(flags);

    // LoadFont("NotoSerif-Medium.ttf")  // TTF font : Font data and atlas are generated directly from TTF
    //  NOTE: We define a font base size of 32 pixels tall and up-to 250 characters
    // Font fontTtf = LoadFontEx("NotoSerif-Medium.ttf", 32, 0, 250);
    //  Font fontTtf = LoadFontEx("NotoSerif-ExtraBoldItalic.ttf", 32, 0, 250);

    while (!exitWindow) // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_ESCAPE))
            showExit = !showExit;

        exitWindow = WindowShouldClose();
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));


        /*---------------------------
         * Drawing the layout
         *-------------------------*/
        ACFT acft = getACFTInfo();
        drawLayout(&state, &showExit, &acft, connecting, launched);

        if (state.Connect) {
        /*---------------------------
         * Printing the logs
         *-------------------------*/
        printLogBuffer(D, &state);
            if (!connecting && !connected) {

                initialize(flags);
                setLogVerbosity(flags, state.LOG_VALUE);
                servers S = populateInfo(&state);
                setServersInfo(&S);
#ifdef _WIN32
                H = CreateThread(NULL, 0, launchthread, flags, 0, &T);
            }
            DWORD retval;
            GetExitCodeThread(H, &retval);
            switch (retval) {
            case STILL_ACTIVE:
                strcpy(state.statusBarText, "Connecting.");
                connecting = true;
                state.Connect =true;
                connected = false;
                break;
            case 0:
                strcpy(state.statusBarText, "Connected.");
                state.Connect =true;
                connecting = false;
                connected = true;
                break;
            case 1:
                strcpy(state.statusBarText, "DISCONNUECTED.");
                state.Connect =false;
                connecting = false;
                connected = false;
                break;
            }
#else
            }
#endif
            if (connected && !launched) {

                main_launch();
                launched = true;
            }
        } else {
            if (launched) {
                cleanup();
                launched = false;
                connecting = false;
                connected = false;
            }
        }

        if (showExit) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
            int result = GuiMessageBox((Rectangle){(float)GetScreenWidth() / 2 - 125, (float)GetScreenHeight() / 2 - 50, 250, 100}, GuiIconText(ICON_EXIT, "Close Window"), "Do you really want to exit?", "YES;NO");
            if ((result == 0) || (result == 2))
                showExit = false;
            else if (result == 1) {
                cleanup();
                state.Connect = false;
                exitWindow = true;
            }
        }

        EndDrawing();
    }

    freeLogBuffer(D);
    CloseWindow();
    return 0;
}
