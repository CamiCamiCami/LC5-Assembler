#pragma once
#ifndef ERRORHANDLING
#define ERRORHANDLING

#include <stdio.h>
#include <stdlib.h>

#define THROW_ERROR(type, ...) do {printf(getErrorString(type), __VA_ARGS__); exit(1);} while(0)

enum __error_type {
	MALLOC = 1,
};

typedef enum __error_type ErrorType;

char* getErrorString(ErrorType type);

#endif // !ERRORHANDLING