//
//  history.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "history.h"
#include "str_list.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

#define HISTORY_DEFAULT 10

// store all history in a linked list
struct str_list_node* head = NULL;

// print recent n history
void print_history(int n);

void add_history(const char* cmdline) {
    head = append(head, cmdline);
}

int cmd_history(int argc, const char* argv[]) {
    if (argc == 1) {
        print_history(HISTORY_DEFAULT);
    } else if (argc == 2) {
        int len = 0;
        len = atoi(argv[1]);
        print_history(len);
    } else {
        fprintf(stderr, "history: too many arguments\n");
        return 1;
    }
    return 0;
}

void print_history(int n) {
    int i = 0;
    struct str_list_node* node = head;
    while (node && i++ < n) {
        printf("%s\n", node->content);
        node = node->next;
    }
}
