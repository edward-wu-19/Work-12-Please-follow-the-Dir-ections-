#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void return_info(DIR *pDir, char folderName[100]);

int main(int argc, char *argv[]){
    char folderName[100];

    if (argc > 1){
        strcpy(folderName, argv[1]);
    }
    else if (argc == 1){
        printf("Please enter the name of the directory\n> ");
        fgets(folderName, 100, stdin);
        *strchr(folderName, '\n') = '\0';
    }
    printf("\n");

    DIR *pDir = opendir(folderName);

    if (pDir == 0){
        printf("Error: %s\n\n", strerror(errno));
        return 0;
    }

    return_info(pDir, folderName);

    return 0;

}

void return_info(DIR *pDir, char folderName[100]){
    struct dirent *dir;
    dir = readdir(pDir);

    printf("Statistics for Directory: %s\n\n", folderName);

    unsigned long total_size = 0;

    struct stat *buffer = malloc(sizeof(struct stat));

    while (dir != 0){
        if (dir->d_type != 4){
            stat(dir->d_name, buffer);
            printf("\t%s\t\tRegular file\t\t%ld bytes\n", dir->d_name, buffer->st_size);
            total_size += buffer->st_size;
        }
        else{
            printf("\t%s\t\tDirectory\n", dir->d_name);
        }
        dir = readdir(pDir);
    }

    printf("\n");
    printf("Total Directory Size: %ld bytes", total_size);


    closedir(pDir);
    printf("\n\n");
}