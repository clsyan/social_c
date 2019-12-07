#ifndef UTILS_H
#define UTILS_H
#ifdef _WIN32
#include "Windows.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//getline from https://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c
//this prevent the overflow of the "get" function
char* _getline();
int str_indexof(char* str, char c, int start);
char* str_sub(char* str, int start, int end);
#endif