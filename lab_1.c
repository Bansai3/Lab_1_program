#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


long getFileSize(FILE* f)
{
    int fileSize = -1;
    fseek(f, 0, SEEK_END);
    fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    return fileSize;
}

long getLinesCount(FILE* f)
{
    int lineCount = 0;
    char c;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
            lineCount++;
    }
    fseek(f, 0, SEEK_SET);
    return lineCount + 1;
}

long getWordsCount(FILE* f)
{
    int wordsCount = 0;
    char c;
    int flag = 0;
    
    while ((c = fgetc(f)) != EOF)
    {
        if (c != ' ' && c != '\n' && !flag)
        {
            flag = 1;
            wordsCount++;
        }
        else
        {
            if (c == ' ' || c == '\n')
                flag = 0;
        }
    }

    fseek(f, 0, SEEK_SET);
    return wordsCount;
}

int main(int argc, char* argv[])
{
    char fileName[255];
    char buf[255];
    unsigned long i;

    FILE* file;
    
    if (argc >= 4) 
    {
    	strcpy(fileName, argv[argc - 1]);
            file = fopen(fileName, "r");
        for (i = 2; i < argc-1; i++)
        {
            strcpy(buf, argv[i]);
            if (strcmp(buf, "-l") == 0 || strcmp(buf, "--lines") == 0)
            {
                printf("Line count: %d\n", getLinesCount(file));

            }
            if (strcmp(buf, "-c") == 0 || strcmp(buf, "--bytes") == 0)
            {
               printf("File size: %d\n", getFileSize(file));

            }
            if (strcmp(buf, "-w") == 0 || strcmp(buf, "--words") == 0)
            {
              printf("Words count: %d\n", getWordsCount(file));

            }
        }
    }
    else
    {
    	file = fopen("text", "r");
    printf("File size: %d\n", getFileSize(file));
    printf("Line count: %d\n", getLinesCount(file));
    printf("Words count: %d\n", getWordsCount(file));
    }
    fclose(file);
    return 0;
}
