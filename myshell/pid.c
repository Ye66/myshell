//
//  pid.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "pid.h"
#include <sys/types.h>
#include <unistd.h>

int cmd_pid(int argc, const char* argv[]) {
    if (argc > 1) {
        fprintf(stderr, "pwd: Too many arguments\n");
    }
    pid_t p = getpid();
    printf("%d\n", p);
    return 0;
}
