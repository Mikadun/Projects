#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int parametrs[3];

int main(int argc, char* argv[]){
    int i;
    if(argc == 1) return 0;
    printf("============================================================\n");
    printf("|| WC by Gribak Yaroslav. Ne bejte, pozhaluista\n");
    enum {wait_parametr, wait_file} read_mode = wait_parametr;
    for(i = 1; i < argc; i++){
        freopen(argv[i], "r", stdin);
        if(read_mode == wait_parametr && argv[i][0] == '-'){
            if(strlen(argv[i]) == 2){
                switch(argv[i][1]){
                    case('c'):
                        parametrs[0] = 1;
                        continue;
                    case('l'):
                        parametrs[1] = 1;
                        continue;
                    case('w'):
                        parametrs[2] = 1;
                        continue;
                }
            }
            printf("|| Unknown parametr '%s'\n", argv[i]);
            continue;
        }
        read_mode = wait_file;
        struct stat statistics;
        printf("============================================================\n");
        if(stdin == NULL){
            printf("|| File '%s' isn't opened\n", argv[i]);
            continue;
        }
        fstat(fileno(stdin), &statistics);

        long long c;
        int str_count = 1, word_count = 1, space_mode = 1;
        while((c = getchar()) != EOF){
            if(c == '\n') {
                str_count++;
                word_count++;
            }
            if(c == ' ') {
                if(!space_mode) word_count++;
                space_mode = 1;
            } else {
                space_mode = 0;
            }
        }
        printf("|| File '%s':\n", argv[i]);
        if(parametrs[0]) printf("||  - Weighs %d byte\n", statistics.st_size);
        if(parametrs[1]) printf("||  - String count %d\n", str_count);
        if(parametrs[2]) printf("||  - Word count %d\n", word_count);
    }
    printf("============================================================");
    return 0;
}
