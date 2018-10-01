//
//  str_list.c
//  myshell
//
//  Created by 樊晔 on 2018/9/24.
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "str_list.h"

#include <stdlib.h>
#include <string.h>

// linked list
struct str_list_node* append(struct str_list_node* head,
                            char* content){
    struct str_list_node* node = (struct str_list_node*) malloc(sizeof(struct str_list_node));
    if (!node) exit(1);
    
    node->content = (char*) malloc(strlen(content)+1);
    strcpy(node->content, content);
    node->next = NULL;
    
    if (!head) return node;
    struct str_list_node* tail = head;
    while (tail->next){
        tail = tail->next;
    }
    tail->next = node;
    return head;
}

void free_str_list(struct str_list_node* head){
    while (head){
        struct str_list_node* next = head->next;
        free(head->content);
        free(head);
        head = next;
    }
}
