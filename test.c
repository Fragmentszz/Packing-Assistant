#include<stdio.h>

int max(int a,int b)
{
    int max;
    if(a > b)   max = a;
    else max = b;
    return max;   
}

int main()
{
    int a = 1,b = 2;
    printf("%d\n",max(1,2));

    return 0;
}