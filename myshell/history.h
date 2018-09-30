//
//  history.h
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#ifndef history_h
#define history_h

#include <stdio.h>

void add_history(const char* cmd);
int cmd_history(int argc, const char* argv[]);

#endif /* history_h */
