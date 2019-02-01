//
// Created by A.M.M on 12/27/2018.
//
extern int q;
extern int ib;
extern int base[1600][900];
extern const double P;
extern const int step;
extern const double step_s;
extern const int EXIT;

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "structs.h"
#include "shape.h"
#include "logic.h"

extern bool play;

void boom (struct bomb *bomb1 , struct bomb *cbomb , int bot , int tank) {
    int I = ib;
    ib += 8;
    for ( int i = 0 ; i < 8 ; ++ i ) {

        bomb1[ I + i ].e = 1;
        bomb1[ I + i ].cbomb = false;
        bomb1[ I + i ].x = ( *cbomb ).x;
        bomb1[ I + i ].y = ( *cbomb ).y;
        bomb1[ I + i ].s = ( i ) * 3.141592 / 4;
        bomb1[ I + i ].v = 14;
        bomb1[ I + i ].start = bot;
        bomb1[ I + i ].t = - 1;
        // printf("i:%d,s:%lf\n",i,bomb1[I+i].s);
    }
    ( *cbomb ).e = 0;
}

void fire (int i , struct bomb *bomb1 , struct tankk *tank1 , int bot) {
    /*if(q%2==0)
    {
        //(*tank1).k--;
        q++;
        return;
    }*/
    //printf("fire! %d \n",tank1->k);
    if (( *tank1 ).mode[ 3 ] == 1 ) {
        ( *tank1 ).cbombon = true;
        ( *tank1 ).ibcb = ib;
        ( *bomb1 ).start = bot;
        ( *bomb1 ).e = 1;
        ( *bomb1 ).x = ( *tank1 ).x + 70 * cos (( *tank1 ).s);
        ( *bomb1 ).y = ( *tank1 ).y + 70 * sin (( *tank1 ).s);
        ( *bomb1 ).s = ( *tank1 ).s;
        ( *bomb1 ).v = 9;
        ( *bomb1 ).t = i;
        ( *bomb1 ).cbomb = true;
        //  printf("debug.log");
        ( *tank1 ).mode[ 3 ] = 0;
        ib ++;
    } else {
        if (( *tank1 ).k <= 0 )
            return;
        ( *tank1 ).k --;
        //
        // printf("k:%d\n",(*tank1).k);
        ( *bomb1 ).start = bot;
        ( *bomb1 ).e = 1;
        ( *bomb1 ).x = ( *tank1 ).x + 70 * cos (( *tank1 ).s);
        ( *bomb1 ).y = ( *tank1 ).y + 70 * sin (( *tank1 ).s);
        ( *bomb1 ).s = ( *tank1 ).s;
        ( *bomb1 ).v = 10;
        ( *bomb1 ).t = i;
        ( *bomb1 ).cbomb = false;
        ib ++;
    }
}

