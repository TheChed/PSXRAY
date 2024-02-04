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
    char TextBox000Text[128];
    bool TextBox003EditMode;
    char TextBox003Text[128];
    bool TextBox006EditMode;
    char TextBox006Text[128];
    bool TextBox007EditMode;
    char TextBox007Text[128];
    bool TextBox008EditMode;
    char TextBox008Text[128];
    bool TextBox010EditMode;
    char TextBox010Text[128];
    bool CheckBoxEx014Checked;
    bool Spinner017EditMode;
    int Spinner017Value;
    bool CheckBoxEx017Checked;
    bool CheckBoxEx018Checked;
    bool CheckBoxEx019Checked;
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

    strcpy(state.TextBox000Text, "LOG MESSAGES");
    state.TextBox003EditMode = false;
    strcpy(state.TextBox003Text, "127.0.0.1");
    state.TextBox006EditMode = false;
    strcpy(state.TextBox006Text, "127.0.0.1");
    state.TextBox007EditMode = false;
    strcpy(state.TextBox007Text, "127.0.0.1");
    state.TextBox008EditMode = false;
    strcpy(state.TextBox008Text, "10747");
    state.TextBox010EditMode = false;
    strcpy(state.TextBox010Text, "10749");
    state.CheckBoxEx014Checked = false;
    state.Spinner017EditMode = false;
    state.Spinner017Value = 0;
    state.CheckBoxEx017Checked = false;
    state.CheckBoxEx018Checked = false;
    state.CheckBoxEx019Checked = false;
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
    if (GuiTextBox((Rectangle){128, 232, 120, 24}, state->TextBox003Text, 128, state->TextBox003EditMode))
        state->TextBox003EditMode = !state->TextBox003EditMode;
    GuiLabel((Rectangle){24, 264, 120, 24}, "PSX Boost Server:");
    GuiLabel((Rectangle){24, 296, 120, 24}, "MSFS server:");
    if (GuiTextBox((Rectangle){128, 264, 120, 24}, state->TextBox006Text, 128, state->TextBox006EditMode))
        state->TextBox006EditMode = !state->TextBox006EditMode;
    if (GuiTextBox((Rectangle){128, 296, 120, 24}, state->TextBox007Text, 128, state->TextBox007EditMode))
        state->TextBox007EditMode = !state->TextBox007EditMode;
    if (GuiTextBox((Rectangle){256, 232, 56, 24}, state->TextBox008Text, 128, state->TextBox008EditMode))
        state->TextBox008EditMode = !state->TextBox008EditMode;
    GuiLabel((Rectangle){248, 232, 16, 24}, ":");
    if (GuiTextBox((Rectangle){256, 264, 56, 24}, state->TextBox010Text, 128, state->TextBox010EditMode))
        state->TextBox010EditMode = !state->TextBox010EditMode;
    GuiLabel((Rectangle){248, 264, 16, 24}, ":");
    GuiGroupBox((Rectangle){5, 336, 400, 128}, "Flags");
    GuiCheckBox((Rectangle){16, 384, 24, 24}, "TCAS inject", &state->CheckBoxEx014Checked);
    if (GuiSpinner((Rectangle){104, 344, 72, 24}, "Log verbosity: ", &state->Spinner017Value, 1, 4, state->Spinner017EditMode))
        state->Spinner017EditMode = !state->Spinner017EditMode;
    GuiCheckBox((Rectangle){208, 384, 24, 24}, "PSX slave to MSFS", &state->CheckBoxEx017Checked);
    GuiCheckBox((Rectangle){16, 424, 24, 24}, "Inject Elevation to MSFS", &state->CheckBoxEx018Checked);
    GuiCheckBox((Rectangle){208, 424, 24, 24}, "Inhib crash detection", &state->CheckBoxEx019Checked);
    GuiLabel((Rectangle){184, 344, 208, 24}, "1= Very Verbose. 4=Error only");
    GuiSetState(STATE_NORMAL);
    GuiLabel((Rectangle){5,469, 100, 20}, "Connected");
    GuiTextBox((Rectangle){5, 5, 400, 200}, state->TextBox000Text, 128, false);
    GuiToggleSlider((Rectangle){ 85, 469, 100, 20 }, "OFF;ON",&state->Connected);
    if (GuiButton((Rectangle){(float)GetScreenWidth() - 55, 469, 50, 20}, "Quit"))
        *exit = true;
    GuiStatusBar((Rectangle){0, (float)GetScreenHeight() - 20, (float)GetScreenWidth(), 20}, "This is a status bar");
}

#endif // GUI_LAYOUT_NAME_IMPLEMENTATION
