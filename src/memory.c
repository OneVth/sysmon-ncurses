#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned long long total_kb;
    unsigned long long available_kb;
    double usage; // 사용률(%)
} MemInfo;

MemInfo *GetMemInfo(void)
{
    MemInfo *memInfo = (MemInfo *)malloc(sizeof(MemInfo));
    if (memInfo == NULL)
    {
        perror("malloc");
        return NULL;
    }
    memInfo->total_kb = 0;
    memInfo->available_kb = 0;
    memInfo->usage = 0.0;

    FILE *fp = NULL;

    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL)
    {
        perror("fopen");
        free(memInfo);
        return NULL;
    }

    char line[256] = {0};
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (memInfo->total_kb != 0 && memInfo->available_kb != 0)
            break;

        if (memInfo->total_kb == 0)
            sscanf(line, "MemTotal: %8llu kB", &memInfo->total_kb);
        if (memInfo->available_kb == 0)
            sscanf(line, "MemAvailable: %12llu kB", &memInfo->available_kb);
    }

    fclose(fp);

    if (memInfo->available_kb != 0 && memInfo->total_kb != 0)
        memInfo->usage = 100 * (1 - (double)memInfo->available_kb / memInfo->total_kb);
    else
    {
        free(memInfo);
        memInfo = NULL;
    }

    return memInfo;
}

long GetTotMem(void)
{
    MemInfo* temp = GetMemInfo();
    if(temp == NULL)
        return -1;

    long totMem = temp->total_kb;
    free(temp);
    return totMem;
}

long GetAvailMem(void)
{
    MemInfo* temp = GetMemInfo();
    if(temp == NULL)
        return -1;

    long availMem = temp->available_kb;
    free(temp);
    return availMem;
}

double GetMemUsage(void)
{
    MemInfo* temp = GetMemInfo();
    if(temp == NULL)
        return -1;

    double usage = temp->usage;
    free(temp);
    return usage;
}