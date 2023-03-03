#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include <Wincon.h>

template<typename ...Args>
inline void Log(int color, Args && ...args)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    (std::cout << ... << args);
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    std::cout << "\n";
}

#ifdef _DEBUG
#define PRINT_ERROR(message, ...) {Log(FOREGROUND_RED   | FOREGROUND_INTENSITY,   "[ ERROR ] ", message, __VA_ARGS__);}
#define PRINT_DEBUG(message, ...) {Log(FOREGROUND_BLUE  | FOREGROUND_INTENSITY,   "[ DEBUG ] ", message, __VA_ARGS__);}
#define PRINT_WARNING(message, ...) {Log(FOREGROUND_RED | FOREGROUND_GREEN  | FOREGROUND_INTENSITY, "[ WARNING ] ", message, __VA_ARGS__);}
#define PRINT_INFO(message, ...)  {Log(FOREGROUND_GREEN | FOREGROUND_INTENSITY,   "[ INFO  ] ", message, __VA_ARGS__);}
#else
#define PRINT_ERROR(message, ...) {}   
#define PRINT_DEBUG(message, ...) {}
#define PRINT_WARNING(message, ...){}
#define PRINT_INFO(message, ...)  {}
#endif
