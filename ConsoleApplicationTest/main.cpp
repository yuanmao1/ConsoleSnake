#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "FigureEngine.h"
#include<chrono>
#include<cstdlib>


int row = 20, col = 40;

FigureEngine figure(row, col);

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Snake {
    int x, y;
    Snake* nextBodyPart;
    Snake(int x, int y) : x(x), y(y), nextBodyPart(nullptr) {}
};

Snake* head = new Snake(10, 10);
Snake* tail = head;
void showSnake() {
    Snake* current = head;
    while (current != nullptr) {
        figure.setChar(current->x, current->y, 'O');
        current = current->nextBodyPart;
    }
}

int direction = -1;
int tempDirection1 = -1;
int tempDirection2 = -1;
void dfs(Snake* current) {
    if (current->nextBodyPart != nullptr) {
        dfs(current->nextBodyPart);
        current->nextBodyPart->x = current->x;
        current->nextBodyPart->y = current->y;
    }
    else figure.setChar(current->x, current->y, ' ');
}

int score = 0;

int64_t lastTime = 0;
int speed = 130;
void moveSnake() {
    const auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if (currentTime - lastTime < speed) return;
    direction = tempDirection1;
    tempDirection1 = tempDirection2;
    lastTime = currentTime;
    dfs(head);
    if (direction == 0) {
        head->x--;
        if (head->x == 0 && speed != 100) head->x = row - 1;
        else if (head->x == 0) figure.gameOver();
    }
    if (direction == 1) {
        head->x++;
        if (head->x == row && speed != 100) head->x = 1;
        else if (head->x == row) figure.gameOver();
    }
    if (direction == 2) {
        head->y -= 2;
        if (head->y == 0 && speed != 100) head->y = col - 2;
        else if (head->y == 0) figure.gameOver();
    }
    if (direction == 3) {
        head->y += 2;
        if (head->y == col && speed != 100) head->y = 2;
        else if (head->y == col) figure.gameOver();
    }
    if (figure.getChar(head->x, head->y) == 'O') {
        //game over
        Sleep(1000);
        figure.gameOver();
    }
    else if (figure.getChar(head->x, head->y) == 'F') {
        //eat food
        score++;
        figure.setChar(head->x, head->y, ' ');
        Snake* newBodyPart = new Snake(head->x, head->y);
        tail->nextBodyPart = newBodyPart;
        tail = newBodyPart;
        figure.generateFood();
    }
}

void directionChange(char key) {
    if (toupper(key) == 'W' && direction != 1 && tempDirection1 == direction) tempDirection1 = 0, tempDirection2 = 0;
    else if (toupper(key) == 'W' && tempDirection1 != direction && tempDirection1 != 1) tempDirection2 = 0;
    if (toupper(key) == 'S' && direction != 0 && tempDirection1 == direction) tempDirection1 = 1, tempDirection2 = 1;
    else if (toupper(key) == 'S' && tempDirection1 != direction && tempDirection1 != 0) tempDirection2 = 1;
    if (toupper(key) == 'A' && direction != 3 && tempDirection1 == direction) tempDirection1 = 2, tempDirection2 = 2;
    else if (toupper(key) == 'A' && tempDirection1 != direction && tempDirection1 != 3) tempDirection2 = 2;
    if (toupper(key) == 'D' && direction != 2 && tempDirection1 == direction) tempDirection1 = 3, tempDirection2 = 3;
    else if (toupper(key) == 'D' && tempDirection1 != direction && tempDirection1 != 2) tempDirection2 = 3;
}

void printScore() {
    if (figure.run())std::cout << "Score: " << score << std::endl;
}

void startPage() {
    std::string str1 = " Hello, Welcome to Snake Game!";
    std::string str2 = " Press up or down to change the model,";
    std::string str3 = " and press Enter to start the game.";
    std::string model1 = "eazy";
    std::string model2 = "normal";
    std::string model3 = "hard";
    int i = 1;
    for (char c : str1) figure.setChar(1, i++, c);
    i = 1;
    for (char c : str2) figure.setChar(2, i++, c);
    i = 1;
    for (char c : str3) figure.setChar(3, i++, c);
    i = 3;
    for (char c : model1) figure.setChar(4, i++, c);
    i = 3;
    for (char c : model2) figure.setChar(5, i++, c);
    i = 3;
    for (char c : model3) figure.setChar(6, i++, c);
}

int pos = 4;
bool gameStart = false;
void model(char key) {
    if (key == 72 && pos != 4) {
        figure.setChar(pos, 1, ' ');
        figure.setChar(pos, 2, ' ');
        pos--;
    }
    if (key == 80 && pos != 6) {
        figure.setChar(pos, 1, ' ');
        figure.setChar(pos, 2, ' ');
        pos++;
    }
    if (key == 13) {
        if (pos == 4) speed = 200;
        if (pos == 5) speed = 130;
        if (pos == 6) speed = 100;
        gameStart = true;
    }
}

void showArrow() {
    if (pos == 4) {
        figure.setChar(4, 1, '-');
        figure.setChar(4, 2, '>');
    }
    if (pos == 5) {
        figure.setChar(5, 1, '-');
        figure.setChar(5, 2, '>');
    }
    if (pos == 6) {
        figure.setChar(6, 1, '-');
        figure.setChar(6, 2, '>');
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    system("title Snake Game");
    startPage();
    figure.setKeyCallback(model);
    figure.setCallback(showArrow);
    while (!gameStart) {
        gotoXY(0, 0);
        figure.print();
    }

    figure.clear();
    figure.deleteCallback(showArrow);
    figure.deleteKeyCallback(model);

    figure.generateFood();
    figure.setKeyCallback(directionChange);
    figure.setCallback(moveSnake);
    figure.setCallback(showSnake);
    figure.setCallback(printScore);
    while (figure.run()) {
        gotoXY(0, 0);
        figure.print();
    }
    std::cout << "You score is : " << score << std::endl;
    system("pause");
    return 0;
}