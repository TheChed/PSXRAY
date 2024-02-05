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

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h> // Required for: strcpy()

#ifndef GUI_LAYOUT_NAME_H
#define GUI_LAYOUT_NAME_H

typedef struct {
    char TE_LOG[128];
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
    int LOG_VALUE;
    bool CB_SLAVE;
    bool CB_ELEV;
    bool CB_CRASH;
    int Connected;

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiLayoutNameState;

GuiLayoutNameState InitGuiLayoutName(void);
void GuiLayoutName(GuiLayoutNameState *state, bool *exit);

#endif // GUI_LAYOUT_NAME_H

/***********************************************************************************
 *
 *   GUI_LAYOUT_NAME IMPLEMENTATION
 *
 ************************************************************************************/
#if defined(GUI_LAYOUT_NAME_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiLayoutNameState InitGuiLayoutName(void)
{
    GuiLayoutNameState state = {0};

    strcpy(state.TE_LOG, "LOG MESSAGES");
    strcpy(state.TE_PSXMAIN, "127.0.0.1");
    state.TE_PSXMAIN_EDIT = false;
    strcpy(state.TE_PSXBOOST, "127.0.0.1");
    state.TE_PSXBOOST_EDIT = false;
    strcpy(state.TE_MSFS, "127.0.0.1");
    state.TE_MSFS_EDIT = false;
    strcpy(state.TE_PSXPORT, "10747");
    state.TE_PSXPORT_EDIT = false;
    strcpy(state.TE_BOOSTPORT, "10749");
    state.TE_BOOSTPORT_EDIT = false;
    state.CB_TCAS = false;
    state.LOG_VALUE = 0;
    state.CB_SLAVE = false;
    state.CB_ELEV = false;
    state.CB_CRASH = false;
    state.Connected = false;

    // Custom variables initialization

    return state;
}

void GuiLayoutName(GuiLayoutNameState *state, bool *exit)
{
    if (state->Connected)
        GuiSetState(STATE_DISABLED);
    GuiGroupBox((Rectangle){5, 224, 400, 104}, "IP ADDRESSES");

    GuiLabel((Rectangle){24, 232, 120, 24}, "PSX Main Server:");
    if (GuiTextBox((Rectangle){128, 232, 120, 24}, state->TE_PSXMAIN, 128, state->TE_PSXMAIN_EDIT)) {
        state->TE_PSXMAIN_EDIT = !state->TE_PSXMAIN_EDIT;
    }

    if (GuiTextBox((Rectangle){256, 232, 56, 24}, state->TE_PSXPORT, 128, state->TE_PSXPORT_EDIT)) {
        state->TE_PSXPORT_EDIT = !state->TE_PSXPORT_EDIT;
    }

    GuiLabel((Rectangle){24, 264, 120, 24}, "PSX Boost Server:");
    if (GuiTextBox((Rectangle){128, 264, 120, 24}, state->TE_PSXBOOST, 128, state->TE_PSXBOOST_EDIT)) {
        state->TE_PSXBOOST_EDIT = !state->TE_PSXBOOST_EDIT;
    }

    if (GuiTextBox((Rectangle){256, 264, 56, 24}, state->TE_BOOSTPORT, 128,state->TE_BOOSTPORT_EDIT)) {
        state->TE_BOOSTPORT_EDIT = !state->TE_BOOSTPORT_EDIT;
    }

    GuiLabel((Rectangle){24, 296, 120, 24}, "MSFS server:");

    if(GuiTextBox((Rectangle){128, 296, 120, 24}, state->TE_MSFS, 128,state->TE_MSFS_EDIT)){
        state->TE_MSFS_EDIT = !state->TE_MSFS_EDIT;
    }

    GuiLabel((Rectangle){248, 232, 16, 24}, ":");
    GuiLabel((Rectangle){248, 264, 16, 24}, ":");
    GuiGroupBox((Rectangle){5, 336, 400, 128}, "Flags");
    GuiCheckBox((Rectangle){16, 384, 24, 24}, "TCAS inject", &state->CB_TCAS);
    GuiSpinner((Rectangle){104, 344, 72, 24}, "Log verbosity: ", &state->LOG_VALUE, 1, 4, false);
    GuiCheckBox((Rectangle){208, 384, 24, 24}, "PSX slave to MSFS", &state->CB_SLAVE);
    GuiCheckBox((Rectangle){16, 424, 24, 24}, "Inject Elevation to MSFS", &state->CB_ELEV);
    GuiCheckBox((Rectangle){208, 424, 24, 24}, "Inhib crash detection", &state->CB_CRASH);
    GuiLabel((Rectangle){184, 344, 208, 24}, "1= Very Verbose. 3=Error only");
    GuiSetState(STATE_NORMAL);
    GuiTextBox((Rectangle){5, 5, 400, 200}, state->TE_LOG, 128, false);
    GuiLabel((Rectangle){5, 469, 70, 20}, "Connected");
    // GuiToggleSlider((Rectangle){ 60, 469, 100, 20 }, "OFF;ON",&state->Connected);
    if (GuiButton((Rectangle){(float)GetScreenWidth() - 55, 469, 50, 20}, "Quit"))
        *exit = true;
    GuiStatusBar((Rectangle){0, (float)GetScreenHeight() - 20, (float)GetScreenWidth(), 20}, "This is a status bar");
    GuiToggleSlider((Rectangle){75, 469, 100, 20}, "OFF;ON", &state->Connected);
}

#endif // GUI_LAYOUT_NAME_IMPLEMENTATION
