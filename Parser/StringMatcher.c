#include "StringMatcher.h"

const char* match(StringMatcher matcher, const char* string) {
	if (matcher == NULL) {
		return NULL;
	}

	const char first_letter = *string;
	for (int i = 0; i < matcher->length; i++) {
		if (matcher->entries[i]->letter == first_letter) {
			const char* result = match(matcher->entries[i]->next, string + 1);
			if (result != NULL)
				return result;
			else if (matcher->entries[i]->isEnd)
				return matcher->entries[i]->full_word;
			else
				return NULL;
		}
	}

	return NULL;
}

StringMatcher newStringMatcher(const char* possible_words) {

}