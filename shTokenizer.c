#include "shell.h"

/**
 ***strTow - split string and ignore repeated delimiters
 *@inputStr: input string
 *@delimiters: delimiter string
 *Return: array of strings pointer, or NULL
 */
char **strTow(char *inputStr, char *delimiters)
{
	int currentIndex, wordIndex, wordLength, characterIndex, numWords = 0;
	char **resultArray;

	if (inputStr == NULL || inputStr[0] == 0)
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (currentIndex = 0; inputStr[currentIndex] != '\0'; currentIndex++)
	{
		if (!isDelim(inputStr[currentIndex], delimiters) && (isDelim
					(inputStr[currentIndex + 1], delimiters) || !inputStr[currentIndex + 1]))
			numWords++;
	}
	if (numWords == 0)
		return (NULL);
	resultArray = malloc((1 + numWords) * sizeof(char *));
	if (!resultArray)
		return (NULL);
	for (currentIndex = 0, wordIndex = 0; wordIndex < numWords; wordIndex++)
	{
		while (isDelim(inputStr[currentIndex], delimiters))
			currentIndex++;
		wordLength = 0;
		while (!isDelim(inputStr[currentIndex + wordLength],
						delimiters) && inputStr[currentIndex + wordLength])
			wordLength++;
		resultArray[wordIndex] = malloc((wordLength + 1) * sizeof(char));
		if (!resultArray[wordIndex])
		{
			for (wordLength = 0; wordLength < wordIndex; wordLength++)
				free(resultArray[wordLength]);
			free(resultArray);
			return (NULL);
		}
		for (characterIndex = 0; characterIndex < wordLength; characterIndex++)
			resultArray[wordIndex][characterIndex] = inputStr[currentIndex++];
		resultArray[wordIndex][characterIndex] = 0;
	}
	resultArray[wordIndex] = NULL;
	return (resultArray);
}


/**
 * strTow2 - Split a string into an array of words using a specified delimiter.
 *
 * @inputStr: The input string to be split.
 * @delimiter: The character used to separate words in the input string.
 *
 * Return: A dynamically allocated array of strings containing the individual
 * words. Returns NULL in case of errors or if no words are found.
 */
char **strTow2(char *inputStr, char delimiter)
{
	int currentIndex, wordIndex, characterIndex, wordLength, numWords = 0;
	char **wordArray;

	if (inputStr == NULL || inputStr[0] == '\0')
		return (NULL); /*Handle empty or NULL input string */
	for (currentIndex = 0; inputStr[currentIndex] != '\0'; currentIndex++)
	{
		if (inputStr[currentIndex] != delimiter &&
			(inputStr[currentIndex + 1] == delimiter || inputStr[currentIndex + 1]
								== '\0' || inputStr[currentIndex + 1] == delimiter))
			numWords++;
	}
	if (numWords == 0)
		return (NULL);
	wordArray = malloc((numWords + 1) * sizeof(char *));
	if (!wordArray)
		return (NULL); /*Memory allocation error */
	for (currentIndex = 0, wordIndex = 0; wordIndex < numWords; wordIndex++)
	{
		while (inputStr[currentIndex] == delimiter)
			currentIndex++;
		wordLength = 0;
		while (inputStr[currentIndex + wordLength] != delimiter &&
			inputStr[currentIndex + wordLength] != '\0' &&
			inputStr[currentIndex + wordLength] != delimiter)
			wordLength++;
		wordArray[wordIndex] = malloc((wordLength + 1) * sizeof(char));
		if (!wordArray[wordIndex])
		{ /*Memory allocation error, free previously allocated memory */
			for (characterIndex = 0; characterIndex < wordIndex; characterIndex++)
				free(wordArray[characterIndex]);
			free(wordArray);
			return (NULL);
		}
		for (characterIndex = 0; characterIndex < wordLength; characterIndex++)
			wordArray[wordIndex][characterIndex] = inputStr[currentIndex++];
		wordArray[wordIndex][characterIndex] = '\0';
	}
	wordArray[wordIndex] = NULL;
	return (wordArray);
}
