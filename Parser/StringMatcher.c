#include "StringMatcher.h"
#include <stdio.h>
#include <errno.h>
#include "ErrorHandling.h"

char* copyFullWord(char full_word[]) {
	size_t size = sizeof(char) * (strlen(full_word) + 1);
	char* copy = malloc(size);
	if (copy == NULL) {
		printf("Memory Allocation Error: %i", errno);
		exit(errno);
		return NULL;
	}
	strcpy_s(copy, size, full_word);
	return copy;
}

const char* matchString(StringMatcher matcher, const char* string) {
	if (matcher == NULL) {
		return NULL;
	}

	const char first_letter = *string;
	for (int i = 0; i < matcher->length; i++) {
		if (matcher->entries[i]->letter == first_letter) {
			const char* result = matchString(matcher->entries[i]->next, string + 1);
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
	if (new_str_matcher != NULL) {
		new_str_matcher->entries = NULL;
		new_str_matcher->length = 0;
		return new_str_matcher;
	} else THROW_ERROR(MALLOC, errno);
}

MatchEntry newMatchEntry(char* word_formed, char letter) {
	MatchEntry new_entry = malloc(sizeof(struct __match_entry));
	if (new_entry != NULL) {
	new_entry->letter = letter;
	new_entry->word_formed = word_formed == NULL ? NULL : copyFullWord(word_formed);
	new_entry->next = newStringMatcher();
	return new_entry;
	} else THROW_ERROR(MALLOC, errno);
}

void _addWord(StringMatcher matcher, const char full_word[], const char progress_word[]) {
	for (int i = 0; i < matcher->length; i++) {
		if (matcher->entries[i]->letter == progress_word[0]) {
			if (progress_word[1] == '\0') {
				matcher->entries[i]->word_formed = copyFullWord(full_word);
				return;
			}
			else {
				_addWord(matcher->entries[i]->next, full_word, progress_word + 1);
				return;
			}
		}
	}

	StringMatcher realocated = realloc(matcher->entries, (++matcher->length)*sizeof(MatchEntry));
	if (realocated != NULL) {
		matcher->entries = realocated;
	} else THROW_ERROR(MALLOC, errno);

	if (progress_word[1] == '\0') {
		// Word fully added
		matcher->entries[matcher->length-1] = newMatchEntry(full_word, progress_word[0]);
		return;
	}
	else {
		matcher->entries[matcher->length-1] = newMatchEntry(NULL, progress_word[0]);
		_addWord(matcher->entries[matcher->length-1]->next, full_word, progress_word + 1);
		return;
	}
}

void addWord(StringMatcher matcher, const char word[]) {
	_addWord(matcher, word, word);
}

void freeMatchEntry(MatchEntry entry) {
	if (entry->word_formed != NULL) {
		free(entry->word_formed);
	}
	freeStringMatcher(entry->next);
	free(entry);
}

void freeStringMatcher(StringMatcher matcher) {
	for (int i = 0; i < matcher->length; i++) {
		freeMatchEntry(matcher->entries[i]);
	}
	if (matcher->length != 0) free(matcher->entries);
	free(matcher);
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