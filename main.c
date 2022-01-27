#include <stdio.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"
#include "associative_array.h"
#include "evil_hangman.h"

#define MAX 30



int main(int argc, char* argv[]) {
	FILE* dictionary;
	GENERIC_VECTOR vectorArr[MAX];
	MY_STRING hString = my_string_init_default();

	int i = 0;
	int noc;
	int wordLength;
	int guessCount;
	char playAgain;
	char showCount;

	for (i = 0; i < MAX; i++)
		vectorArr[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);

	dictionary = fopen("dictionary.txt", "r");

	while (my_string_extraction(hString, dictionary))
		generic_vector_push_back(vectorArr[my_string_get_size(hString) - 1], hString);
	
	fclose(dictionary); dictionary = NULL;

	do {
		printf("~--Evil Hangman--~\n");

		printf("What is the word length: "); 
		fscanf(stdin, "%d", &wordLength);
		clear_keyboard_buffer();

		while (wordLength < 2 || wordLength >29 || wordLength == 27 || wordLength == 26 || wordLength == 23 || wordLength == 25) {
			printf("No word of that length exists, please enter again: ");
			fscanf(stdin, "%d", &wordLength);
			clear_keyboard_buffer();
		}

		printf("How many guesses do you want to play with: ");
		noc = fscanf(stdin, "%d", &guessCount);
		clear_keyboard_buffer();

		while (guessCount < 0 || noc != 1) {
			printf("Invalid input, the number must be greater than 1, please enter again: ");
			noc = fscanf(stdin, "%d", &guessCount);
			clear_keyboard_buffer();
		}

		printf("Show remaining words after each turn? (y/n): ");
		fscanf(stdin, "%c", &showCount);
		clear_keyboard_buffer();

		while (showCount != 'y' && showCount != 'Y' && showCount != 'n' && showCount != 'N') {
			printf("Invalid input, you must enter (y) or (n), please enter again: ");
			fscanf(stdin, "%c", &showCount);
			clear_keyboard_buffer();
		}

		playEvilHangman(vectorArr, wordLength, guessCount, showCount);

		printf("Do you wish to play again? (y/n); "); fscanf(stdin, "%c", &playAgain);
		playAgain = tolower(playAgain);

	} while (playAgain == 'y' || playAgain == 'Y');
	
	for (i = 0; i < MAX; i++){
		generic_vector_destroy(vectorArr + i);
	}
	my_string_destroy(&hString);

	return 0;
}

