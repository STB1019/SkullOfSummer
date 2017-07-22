//
//  main.c
//  LogUtility
//
//  Created by Andrea Rossi on 22/07/2017.
//  Copyright © 2017 Andrea Rossi. All rights reserved.
//

#include <stdio.h>
#define DEBUG
#define INFO
#include "log/log.h"

int main(int argc, const char * argv[]) {
    // insert code here..
    printf("\nHello, World!\n");
    _log("PROVAMI");
    printf("ASGARD");
    log_d("DEBBBBBUGGGGO");
    log_i("INFOOOO");
    return 0;
}
