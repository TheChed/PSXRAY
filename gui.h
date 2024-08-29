/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_LAYOUT_NAME_IMPLEMENTATION
*       #include "gui_layout_name.h"
4
*       INIT: GuiLayoutNameState state = InitGuiLayoutName();
*       DRAW: GuiLayoutName(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include <stdio.h>
#include "raylib.h"

#include "PSXMSFS.h"
// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h> // Required for: strcpy()

typedef struct {
    char TE_LOG[4192];
    bool TE_LOGEdit;
    char TE_PSXMAIN[128];
    bool TE_PSXMAIN_EDIT;
    char TE_PSXBOOST[128];
    bool TE_PSXBOOST_EDIT;
    char TE_MSFS[128];
    bool TE_MSFS_EDIT;
    char TE_PSXPORT[128];
    bool TE_PSXPORT_EDIT;
    char TE_BOOSTPORT[128];
    bool TE_BOOSTPORT_EDIT;
    bool CB_TCAS;
    bool CB_ONLINE;
    int LOG_VALUE;
    bool CB_SLAVE;
    bool CB_ELEV;
    bool CB_CRASH;
    int Connect;
    char statusBarText[128];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiLayoutNameState;

#define TEXTLENGTH 4192
typedef enum {
    DISCONNECTED,
    CONNECTING,
    CONNECTED
} Status;

GuiLayoutNameState InitGuiLayout(FLAGS *flags);
void drawLayout(GuiLayoutNameState *state, bool *exit, ACFT *A, Status status);

/***********************************************************************************
 *
 *   GUI_LAYOUT_NAME IMPLEMENTATION
 *
 ************************************************************************************/

#include "raygui.h"

GuiLayoutNameState InitGuiLayout(FLAGS *flags)
{
    GuiLayoutNameState state = {0};

    servers S = getServersInfo(flags);
    unsigned int switches = getSwitch(flags);

    strcpy(state.TE_LOG, "");
    strcpy(state.TE_PSXMAIN, S.PSXIP);
    state.TE_PSXMAIN_EDIT = false;
    strcpy(state.TE_PSXBOOST, S.BOOSTIP);
    state.TE_PSXBOOST_EDIT = false;
    strcpy(state.TE_MSFS, S.MSFSIP);
    state.TE_MSFS_EDIT = false;
    sprintf(state.TE_PSXPORT, "%d", S.PSXPORT);
    state.TE_PSXPORT_EDIT = false;
    sprintf(state.TE_BOOSTPORT, "%d", S.BOOSTPORT);
    state.TE_BOOSTPORT_EDIT = false;
    state.CB_TCAS = (switches & F_TCAS);
    state.LOG_VALUE = getLogVerbosity(flags);
    state.CB_SLAVE = (switches & F_SLAVE);
    state.CB_ELEV = (switches & F_INJECT);
    state.CB_CRASH = (switches & F_INHIB);
    state.CB_ONLINE = (switches & F_ONLINE);
    state.statusBarText[0] = '\0';
    state.Connect = 0;

    // Custom variables initialization

    return state;
}

void drawLayout(GuiLayoutNameState *state, bool *exit, ACFT *A, Status status)
{

    char statusbuff[128] = {0}, LAT, LONG;
    double lat, longi, minlat, minlong;
    LAT = A->latitude * 180 / PI > 0 ? 'N' : 'S';
    LONG = A->longitude * 180 / PI > 0 ? 'E' : 'W';
    lat = fabs(A->latitude);
    longi = fabs(A->longitude);
    minlat = (lat * 180 / PI - (int)(lat * 180 / PI)) * 60;
    minlong = (longi * 180 / PI - (int)(longi * 180 / PI)) * 60;

    switch (status) {
    case CONNECTED: {
        sprintf(statusbuff, "%c %02d %04.1f\t%c %03d %04.1f \t\tFltDeck Alt: %5d ft \t\t True Hdg: %03d", LAT, (int)(lat * 180 / PI), minlat, LONG, (int)(longi * 180 / PI), minlong, (int)(A->Alt), (int)(A->heading * 180 / PI));
        GuiSetState(STATE_DISABLED);
        break;
    }
    case CONNECTING: {
        strcpy(statusbuff, "CONNECTING...");
        GuiSetState(STATE_DISABLED);
        break;
    }
    case DISCONNECTED: {
        strcpy(statusbuff, "DISCONNECTED");
        break;
    }
    }

    GuiGroupBox((Rectangle){5, 224, 400, 104}, "SERVERS");

    GuiLabel((Rectangle){16, 232, 120, 24}, "PSX Main Server:");
    if (GuiTextBox((Rectangle){128, 232, 120, 24}, state->TE_PSXMAIN, 128, state->TE_PSXMAIN_EDIT)) {
        state->TE_PSXMAIN_EDIT = !state->TE_PSXMAIN_EDIT;
    }

    if (GuiTextBox((Rectangle){256, 232, 56, 24}, state->TE_PSXPORT, 128, state->TE_PSXPORT_EDIT)) {
        state->TE_PSXPORT_EDIT = !state->TE_PSXPORT_EDIT;
    }

    GuiLabel((Rectangle){16, 264, 120, 24}, "PSX Boost Server:");
    if (GuiTextBox((Rectangle){128, 264, 120, 24}, state->TE_PSXBOOST, 128, state->TE_PSXBOOST_EDIT)) {
        state->TE_PSXBOOST_EDIT = !state->TE_PSXBOOST_EDIT;
    }

    if (GuiTextBox((Rectangle){256, 264, 56, 24}, state->TE_BOOSTPORT, 128, state->TE_BOOSTPORT_EDIT)) {
        state->TE_BOOSTPORT_EDIT = !state->TE_BOOSTPORT_EDIT;
    }

    GuiLabel((Rectangle){16, 296, 120, 24}, "MSFS server:");

    if (GuiTextBox((Rectangle){128, 296, 120, 24}, state->TE_MSFS, 128, state->TE_MSFS_EDIT)) {
        state->TE_MSFS_EDIT = !state->TE_MSFS_EDIT;
    }

    GuiLabel((Rectangle){248, 232, 16, 24}, ":");
    GuiLabel((Rectangle){248, 264, 16, 24}, ":");
    GuiGroupBox((Rectangle){5, 336, 400, 128}, "Flags");
    GuiCheckBox((Rectangle){16, 384, 24, 24}, "TCAS inject", &state->CB_TCAS);
    GuiCheckBox((Rectangle){128, 384, 24, 24}, "ONLINE hack", &state->CB_ONLINE);
    GuiCheckBox((Rectangle){240, 384, 24, 24}, "PSX slave to MSFS", &state->CB_SLAVE);
    GuiSpinner((Rectangle){110, 344, 72, 24}, "Log verbosity: ", &state->LOG_VALUE, 1, 4, false);
    GuiLabel((Rectangle){190, 344, 208, 24}, "1= Very Verbose to 4=Error only");
    GuiCheckBox((Rectangle){16, 424, 24, 24}, "Inject Elevation to MSFS", &state->CB_ELEV);
    GuiCheckBox((Rectangle){240, 424, 24, 24}, "Inhib crash detection", &state->CB_CRASH);
    GuiSetState(STATE_NORMAL);
    GuiTextBox((Rectangle){5, 5, 400, 200}, state->TE_LOG,TEXTLENGTH, false);
    GuiLabel((Rectangle){5, 469, 70, 20}, "Connected");
    if (GuiButton((Rectangle){(float)GetScreenWidth() - 55, 469, 50, 20}, "Quit"))
        *exit = true;

    GuiToggleSlider((Rectangle){75, 469, 100, 20}, "NO;YES", &state->Connect);
    GuiStatusBar((Rectangle){0, (float)GetScreenHeight() - 20, (float)GetScreenWidth(), 20}, statusbuff);
}
