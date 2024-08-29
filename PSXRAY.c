#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "PSXMSFS.h"
#include "mock.h"

// test
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

void printLogBuffer(void *Param, GuiLayoutNameState *gui, Status status)
{

    logMessage *D = (logMessage *)Param;

    static uint64_t oldLogID = 0;
    static uint64_t count = 0;
    uint64_t ID;
    char *mess;
    char buffer[TEXTLENGTH] = {0};

    if (status == DISCONNECTED) {
        gui->TE_LOG[0] = '\0';
        oldLogID = 0;
        count = 0;
        return;
    }
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
                if (strlen(messages[i]))
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

    Status status = DISCONNECTED;

    logMessage *LogBuffer = NULL;
    /*----------------------------
     * Trying to read the ini file
     *--------------------------*/

    flags = createFlagsPSXMSFS(); // Fills in default values for the flags
    /*----------------------------------------------
     * Once we have the init flags, update the layout
     *--------------------------------------------*/

    GuiLayoutNameState state = InitGuiLayout(flags);

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
        drawLayout(&state, &showExit, &acft, status);
        switch (status) {
        case DISCONNECTED: {
            if (state.Connect) {
                LogBuffer = getLogBuffer(NB_LOGS);
                initializePSXMSFS(flags);
                setLogVerbosity(flags, state.LOG_VALUE);
                setOnlineHack(flags, state.CB_ONLINE);
                setTCASinject(flags, state.CB_TCAS);
                setElevationInject(flags, state.CB_ELEV);
                setCrashInhib(flags, state.CB_CRASH);
                setPSXslave(flags, state.CB_SLAVE);
                servers S = populateInfo(&state);
                setServersInfo(&S, flags);
                if (connectPSXMSFS(flags) == 0) {
                    status = CONNECTING;
                } else {
                    state.Connect = false;
                }
            }
            break;
        }

        case CONNECTING: {
            strncpy(state.TE_LOG, "Warming up", 4191);
            launchPSXMSFS(flags);
            status = CONNECTED;
            break;
        }
        case CONNECTED: {
            printLogBuffer(LogBuffer, &state, status);
            if (!state.Connect) {
                status = DISCONNECTED;
                state.TE_LOG[0] = '\0';
                disconnectPSXMSFS(flags);
                freeLogBuffer(LogBuffer);
            }
            break;
        }
        default:
            break;
        }

        if (showExit) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
            int result = GuiMessageBox((Rectangle){(float)GetScreenWidth() / 2 - 125, (float)GetScreenHeight() / 2 - 50, 250, 100}, GuiIconText(ICON_EXIT, "Close Window"), "Do you really want to exit?", "YES;NO");
            if ((result == 0) || (result == 2))
                showExit = false;
            else if (result == 1) {
                disconnectPSXMSFS(flags);
                deleteFlagsPSXMSFS(flags);
                freeLogBuffer(LogBuffer);
                state.Connect = false;
                exitWindow = true;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
