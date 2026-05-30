#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECRATE

#define BUFFER_SIZE 256
#define SHIFT_AMOUNT 5
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void EncryptToFile(int MessageSize, char OriginalMessage[BUFFER_SIZE])
{
	char* EncryptedMessage = (char*)malloc(sizeof(char) * (MessageSize + 1));
	memset(EncryptedMessage, 0, sizeof(char) * (MessageSize + 1));

	for (int i = 0; i < MessageSize; i++)
	{
		EncryptedMessage[i] = OriginalMessage[i] + SHIFT_AMOUNT;
	}
	EncryptedMessage[MessageSize] = '\0';

	FILE* FilePointer = fopen("EncryptedText.txt", "w");
	fputs(EncryptedMessage, FilePointer);

	printf("Encrypted message: %s\n", EncryptedMessage);

	fclose(FilePointer);
	free(EncryptedMessage);
}

void DecryptFromFile()
{
	int i = 0;
	int MessageSize;
	char FileMessage[BUFFER_SIZE];

	FILE* FilePointer = fopen("EncryptedText.txt", "r");

	if (fseek(FilePointer, 0L, SEEK_END) == 0)
	{
		MessageSize = ftell(FilePointer);
	}
	rewind(FilePointer);

	char* DecryptedMessage = (char*)malloc(sizeof(char) * (MessageSize + 1));
	memset(DecryptedMessage, 0, sizeof(char) * (MessageSize + 1));

	fgets(FileMessage, BUFFER_SIZE, FilePointer);
	for (int i = 0; i < MessageSize; i++)
	{
		DecryptedMessage[i] = FileMessage[i] - SHIFT_AMOUNT;
	}

	printf("Decrypted message: %s\n", DecryptedMessage);

	fclose(FilePointer);
	free(DecryptedMessage);
}

int main()
{
	int Choice;
	char OriginalMessage[BUFFER_SIZE];
	int MessageSize;

	while (1)
	{
		printf("--------------------------------------\n");
		printf("1. Encrypt\n");
		printf("2. Decrypt\n");
		printf("3. Exit\n");
		printf("Enter your choice\n");
		scanf("%d", &Choice);

		switch (Choice)
		{
		case 1:
		{
			printf("Enter a message to Encrypt\n");
			scanf("%s", OriginalMessage);
			fgets(OriginalMessage, BUFFER_SIZE, stdin);
			MessageSize = strnlen(OriginalMessage, BUFFER_SIZE);

			EncryptToFile(MessageSize, OriginalMessage);
			break;
		}
		case 2:
		{
			DecryptFromFile();
			break;
		}
		case 3: exit(1); break;
		default: printf("Enter valid choice\n"); break;
		}
	}

	return 0;
}
