//
//  exit.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "exit.h"
#include <stdlib.h>

int cmd_exit(int argc, const char* argv[]){
    printf("Thanks for using my shell. Bye!\n");
    exit(0);
    return 0;
}
