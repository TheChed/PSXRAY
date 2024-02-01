/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
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

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    bool TextBox000EditMode = false;
    char TextBox000Text[128] = "SAMPLE TEXT";
    bool TextBox003EditMode = false;
    char TextBox003Text[128] = "127.0.0.1";
    bool TextBox006EditMode = false;
    char TextBox006Text[128] = "127.0.0.1";
    bool TextBox007EditMode = false;
    char TextBox007Text[128] = "127.0.0.1";
    bool TextBox008EditMode = false;
    char TextBox008Text[128] = "10747";
    bool TextBox010EditMode = false;
    char TextBox010Text[128] = "10749";
    bool CheckBoxEx014Checked = false;
    bool Spinner017EditMode = false;
    int Spinner017Value = 0;
    bool CheckBoxEx017Checked = false;
    bool CheckBoxEx018Checked = false;
    bool CheckBoxEx018Checked = false;
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (GuiTextBox((Rectangle){ 0, 40, 400, 176 }, TextBox000Text, 128, TextBox000EditMode)) TextBox000EditMode = !TextBox000EditMode;
            GuiGroupBox((Rectangle){ 0, 224, 400, 104 }, "IP ADDRESSES");
            GuiLabel((Rectangle){ 24, 232, 120, 24 }, "PSX Main Server:");
            if (GuiTextBox((Rectangle){ 128, 232, 120, 24 }, TextBox003Text, 128, TextBox003EditMode)) TextBox003EditMode = !TextBox003EditMode;
            GuiLabel((Rectangle){ 24, 264, 120, 24 }, "PSX Boost Server:");
            GuiLabel((Rectangle){ 24, 296, 120, 24 }, "MSFS server:");
            if (GuiTextBox((Rectangle){ 128, 264, 120, 24 }, TextBox006Text, 128, TextBox006EditMode)) TextBox006EditMode = !TextBox006EditMode;
            if (GuiTextBox((Rectangle){ 128, 296, 120, 24 }, TextBox007Text, 128, TextBox007EditMode)) TextBox007EditMode = !TextBox007EditMode;
            if (GuiTextBox((Rectangle){ 256, 232, 56, 24 }, TextBox008Text, 128, TextBox008EditMode)) TextBox008EditMode = !TextBox008EditMode;
            GuiLabel((Rectangle){ 248, 232, 16, 24 }, ":");
            if (GuiTextBox((Rectangle){ 256, 264, 56, 24 }, TextBox010Text, 128, TextBox010EditMode)) TextBox010EditMode = !TextBox010EditMode;
            GuiLabel((Rectangle){ 248, 264, 16, 24 }, ":");
            GuiGroupBox((Rectangle){ 0, 336, 400, 128 }, "Flags");
            GuiCheckBox((Rectangle){ 16, 384, 24, 24 }, "TCAS inject", &CheckBoxEx014Checked);
            if (GuiSpinner((Rectangle){ 104, 344, 72, 24 }, "Log verbosity: ", &Spinner017Value, 0, 100, Spinner017EditMode)) Spinner017EditMode = !Spinner017EditMode;
            GuiStatusBar((Rectangle){ 0, 456, 400, 12 }, "SAMPLE TEXT");
            GuiCheckBox((Rectangle){ 208, 384, 24, 24 }, "PSX slave to MSFS", &CheckBoxEx017Checked);
            GuiCheckBox((Rectangle){ 16, 424, 24, 24 }, "Inject Elevation to MSFS", &CheckBoxEx018Checked);
            GuiCheckBox((Rectangle){ 208, 424, 24, 24 }, "Inhib crash detection", &CheckBoxEx018Checked);
            GuiLabel((Rectangle){ 184, 344, 208, 24 }, "1= Very Verbose. 3=Error only");
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

