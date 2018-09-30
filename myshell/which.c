//
//  which.c
//  myshell
//
//  Created by 樊晔 on 2018/9/24.
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "which.h"

#include "get_path.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "utils.h"

void which_helper(const char* cmd, int found);

int cmd_which(int argc, const char* argv[]){
    if (argc == 1) {
        perror("which: Too few arguments.");
    }
    for (int i = 1; i < argc; i++) {
        int found = 0;
        if (find_build_in_cmd(argv[i])) {
            found = 1;
            printf("%s: shell built-in command.\n", argv[i]);
        } else {
            which_helper(argv[i], found);
        }
    }
    return 0;
}

void which_helper(const char* cmd, int found){
    const char* cmd_with_path = find_cmd_in_path(cmd);
    if (!cmd_with_path && !found) {
        fprintf(stderr, "%s: Command not found.\n", cmd);
        return;
    }
    printf("%s\n", cmd_with_path);
    free((void *)cmd_with_path);
}
