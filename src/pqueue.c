#include <string.h>
#include <stdlib.h>

int list[10];
int currentListSize = 10;
int elements = 0;
int MAX = NULL;

void getMax(int data[])
{
	int x;
	for (x = 0; x < currentListSize; x++)
	{
		if (MAX < list[x])
		{
			MAX = list[x];
		}
	}
}

void makeBiggerArray(int size)
{
	int* list = realloc(list, size * sizeof *list);
	currentListSize *= currentListSize;
}

void checkArray(int length)
{
	if (length-1 >= currentListSize)
	{
		makeBiggerArray(currentListSize);
	}
	else
		return;
}

void inqueue(int data)
{
	elements++;
	checkArray(elements);
	list[elements - 1] = data;
	if (MAX == NULL)
	{
		MAX = data;
		return;
	}
	else
		getMax(list);
	return;
}
int dequeue()
{
	int x, oldMax;
	if (elements == 0)
		return -1;
	oldMax = MAX;
	for (x = 0; x < currentListSize; x++)
	{
		if (MAX == list[x])
		{
			for(;x < currentListSize; x++)
				list[x] = list[(x + 1)];
		}
	}
	MAX = NULL;
	elements--;
	getMax(list);
	slog("%d",oldMax);
	return oldMax;
}

