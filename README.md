# grocery-analysis

Download the grocery.c(the drive function) file along with the two header files: groceryFile.h and stats.h, and two source code files that define the functions declared in the header files:
groceryFile.c -- function for reading purchase data from a CSV file.
stats.c -- functions to extract statistics from the file data.
All of these files are compiled and linked together to create a single executable program.

## Description of the program:
This program is used to read and analyze the statistics of a purchase at a grocery store. We will be obtaining data about grocery store purchases from the files: 'groceries.csv', and 'sample500.csv'.

## Statistics of a grocery data calculated by my program:
• Support(X) = fraction of transactions that contain item X
• Confidence(X,Y) = fraction of transactions containing X that also contain Y
• Lift(X,Y) = increase in probability of purchasing Y when X is purchased, compared to the probability of purchasing Y with no knowledge of X. If lift is greater than 1, there is a high association of Y with X -- in other words, if X is purchased, it’s more likely that Y is also purchased.
My program can calculate these statistics for any given .csv file that contains grocery data in the following order:
• Member (integer)
• Date (string)
• Item (string)
Just as a note, as a default, my program will be calculating the above stats for the grocery file: 'sample500.csv'.


