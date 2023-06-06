#pragma once

#include <Windows.h>
#include <time.h>
#include <cstdlib>


using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

ref class GameForm : public Form
{
private:
    int boardSize;
    const int cellSize = 40;
    bool* boardAI;
    bool* boardPlayer;
    bool isPlayerRed;
    bool isTwoPlayerMode;

public:
    GameForm(int size, bool twoPlayerMode);
    ~GameForm();

private:
    void OnPaint(Object^ sender, PaintEventArgs^ e);
    void OnMouseDown(Object^ sender, MouseEventArgs^ e);
    bool CheckWin(int i, int j);
    bool CheckDraw();
    void MakeAIMove();
    int MiniMax();
    int Mini(bool* playerBoard, bool* aiBoard, int depth, bool isMax);
    int Evaluate(bool* playerBoard, bool* aiBoard);
    int GetScore(int aiCount, int playerCount);
    void ClearBoards();
};

