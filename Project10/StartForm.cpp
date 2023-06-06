#include "StartForm.h"

StartForm::StartForm()
{
    this->ClientSize = Drawing::Size(250, 200);
    this->Text = "Start Form";

    gameModeComboBox = gcnew ComboBox();
    gameModeComboBox->Location = Drawing::Point(20, 20);
    gameModeComboBox->Size = Drawing::Size(200, 20);
    gameModeComboBox->Items->Add("Player vs. AI");
    gameModeComboBox->Items->Add("Player vs. Player");
    gameModeComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnGameModeChanged);
    this->Controls->Add(gameModeComboBox);

    boardSizeComboBox = gcnew ComboBox();
    boardSizeComboBox->Location = Drawing::Point(20, 60);
    boardSizeComboBox->Size = Drawing::Size(200, 20);
    boardSizeComboBox->Items->Add("10x10");
    boardSizeComboBox->Items->Add("15x15");
    boardSizeComboBox->Items->Add("20x20");
    boardSizeComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnBoardSizeChanged);
    this->Controls->Add(boardSizeComboBox);

    colorComboBox = gcnew ComboBox();
    colorComboBox->Location = Drawing::Point(20, 100);
    colorComboBox->Size = Drawing::Size(200, 20);
    colorComboBox->Items->Add("Black");
    colorComboBox->Items->Add("White");
    colorComboBox->SelectedIndexChanged += gcnew EventHandler(this, &StartForm::OnColorChanged);
    this->Controls->Add(colorComboBox);

    startButton = gcnew Button();
    startButton->Location = Drawing::Point(20, 140);
    startButton->Size = Drawing::Size(200, 30);
    startButton->Text = "Start Game";
    startButton->Enabled = false;
    startButton->Click += gcnew EventHandler(this, &StartForm::OnStartButtonClick);
    this->Controls->Add(startButton);
}

void StartForm::OnGameModeChanged(Object^ sender, EventArgs^ e)
{
    // обробка події OnGameModeChanged
    if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
    {
        startButton->Enabled = true;
    }
    else
    {
        startButton->Enabled = false;
    }
}

void StartForm::OnBoardSizeChanged(Object^ sender, EventArgs^ e)
{
    // обробка події OnBoardSizeChanged
    if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
    {
        startButton->Enabled = true;
    }
    else
    {
        startButton->Enabled = false;
    }
}

void StartForm::OnColorChanged(Object^ sender, EventArgs^ e)
{
    // обробка події OnColorChanged
    if (gameModeComboBox->SelectedIndex >= 0 && boardSizeComboBox->SelectedIndex >= 0 && colorComboBox->SelectedIndex >= 0)
    {
        startButton->Enabled = true;
    }
    else
    {
        startButton->Enabled = false;
    }
}

void StartForm::OnStartButtonClick(Object^ sender, EventArgs^ e)
{
    // обробка події OnStartButtonClick
    int boardSize = 0;
    if (boardSizeComboBox->SelectedIndex == 0)
    {
        boardSize = 10;
    }
    else if (boardSizeComboBox->SelectedIndex == 1)
    {
        boardSize = 15;
    }
    else if (boardSizeComboBox->SelectedIndex == 2)
    {
        boardSize = 20;
    }

    bool twoPlayerMode = (gameModeComboBox->SelectedIndex == 1);

    gameForm = gcnew GameForm(boardSize, twoPlayerMode);

    if (colorComboBox->SelectedIndex == 0)
    {
        gameForm->BackColor = Drawing::Color::Black;
    }
    else if (colorComboBox->SelectedIndex == 1)
    {
        gameForm->BackColor = Drawing::Color::White;
    }

    gameForm->Show();
}

