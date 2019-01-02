//
// Created by A.M.M on 12/27/2018.
//
extern int q;
extern int ib;
extern int base[1600][900];
extern int xxx,yyy;
extern const double P;
extern const int step ;
extern const double step_s;
extern const EXIT;
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "structs.h"
#include "shape.h"
#include "logic.h"
void fire (int i, struct bomb* bomb1, struct tankk* tank1,int bot)
{
    /*if(q%2==0)
    {
        //(*tank1).k--;
        q++;
        return;
    }*/
    //printf("fire! %lf %lf %lf \n",tank1.x+65*cos(tank1.s),(tank1).y+65*sin(tank1.s),tank1.s);
    if((*tank1).k<=0)
        return;
    (*tank1).k--;
  //
  // printf("k:%d\n",(*tank1).k);
    (*bomb1).start = bot;
    (*bomb1).e = 1 ;
    (*bomb1).x = (*tank1).x+70*cos((*tank1).s);
    (*bomb1).y = (*tank1).y+70*sin((*tank1).s);
    (*bomb1).s = (*tank1).s;
    (*bomb1).v = 12;
    (*bomb1).t = i;
    ib++;
}
int fireevent(int i, Uint8* state, struct tankk *tank1 , struct bomb *bomb1, struct SDL_Renderer* renderer,int bot)
{
    /*if(state[SDL_SCANCODE_M]==1){
        (*bomb1).e=1;
        if((*tank1).k>0)
      //      fire(0,bomb1,tank1,bot);
    }
    if(state[SDL_SCANCODE_V]==1){
        (*bomb1).e=1;
    //    fire(1,bomb1,tank1,bot);
    }*/
}
void movement (Uint8* state, struct tankk *tank1 , struct bomb *bomb1, struct SDL_Renderer* renderer) {
    SDL_Event event;
 //   SDL_Event event;
    /*while (SDL_PollEvent(&event)) {
        printf("in\n\n\n");
        fireevent(i,state,tank1,bomb1,renderer,bot);
    }*/
    for(int j=0;j<2;j++) {
        struct tankk tankb=*(tank1+j);
        if (j == 0) {
           // while (SDL_PollEvent(&event)) {
                //if (event.type == SDL_KEYDOWN) {
             //       printf("ajaqvajaq\n");
                    if (event.key.keysym.sym == SDLK_m) {
                        printf("iiiiiiinnnnnnnnnnn\n");
                      //  fire(j, bomb1, *(tank1 + j), bot);
                    }
                //}
            //}
            if (state[SDL_SCANCODE_UP] == 1) {
                tankb.y += step * sin(tankb.s);
                tankb.x += step * cos(tankb.s);
            }
            if (state[SDL_SCANCODE_DOWN] == 1) {
                tankb.y -= step / 2 * sin(tankb.s);
                tankb.x -= step / 2 * cos(tankb.s);
            }
            if (state[SDL_SCANCODE_M]) {
                //fire(j, bomb1, *(tank1 + j), bot);
            }
            if (state[SDL_SCANCODE_RIGHT] == 1) { tankb.s += step_s; }
            if (state[SDL_SCANCODE_LEFT] == 1) {
                tankb.s -= step_s;
            }
            if (buffer(tankb, renderer))
                *(tank1+j) = tankb;
        }
        if (j == 1) {
            if (state[SDL_SCANCODE_W] == 1) {
                tankb.y += step * sin(tankb.s);
                tankb.x += step * cos(tankb.s);
            }
            if (state[SDL_SCANCODE_S] == 1) {
                tankb.y -= step / 2 * sin(tankb.s);
                tankb.x -= step / 2 * cos(tankb.s);
            }
            if (state[SDL_SCANCODE_D] == 1) { tankb.s += step_s; }
            if (state[SDL_SCANCODE_A] == 1) { tankb.s -= step_s; }
            if (buffer(tankb, renderer))
                *(tank1+j) = tankb;
        }
    }

}

int handleEvents(struct tankk *tank, struct bomb* bomb1, struct SDL_Renderer* renderer,Uint8* state,int bot) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return EXIT;
        if(event.key.keysym.sym == SDLK_m ){
            if(q%2==0)
            {
                //(*tank1).k--;
                q=1;
                break;
            }
            q++;
            if((*(tank+0)).k>0)
            fire(0,bomb1,((tank+0)),bot);
            printf("x");
        }

        if(event.key.keysym.sym == SDLK_v ){
            if(q%2==0)
            {
                //(*tank1).k--;
                q=1;
                break;
            }
            q++;
            if((*(tank+1)).k>0)
            fire(1,bomb1,((tank+1)),bot);
        }
        if(event.key.keysym.sym == SDLK_i ){
            printf("\nk0:%d   k1:%d\n",(*(tank+0)).k,(*(tank+1)).k);
        }
    }
}
int quit () {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return EXIT;
    }
}