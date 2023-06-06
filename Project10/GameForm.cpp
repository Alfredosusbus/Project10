#include "GameForm.h"
#include "GameForm.h"

GameForm::GameForm(int size, bool twoPlayerMode)
{
    boardSize = size;
    boardAI = new bool[boardSize * boardSize];
    boardPlayer = new bool[boardSize * boardSize];
    ClearBoards();
    this->ClientSize = Drawing::Size(boardSize * cellSize, boardSize * cellSize);
    this->Text = "П'ять у ряд";
    isPlayerRed = true;
    isTwoPlayerMode = twoPlayerMode;

    this->Paint += gcnew PaintEventHandler(this, &GameForm::OnPaint);
    this->MouseDown += gcnew MouseEventHandler(this, &GameForm::OnMouseDown);

    this->BackColor = Color::White;
}

GameForm::~GameForm()
{
    delete[] boardAI;
    delete[] boardPlayer;
}

void GameForm::OnPaint(Object^ sender, PaintEventArgs^ e)
{
    // Function implementation
    Graphics^ g = e->Graphics;

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            int x = i * cellSize;
            int y = j * cellSize;

            if (boardAI[i + j * boardSize])
            {
                // Малюємо нолик
                g->DrawEllipse(Pens::Blue, x, y, cellSize, cellSize);
            }
            else if (boardPlayer[i + j * boardSize])
            {
                // Малюємо хрестик
                g->DrawLine(Pens::Red, x, y, x + cellSize, y + cellSize);
                g->DrawLine(Pens::Red, x + cellSize, y, x, y + cellSize);
            }
            else
            {
                // Малюємо пусту клітинку
                g->FillEllipse(Brushes::Gray, x, y, cellSize, cellSize);
            }
        }
    }
}

void GameForm::OnMouseDown(Object^ sender, MouseEventArgs^ e)
{
    // Function implementation
    int i = e->X / cellSize;
    int j = e->Y / cellSize;

    if (i >= 0 && i < boardSize && j >= 0 && j < boardSize)
    {
        int index = i + j * boardSize;

        if (boardAI[index] || boardPlayer[index])
            return;

        if (isPlayerRed)
        {
            boardPlayer[index] = true;
        }
        else if (isTwoPlayerMode)
        {
            boardAI[index] = true;
        }
        this->Invalidate();

        if (CheckWin(i, j))
        {
            if (isPlayerRed)
                MessageBox::Show("Перемога червоного гравця!");
            else if (isTwoPlayerMode)
                MessageBox::Show("Перемога зеленого гравця!");
            else
                MessageBox::Show("Перемога синього гравця!");

            ClearBoards();
        }
        else if (CheckDraw())
        {
            MessageBox::Show("Гра закінчилася нічиєю!");
            ClearBoards();
        }
        else
        {
            isPlayerRed = !isPlayerRed;
            if (!isPlayerRed && !isTwoPlayerMode)
            {
                MakeAIMove();
            }
        }
    }
}

bool GameForm::CheckWin(int i, int j)
{
    // Function implementation
    int count = 0;
    for (int k = 0; k < boardSize; k++)
    {
        if (boardAI[k + j * boardSize])
            count++;
        else
            count = 0;

        if (count == 5)
            return true;
    }

    count = 0;
    for (int k = 0; k < boardSize; k++)
    {
        if (boardAI[i + k * boardSize])
            count++;
        else
            count = 0;

        if (count == 5)
            return true;
    }

    count = 0;
    int startRow = i - min(i, j);
    int startCol = j - min(i, j);
    while (startRow < boardSize && startCol < boardSize)
    {
        if (boardAI[startRow + startCol * boardSize])
            count++;
        else
            count = 0;

        if (count == 5)
            return true;

        startRow++;
        startCol++;
    }

    count = 0;
    startRow = i + min(boardSize - i - 1, j);
    startCol = j - min(boardSize - i - 1, j);
    while (startRow >= 0 && startCol < boardSize)
    {
        if (boardAI[startRow + startCol * boardSize])
            count++;
        else
            count = 0;

        if (count == 5)
            return true;

        startRow--;
        startCol++;
    }

    count = 0;
    for (int k = 0; k < boardSize; k++)
    {
        if (boardPlayer[k + j * boardSize])
            count++;
        else
            count = 0;

        if (count == 5)
            return true;
    }

    count = 0;
    for (int k = 0; k < boardSize; k++)
    {
        if (boardPlayer[i + k * boardSize])
            count++;
        else
            count = 0;

        if (count == 5)
            return true;
    }

    count = 0;
    startRow = i - min(i, j);
    startCol = j - min(i, j);
    while (startRow < boardSize && startCol < boardSize)
    {
        if (boardPlayer[startRow + startCol * boardSize])
            count++;
        else
            count = 0;

        if (count == 5)
            return true;

        startRow++;
        startCol++;
    }

    count = 0;
    startRow = i + min(boardSize - i - 1, j);
    startCol = j - min(boardSize - i - 1, j);
    while (startRow >= 0 && startCol < boardSize)
    {
        if (boardPlayer[startRow + startCol * boardSize])
            count++;
        else
            count = 0;

        if (count == 5)
            return true;

        startRow--;
        startCol++;
    }

    return false;
}

