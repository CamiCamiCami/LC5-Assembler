#include "utils.h"

void comoStr(bin word, char repr[17]){
	bin k;
	for(int c = 15; c >= 0; c--){
		k = word >> c;

		if(k & 1){
			repr[15-c] = '1';
		} else {
			repr[15-c] = '0';
		}
	}
	repr[16] = '\0';
}

void intComoStr(int word, char repr[33]){
    bin k;
	for(int c = 31; c >= 0; c--){
		k = word >> c;

		if(k & 1){
			repr[31-c] = '1';
		} else {
			repr[31-c] = '0';
		}
	}
	repr[32] = '\0';
}