//
// Created by srini on 11/10/2020.
//
#include "groceryFile.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void transactionFinder(FileInfo *a, int num); //this is a function to assign correct transaction id's to all the purchases in the file

bool readline(FILE *reader,FileInfo *file, int count);//this fucntion reads each line seperately and stores data into the 'data' array of Purchases structure

void uniqueitems(FileInfo *a, int num);// this is a small function to find out number of unique items present in the file

//the readfile() function is only used to allocate 40,000 elements to the data array, and then keep calling the readline() function multiple times through a while loop to read each purchase
bool readFile(const char *filename,FileInfo *file)
{
    file->data = (Purchase * ) malloc(40000 * sizeof(Purchase)); //dynamically allocate an array of type 'Purchase' with 40,000 elements
    int count=0; //count variable to count the total number of purchases made
    char readstr[60]; //read only the first line in grocery.csv
    FILE *infile;
    infile = fopen(filename, "r");

    //return false if the file doesn't exist
    if(!infile)
    {
        return false;
    }
    fgets(readstr,60,infile); //read only the first line
    bool p= true;

    //while loop to read all the transactions from the file by repeatedly calling readline()
    while(p)
    {
        p=readline(infile,file,count);
        count++;
    }

    file->purchases = count-1;
    fclose(infile);

    transactionFinder(file,count-1);
    uniqueitems(file,count-1);
    return true;
}

//function that reads each purchase from the file
bool readline(FILE *reader,FileInfo *file, int count)
{
    char a,b,c,d ; //variable to store unwanted characters like commas and '/' and '-'
    int x,y,z; // variables to store the month, day and year

    //this if condition will tell the function to stop reading when you reach the end-of-file
    if(fscanf(reader,"%d",&(file->data[count].member))==EOF)
    {
        return false;
    }

    fscanf(reader,"%c",&a);//scan a comma

    fscanf(reader,"%d%c%d%c%d%c",&x,&b,&y,&c,&z,&d); //scan the entire date from a purchase

    //assign different values for date based on two different formats- mm/dd/yyyy and dd-mm-yyyy
    if(b=='/')
    {
        file->data[count].date = (1000000*x)+(10000*y)+z;
    }
    else
    {
        file->data[count].date = (10000*x)+(1000000*y)+z;
    }

    char *itemStr = file->data[count].item; //string to store the item name
    char itemChar='0';
    //stops storing once you encounter new line
    while(itemChar!='\n')
    {
        fscanf(reader,"%c",&itemChar);
        if(itemChar=='\n')
        {
            *itemStr='\0';
        }
        else
        {
            *itemStr=itemChar;
            itemStr++;
        }
    }
    return true;
}

//function to assign transaction id's and find out number of unique members
void transactionFinder(FileInfo *a, int num)
{
    //just following the selection sort algorithm
int i, j, min;
char temp[25]; //temporary string used for swapping
int tempNum; // temporary integer used for swapping

//sorting based on member id from lowest to highest
    for(i=0;i<num;i++)
    {
        min = i;
        for (j = i + 1; j < num; j++)
        {
            if (a->data[min].member>a->data[j].member)
            {
                min = j;
            }
        }
       tempNum=a->data[i].member;
        a->data[i].member = a->data[min].member;
        a->data[min].member = tempNum;

        tempNum=a->data[i].date;
        a->data[i].date = a->data[min].date;
        a->data[min].date = tempNum;

        strcpy(temp,a->data[i].item);
        strcpy(a->data[i].item,a->data[min].item);
        strcpy(a->data[min].item,temp);
    }
    //code to find out number of uniques members
    int no_of_members=0;
    for(i=0;i<num;i++)
    {
        j=i+1;
        while((a->data[i].member == a->data[j].member)&&(j<num))
        {
            j++;
        }
        i=j-1;
        no_of_members++;
    }
    a->members=no_of_members;

    //sorting based on date only for purchases that have the same member-id.
    //this is needed to get the unique transactions clubbed together
    for(i=0;i<num;i++)
    {
        min = i;
        for (j = i + 1; (a->data[min].member==a->data[j].member)&&(j<num); j++) {
                if (a->data[min].date > a->data[j].date) {
                    min = j;
                }
        }
        tempNum=a->data[i].date;
        a->data[i].date = a->data[min].date;
        a->data[min].date = tempNum;

        strcpy(temp,a->data[i].item);
        strcpy(a->data[i].item,a->data[min].item);
        strcpy(a->data[min].item,temp);
    }

    //assigning each purchase a transaction id starting from 1 and just incrementing
    int transid=1;
    for(i=0;i<num;i++)
    {
        for (j = i + 1; ((a->data[i].member == a->data[j].member)&&(a->data[i].date == a->data[j].date))&&(j<num); j++)
        {
                a->data[j-1].trans_id= transid;
        }
        i=j-1;
        transid++;
    }
    a->transactions=transid-1;
}

//function to find out the number of unique items
void uniqueitems(FileInfo *a, int num)
{
    //sort based on items from lowest to highest using strcasecmp
    int i,j,min;
    char temp[25];
    int tempNum;
    for(i=0;i<num;i++)
    {
        min=i;
        for(j=i+1;j<num;j++)
        {
         if(strcasecmp(a->data[j].item,a->data[min].item)<0)
         {
             min=j;
         }
        }
        tempNum=a->data[i].member;
        a->data[i].member = a->data[min].member;
        a->data[min].member = tempNum;

        tempNum=a->data[i].date;
        a->data[i].date = a->data[min].date;
        a->data[min].date = tempNum;

        strcpy(temp,a->data[i].item);
        strcpy(a->data[i].item,a->data[min].item);
        strcpy(a->data[min].item,temp);
    }
    //to count number of unique items
    int no_of_items=0;
    for(i=0;i<num;i++)
    {
        j=i+1;
        while((strcasecmp(a->data[i].item,a->data[j].item)==0)&&(j<num))
        {
            j++;
        }
        i=j-1;
        no_of_items++;
    }
    a->items=no_of_items;
}


