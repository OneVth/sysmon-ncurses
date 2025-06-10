#include <stdio.h>

typedef struct
{
    long total_kb;
    long available_kb;
    double usage; // 사용률(%)
} MemInfo;

MemInfo *GetMemInfo(void)
{
    return NULL;
}

long GetTotMem(void)
{
    return 0;
}

long GetAvailMem(void)
{
    return 0;
}

double GetMemUsage(void)
{
    return 0.0;
}

double CalMemUsage(void)
{
    return 0.0;
}