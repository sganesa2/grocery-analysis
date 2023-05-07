// Program 3 - Fall 2020
// This program reads a data file that contains information about grocery purchases.
// A number of statistical analysis functions are called on the data retrieved from the file.
// The main() function is not particularly interesting, and is only provided for
// simple testing. The assignment is to implement the functions declared in groceryFile.h and stats.h.

#include <stdio.h>
#include <stdbool.h>

#include "groceryFile.h"
#include "stats.h"


int main() {
    FileInfo f;
    bool success = readFile("sample500.csv", &f);
    if (!success) {
        printf("Could not open file.\n");
        return 0;
    }
    printf("%d purchases\n", f.purchases);
    printf("%d members\n", f.members);
    printf("%d transactions\n", f.transactions);
    printf("%d items\n", f.items);
    printf("---\n");
    printf("Count(yogurt) = %d\n", countItem("yogurt", &f));
    printf("Count(yogurt,bottled beer) = %d\n", countPair("yogurt", "bottled beer", &f));
    printf("Support(yogurt) = %g\n", support("yogurt", &f));
    printf("Support(bottled beer) = %g\n", support("bottled beer", &f));
    printf("Confidence(bottled beer->yogurt) = %g\n", confidence("bottled beer", "yogurt", &f));
    printf("Lift(yogurt-> bottled beer) = %g\n", lift("yogurt", "bottled beer", &f));
    printf("---\n");
    printf("Top 10 items: ");
    ItemCount items[10];
    int i, n;
    n = topItems(items, 10, &f);
    printf("(%d returned)\n", n);
    for (i=0; i < n; i++) {
        printf("%4d %s\n", items[i].count, items[i].item);
    }

    return 0;
}
