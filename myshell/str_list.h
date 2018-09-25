//
//  str_list.h
//  myshell
//
//  Created by 樊晔 on 2018/9/24.
//  Copyright © 2018 樊晔. All rights reserved.
//

#ifndef str_list_h
#define str_list_h

#include <stdio.h>

struct str_list_node{
    char* content;
    struct str_list_node* next;
};

struct str_list_node* append(struct str_list_node* head,
                             char* content);
void free_str_list(struct str_list_node* head);

#endif /* str_list_h */
