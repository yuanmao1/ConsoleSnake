#pragma once
#include <iostream>
#include <vector>
#include<string>
#include <Windows.h>
#include <conio.h>
#include <random>

class FigureEngine {
private:
    int rows, cols;
    std::vector<std::string> figure;
    using CallbackFunction = void(*)();  // ����ص���������
    using KeyCallbackFunction = void(*)(char);  // ���尴���ص���������
    std::vector<CallbackFunction> callbacks;  // ����Ϊ�洢����ָ�������
    std::vector<KeyCallbackFunction> keyCallbacks;  // �����ص�����
    bool isGameOver;
    std::mt19937 gen;
public:
    FigureEngine(int rows, int cols);
    void print();
    void clear();
    void setChar(int row, int col, char c);
    char getChar(int row, int col);
    void setCallback(CallbackFunction callback);  // ���ûص�����
    bool run();
    void deleteCallback(CallbackFunction callback);  // ɾ���ص�����
    void deleteKeyCallback(KeyCallbackFunction keyCallback);  // ɾ�������ص�����
    void setKeyCallback(KeyCallbackFunction keyCallback);  // �����ص�����
    void gameOver();
    void generateFood();
};
