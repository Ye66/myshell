//
//  kill.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "kill.h"

#include <sys/types.h>
#include <signal.h>

int cmd_kill(int argc, const char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "kill: too few arguments\n");
        return 1;
    } else if (argc == 2) {
        int pid = 0;
        pid = atoi(argv[1]);
        if (!pid) {
            fprintf(stderr, "kill: Won't kill pid 0\n");
            return 1;
        }
        return kill(pid, SIGTERM);

    } else if (argc == 3) {
        if (argv[1][0] != '-') {
            fprintf(stderr, "kill: wrong arguments\n");
            return 1;
        }
        int sig = 0;
        sig = atoi(argv[1] + 1);
        
        int pid = 0;
        pid = atoi(argv[2]);
        if (!pid) {
            fprintf(stderr, "kill: Won't kill pid 0\n");
            return 1;
        }
        return kill(pid, sig);
    } else {
        fprintf(stderr, "kill: too many arugments\n");
        return 1;
    }
    return 0;
}
