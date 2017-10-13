/*************************************************************************
* Title: (CIS265_7A) Smallest & Largest Words.
* File: main.c
* Author: James Eli
* Date: 9/3/2017
*
* Write a program that finds the “smallest” and “largest” in a series of 
* words. After the user enters the words, the program will determine which 
* words would come first and last if the words were listed in dictionary 
* order. The program must stop accepting input when the user enters a 
* four-letter word. Assume that no word is more than 20 letters long. An 
* interactive session with the program might look like this:
*   Enter word: dog
*   Enter word: zebra
*   Enter word: rabbit
*   Enter word: catfish
*   Enter word: walrus
*   Enter word: cat
*   Enter word: fish
*   Smallest word: cat
*   Largest word: zebra
*
* Hint: Use two strings named smallest_word and largest_word to keep track 
* of the “smallest” and “largest” words entered so far. Each time the user 
* enters a new word, use strcmp to compare it with smallest_word; if the 
* word is “smaller”, use strcpy to save it in smallest_word. Do a similar 
* comparison with largest_word. Use strlen to determine when the user 
* entered a four-letter word.
*
* Notes:
*  (1) Uses strcmp function to make small/large comparison.
*  (2) Comparison of words are case sensitive.
*  (3) Performs several validity checks on word entered.
*  (4) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/03/2017: Initial release. JME
*   09/27/2017: Added conversion of word to lower case. JME
*   10/09/2017: Removed some unnecessary code. JME
*************************************************************************/
#include <assert.h> 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definitions.
#define MAX_WORD_LENGTH    20                    // Max word length.
#define WORD_LENGTH        (MAX_WORD_LENGTH + 1) // String length.
#define MAX_INPUT_ATTEMPTS 3                     // Maximum invalid input attempts.
#define INSTRUCTIONS       "This program finds the \"smallest\" and \"largest\" word in a series\n" \
                           "of words entered. The program will stop accepting input when a\n"       \
                           "four-letter word is entered. Words over 20 letters are ignored.\n\n"

// Validate string characters as alphabetic.
bool validateWord(const char* s) {
	// Empty?
	if (s == NULL || *s == '\0')
		return false;
	// Check alphabetic.
	while (*s != '\0' && *s != '\n')
		if (!isalpha(*s++))
			return false;
	// Arriving here means only valid chars found.
	return true;
}

// Program starts here.
int main(void) {
	unsigned int attempts = 0;                 // Empty entry counter.
	char largest_word[WORD_LENGTH] = { 0 };    // Set longest word to empty.
	char smallest_word[WORD_LENGTH] = { 'z' }; // Make shortest word artifically long, so everything is shorter.

	// Display program instructions.
	fputs(INSTRUCTIONS, stdout);

	// Main entry/test loop.
	while (1) {
		char word[WORD_LENGTH]; // Word entered by user.
		
		// Enter a word.
		fputs("Enter a word: ", stdout);
		if (!fgets(word, sizeof word, stdin)) {
			fputs("Fatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(word, '\n')) {
			// Input too long, eat remainder.
			while (fgets(word, sizeof word, stdin) && !strchr(word, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		// So far so good, now check word entered...
		else {
			// Trim off trailing LF inserted by fgets.
			if (*(word + strlen(word) - 1) == '\n')
				word[strlen(word) - 1] = 0;

			// Check if empty entry.
			if (strlen(word) == 0) {
				// Only allow so many empty entries.
				if (++attempts >= MAX_INPUT_ATTEMPTS) {
					fputs("Program terminating.\n", stderr);
					exit(EXIT_FAILURE);
				}
				continue;
			}

			// Validate word as alphabetic charaters.
			if (!validateWord(word)) {
				fputs("Skipping word, entry contains non-alphabetic characters.\n", stdout);
				continue;
			}

			attempts = 0; // Reset.

			// Convert word to lower case (added 9/27/17 JME).
			for (char *c = word; *c; ++c) 
				*c = tolower(*c);

			// Case sensitive compare for a smaller word.
			if (strcmp(word, smallest_word) < 0)
				strcpy_s(smallest_word, _countof(word), word);

			// Case sensitive compare for a larger word.
			if (strcmp(word, largest_word) > 0)
				strcpy_s(largest_word, _countof(word), word);

			// Terminate entry loop?
			if (strlen(word) == 4)
				break;
		}
	}

	// Display statistics.
	fprintf(stdout, "Smallest word is %s.\n", smallest_word);
	fprintf(stdout, "Largest word is %s.\n", largest_word);
}
