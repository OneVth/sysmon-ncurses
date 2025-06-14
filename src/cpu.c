#include <stdio.h>
#include "cpu.h"

typedef struct 
{
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
    unsigned long long guest;
    unsigned long long guest_nice;

    double usage;   // CPU usage percentage
} CpuInfo;

CpuInfo* GetCpuInfo(void)
{
    return NULL;
}

double GetCpuUsage(void)
{
    return 0.0;
}