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
			else if (matcher->entries[i]->word_formed != NULL)
				return matcher->entries[i]->word_formed;
			else
				return NULL;
		}
	}

	return NULL;
}

StringMatcher newStringMatcher() {
	StringMatcher new_str_matcher = malloc(sizeof(struct __string_matcher));
	new_str_matcher->entries = NULL;
	new_str_matcher->length = 0;
	return new_str_matcher;
}

MatchEntry newMatchEntry(char* word_formed, char letter) {
	MatchEntry new_entry = malloc(sizeof(struct __match_entry));
	new_entry->letter = letter;
	new_entry->word_formed = word_formed == NULL ? NULL : copyFullWord(word_formed);
	new_entry->next = newStringMatcher();
	return new_entry;
}

void addWord(StringMatcher matcher, const char full_word[], const char progress_word[]) {
	for (int i = 0; i < matcher->length; i++) {
		if (matcher->entries[i]->letter == progress_word[0]) {
			if (progress_word[1] == '\0') {
				matcher->entries[i]->word_formed = copyFullWord(full_word);
				return;
			}
			else {
				addWord(matcher->entries[i]->next, full_word, progress_word + 1);
				return;
			}
		}
	}

	matcher->entries = realloc(matcher->entries, ++matcher->length);

	if (progress_word[1] == '\0') {
		// Word fully added
		matcher->entries[matcher->length] = newMatchEntry(full_word, progress_word[0]);
		return;
	}
	else {
		matcher->entries[matcher->length] = newMatchEntry(NULL, progress_word[0]);
		addWord(matcher->entries[matcher->length]->next, full_word, progress_word + 1);
		return;
	}
}

char* copyFullWord(char full_word[]) {
	char* copy = malloc(sizeof(char) * strlen(full_word));
	strcpy(copy, full_word);
	return copy;
}

void freeStringMatcher(StringMatcher matcher) {
	for (int i = 0; i < matcher->length; i++) {
		freeMatchEntry(matcher->entries[i]);
	}

	free(matcher);
}

void freeMatchEntry(MatchEntry entry) {
	if (entry->word_formed != NULL) {
		free(entry->word_formed);
	}
	freeStringMatcher(entry->next);
	free(entry);
}

const char* sortWords(const char** words, int length) {
	bool bubble_must_continue = true;
	while (bubble_must_continue) {
		bubble_must_continue = false;
		for (int i = 0; i < length - 1; i++) {
			if (strcmp(words[i], words[i + 1]) > 0) {
				const char* aux_swap = words[i];
				words[i] = words[i + 1];
				words[i + 1] = aux_swap;
				bubble_must_continue = true;
			}
		}
	}
}