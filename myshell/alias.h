//
//  alias.h
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#ifndef alias_h
#define alias_h

#include <stdio.h>

struct alias_t {
    char *alias;
    char *cmd;
};

extern struct alias_t all_alias[];

void do_alias(char* cmdline);
int cmd_alias(int argc, const char* argv[]);


#endif /* alias_h */
