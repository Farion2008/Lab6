#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h";

int randomInt(int min, int max) // Для генерации рандомного числа
{ 
	return rand() % (max - min + 1) + min;
}
void tampArray(char** array, int* forRemove, int* n, int* c, int* lineCount)
{
	int isBiggest = forRemove[0] > forRemove[1] ? forRemove[0] : forRemove[1], isSmallest = forRemove[0] < forRemove[1] ? forRemove[0] : forRemove[1];
	for (int i = isSmallest; i < *n; i++)
	{
		if ((array[i + 1] == NULL || array[i] == NULL) && i != isSmallest) array[i] = array[i + 2];
		else array[i] = array[i + 1];
		if (i > isBiggest) array[i] = NULL;
	}
	*n -= *lineCount;
}
void getLines(char** array, int* n, char* alphabet, int* index, int* forRemove)
{
	for (int i = 0; i < *n; i++)
	{
		if (array[i][0] == alphabet[*index] && forRemove[0] == NULL)
		{
			forRemove[0] = i;
		}
		int backIndex = *n - 1 - i;
		if (array[backIndex][0] == alphabet[25 - *index] && forRemove[1] == NULL)
		{
			forRemove[1] = backIndex;
		}
	}
	if (forRemove[0] == NULL || forRemove[1] == NULL)
	{
		*index += 1;
		getLines(array, n, alphabet, index, forRemove);
	}
}
void removeLines(char** array, int* n, int* c, char* alphabet)
{
	int lineCount = 2; // Кол-во строк для удаления
	int* forRemove = calloc(lineCount, sizeof(int)), index = 0;
	void (*tamp)(char** array, int* forRemove, int* n, int* c) = tampArray;
	getLines(array, n, alphabet, &index, forRemove);
	for (int i = 0; i < lineCount; i++) // Удаляем 2 требуемые строки по индексу
	{
		array[forRemove[i]] = NULL;
	}
	tamp(array, forRemove, n, c, &lineCount); // Уплотняем массив
}

int main()
{
	int n = 8, c = 8; // n - длина массива, c - длина строки
	char** array = (char**)calloc(16, sizeof(char*));

	void (*rem)(char** array, int* n, int* c, char* alphabet) = removeLines;
	char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < n; i++) // Выделяем область памяти для каждой строки
	{
		array[i] = (char*)calloc(c, sizeof(char));
		for (int j = 0; j < c; j++)
		{
			char* forAdd = (char*)calloc(c, sizeof(char));
			sprintf(forAdd, "%c", alphabet[randomInt(0, 25)]);
			strcat(array[i], forAdd);
		}
		printf("%s ", array[i]);
	}

	rem(array, &n, &c, alphabet); // Удаляем из массива первую и последнюю строку по алфавиту, после уплотняем

	printf("\n");
	for (int i = 0; i < n; i++) // Вывод значения послее удаления
	{
		printf("%s ", array[i]);
	}

	_getch();
	return 0;
}