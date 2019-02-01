const double P = 3.141592;
const int step = 5;
const int FPS = 50;
const double step_s = 0.0628318530;
int q = 0;

#include <time.h>
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
bool play = true;
int base[1600][900];
int ib = 0 , ttime = 0;
const int EXIT = 12345;

int main(int argc , char *argv[]) {
    srand (time (NULL));
    int ipo = 0;
    int pov;
    struct tankk *tank;
    tank = ( struct tankk * ) malloc (3 * sizeof (struct tankk));
    tank[ 0 ].color = 'r';
    tank[ 1 ].color = 'g';
    tank[ 2 ].color = 'b';
    int winner;
    int number;
    printf ("Enter Number of players");
    scanf ("%d" , &number);
    printf ("Enter point of Victory");
    scanf ("%d" , &pov);
    SDL_Init (SDL_INIT_VIDEO);
    tank[ 0 ].score = 0;
    tank[ 1 ].score = 0;
    tank[ 2 ].score = 0;
    tank[ 0 ].e = 0;
    tank[ 1 ].e = 0;
    tank[ 2 ].e = 0;
    tank[ 0 ].cbombon = false;
    tank[ 1 ].cbombon = false;
    tank[ 2 ].cbombon = false;
    SDL_Window *window = SDL_CreateWindow ("alter" , 200 , 100 , 1600 , 900 , SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer (window , - 1 , SDL_RENDERER_ACCELERATED);
    for ( int k = 0 ; k < 100 ; ++ k ) {
        struct wall *wall1;
        struct powerup *powerup1;
        powerup1 = ( struct powerup * ) malloc (30 * sizeof (struct powerup));
        for ( int l = 0 ; l < 10 ; ++ l ) {
            powerup1[ l ].e = 0;
        }
        int n = 0;
        wall1 = ( struct wall * ) malloc (30 * sizeof (struct wall));
        FILE *fp;
        char r[50] = "map1.map";
        r[ 3 ] = ( char ) ( rand () % 3 + '1' );
        fp = fopen (r , "r");
        ipo = 0;
        for ( int j = 0 ; j < 50 ; j ++ ) {
            char r[50];
            int x1 , x2 , y1 , y2;
            fgets (r , 30 , fp);
            if ( r[ 0 ] == 'T' ) {
                wall1[ j ].e = false;
                break;
            }
            n ++;
            sscanf (r , "%d,%d,%d,%d" , &x1 , &y1 , &x2 , &y2);
            ( *( wall1 + j )).x1 = x1;
            ( *( wall1 + j )).y1 = y1;
            ( *( wall1 + j )).x2 = x2;
            ( *( wall1 + j )).y2 = y2;
            ( *( wall1 + j )).e = true;
        }
        for ( int j = 0 ; j < number ; j ++ ) {
            char r[50];
            int x , y;
            double s;
            fgets (r , 20 , fp);
            sscanf (r , "%d,%d,%lf" , &x , &y , &s);
            tank[ j ].x = x;
            tank[ j ].y = y;
            tank[ j ].s = s;
            tank[ j ].k = 5;
            tank[ j ].e = 1;
        }
        //meghdar dehy
        struct bomb *bombb;
        bombb = ( struct bombb * ) malloc (300 * sizeof (struct bomb));
        int counter = 0;
        basemap (wall1 , n);
        for ( int i = 0 ; i < 10 ; i ++ ) {
            ( *( bombb + i )).e = 0;
            ( *( bombb + i )).n = i;
            ( *( bombb + i )).start = 0;
        }
        for ( int i = 0 ; i < 5 ; i ++ ) {
            tank[ 0 ].mode[ i ] = 0;
            tank[ 1 ].mode[ i ] = 0;
            tank[ 2 ].mode[ i ] = 0;
        }
        int bot = SDL_GetTicks ();
        int end = 0;
        int time = 0 , t1 = 0;
        int mark = 2 , qq = 0;
        while ( 1 ) {
            SDL_SetRenderDrawColor (renderer , 200 , 200 , 200 , 255);
            SDL_RenderClear (renderer);
            SDL_Event event;
            if ( ! play ) {
                if ( t1 == 0 ) {
                    t1 = SDL_GetTicks ();
                }
                int g[4] = { 0 };
                g[ mark / 2 - 1 ] = 250;
                boxRGBA (renderer , 600 , 100 , 900 , 150 , 255 , g[ 0 ] , 0 , 255);
                boxRGBA (renderer , 600 , 225 , 900 , 275 , 255 , g[ 1 ] , 0 , 255);
                boxRGBA (renderer , 600 , 350 , 900 , 400 , 255 , g[ 2 ] , 0 , 255);
                boxRGBA (renderer , 600 , 475 , 900 , 525 , 255 , g[ 3 ] , 0 , 255);
                SDL_RenderSetScale (renderer , 5 , 5);
                stringRGBA (renderer , 128 , 21 , "resume" , 50 , 50 , 0 , 255);
                stringRGBA (renderer , 135 , 45 , "save" , 50 , 50 , 0 , 255);
                stringRGBA (renderer , 132 , 72 , "load" , 50 , 50 , 0 , 255);
                stringRGBA (renderer , 133 , 96 , "exit" , 50 , 50 , 0 , 255);
                SDL_RenderSetScale (renderer , 1 , 1);
                while ( SDL_PollEvent (&event)) {
                    if ( event.key.keysym.sym == SDLK_UP ) {
                        mark --;
                        if(mark<2)mark=2;
                    }
                    if ( event.key.keysym.sym == SDLK_DOWN ) {
                        mark ++;
                        if(mark>8)mark=8;
                    }
                    if ( event.key.keysym.sym == SDLK_l ) {
                        switch ( mark ) {
                            case 2:
                                play = true;
                                bot += SDL_GetTicks () - t1;
                                t1 = 0;
                                break;
                            case 4: {
                                if ( qq == 0 ) {
                                    save (wall1 , tank , powerup1 , time , pov , number);
                                    qq = 1;
                                } else qq = 0;

                            }
                                break;
                            case 6:
                                if ( qq == 0 ) {
                                    load (&wall1 , &tank , &powerup1 , &time , &bot , &number);
                                    basemap (wall1 , n);
                                    qq = 1;
                                } else qq = 0;
                                break;
                            case 8:
                                return 2;
                                break;

                        }
                    }
                    if ( event.type == SDL_QUIT )return 2;
                }
            }
            if ( play ) {
                {
                    int ra = rand () % 200;
                    if ( ra == 2 && ipo < 5 ) {
                        int x , y;
                        ra = rand () % 4 + 1;
                        powerup1[ ipo ].mode = ra;
                        if ( ra != 3 )
                            powerup1[ ipo ].e = 1;
                        do {
                            x = powerup1[ ipo ].x = rand () % 1600;
                            y = powerup1[ ipo ].y = rand () % 900;
                        } while ( base[ x ][ y ] == 1 );
                        {
                            if ( ra != 3 )
                                ipo ++;
                        }
                    }
                }
                int flag = 0;
                Uint8 *state = SDL_GetKeyboardState (NULL);
                int start_ticks = SDL_GetTicks ();
                time = start_ticks - bot;

                if ( handleEvents (tank , time , bombb , bombb + ib , renderer , state , time) == EXIT ) {
                    return 1;
                }
                movement (state , tank , bombb + ( ib % 300 ) , renderer);
                maprender (wall1 , renderer , 8);
                int lnumber = 0;
                for ( int i = 0 ; i < 3 ; i ++ ) {
                    if ( tank[ i ].e == 1 ) {
                        lnumber ++;
                        tank2 (tank[ i ] , renderer , tank[ i ].color);
                    }
                }
                if ( lnumber == 1 ) {
                    if ( end == 0 ) {
                        end = time + 3000;
                    }
                }
                if ( end != 0 )
                    if ( time > end ) {
                        flag = 1;
                        winner = - 1;
                        for ( int i = 0 ; i < number ; i ++ ) {
                            if ( tank[ i ].e == 1 ) {
                                winner = i;
                                tank[ i ].score ++;
                                if ( tank[ i ].score == pov ) {
                                    ttime += time / 1000;
                                    SDL_DestroyRenderer (renderer);
                                    SDL_DestroyWindow (window);
                                    SDL_Quit ();
                                    getchar ();
                                    printf ("winner ");
                                    switch ( winner ) {
                                        case 0:
                                            printf ("red");
                                            break;
                                        case 1:
                                            printf ("green");
                                            break;
                                        case 2:
                                            printf ("blue");
                                            break;
                                    }
                                    printf ("\ntotal time: %ds" , ttime);
                                    getchar ();
                                    return 5;
                                }

                            }
                        }
                    }
                for ( int i = 0 ; i < 300 ; i ++ ) {
                    if (( *( bombb + i )).e != 0 ) {
                        bomb1 (renderer , bombb , bombb + i , time , tank , number);
                    }
                }
                for ( int i = 0 ; i < 10 ; i ++ ) {
                    if ( powerup1[ i ].e == 1 ) {
                        poweruprenderer (renderer , &powerup1[ i ] , tank);
                    }
                }
                char *buffer = malloc (sizeof (char) * 50);
                char *buffer1 = malloc (sizeof (char) * 5);
                if ( counter == 0 ) {
                    int r = 40 , g = 40 , b = 40;
                    char *buffer = malloc (sizeof (char) * 50);
                    sprintf (buffer , "READY?");
                    if ( k > 0 ) {
                        if ( winner == 0 ) {
                            r = 200;
                            sprintf (buffer1 , "WINNER:RED");
                        } else if ( winner == 1 ) {
                            g = 200;
                            sprintf (buffer1 , "WINNER:GREEN");
                        } else if ( winner == 2 ) {
                            b = 200;
                            sprintf (buffer1 , "WINNER:BLUE");
                        } else
                            sprintf (buffer1 , "");

                    }
                    SDL_RenderSetScale (renderer , 25 , 25);
                    stringRGBA (renderer , 10 , 15 , buffer , 0 , 0 , 0 , 150);
                    SDL_RenderSetScale (renderer , 5 , 5);
                    if ( k > 0 )
                        stringRGBA (renderer , 100 , 120 , buffer1 , r , g , b , 200);
                    SDL_RenderSetScale (renderer , 1 , 1);
                    free (buffer);
                }
                *buffer = malloc (sizeof (char) * 50);
                if ( number != 3 )
                    sprintf (buffer , "score: red:%d  green:%d elapsed time: %ds  " , tank[ 0 ].score ,
                             tank[ 1 ].score ,
                             time / 1000);
                else
                    sprintf (buffer , "score: red:%d  green:%d blue:%d  elapsed time: %ds  " , tank[ 0 ].score ,
                             tank[ 1 ].score ,
                             tank[ 2 ].score , time / 1000);
                SDL_RenderSetScale (renderer , 2 , 2);
                stringRGBA (renderer , 20 , 20 , buffer , 0 , 0 , 0 , 255);
                SDL_RenderSetScale (renderer , 1 , 1);
                free (buffer);
                if ( 1 == flag ) {

                    break;
                }//FPS lock
                while ( SDL_GetTicks () - start_ticks < 1000 / FPS );
            }
            SDL_RenderPresent (renderer);
            if ( counter == 0 ) {
                bot += 2000;
                SDL_Delay (2000);
            }
            counter ++;
        }
        ttime += time / 1000;
        free (wall1);
        free (powerup1);
    }
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    SDL_Quit ();
    return 0;
}