#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool isequals(const char* str1, const char* str2) {
	return strcmp(str1, str2);
}

char* readstring(const unsigned int length, char* mensage) {
	char* string = (char*)malloc(sizeof(char) * length);
	printf("%s", mensage);
	scanf("%s", string);
	return string;
}

bool isnumber(const char character) {
	return (character >= '1' && character <= '9');
}

int readInt(const char* msg) {
	int number;
	printf(msg);
	scanf("%d", &number);
	return number;
}