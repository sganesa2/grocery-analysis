#ifndef _STATS_H
#define _STATS_H

#include "groceryFile.h"

struct itemCount {
    const char * item;
    int count;   // number of times this item was purchased
};
typedef struct itemCount ItemCount;

int countItem(const char *item, const FileInfo * info);
int countPair(const char *item1, const char *item2, const FileInfo* info);

int topItems(ItemCount top[], int n, const FileInfo *info);

double support(const char *item, const FileInfo* info);
double confidence(const char *item1, const char *item2, const FileInfo* info);
double lift(const char *item1, const char *item2, const FileInfo* info);

#endif //_STATS_H
