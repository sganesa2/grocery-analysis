#ifndef _GROCERYFILE_H
#define _GROCERYFILE_H

#include <stdbool.h>

struct purchase {
    int trans_id;   // transaction that includes this purchase
    int member;     // member who made this purchase
    int date;       // date in number form: month * 1000000 + day * 10000 + year
    char item[31];
};
typedef struct purchase Purchase;


struct fileInfo {
    int purchases;        // number of purchases in file
    int transactions;     // number of transactions in file
    int members;          // number of unique members
    int items;            // number of unique items
    Purchase *data;       // array of purchases
};
typedef struct fileInfo FileInfo;

// opens file and reads data, fills in values in fileInfo
// returns true if file opened, false if cannot be opened
bool readFile(const char *filename, FileInfo *);

#endif //_GROCERYFILE_H
