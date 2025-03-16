#include "ErrorHandling.h"


char* malloc_string = "Memory Allocation Error %i\n";

char* getErrorString(ErrorType type) {
	switch (type)
	{
	case MALLOC:
		return malloc_string;
	default:
		printf("Invalid Error Type\n");
		exit(1);
	}
}