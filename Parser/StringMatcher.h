#pragma once
#include <stdbool.h>
#include <stdlib.h>

struct __match_entry {
	bool isEnd;
	const char* full_word;
	struct __string_matcher* next;
	char letter;
};

struct __string_matcher {
	int length;
	struct __match_entry** entries;
};

typedef struct __match_entry* MatchEntry;
typedef struct __string_matcher* StringMatcher;