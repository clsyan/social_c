#include "utils.h"
char* _getline() {
	char* line = (char*)malloc(100), * linep = line;
	size_t lenmax = 100, len = lenmax;
	int c;

	if (line == NULL)
		return NULL;

	for (;;) {
		c = fgetc(stdin);
		if (c == EOF)
			break;

		if (--len == 0) {
			len = lenmax;
			char* linen = (char*)realloc(linep, lenmax *= 2);

			if (linen == NULL) {
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}

		if ((*line++ = c) == '\n')
			break;
	}
	*line = '\0';
	return linep;
}
int str_indexof(char* str, char c, int start) {
	int len = strlen(str);
	for (int i = start; i < len; i++) {
		if (str[i] == c)
			return i;
	}
	return -1;
}
char* str_sub(char* str, int start, int end) {
	if (end == -1) end = strlen(str);
	char* r = (char*)malloc((end - start) + 1);
	memcpy(r, str + start, end - start);
	r[end - start] = '\0';
	return r;
}