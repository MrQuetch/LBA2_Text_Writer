#include <iostream>
#include <string.h>

// Macros.
#define MAX_TEXTS 1000

// Variables.
int headerOffset;

int textAmount;
int textPosition;
short textOffsets[MAX_TEXTS];
char singleString[MAX_TEXTS];
char multipleStrings[MAX_TEXTS][MAX_TEXTS];

// Functions.
int calculateTextOffset(int index)
	{
	int amount = headerOffset;
	
	for (int j = 0; j < index; j++)
		amount += (strlen(singleString) + sizeof(short));
	
	return amount;
	};

int calculateTextOffsetMultiple(int index)
	{
	int amount = headerOffset;
	
	for (int j = 0; j < index; j++)
		amount += (strlen(multipleStrings[j]) + sizeof(short));
	
	return amount;
	};

void writeByOne()
	{
	FILE* writeByOne;
	
	char zeroChar = 0x00;
	short zeroShort = 0x0000;
	char oneChar = 0x01;
	short oneShort = 0x0100;
	
	const char* fileName = "TEXT002.lbt";
	
	printf("\n'Write by one' was selected. \n");
	
	// Count all text entries.
	headerOffset = ((textAmount * sizeof(short)) + sizeof(short));
	
	for (int i = 0; i < textAmount; i++)
		{
		printf("Type in the text for string %d: \n", i);
		scanf("%s", &multipleStrings[i]);
		};
	
	printf("Writing to the file... \n");
	
	writeByOne = fopen(fileName, "wb");
	
	// Count all text entries.
	headerOffset = ((textAmount * sizeof(short)) + sizeof(short));
	
	// Calculate offsets.
	for (int i = 0; i < textAmount; i++)
		textOffsets[i] = calculateTextOffsetMultiple(i);
	
	// Stub headers.
	for (int i = 0; i < textAmount; i++)
		fwrite(&zeroShort, sizeof(short), 0x1, writeByOne);
	
	// Stub last header.
	fwrite(&zeroShort, sizeof(short), 0x1, writeByOne);
	
	// Write texts.
	for (int i = 0; i < textAmount; i++)
		{
		if (i == 0)
			fwrite(&oneChar, sizeof(char), 0x1, writeByOne);
		else
			fwrite(&oneShort, sizeof(short), 0x1, writeByOne);
		
		for (int j = 0; j < strlen(multipleStrings[i]); j++)
			fwrite(&multipleStrings[i][j], sizeof(char), 0x1, writeByOne);
		
		if (i == (textAmount - 1))
			fwrite(&zeroChar, sizeof(char), 0x1, writeByOne);
		};
	
	// Go back to header.
	fseek(writeByOne, 0x00, SEEK_SET);
	
	// Write offsets.
	for (int i = 0; i < textAmount; i++)
		fwrite(&textOffsets[i], sizeof(short), 0x1, writeByOne);
	
	// Write last offset.
	textOffsets[textAmount] = calculateTextOffsetMultiple(textAmount);
	fwrite(&textOffsets[textAmount], sizeof(short), 0x1, writeByOne);
	
	for (int i = 0; i < textAmount; i++)
		printf("multipleStrings[%d] = %s \n", i, multipleStrings[i]);
	
	fclose(writeByOne);
	
	printf("Writing complete. \n");
	};

void fillAll()
	{
	FILE* fillAll;
	
	char zeroChar = 0x00;
	short zeroShort = 0x0000;
	char oneChar = 0x01;
	short oneShort = 0x0100;
	
	const char* fileName = "TEXT002.lbt";
	
	printf("\n'Fill all' was selected. \n");
	//printf("What is the name of the file? \n");
	
	printf("Type in the text: \n");
	scanf("%s", &singleString);
	
	fillAll = fopen(fileName, "wb");
	
	printf("Writing to the file... \n");
	
	// Count all text entries.
	headerOffset = ((textAmount * sizeof(short)) + sizeof(short));
	
	// Calculate offsets.
	for (int i = 0; i < textAmount; i++)
		textOffsets[i] = calculateTextOffset(i);
	
	// Stub headers.
	for (int i = 0; i < textAmount; i++)
		fwrite(&zeroShort, sizeof(short), 0x1, fillAll);
	
	// Stub last header.
	fwrite(&zeroShort, sizeof(short), 0x1, fillAll);
	
	// Write texts.
	for (int i = 0; i < textAmount; i++)
		{
		if (i == 0)
			fwrite(&oneChar, sizeof(char), 0x1, fillAll);
		else
			fwrite(&oneShort, sizeof(short), 0x1, fillAll);
		
		for (int j = 0; j < strlen(singleString); j++)
			fwrite(&singleString[j], sizeof(char), 0x1, fillAll);
		
		if (i == (textAmount - 1))
			fwrite(&zeroChar, sizeof(char), 0x1, fillAll);
		};
	
	// Go back to header.
	fseek(fillAll, 0x00, SEEK_SET);
	
	// Write offsets.
	for (int i = 0; i < textAmount; i++)
		fwrite(&textOffsets[i], sizeof(short), 0x1, fillAll);
	
	// Write last offset.
	textOffsets[textAmount] = calculateTextOffset(textAmount);
	fwrite(&textOffsets[textAmount], sizeof(short), 0x1, fillAll);
	
	fclose(fillAll);
	
	printf("Writing complete. \n");
	};

int main()
	{
	int option;
	
	printf("How many texts would you like to write? \n");
	
	scanf("%d", &textAmount);
	
	printf("\nWould you like to write by one or fill all? \n");
	printf("1 - Write by one. \n");
	printf("2 - Fill all. \n");
	
	scanf("%d", &option);
	
	if (option == 1)
		writeByOne();
	else if (option == 2)
		fillAll();
	
	return 0;
	};
