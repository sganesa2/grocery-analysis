//
// Created by srini on 20/10/2020.
//
#include "groceryFile.h"
#include"stats.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//countItem function is used to count the number of times each unique item is purchased
int countItem(const char *item, const FileInfo * info)
{
    int counter = info->purchases; //counter to get exact number of purchases in the file

    //basic selection sort algorithm to sort based on items from lowest to highest using strcasecmp
    int i,j,min;
    char temp[25];
    int tempNum;
    for(i=0;i<counter;i++)
    {
        min=i;
        for(j=i+1;j<counter;j++)
        {
            if(strcasecmp(info->data[j].item,info->data[min].item)<0)
            {
                min=j;
            }
        }
        tempNum=info->data[i].member;
        info->data[i].member = info->data[min].member;
        info->data[min].member = tempNum;

        tempNum=info->data[i].date;
        info->data[i].date = info->data[min].date;
        info->data[min].date = tempNum;

        strcpy(temp,info->data[i].item);
        strcpy(info->data[i].item,info->data[min].item);
        strcpy(info->data[min].item,temp);
    }

    //find the number of times each unique item is repeated
    int repeateditems=0;
    int k=0; //variable that goes to the position of the exact item that the user is searching for using strcasecmp
    while(strcasecmp(info->data[k].item,item)!=0)
    {
        k++;
        if(k>40000)
        {
            return 0;
        }
    }
    //check how many times that item is repeated
    j=k+1;
    while(strcasecmp(info->data[k].item,info->data[j].item)==0)
    {
        repeateditems++;
        j++;
    }
    return repeateditems+1;
}

//function to count the number of transactions where both item1 and item2 are encountered
int countPair(const char *item1, const char *item2, const FileInfo* info)
{
    //you have to sort based on members first, and then based on date and then items to get unique items clubbed together in a unique transaction

    int counter = info->purchases;
    //sorting based on members first
    int i,j,min;
    char temp[25];
    int tempNum;
    for(i=0;i<counter;i++)
    {
        min=i;
        for(j=i+1;j<counter;j++)
        {
            if(info->data[j].member<info->data[min].member)
            {
                min=j;
            }
        }
        tempNum=info->data[i].member;
        info->data[i].member = info->data[min].member;
        info->data[min].member = tempNum;

        tempNum=info->data[i].date;
        info->data[i].date = info->data[min].date;
        info->data[min].date = tempNum;

        strcpy(temp,info->data[i].item);
        strcpy(info->data[i].item,info->data[min].item);
        strcpy(info->data[min].item,temp);
    }
    //now sort based on date where member id's are same
    for(i=0;i<counter;i++)
    {
        min = i;
        for (j = i + 1; (info->data[min].member==info->data[j].member)&&(j<counter); j++)
        {
            if (info->data[min].date > info->data[j].date)
            {
                min = j;
            }
        }
        tempNum=info->data[i].date;
        info->data[i].date = info->data[min].date;
        info->data[min].date = tempNum;

        strcpy(temp,info->data[i].item);
        strcpy(info->data[i].item,info->data[min].item);
        strcpy(info->data[min].item,temp);
    }

    //now sort based on items for each unique transaction seperately
    for(i=0;i<counter;i++)
    {
        min = i;
        for (j = i + 1; (info->data[min].date==info->data[j].date)&&(info->data[min].member==info->data[j].member)&&(j<counter); j++)
        {
            if (strcasecmp(info->data[min].item,info->data[j].item)>0)
            {
                min = j;
            }
        }
        strcpy(temp,info->data[i].item);
        strcpy(info->data[i].item,info->data[min].item);
        strcpy(info->data[min].item,temp);
    }

    //npow you will be able to check through each item to find out if both item1 and item2 are present in each transaction
    int transactions_with_bothItems=0;
    for(i=0;i<counter;i++)
    {
        j=i+1;
         int n1=0,n2=0; //n1 checks if item1 has been encountered atleast once; and n2 checks if item2 has been encountered atleast once
        while((info->data[i].date == info->data[j].date)&&(info->data[i].member == info->data[j].member)&&(j<counter))
        {
            if((strcasecmp(info->data[j].item,item1)==0)||(strcasecmp(info->data[i].item,item1)==0))
            {
                n1++;
            }
            if((strcasecmp(info->data[j].item,item2)==0)||(strcasecmp(info->data[i].item,item2)==0))
            {
               n2++;
            }
            j++;
        }
        //if both items have been encountered atleast once then increment the count for the number of transactions with both items
        if((n1>0)&&(n2>0))
        {
            transactions_with_bothItems++;
        }
        i=j-1;
    }
 return transactions_with_bothItems;
}

