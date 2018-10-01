//
//  signal.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "signal.h"
#include <signal.h>
#include "shell.h"

typedef void (*sighandler_t)(int);

void do_nothing(int t) {
}

void route_sigterm_to_child(int t) {
    if (child_pid > 0) {
        kill(child_pid, SIGTERM);
    }
}

void route_sigstp_to_child(int t) {
    if (child_pid > 0) {
        kill(child_pid, SIGTSTP);
    }
}

sighandler_t old_SIGINT_handler = NULL;
sighandler_t old_SIGTERM_handler = NULL;
sighandler_t old_SIGTSTP_handler = NULL;

void ignore_signals() {
    old_SIGINT_handler = signal(SIGINT, do_nothing);
    old_SIGTERM_handler = signal(SIGTERM, route_sigterm_to_child);
    old_SIGTSTP_handler = signal(SIGTSTP, route_sigstp_to_child);
}

void unignore_signal(int signum) {
    if (!old_SIGINT_handler) {
        signal(SIGINT, old_SIGINT_handler);
        signal(SIGTERM, old_SIGTERM_handler);
        signal(SIGTSTP, old_SIGTSTP_handler);
    }
}

