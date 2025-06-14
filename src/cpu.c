#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

    double usage; // CPU usage percentage
} CpuInfo;

CpuInfo *GetCpuInfo(void)
{
    CpuInfo *cpuInfo = (CpuInfo *)malloc(sizeof(CpuInfo));

    FILE *fp = NULL;
    fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("fopen");
        free(cpuInfo);
        return NULL;
    }

    char line[256] = {0};
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "cpu ", 4) == 0)
        {
            int parsed = sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                                &cpuInfo->user, &cpuInfo->nice, &cpuInfo->system, &cpuInfo->idle,
                                &cpuInfo->iowait, &cpuInfo->irq, &cpuInfo->softirq, &cpuInfo->steal,
                                &cpuInfo->guest, &cpuInfo->guest_nice);

            if (parsed != 10)
            {
                fprintf(stderr, "Error: parsed only %d fields from /proc/stat\n", parsed);
                free(cpuInfo);
                cpuInfo = NULL;
            }
            break;
        }
    }

    fclose(fp);
    return cpuInfo;
}

double GetCpuUsage(void)
{
    CpuInfo *cpuInfo_1 = GetCpuInfo();
    sleep(1);
    CpuInfo *cpuInfo_2 = GetCpuInfo();
    if (!cpuInfo_1 || !cpuInfo_2)
    {
        free(cpuInfo_1);
        free(cpuInfo_2);
        return -1.0;
    }

    unsigned long long total_time_1 =
        cpuInfo_1->user + cpuInfo_1->nice + cpuInfo_1->system +
        cpuInfo_1->idle + cpuInfo_1->iowait + cpuInfo_1->irq +
        cpuInfo_1->softirq + cpuInfo_1->steal + cpuInfo_1->guest +
        cpuInfo_1->guest_nice;

    unsigned long long total_time_2 =
        cpuInfo_2->user + cpuInfo_2->nice + cpuInfo_2->system +
        cpuInfo_2->idle + cpuInfo_2->iowait + cpuInfo_2->irq +
        cpuInfo_2->softirq + cpuInfo_2->steal + cpuInfo_2->guest +
        cpuInfo_2->guest_nice;

    unsigned long long active_time_1 = total_time_1 - (cpuInfo_1->idle + cpuInfo_1->iowait);
    unsigned long long active_time_2 = total_time_2 - (cpuInfo_2->idle + cpuInfo_2->iowait);
    double usage = (double)(active_time_2 - active_time_1) / (total_time_2 - total_time_1) * 100;

    free(cpuInfo_1);
    free(cpuInfo_2);
    return usage;
}