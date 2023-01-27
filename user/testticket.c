//
// Created by Mohamad Sadegh Mohamadi on 1/26/2023 AD.
//
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/pstat.h"

int heavy_calculation(void) {
    int a = 0;
    int b = 0;
    for (int i = 0; i < 100000; ++i) {
        for (int j = 0; j < 10000; ++j) {
            a = i - j;
            b = a % 10;
        }
    }
    return a * b;
}

int main() {
    settickets(10);

    int pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // settickets(20);

        printf("calculation res: %d\n", heavy_calculation());

        struct processes_info ps;
        getprocessinfo(&ps);

        printf("child call to getpinfo results:\n");
        for (int j = 0; j < ps.num_processes; ++j) {
            printf("pid %d, tickets %d, ticks %d\n", ps.pids[j], ps.tickets[j], ps.ticks[j]);
        }

        exit(0);
    } else {
        wait(0);
        printf("child finished\n");

        struct processes_info ps;
        getprocessinfo(&ps);

        printf("parent call to getpinfo results:\n");
        for (int j = 0; j < ps.num_processes; ++j) {
            printf("pid %d, tickets %d, ticks %d\n", ps.pids[j], ps.tickets[j], ps.ticks[j]);
        }

        exit(0);
    }
}
