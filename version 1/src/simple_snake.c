const double P=3.141592;
const int step =3;
const double step_s=0.0628318530/2;
int q=0;
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "structs.h"
#include "shape.h"
#include "event.h"
#include "other.h"
#include "logic.h"
#ifdef main
#undef main
#endif
int xxx,yyy;
int base[1600][900]={0};
int ib=0;
const int EXIT = 12345;
int main(int argc,char* argv[]) {
    struct tankk tank[3];
    struct powerup powerup1[10];
    char c[3];
    c[0]='r';
    c[1]='g';
    int winner;
    int number;
    printf("Enter Number of players");
    scanf("%d",&number);
	SDL_Init(SDL_INIT_VIDEO);
	tank[0].score=0;
    tank[1].score=0;
	SDL_Window* window = SDL_CreateWindow("alter", 20, 20, 1600, 900, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    for (int k = 0; k <50 ; ++k) {
        struct wall* wall1;
        int n=0;
        wall1=(struct wall*)malloc(20* sizeof(struct wall));
        FILE* fp;
        fp=fopen("map1.map","r");
        //char r[50];
       // fgets(r,5,fp);
        //printf("%s\n",r);
        for (int j = 0; j <50 ; j++) {
            char r[50];
            int x1,x2,y1,y2;
            fgets(r,20,fp);
            printf("%s\n",r);
            if(r[0]=='T') {
                printf("bbb");
                break;
            }
            n++;
            sscanf(r,"%d,%d,%d,%d",&x1,&y1,&x2,&y2);
            (*(wall1+j)).x1=x1;(*(wall1+j)).y1=y1;
            (*(wall1+j)).x2=x2;(*(wall1+j)).y2=y2;
            printf("%d , %d , %d , %d \n",x1,y1,x2,y2);
        }
        for (int j = 0; j < 2 ; j++) {
            char r[50];
            int x,y,s;
            fgets(r,20,fp);
            printf("%s\n",r);
            if(r[0]=='T') {
                printf("bbb");
                break;
            }
            //n++;
            sscanf(r,"%d,%d,%d",&x,&y,&s);
            tank[j].x=x;tank[j].y = y;
            tank[j].s=s;
            printf("%d , %d , %d \n",x,y,s);
        }
        //meghdar dehy
        powerup1[0].e=1;
        powerup1[0].x=1000;
        powerup1[0].y=500;
        powerup1[0].mode=1;
        powerup1[1].e=1;
        powerup1[1].x=800;
        powerup1[1].y=200;
        powerup1[1].mode=2;
        struct bomb* bombb;
        bombb=(struct bombb*)malloc(300* sizeof(struct bomb));
        int counter=0;
        /*
        (*(wall1+2)).x1 = 190;
        (*(wall1+2)).x2 = 200;
        (*(wall1+2)).y1 = 600;
        (*(wall1+2)).y2 = 800;
        (*(wall1+1)).x1 = 200;
        (*(wall1+1)).x2 = 600;
        (*(wall1+1)).y1 = 190;
        (*(wall1+1)).y2 = 200;
        (*(wall1+3)).x1 = 0;
        (*(wall1+3)).x2 = 1600;
        (*(wall1+3)).y1 = 0;
        (*(wall1+3)).y2 = 10;
        (*(wall1+4)).x1 = 0;
        (*(wall1+4)).x2 = 1600;
        (*(wall1+4)).y1 = 890;
        (*(wall1+4)).y2 = 900;
        (*(wall1+5)).x1 = 0;
        (*(wall1+5)).y1 = 0;
        (*(wall1+5)).x2 = 10;
        (*(wall1+5)).y2 = 900;
        (*(wall1+0)).x1 = 1590;
        (*(wall1+0)).y1 = 0;
        (*(wall1+0)).x2 = 1600;
        (*(wall1+0)).y2 = 900;*/
        basemap(wall1, n);
        for (int i = 0; i < 10; i++) {
            (*(bombb+i)).e = 0;
            (*(bombb+i)).n = i;
            (*(bombb+i)).start = 0;
        }
        for (int i = 0; i < 3; i++) {
            tank[i].e = 0;
        }
        //tank[0].x = 100;
        //tank[0].y = 100;
        //tank[0].s = 0;
        tank[0].e = 1;
  //    tank[0].score=0;
        tank[1].e = 1;
//          tank[1].score=0;
        tank[1].k = 5;
        tank[0].k = 5;
        //tank[1].x = 1000;
       // tank[1].y = 100;
     //   tank[1].s = 1.7;
        //  int tx=100,ty=100,td=0;
        for(int i=0;i<5;i++)
        {
            tank[0].mode[i]=0;
            tank[1].mode[i]=0;
        }
        int bot = SDL_GetTicks();
        int FPS = 30;
        int end=0;
        int time=0;
        printf("okey");
        while (1) {
            int flag = 0;
            Uint8 *state = SDL_GetKeyboardState(NULL);
            int start_ticks = SDL_GetTicks();
            time = start_ticks - bot;
            if (handleEvents(&tank, bombb+ib, renderer, state, time) == EXIT) {
                return 1;
            }
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderClear(renderer);
            //if (quit() == EXIT) break;
            //movement(state,&tank[0],&bombb[ib%10],renderer);
            //tank(tank_x,tank_y,tank_s,window,renderer);
            maprender(wall1, renderer, 8);
            int number=0;
            for (int i = 0; i < 3; i++) {
                //int number=0;
                movement(state, &tank, bombb+(ib%300), renderer);
                if (tank[i].e == 1) {
                    number++;
                   // winner = i;
                    tank2(tank[i], renderer, c[i]);
                }
              //  if(number==1)
                    //flag=1;
            }
            //printf("%d\n",number);
            if(number==1)
            {
                if(end==0)
                {
                    end=time+3000;
                }
            }
            if(end!=0)
                if(time>end) {
                    flag = 1;
                    winner=-1;
                    for(int i=0;i<2;i++)
                    {
                        if(tank[i].e==1) {
                  //          printf("score+ %d\n",i);
                            winner=i;
                            tank[i].score++;
                        }
                    }
                }
            for (int i = 0; i < 20; i++) {
                //  printf("%d: e:%d start:%d\n",i,bombb[i].e,bombb[i].start);
                if ((*(bombb+i)).e != 0) {
                    bomb1(renderer,bombb+i, time, &tank, 2);
                }
            }
            for(int i=0;i<10;i++)
            {
                if (powerup1[i].e==1)
                {
                    poweruprenderer(renderer,&powerup1[i],&tank);
                }
            }
            char *buffer = malloc(sizeof(char) * 50);
            char *buffer1=malloc(sizeof(char)*5);
            if(counter==0)
            {
                int r=40,g=40,b=40;
                char *buffer = malloc(sizeof(char) * 50);
                sprintf(buffer, "READY?");
                if(k>0)
                {
                    printf("winner %d /n",winner);
                    if(winner==0) {
                        r=200;
                        sprintf(buffer1, "WINNER:RED");
                    }
                    if(winner==1) {
                        g=200;
                        sprintf(buffer1, "WINNER:GREEN");
                    }
                }
                //printf("%s", buffer)
                SDL_RenderSetScale(renderer,25,25);
                stringRGBA(renderer, 10,15, buffer, 0, 0, 0,150);
                SDL_RenderSetScale(renderer,5,5);
                if(k>0)
                stringRGBA(renderer,100,120,buffer1,r,g,b,200);
                SDL_RenderSetScale(renderer,1,1);
                free(buffer);
            }
            filledCircleRGBA(renderer,xxx,yyy,5,0,255,0,100);
            *buffer = malloc(sizeof(char) * 50);
            sprintf(buffer, "score: red:%d  green:%d elapsed time: %ds  ", tank[0].score,tank[1].score, time / 1000);
            //printf("%s", buffer);
           // SDL_Delay(500);
           SDL_RenderSetScale(renderer,2,2);
            stringRGBA(renderer, 20, 20, buffer, 0, 0, 0, 255);
            SDL_RenderSetScale(renderer,1,1);
            SDL_RenderPresent(renderer);
            free(buffer);
            if(counter==0) {
                bot+=2000;
                SDL_Delay(2000);
            }
            if( 1== flag) {

                break;
            }
            counter++;
            while (SDL_GetTicks() - start_ticks < 1000 / FPS);
        }
       // free(wall1);
     //   free(bombb);
        printf("counter:%d\n",1000*counter/time);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}