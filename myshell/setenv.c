//
//  setenv.c
//  myshell
//
//  Copyright © 2018 樊晔. All rights reserved.
//

#include "setenv.h"
#include "printenv.h"

#include <stdlib.h>

// command setenv
// 1 argument: printenv
// 2 arguments: setenv with specify key, value is ""
// 3 arguments: setenv with specify key and value
int cmd_setenv(int argc, const char* argv[]) {
    if (argc == 1) {
        return cmd_printenv(argc, argv);
    } else if (argc == 2){
        return setenv(argv[1], "", 1);
    } else if (argc == 3) {
        return setenv(argv[1], argv[2], 1);
    } else {
        fprintf(stderr, "setenv: too many arguments for setenv");
        return 1;
    }
}
