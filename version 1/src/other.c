//
// Created by A.M.M on 12/27/2018.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "structs.h"
#include "shape.h"
#include "event.h"
double distance(double x1,double y1,double x2 ,double y2)
{
    return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}
int max(int a,int b)
{
    return a*(a>=b)+b*(b>a);
}
int min(int a,int b)
{
    return a+b-max(a,b);
}
int readint (char a[],int i)
{
    int x=0;
    for(;a[i]>='0'&&a[i]<='9';i++)
    {
        x*=10;
        x+=a[i]-'0';
    }
    return x;
}
int intsize (int x)
{
    int i=0;
    while(x>0)
    {
        i++;
        x/=10;
    }
    return i;
}