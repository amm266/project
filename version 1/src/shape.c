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
#include "logic.h"
#include "other.h"
extern int base[1600][900];
extern int xxx,yyy;
extern const double P;
void tank2 (struct tankk tank, struct SDL_Renderer* renderer,char color){
    int r=40,g=40,b=40,rr=0,gg=0,bb=0;
    switch (color)
    {
        case 'r' :
        r=130;
            break;
        case 'g' :
            g=130;
            break;
        case 'b' :
            b=130;
            break;
    }
    if(tank.mode[0]==1){
        r=50+rand()%156;
        g=50+rand()%156;
        b=50+rand()%156;
    }
    if(tank.mode[1]==1)
    {
        rr=50+rand()%156;
        gg=50+rand()%156;
        bb=50+rand()%156;
    }
    thickLineRGBA(renderer,tank.x+40*cos(tank.s),tank.y+40*sin(tank.s),tank.x-40*cos(tank.s),tank.y-40*sin(tank.s),55,r,g,b,255);
  //  filledCircleRGBA(renderer, tank.x, tank.y, 30, 200, 200, 200, 255);
    filledCircleRGBA(renderer, tank.x, tank.y, 14, 100, 100, 100, 255);
    thickLineRGBA(renderer,tank.x+50*cos(tank.s),tank.y+50*sin(tank.s),tank.x,tank.y,3,rr,gg,bb,255);
    /* filledCircleRGBA(renderer,tank.x+50*cos(tank.s),tank.y+50*sin(tank.s),5,0,0,255,255);
     filledCircleRGBA(renderer,tank.x-40*cos(tank.s),tank.y-40*sin(tank.s),5,0,0,255,255);
     filledCircleRGBA(renderer,tank.x-30*sin(tank.s),tank.y+30*cos(tank.s),5,0,0,255,255);
     filledCircleRGBA(renderer,tank.x+30*sin(tank.s),tank.y-30*cos(tank.s),5,0,0,255,255);
     filledCircleRGBA(renderer,tank.x+40*cos(tank.s)-30*sin(tank.s),tank.y+40*sin(tank.s)+30*cos(tank.s),5,0,0,255,255);
    filledCircleRGBA(renderer,tank.x+40*cos(tank.s)+30*sin(tank.s),tank.y+40*sin(tank.s)-30*cos(tank.s),5,0,0,255,255);
    filledCircleRGBA(renderer,tank.x-40*cos(tank.s)-30*sin(tank.s),tank.y-40*sin(tank.s)+30*cos(tank.s),5,0,0,255,255);
    filledCircleRGBA(renderer,tank.x-40*cos(tank.s)+30*sin(tank.s),tank.y-40*sin(tank.s)-30*cos(tank.s),5,0,0,255,255);
    //new
    filledCircleRGBA(renderer,tank.x+40*cos(tank.s)+15*sin(tank.s),tank.y+40*sin(tank.s)-15*cos(tank.s),5,0,255,255,255);
    filledCircleRGBA(renderer,tank.x+40*cos(tank.s)-15*sin(tank.s),tank.y+40*sin(tank.s)+15*cos(tank.s),5,0,255,255,255);
    filledCircleRGBA(renderer,tank.x-40*cos(tank.s)-15*sin(tank.s),tank.y-40*sin(tank.s)+15*cos(tank.s),5,0,255,255,255);
    filledCircleRGBA(renderer,tank.x-40*cos(tank.s)+15*sin(tank.s),tank.y-40*sin(tank.s)-15*cos(tank.s),5,0,255,255,255);
    filledCircleRGBA(renderer,tank.x+20*cos(tank.s)-30*sin(tank.s),tank.y+20*sin(tank.s)+30*cos(tank.s),5,255,255,255,255);
    filledCircleRGBA(renderer,tank.x+20*cos(tank.s)+30*sin(tank.s),tank.y+20*sin(tank.s)-30*cos(tank.s),5,255,255,255,255);
    filledCircleRGBA(renderer,tank.x-20*cos(tank.s)-30*sin(tank.s),tank.y-20*sin(tank.s)+30*cos(tank.s),5,255,255,255,255);
    filledCircleRGBA(renderer,tank.x-20*cos(tank.s)+30*sin(tank.s),tank.y-20*sin(tank.s)-30*cos(tank.s),5,255,255,255,255);*/
}
int bomb1 (struct SDL_Renderer* renderer, struct bomb* bomb1, int bot, struct tankk* tank1,int n){
    struct powerup powerup1;
    if((*bomb1).x>1600||(*bomb1).x<0||(*bomb1).y>900 ||(*bomb1).y<0)
    {
        (*bomb1).e=0;(*bomb1).x=0;
        (*bomb1).y=0;(*bomb1).v=0;
        (*bomb1).s=0;
        return 1;
    }
    if(bot-(*bomb1).start>5000) {
        (*(tank1+(*bomb1).t)).k+=1;
        //printf("k++ tank%d\n",(*bomb1).t);
        (*bomb1).e = 0;
        (*bomb1).x = 0;
        (*bomb1).y = 0;
        (*bomb1).v = 0;
        (*bomb1).s = 0;
        return 1;
    }
    if(bot-(*bomb1).start>50){
        for(int i=0;i<n;i++)
        {
            if((*(tank1+i)).e ==1 )
            {
                if(destroy(1,(tank1+i ),bomb1,powerup1)==1)
                {
                    (*(tank1+(*bomb1).t)).k++;
                }
            }
        }

    }

    filledCircleRGBA(renderer,(*bomb1).x,(*bomb1).y,5,0,0,0,255);
    struct bomb bomb=(*bomb1);
    int x=(*bomb1).x,y=(*bomb1).y;
    double ix=cos((*bomb1).s),iy=sin((*bomb1).s);
    for(int i=0;i<20;i++)
    {
        int xx=x+i*ix,yy=y+i*iy;
        xxx=xx;yyy=yy;
        if(base[xx][yy]==1)
        {
            //printf("mmmmm are\n");
            bombbuffer(bomb1,i);
            break;
        }
    }
    (*bomb1).x += (*bomb1).v*cos((*bomb1).s);
    (*bomb1).y += (*bomb1).v*sin((*bomb1).s);
}
void wallrender (struct wall wall1,struct SDL_Renderer* renderer)
{
    boxRGBA(renderer,(wall1).x1,(wall1).y1,(wall1).x2,(wall1).y2,100,100,10,255);
}
void maprender (struct wall wall1[], struct SDL_Renderer* renderer,int n)
{
    for(int i=0;i<n;i++)
        wallrender(wall1[i],renderer);
}
void poweruprenderer (struct SDL_Renderer* renderer,struct powerup* powerup1, struct tankk* tank1 ){
    switch ((*powerup1).mode)
    {
        case 1:
            filledCircleRGBA(renderer,(*powerup1).x,(*powerup1).y,18,rand()%256,rand()%256,rand()%256,250);
            for(int i=0;i<2;i++) {
                if (hittank((*(tank1+i)), (*powerup1).x, (*powerup1).y, 5) == 1) {
                    (*(tank1+i)).mode[0] = 1;
                    (*powerup1).e = 0;
                    (*powerup1).x = 0;
                    (*powerup1).y = 0;
                }
            }
            break;
        case 2:
            filledCircleRGBA(renderer,(*powerup1).x,(*powerup1).y,18,200,40,200,255);
            for(int i=0;i<2;i++) {
                if (hittank((*(tank1+i)), (*powerup1).x, (*powerup1).y, 5) == 1) {
                    (*(tank1+i)).k=100;
                    (*(tank1+i)).mode[1]=1;
                    (*powerup1).e = 0;
                    (*powerup1).x = 0;
                    (*powerup1).y = 0;
                }
            }
    }
}