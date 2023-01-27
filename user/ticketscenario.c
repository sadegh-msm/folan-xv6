//
// Created by Alireza Zare on 1/27/2023.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

int
main(int argc, char *argv[]){
    int t = 15;
    if (settickets(15)){
        printf("successfully done...\n");
    } else {
        printf("something went wrong...\n");
    }
    exit(0);
}