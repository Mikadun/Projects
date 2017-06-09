#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int i;
    printf("%d\n", argc);
    int n = argc;
    for(i = 1; i < n; i++){
        FILE *file = fopen("file_size.o", "rb");
        struct stat statistics;
        if(file == NULL){
            printf("File isn't opened\n");
            continue;
        }
        fstat(fileno(file), &statistics);
        printf("%d\n", statistics.st_size);
        close(file);
    }
    return 0;
}
