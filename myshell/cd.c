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

int cmd_cd(int argc, const char* argv[]) {
    if (argc > 2) {
        fprintf(stderr, "cd: Too many arguments\n");
        return 1;
    }

    if (argc == 1) {
        char* home = getenv("HOME");
        if (!home) {
            fprintf(stderr, "cd: Fail to get home\n");
        }
        return chdir(home);
    }
    static char buffer[CWD_MAX_PATH_LEN] = {0};
    static const char* last_cwd = NULL;
    if (!strcmp(argv[1], "-") && last_cwd) {
        return chdir(last_cwd);
    } else {
        last_cwd = getcwd(buffer, CWD_MAX_PATH_LEN);
        return chdir(argv[1]);
    }
}
