#include "FigureEngine.h"

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

FigureEngine::FigureEngine(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->isGameOver = false;
    this->figure = std::vector<std::string>(rows + 1, std::string(cols + 1, ' '));
    for (int i = 0; i <= rows; i++) {
        figure[i][0] = '#';
        figure[i][cols] = '#';
    }
    for (int j = 0; j <= cols; j++) {
        figure[0][j] = '#';
        figure[rows][j] = '#';
    }
    HideCursor();
}

void FigureEngine::clear() {
    this->figure = std::vector<std::string>(rows + 1, std::string(cols + 1, ' '));
    for (int i = 0; i <= rows; i++) {
        figure[i][0] = '#';
        figure[i][cols] = '#';
    }
    for (int j = 0; j <= cols; j++) {
        figure[0][j] = '#';
        figure[rows][j] = '#';
    }
}

void FigureEngine::setCallback(CallbackFunction callback) {
    this->callbacks.push_back(callback);
}

void FigureEngine::print() {
    for (int i = 0; i <= rows; i++) {
        std::cout << figure[i];
        std::cout << '\n';
    }
    for (auto callback : callbacks) {
        callback();
    }
    char c;
    if (_kbhit()) {
        c = _getch();
        for (auto keyCallback : keyCallbacks) {
            keyCallback(c);
        }
    }
}

char FigureEngine::getChar(int row, int col) {
    if (row > 0 && row <= rows && col > 0 && col <= cols) {
        return figure[row][col];
    }
    return '0';
}

void FigureEngine::setKeyCallback(KeyCallbackFunction keyCallback) {
    this->keyCallbacks.push_back(keyCallback);
}

void FigureEngine::deleteCallback(CallbackFunction callback) {
    this->callbacks.erase(std::remove(this->callbacks.begin(), this->callbacks.end(), callback), this->callbacks.end());
}

void FigureEngine::deleteKeyCallback(KeyCallbackFunction keyCallback) {
    this->keyCallbacks.erase(std::remove(this->keyCallbacks.begin(), this->keyCallbacks.end(), keyCallback), this->keyCallbacks.end());
}

void FigureEngine::setChar(int row, int col, char c) {
    if (row > 0 && row <= rows && col > 0 && col <= cols) {
        figure[row][col] = c;
    }
}

bool FigureEngine::run() {
    return !this->isGameOver;
}

void FigureEngine::gameOver() {
    this->isGameOver = true;
    system("cls");
    std::cout << "Game Over!" << std::endl;
    Sleep(500);
}

void FigureEngine::generateFood() {
    std::vector<std::pair<int, int>> emptyCells;

    // 收集所有y坐标为偶数的空白位置
    for (int i = 1; i < rows; ++i) {
        for (int j = 2; j < cols; j += 2) { // 从2开始，步长为2
            if (figure[i][j] == ' ') {
                emptyCells.emplace_back(i, j);
            }
        }
    }

    if (!emptyCells.empty()) {
        std::uniform_int_distribution<size_t> dist(0, emptyCells.size() - 1);
        auto& [x, y] = emptyCells[dist(gen)];
        figure[x][y] = 'F';
    }
    else {
        // TODO: Win
    }
}