bool GameForm::CheckDraw()
{
    // Function implementation
    for (int i = 0; i < boardSize * boardSize; i++)
    {
        if (!boardAI[i] && !boardPlayer[i])
            return false;
    }

    int aiCount = 0;
    int playerCount = 0;
    for (int i = 0; i < boardSize * boardSize; i++)
    {
        if (boardAI[i])
            aiCount++;
        if (boardPlayer[i])
            playerCount++;
    }

    return (aiCount == 5 && playerCount == 5);
}

void GameForm::MakeAIMove()
{
    // Function implementation
    int index = MiniMax();
    boardAI[index] = true;
    this->Invalidate();

    int aiRow = index % boardSize;
    int aiCol = index / boardSize;

    if (CheckWin(aiRow, aiCol))
    {
        MessageBox::Show("AI Wins!");
        ClearBoards();
    }
    else
    {
        isPlayerRed = !isPlayerRed;
    }
}

int GameForm::MiniMax()
{
    // Function implementation
    int bestScore = -1000;
    int bestMove = -1;
    for (int i = 0; i < boardSize * boardSize; i++)
    {
        if (!boardAI[i] && !boardPlayer[i])
        {
            boardAI[i] = true;
            int score = Mini(boardPlayer, boardAI, 0, false);
            boardAI[i] = false;
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

int GameForm::Mini(bool* playerBoard, bool* aiBoard, int depth, bool isMax)
{
    // Function implementation
    if (CheckWin(boardSize, boardSize) || depth == 3)
    {
        return Evaluate(playerBoard, aiBoard);
    }

    if (isMax)
    {
        int bestScore = -1000;
        for (int i = 0; i < boardSize * boardSize; i++)
        {
            if (!playerBoard[i] && !aiBoard[i])
            {
                aiBoard[i] = true;
                int score = Mini(playerBoard, aiBoard, depth + 1, false);
                aiBoard[i] = false;
                bestScore = max(bestScore, score);
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int i = 0; i < boardSize * boardSize; i++)
        {
            if (!playerBoard[i] && !aiBoard[i])
            {
                playerBoard[i] = true;
                int score = Mini(playerBoard, aiBoard, depth + 1, true);
                playerBoard[i] = false;
                bestScore = min(bestScore, score);
            }
        }
        return bestScore;
    }
}

int GameForm::Evaluate(bool* playerBoard, bool* aiBoard)
{
    // Function implementation
    int aiScore = 0;
    int playerScore = 0;

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            int index = i + j * boardSize;

            // Check horizontal
            if (i < boardSize - 4)
            {
                int aiCount = 0;
                int playerCount = 0;
                for (int k = 0; k < 5; k++)
                {
                    if (aiBoard[index + k])
                        aiCount++;
                    if (playerBoard[index + k])
                        playerCount++;
                }
                aiScore += GetScore(aiCount, playerCount);
                playerScore += GetScore(playerCount, aiCount);
            }

            // Check vertical
            if (j < boardSize - 4)
            {
                int aiCount = 0;
                int playerCount = 0;
                for (int k = 0; k < 5; k++)
                {
                    if (aiBoard[index + k * boardSize])
                        aiCount++;
                    if (playerBoard[index + k * boardSize])
                        playerCount++;
                }
                aiScore += GetScore(aiCount, playerCount);
                playerScore += GetScore(playerCount, aiCount);
            }

            // Check diagonal (top-left to bottom-right)
            if (i < boardSize - 4 && j < boardSize - 4)
            {
                int aiCount = 0;
                int playerCount = 0;
                for (int k = 0; k < 5; k++)
                {
                    if (aiBoard[index + k + k * boardSize])
                        aiCount++;
                    if (playerBoard[index + k + k * boardSize])
                        playerCount++;
                }
                aiScore += GetScore(aiCount, playerCount);
                playerScore += GetScore(playerCount, aiCount);
            }

            // Check diagonal (top-right to bottom-left)
            if (i >= 4 && j < boardSize - 4)
            {
                int aiCount = 0;
                int playerCount = 0;
                for (int k = 0; k < 5; k++)
                {
                    if (aiBoard[index - k + k * boardSize])
                        aiCount++;
                    if (playerBoard[index - k + k * boardSize])
                        playerCount++;
                }
                aiScore += GetScore(aiCount, playerCount);
                playerScore += GetScore(playerCount, aiCount);
            }
        }
    }

    return aiScore - playerScore;
}

int GameForm::GetScore(int aiCount, int playerCount)
{
    // Function implementation
    if (aiCount == 5)
        return 100;
    else if (aiCount == 4 && playerCount == 0)
        return 10;
    else if (aiCount == 3 && playerCount == 0)
        return 5;
    else if (aiCount == 2 && playerCount == 0)
        return 2;

    if (playerCount == 5)
        return -100;
    else if (playerCount == 4 && aiCount == 0)
        return -10;
    else if (playerCount == 3 && aiCount == 0)
        return -5;
    else if (playerCount == 2 && aiCount == 0)
        return -2;

    return 0;
}

void GameForm::ClearBoards()
{
    // Function implementation
    for (int i = 0; i < boardSize * boardSize; i++)
    {
        boardAI[i] = false;
        boardPlayer[i] = false;
    }

    isPlayerRed = true;
    this->Invalidate();
}


