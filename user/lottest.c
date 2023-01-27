//
// Created by Mohamad Sadegh Mohamadi on 1/27/2023 AD.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/pstat.h"
#define LOOP 1326044832

//Avoid optimization
#pragma GCC push_options
#pragma GCC optimize ("O0")

void spin() {
    long x = 0;
    while (x < LOOP) x++;
}

#pragma GCC pop_options

void printpinfo(int pid)
{
    struct processes_info pi = {0};
    getprocessinfo(&pi);
    int i;
    for (i = 0; i < NPROC; i++) {
        if(pi.pids[i] == pid) {
            printf("Number of tickets that PID %d has: %d\n", pid, pi.tickets[i]);
            printf("Number of ticks that PID %d has: %d\n", pid, pi.ticks[i]);
            printf("Is the process with PID %d in use? (0 or 1): %d\n\n\n", pid, pi.num_processes);
            break;
        }
    }
}

int
main(int argc, char *argv[])
{
    int pid1, pid2, pid3;
    int first;

    settickets(900);

    //Create different processes with 10, 20 and 30 tickets
    if ((pid1 = fork()) == 0) {
        settickets(10);
        int pp1 = getpid();
        printf("Process started with PID %d\n\n", pp1);
        spin();
        printf("Process with PID %d finished!\n\n", pp1);
        printpinfo(pp1);
        exit(0);
    }
    else if ((pid2 = fork()) == 0) {
        settickets(20);
        int pp2 = getpid();
        printf("Process started with PID %d\n\n", pp2);
        spin();
        printf("Process with PID %d finished!\n\n", pp2);
        printpinfo(pp2);
        exit(0);
    }
    else if ((pid3 = fork()) == 0) {
        settickets(30);
        int pp3 = getpid();
        printf("Process started with PID %d\n\n", pp3);
        spin();
        printf("Process with PID %d finished!\n\n", pp3);
        printpinfo(pp3);
        exit(0);
    }

    int pid11 = pid1;

    if((first = wait(&pid11))>0 || (first = wait(&pid2))>0 || (first = wait(&pid3))>0){
        if(first == pid1){
            printpinfo(pid3);
            printpinfo(pid2);

            kill(pid2);
            kill(pid3);
        }else if(first == pid2){
            printpinfo(pid3);
            printpinfo(pid1);

            kill(pid1);
            kill(pid3);
        }else{
            printpinfo(pid2);
            printpinfo(pid1);

            kill(pid1);
            kill(pid2);
        }
    }

    exit(0);
}