#include "command.h"
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void listDir()
{
    /* Uses dirent.h and a struct to store file info */

    DIR* currentDirectory;
    char cwd[PATH_MAX]; /* Stores the cwd path: /usr/blabla */
    struct dirent *directory; /* Struct that holds file info */
    

    if(getcwd(cwd, sizeof(cwd)) != NULL) /*  */
    {
        printf("Current working directory: %s\n", cwd);
        currentDirectory = opendir(cwd);
        while((directory = readdir(currentDirectory)) != NULL)
            {
                write(1, directory->d_name, strlen(directory->d_name));
                write(1, " ", 1);
            }
    }
    else
    {
        printf("cwd error\n");
    }
    
    closedir(currentDirectory);
    write(1, "\n", 2);
    
}

void showCurrentDir()
{
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != NULL)
    {
        write(1, cwd, strlen(cwd));
        write(1, "\n", 2);
    }
}

void displayFile(char* fileName)
{
    int fileNameLength = strlen(fileName) + 1;  // save length for forloop below
    char newFileName[fileNameLength]; 
    ssize_t numCharacters;  // store how many characters read using the read() function
    char buffer[255];
    // buffer = malloc(sizeof(char) * 255);
    // newFileName = malloc(strlen(fileName));

    // Set string to NULL to appease the Valgrind Gods
    memset(newFileName, '\0', sizeof(char) * fileNameLength);
    memset(buffer, '\0', sizeof(char) * 255);

    for (int i = 0; i < fileNameLength; i++)
    {
        /*
        This just removes the "\n" gathered by getline if
        the command is entered as "cat test.txt[\n]"
        */
        if (strcmp(&fileName[i], "\n") != 0)
        {
            // printf("filename[i] %c\n", fileName[i]);
            strncat(newFileName, &fileName[i], 1);
        }
    }
    printf("New string %s\n", newFileName);
    int catFile = open(newFileName, O_RDONLY); // open in read only

    if(catFile == -1)
    {
        char* errorMessage = "Error opening file: ";
        write(1, errorMessage, strlen(errorMessage));
        write(1, newFileName, strlen(newFileName));
        write(1, "\n", 1);
    }
    else
    {
        numCharacters = read(catFile, buffer, 255);
        while(numCharacters != 0)
        {
            write(1, buffer, numCharacters);
            numCharacters = read(catFile, buffer, 255);
        }
        close(catFile);
    }
    
    // free(buffer);
    // free(newFileName);
    write(1, "\n", 1);
}

void makeDir(char *dirName)
{
    int length = strlen(dirName);
    char newName[length];
    memset(newName, '\0', sizeof(char) * length);
    for(int i = 0; i < length; i++)
    {
        /*
        Remove the trailing \n if there is one
        */
        if (strcmp(&dirName[i], "\n") != 0)
        {
            // printf("filename[i] %c\n", fileName[i]);
            strncat(newName, &dirName[i], 1);
        }
    }

    mkdir(newName, 0777);  // man page says 0777 is default
}
