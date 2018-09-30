//
//  signal.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "signal.h"
#include <signal.h>

typedef void (*sighandler_t)(int);

void do_nothing(int t) {
}

sighandler_t old_SIGINT_handler = NULL;
sighandler_t old_SIGTERM_handler = NULL;
sighandler_t old_SIGTSTP_handler = NULL;

void ignore_signals() {
    old_SIGINT_handler = signal(SIGINT, do_nothing);
    old_SIGTERM_handler = signal(SIGTERM, do_nothing);
    old_SIGTSTP_handler = signal(SIGSTOP, do_nothing);
}

void unignore_signal(int signum) {
    if (!old_SIGINT_handler) {
        signal(SIGINT, old_SIGINT_handler);
        signal(SIGTERM, old_SIGTERM_handler);
        signal(SIGSTOP, old_SIGTSTP_handler);
    }
}

