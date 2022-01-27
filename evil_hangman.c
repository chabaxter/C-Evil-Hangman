#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "generic_vector.h"
#include "my_string.h"
#include "associative_array.h"
#include "multi.h"
#include "evil_hangman.h"

//void playHangman() Impliment later

void playEvilHangman(GENERIC_VECTOR* phVectorArray, int wordLength, int numGuesses, char showCount) {
	MY_STRING hGuessedLetters = my_string_init_default();
	MY_STRING hKey = my_string_init_default();
	MY_STRING hCurrentKey = my_string_init_default();
	MY_STRING hCurrentWord;

	Node* pTree = NULL;
	Node* pLargestNode;
	Status status;
	Boolean correctGuess;

	GENERIC_VECTOR hWordList = generic_vector_init_default(my_string_assignment, my_string_destroy);

	int i;
	int wordListLength;
	int noc;
	char guess;
	int remainingGuesses = numGuesses;

	for (i = 0; i < wordLength; i++) {
		my_string_push_back(hKey, '-');
		my_string_push_back(hCurrentKey, '-');
	}

	for (i = 0; i < generic_vector_get_size(phVectorArray[wordLength - 1]); i++) {
		generic_vector_push_back(hWordList, generic_vector_at(phVectorArray[wordLength - 1], i));
	}

	while (remainingGuesses > 0 && !wonGame(hKey)) {
		avl_destroy(&pTree);
		wordListLength = generic_vector_get_size(hWordList);
		if (showCount == 'y' || showCount == 'Y')
			printf("\nNumber of words: %d\n****\n", wordListLength);

		printf("Guesses Remaining: %d\n", remainingGuesses);
		printf("Guessed Letters: %s\n", my_string_c_str(hGuessedLetters));
		printf("Word: %s\n", my_string_c_str(hKey));

		printf("What is your guess? ");
		noc = fscanf(stdin, "%c", &guess);
		clear_keyboard_buffer();

		while (noc != 1 || !isalpha(guess)) {
			printf("Invalid input, please enter your guess: ");
			noc = fscanf(stdin, "%c", &guess);
			clear_keyboard_buffer();
		}

		guess = tolower(guess);

		while (wordGuessed(hGuessedLetters, guess)) {
			printf("You have already guessed that letter, guess again\n");

			printf("What is your guess? ");
			noc = fscanf(stdin, "%c", &guess);
			clear_keyboard_buffer();

			while (noc != 1 || !isalpha(guess)) {
				printf("Invalid input, please enter your guess: ");
				noc = fscanf(stdin, "%c", &guess);
				clear_keyboard_buffer();
			}

			guess = tolower(guess);
		}

		my_string_push_back(hGuessedLetters, guess);

		correctGuess = FALSE;
		pTree = NULL;

		for (i = 0; i < wordListLength; i++)
		{
			hCurrentWord = generic_vector_at(hWordList, i);

			get_word_key_value(hKey, hCurrentKey, hCurrentWord, guess);

			if (!avl_insert(&pTree, hCurrentKey, hCurrentWord)) {
				printf("Something went wrong, computer is sad D:\n");
				exit(1);
			}
		}

		avl_print_inorder(pTree);	//	Debug Option

		generic_vector_destroy(&hWordList);
		my_string_destroy(&hKey);
		
		pLargestNode = get_largest_node(pTree);

		hWordList = generic_vector_init_default(my_string_assignment, my_string_destroy);
		hKey = my_string_init_default();

		for (i = 0; i < generic_vector_get_size(pLargestNode->hVector); i++)
			generic_vector_push_back(hWordList, generic_vector_at(pLargestNode->hVector, i));
		
		my_string_assignment(&hKey, pLargestNode->hKey);

		if (isCorrectGuess(hKey, guess)) {
			printf("You guessed correctly\n");
		}
		else {
			printf("Wrongggggg\n");
			remainingGuesses--;
		}
	}

	if (remainingGuesses == 0) {
		printf("\n\nYou have lost :(\nThe correct word was: ");
		my_string_insertion(generic_vector_at(pLargestNode->hVector, 0), stdout);
		printf("\n");
	}
	else {
		printf("\n\nYou have won the game !!! \n\n");
	}
	
	avl_destroy(&pTree);
	my_string_destroy(&hGuessedLetters);
	my_string_destroy(&hKey);
	my_string_destroy(&hCurrentKey);
	generic_vector_destroy(&hWordList);

}

Boolean wordGuessed(MY_STRING hGuessedLetters, char guess) {
	int i;

	for (i = 0; i < my_string_get_size(hGuessedLetters); i++) {
		if (*my_string_at(hGuessedLetters, i) == guess) return TRUE;
	}

	return FALSE;
}

Boolean wonGame(MY_STRING hKey) {
	int i, count;

	if (my_string_get_size(hKey) == 0) return FALSE;

	for (i = 0; i < my_string_get_size(hKey); i++)
		if (*my_string_at(hKey, i) == '-') return FALSE;
	return TRUE;
}

Boolean isCorrectGuess(MY_STRING hKey, char guess) {
	int i;

	for (i = 0; i < my_string_get_size(hKey); i++) {
		if (*my_string_at(hKey, i) == guess) {
			return TRUE;
		}
	}

	return FALSE;
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess) {
	int i;
	guess = tolower(guess);
	char c;

	for (i = 0; i < my_string_get_size(word); i++) {
		if (tolower(*my_string_at(word, i)) == guess) {
			*my_string_at(new_key, i) = guess;
		}
		else {
			*my_string_at(new_key, i) = *my_string_at(current_word_family, i);
		}
	}

	return SUCCESS;
}

void clear_keyboard_buffer(void)
{
	char c;

	do
	{
		scanf("%c", &c);
	} while (c != '\n');
}
