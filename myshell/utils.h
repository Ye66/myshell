//
//  utils.h
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>
#include "shell.h"

#define CWD_MAX_PATH_LEN 256

char* dup_str(const char* s);
struct build_in_cmd* find_build_in_cmd(const char* cmd);
char* find_cmd_in_path(const char* cmd_in);

int is_path(const char* str);

#endif /* utils_h */
