//
// Created by Mohamad Sadegh Mohamadi on 1/27/2023 AD.
//
#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct processes_info {
    int num_processes;
    int tickets[NPROC]; // the number of tickets this process has
    int pids[NPROC];     // the PID of each process
    int ticks[NPROC];   // the number of ticks each process has accumulated
};

#endif // _PSTAT_H_