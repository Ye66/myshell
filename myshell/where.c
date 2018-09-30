//
//  where.c
//  myshell
//
//  Created by 樊晔 on 2018/9/24.
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "where.h"

#include "get_path.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "utils.h"

void where_helper(const char* cmd);

int cmd_where(int argc, const char* argv[]){
    for (int i = 1; i < argc; i++) {
        if (find_build_in_cmd(argv[i])) {
            printf("%s: shell built-in command.\n", argv[i]);
        }
        where_helper(argv[i]);
    }
    return 0;
}

void where_helper(const char* cmd){
    const char* cmd_with_path = find_cmd_in_path(cmd);
    if (!cmd_with_path) fprintf(stderr, "%s: Command not found.\n", cmd);
    do {
        printf("%s\n", cmd_with_path);
        free((void *)cmd_with_path);
    } while( (cmd_with_path = find_cmd_in_path(NULL)));
}
