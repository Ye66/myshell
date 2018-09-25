//
//  get_path.c
//  myshell
//
//  Created by 樊晔 on 2018/9/24.
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "get_path.h"

#include <stdlib.h>
#include <string.h>

struct str_list_node* get_path()
{
  
    char *path, *p;
    
    struct str_list_node* head = NULL;
    
    p = getenv("PATH");
    path = malloc((strlen(p)+1)*sizeof(char));
    strcpy(path, p);
    
    p = strtok(path, ":");
    do
    {
        head = append(head, p);
    } while ((p = strtok(NULL, ":")));
    free(path);
    return head;
}