int
fireevent (int i , Uint8 *state , struct tankk *tank1 , struct bomb *bomb1 , struct SDL_Renderer *renderer , int bot) {
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

void movement (Uint8 *state , struct tankk *tank1 , struct bomb *bomb1 , struct SDL_Renderer *renderer) {
    for ( int j = 0 ; j < 3 ; j ++ ) {
        struct tankk tankb = *( tank1 + j );
        if ( j == 0 ) {
            if ( state[ SDL_SCANCODE_UP ] == 1 ) {
                tankb.y += step * sin (tankb.s);
                tankb.x += step * cos (tankb.s);
            }
            if ( state[ SDL_SCANCODE_DOWN ] == 1 ) {
                tankb.y -= step / 2 * sin (tankb.s);
                tankb.x -= step / 2 * cos (tankb.s);
            }
            if ( state[ SDL_SCANCODE_M ] ) {
                //fire(j, bomb1, *(tank1 + j), bot);
            }
            if ( state[ SDL_SCANCODE_RIGHT ] == 1 ) { tankb.s += step_s; }
            if ( state[ SDL_SCANCODE_LEFT ] == 1 ) {
                tankb.s -= step_s;
            }
            if ( buffer (tankb , renderer))
                *( tank1 + j ) = tankb;
        }
        if ( j == 1 ) {
            if ( state[ SDL_SCANCODE_W ] == 1 ) {
                tankb.y += step * sin (tankb.s);
                tankb.x += step * cos (tankb.s);
            }
            if ( state[ SDL_SCANCODE_S ] == 1 ) {
                tankb.y -= step / 2 * sin (tankb.s);
                tankb.x -= step / 2 * cos (tankb.s);
            }
            if ( state[ SDL_SCANCODE_D ] == 1 ) { tankb.s += step_s; }
            if ( state[ SDL_SCANCODE_A ] == 1 ) { tankb.s -= step_s; }
            if ( buffer (tankb , renderer))
                *( tank1 + j ) = tankb;
        }
        if ( j == 2 ) {
            if ( state[ SDL_SCANCODE_I ] == 1 ) {
                tankb.y += step * sin (tankb.s);
                tankb.x += step * cos (tankb.s);
            }
            if ( state[ SDL_SCANCODE_K ] == 1 ) {
                tankb.y -= step / 2 * sin (tankb.s);
                tankb.x -= step / 2 * cos (tankb.s);
            }
            if ( state[ SDL_SCANCODE_L ] == 1 ) { tankb.s += step_s; }
            if ( state[ SDL_SCANCODE_J ] == 1 ) {
                tankb.s -= step_s;
            }
            if ( buffer (tankb , renderer))
                *( tank1 + j ) = tankb;
        }
    }

}

int
handleEvents (struct tankk *tank , int time , struct bomb *all , struct bomb *bomb1 , struct SDL_Renderer *renderer ,
              Uint8 *state , int bot) {
    SDL_Event event;
    while ( SDL_PollEvent (&event)) {
        if ( event.type == SDL_QUIT )
            return EXIT;
        if ( event.key.keysym.sym == SDLK_RCTRL ) {
            if ( q % 2 == 0 ) {
                //(*tank1).k--;
                q = 1;
                break;
            }
            q ++;
            if ( tank[ 0 ].cbombon ) {
                boom (all , &all[ tank[ 0 ].ibcb ] , time - 3000 , 0);
                all[ tank[ 0 ].ibcb ].e = 0;
                tank[ 0 ].cbombon = false;
            } else {
                if (( *( tank + 0 )).k > 0 )
                    fire (0 , bomb1 , (( tank + 0 )) , bot);
                // printf("x");
            }
        }

        if ( event.key.keysym.sym == SDLK_q ) {
            if ( q % 2 == 0 ) {
                //(*tank1).k--;
                q = 1;
                break;
            }
            q ++;
            if ( tank[ 1 ].cbombon ) {
                boom (all , &all[ tank[ 1 ].ibcb ] , time - 3000 , 1);
                all[ tank[ 1 ].ibcb ].e = 0;
                tank[ 1 ].cbombon = false;
            } else {
                if (( *( tank + 1 )).k > 0 ) {
                    fire (1 , bomb1 , (( tank + 1 )) , bot);
                }
            }
        }
        if ( event.key.keysym.sym == SDLK_u ) {
            if ( q % 2 == 0 ) {
                q = 1;
                break;
            }
            q ++;
            if ( tank[ 2 ].cbombon ) {
                boom (all , &all[ tank[ 2 ].ibcb ] , time - 3000 , 2);
                all[ tank[ 2 ].ibcb ].e = 0;
                tank[ 2 ].cbombon = false;
            } else {
                if (( *( tank + 2 )).k > 0 )
                    fire (2 , bomb1 , (( tank + 2 )) , bot);
            }
        }
        if ( event.key.keysym.sym == SDLK_i ) {
            //   printf("\nk0:%d   k1:%d\n",(*(tank+0)).k,(*(tank+1)).k);
        }
        if ( event.key.keysym.sym == SDLK_ESCAPE ) {
            if ( q % 2 == 0 ) {
                //(*tank1).k--;
                q = 1;
                break;
            }
            q ++;
            if ( play )
                play = false;
        }
    }
}