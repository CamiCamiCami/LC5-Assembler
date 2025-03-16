#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct __match_entry {
	const char* word_formed;
	struct __string_matcher* next;
	char letter;
};

struct __string_matcher {
	int length;
	struct __match_entry** entries;
};

typedef struct __match_entry* MatchEntry;
typedef struct __string_matcher* StringMatcher;

const char* matchString(StringMatcher matcher, const char* string);

StringMatcher newStringMatcher();

void addWord(StringMatcher matcher, const char word[]);

void freeStringMatcher(StringMatcher matcher);

