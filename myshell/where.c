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

void where_helper(const char* cmd);

int cmd_where(int argc, const char* argv[]){
    for (int i = 1; i < argc; i++) {
        where_helper(argv[i]);
    }
    return 0;
}

void where_helper(const char* cmd){
    struct str_list_node* p = get_path();
    while (p) {
        unsigned long buffer_len = strlen(p->content) + strlen(cmd) + 2;
        char* buffer = (char*) malloc(buffer_len);
        memset(buffer, 0, buffer_len);
        sprintf(buffer, "%s/%s", p->content, cmd);
        if (access(buffer, F_OK) == 0) {
            printf("[%s]\n", cmd);
        }
        p = p->next;
    }
}
