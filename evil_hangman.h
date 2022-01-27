void playEvilHangman(GENERIC_VECTOR* phVectorArray, int wordLength, int remainingGuesses, char showCount);

Boolean wordGuessed(MY_STRING hGuessedLetters, char guess);

Boolean wonGame(MY_STRING hKey);

Boolean isCorrectGuess(MY_STRING hKey, char guess);

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);

void clear_keyboard_buffer(void);