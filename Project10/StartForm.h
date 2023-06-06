#pragma once

#include <Windows.h>
#include <vcclr.h>
#include "GameForm.h"

using namespace System;
using namespace System::Windows::Forms;

ref class StartForm : public Form
{
private:
    ComboBox^ gameModeComboBox;
    ComboBox^ boardSizeComboBox;
    ComboBox^ colorComboBox;
    Button^ startButton;
    GameForm^ gameForm;

public:
    StartForm();

private:
    void OnGameModeChanged(Object^ sender, EventArgs^ e);
    void OnBoardSizeChanged(Object^ sender, EventArgs^ e);
    void OnColorChanged(Object^ sender, EventArgs^ e);
    void OnStartButtonClick(Object^ sender, EventArgs^ e);
};