//function to find out support value
double support(const char *item, const FileInfo* info)
{
    double a;
    if((info->transactions)!=0) //to check if denominator is zero or not
    {
        a= (double)(countItem(item,info))/(info->transactions); //type casting the integer numerator into double
        return a ;
    }
    else
    {
        return 0;
    }
}

//function to find out confidence value
double confidence(const char *item1, const char *item2, const FileInfo* info)
{
    double a;
    if((double)(countItem(item1,info))!=0)//to check if denominator is zero or not
    {
        a= (double)(countPair(item1,item2,info))/(double)(countItem(item1,info));//type casting the integer numerator into double
        return a ;
    }
    else
    {
        return 0;
    }
}

//function to find out lift value
double lift(const char *item1, const char *item2, const FileInfo* info)
{
    double a;
    if(support(item2,info)!=0)
    {
        a=confidence(item1,item2,info)/support(item2,info);
        return a;
    }
    else
    {
        return 0;
    }
}

//function that finds out top ten items purchased in the file
int topItems(ItemCount top[], int n, const FileInfo *info)
{
    int counter = info->purchases; //number of purchases
    int num = info->items; // number of unique items
    ItemCount x[num * sizeof(info->data->item)]; //create a new array of type ItemCount that will have only unique items from the file and the number of times each of them was purchased

    //sorting based on item to get the unique items . We do not worry about unique transactions now
    int i, j, min;
    char temp[sizeof(info->data->item)];
    int tempNum;
    for (i = 0; i < counter; i++) {
        min = i;
        for (j = i + 1; j < counter; j++) {
            if (strcasecmp(info->data[j].item, info->data[min].item) > 0) {
                min = j;
            }
        }
        tempNum = info->data[i].member;
        info->data[i].member = info->data[min].member;
        info->data[min].member = tempNum;

        tempNum = info->data[i].date;
        info->data[i].date = info->data[min].date;
        info->data[min].date = tempNum;

        strcpy(temp, info->data[i].item);
        strcpy(info->data[i].item, info->data[min].item);
        strcpy(info->data[min].item, temp);
    }

    // Assigning each element of x with an 'item' and its 'count'
    int no_of_items = 0;
    for (i = 0; i < counter; i++) {
        j = i + 1;
        x[no_of_items].count = 0;
        while ((strcasecmp(info->data[i].item, info->data[j].item) == 0) && (j < counter)) {
            (x[no_of_items].count)++; //increment count each time the same item is encountered
            j++;
        }
        x[no_of_items].item = info->data[i].item;
        x[no_of_items].count=(x[no_of_items].count)+1; //we have to account for the first time the item was encountered
        i = j - 1;
        no_of_items++;
    }

    //sort the array x based on count from highest to lowest
    for (i = 0; i<num; i++) {
        min = i;
        for (j = i + 1; j < num; j++) {
            if (x[j].count > x[min].count) {
                min = j;
            }
        }
        tempNum = x[i].count;
        x[i].count = x[min].count;
        x[min].count = tempNum;

        const char *str = x[i].item; //tricky part: swapping pointer but use 'const char'
        x[i].item= x[min].item;
        x[min].item=str;
    }
    //copy all the values of 'item' and 'count' into top array passed to the function by the user
    for(i=0;i<n;i++)
    {
        top[i].item=x[i].item;
        top[i].count=x[i].count;
    }
    //return only ten items or less
    if(no_of_items<=10)
    {
        return no_of_items;
    }
    else
    {
        return 10;
    }
}
