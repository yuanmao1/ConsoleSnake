#pragma once
#include <iostream>
#include <vector>
#include<string>
#include <Windows.h>
#include <conio.h>

class FigureEngine {
private:
    int rows, cols;
    std::vector<std::string> figure;
    using CallbackFunction = void(*)();  // 定义回调函数类型
    using KeyCallbackFunction = void(*)(char);  // 定义按键回调函数类型
    std::vector<CallbackFunction> callbacks;  // 更改为存储函数指针的向量
    std::vector<KeyCallbackFunction> keyCallbacks;  // 按键回调函数
    bool isGameOver;

public:
    FigureEngine(int rows, int cols);
    void print();
    void clear();
    void setChar(int row, int col, char c);
    char getChar(int row, int col);
    void setCallback(CallbackFunction callback);  // 设置回调函数
    bool run();
    void deleteCallback(CallbackFunction callback);  // 删除回调函数
    void deleteKeyCallback(KeyCallbackFunction keyCallback);  // 删除按键回调函数
    void setKeyCallback(KeyCallbackFunction keyCallback);  // 按键回调函数
    void gameOver();
};
