//
//  main.c
//  hlink
//
//  Created by Vladislav Orlov on 10.09.15.
//  Copyright (c) 2015 Vladislav Orlov. All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void pinfo() {
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "\thlink make src_dir target_dir\n");
    fprintf(stderr, "\thlink remove target_dir\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) {
        fprintf(stderr, "error: see info below\n");
        pinfo();
        return 1;
    }
    
    if (strcmp(argv[1], "make") == 0) {
        //unlink doesn't understand dir as target
        if (argv[3][strlen(argv[3])-1] == '/') {
            unsigned long idxToDel = strlen(argv[3]) - 1;
            memmove(&argv[3][idxToDel], &argv[3][idxToDel + 1], strlen(argv[3]) - idxToDel);
        }
        
        int res = link(argv[2], argv[3]);
        
        if (res != 0)
            perror("link");
    } else if (strcmp(argv[1], "remove") == 0) {
        int res = unlink(argv[2]);
        
        if (res != 0)
            perror("unlink");
    } else {
        pinfo();
    }
    
    return 0;
}