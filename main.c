#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    DIR *pDir = opendir("./");

    struct dirent *dir;
    dir = readdir(pDir);

    printf("Statistics for Directory: .\n\n");

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
    return 0;
}