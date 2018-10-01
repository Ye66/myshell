//
//  cd.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "cd.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

// try cd, if failed print error message
int try_cd(const char * dir);

// command cd function
int cmd_cd(int argc, const char* argv[]) {
    if (argc > 2) {
        fprintf(stderr, "cd: Too many arguments\n");
        return 1;
    }

    if (argc == 1) {
        char* home = getenv("HOME");
        if (!home || chdir(home)) {
            fprintf(stderr, "cd: Fail to get home\n");
        }
        return chdir(home);
    }
    // cd to a directory
    static char buffer[CWD_MAX_PATH_LEN] = {0};
    static const char* last_cwd = NULL;
    if (!strcmp(argv[1], "-") && last_cwd) {
        return try_cd(last_cwd);
    } else {
        last_cwd = getcwd(buffer, CWD_MAX_PATH_LEN);
        return try_cd(argv[1]);
    }
}

int try_cd(const char * dir){
    if (!chdir(dir)) {
        return 0;
    } else {
        fprintf(stderr, "cd: Fail to get to directory %s\n", dir);
        return 1;
    }
}
