#pragma once 
#include "mbed.h"
#include <ctype.h> // included so that toupper() can be used to make chars uppercase in s 

void IdleAnimation();

void AdjustDisplay();

void DisplayClear();

void DisplayChar(const int c[], const int n);

void DisplayString(const char s[], const int n);

