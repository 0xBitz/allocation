#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

int Dasprintf(char **string_ptr, const char *format, ...)
{
	int len;
    char *buffer = NULL;
    va_list args;
    va_start(args, format);

    len = vasprintf(&buffer, format, args);

    if(malloc_usable_size(*string_ptr) > 0)
	{	
		*string_ptr = realloc(*string_ptr, len + 1);
		memcpy(*string_ptr, buffer, len + 1);
	} else {
		*string_ptr = malloc(len + 1);
		memcpy(*string_ptr, buffer, len + 1);
	}
	va_end(args);
    free(buffer);

    (*string_ptr)[len] = '\0'; 

	return len;
}

int main() 
{
	char *goob = NULL;
	int l;
	int Seconds = 10;
	while(Seconds-- > 0)
	{
		char CapStr[80] = { 0 };
        for(l = 0; l < (rand()%10) + 3; l++)
            CapStr[l]=(char)(rand() % ('z' - 'a') + 'a');

		int len = Dasprintf(&goob, "%s", CapStr);
		printf("%d:%s\n", len, goob);
	}

	free(goob);
}