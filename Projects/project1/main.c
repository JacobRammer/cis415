#include "command.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    
    int fileMode = 0;
    int characters;
    char* lineBuffer;  /* stores the buffer of terminal input */
    char* savePtr;  /* stores the remaining of lineBuffer for strtok_r */
    char* tempSavePtr;
    char* tokBuffer;
    size_t bufferSize = 256;
    lineBuffer = (char*)malloc(bufferSize * sizeof(char));
    
    FILE* fName;
    FILE* output;

    if(argc > 1)  /* check to see if we should run in file mode */
    {
        if(strcmp(argv[1], "-f") == 0)
        {
            fileMode = 1;
            printf("Running in file mode\n");
        }

        /* Check to see if input file is valid */
        fName = fopen(argv[2], "r");
        if(fName == NULL)
        {
            printf("No valid file: %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }
    }

    if(fileMode)
    {
        // output = freopen("output.txt", "w+", stdout);
        char* argument;
        char* command;
        int len = 0;
;        while(fgets(lineBuffer, bufferSize, fName) != NULL)
        {
            printf("Line is: %s", lineBuffer);
        }
        printf("\n");
        // ret = strrchr(lineBuffer, ';');
        command = strtok_r(lineBuffer, ";", &savePtr);
        argument = strchr(command, ' ');
        printf("Command is %s\n", command);
        printf("Ret is: %s\n", argument);

        printf("saveptr is %ld\n", strlen(savePtr));
        
        len = strlen(argument);

        // command = strtok_r(NULL, " ", &savePtr);
        // argument = strtok_r(NULL, ";", &savePtr);
        // printf("Command is %s\n", command);
        // printf("Ret is: %s\n", argument);
        
        // argument = strtok_r(NULL, ";", &savePtr);
        // printf("new Ret is: %s\n", argument);
        
        /*
        After we get the first command from the line, I then
        need to look at the commands, and do the error checking there. 
        */
       printf("strlen ret: %ld\n", strlen(argument));
       if(strcmp(argument, "ls ") == 0 && strlen(argument) == 2)
       {
           listDir();
       }
       else if(strcmp(argument, "pwd") == 0 )
       {
           printf("yop\n");
           showCurrentDir();
       }

        // char *test = strtok_r(ret, " ", &tempSavePtr);
        // printf("test is: %s\n", test);
        // ret = strtok_r(NULL, ";", &savePtr);
        // printf("Ret is: %s\n", ret);
        
    }else
    {
        while (1)
        {
            printf(">>> ");
            characters = getline(&lineBuffer, &bufferSize, stdin);
            tokBuffer = strtok_r(lineBuffer, " \n", &savePtr);
            printf("token buffer %s\n", tokBuffer);
            if (strcmp(tokBuffer, "ls") == 0)
            {
                listDir();
            }
            else if (strcmp(tokBuffer, "pwd") == 0)
            {
                showCurrentDir();
            }
            else if (strcmp(tokBuffer, "cat") == 0)
            {
                tokBuffer = strtok_r(NULL, " ", &savePtr);
                displayFile(tokBuffer);
            }
            else if (strcmp(tokBuffer, "mkdir") == 0)
            {
                tokBuffer = strtok_r(NULL, " ", &savePtr);
                makeDir(tokBuffer);
            }
            else if (strcmp(tokBuffer, "rm") == 0)
            {
                tokBuffer = strtok_r(NULL, " ", &savePtr); // get rid of "rm"
                deleteFile(tokBuffer);
            }
            else if (strcmp(tokBuffer, "cd") == 0)
            {
                tokBuffer = strtok_r(NULL, " ", &savePtr);
                changeDir(tokBuffer);
            }
            else if (strcmp(tokBuffer, "mv") == 0)
            {
                char *source = strtok_r(NULL, " ", &savePtr);
                char *dest = tokBuffer = strtok_r(NULL, " ", &savePtr);
                // printf("mv token is: %s\n", source);
                // printf("mv token is: %s\n", dest);
                moveFile(source, dest);
            }
            else if (strcmp(tokBuffer, "cp") == 0)
            {
                char *source = strtok_r(NULL, " ", &savePtr);
                char *dest = tokBuffer = strtok_r(NULL, " ", &savePtr);
                // printf("mv token is: %s\n", source);
                // printf("mv token is: %s\n", dest);
                copyFile(source, dest);
            }
            else if (strcmp(tokBuffer, "exit") == 0)
                break;
        }
    }
    
    

    

    // fclose(fName);  TODO fix this
    free(lineBuffer);
    // fclose(output);
    return 0;
}