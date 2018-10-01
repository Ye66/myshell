//
//  list.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "list.h"

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

void print_dir(const char* dir_str);

// list can have one or more then one arguments
int cmd_list(int argc, const char* argv[]) {
    if (argc == 1) {
        print_dir("./");
        printf("\n");
    } else {
        // list each directory with a blank line.
        for (int i = 1; i < argc; i++) {
            printf("\n%s: ", argv[i]);
            print_dir(argv[i]);
            printf("\n");
        }
    }
    return 0;
}

// print a specify directory.
void print_dir(const char* dir_str) {
    DIR* dir = opendir(dir_str);
    if (dir <= 0) {
        fprintf(stderr, "ls: %s: Fail to open dir", dir_str);
        return;
    }
    struct dirent * entry = NULL;
    while ((entry = readdir(dir)) > 0) {
        printf("%s  ", entry->d_name);
    }
}
