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
#include "event.h"

extern int base[1600][900];
extern const double P;

void tank2 (struct tankk tank , struct SDL_Renderer *renderer , char color) {
    int r = 40 , g = 40 , b = 40 , rr = 0 , gg = 0 , bb = 0 , rrr = 110 , ggg = 110 , bbb = 110;
    switch ( color ) {
        case 'r' :
            r = 130;
            break;
        case 'g' :
            g = 130;
            break;
        case 'b' :
            b = 130;
            break;
    }
    if ( tank.mode[ 0 ] == 1 ) {
        r = 50 + rand () % 156;
        g = 50 + rand () % 156;
        b = 50 + rand () % 156;
    }
    if ( tank.mode[ 1 ] == 1 ) {
        rr = 50 + rand () % 156;
        gg = 50 + rand () % 156;
        bb = 50 + rand () % 156;
    }
    if ( tank.mode[ 2 ] == 1 ) {
        rrr = rand ();
        ggg = rand ();
        bbb = 255;
    }
    if ( tank.mode[ 3 ] == 1 ) {
        rrr = 50;
        ggg = 50;
        bbb = 50;
    }
    thickLineRGBA (renderer , tank.x + 40 * cos (tank.s) , tank.y + 40 * sin (tank.s) , tank.x - 40 * cos (tank.s) ,
                   tank.y - 40 * sin (tank.s) , 55 , r , g , b , 255);
    //  filledCircleRGBA(renderer, tank.x, tank.y, 30, 200, 200, 200, 255);
    filledCircleRGBA (renderer , tank.x , tank.y , 14 , rrr , ggg , bbb , 255);
    thickLineRGBA (renderer , tank.x + 50 * cos (tank.s) , tank.y + 50 * sin (tank.s) , tank.x , tank.y , 3 , rr , gg ,
                   bb , 255);
}

int
bomb1 (struct SDL_Renderer *renderer , struct bomb *all , struct bomb *bomb1 , int bot , struct tankk *tank1 , int n) {
    struct powerup powerup1;
    if (( *bomb1 ).x > 1600 || ( *bomb1 ).x < 0 || ( *bomb1 ).y > 900 || ( *bomb1 ).y < 0 ) {
        ( *bomb1 ).e = 0;
        ( *bomb1 ).x = 0;
        ( *bomb1 ).y = 0;
        ( *bomb1 ).v = 0;
        ( *bomb1 ).s = 0;
        return 1;
    }
    if ( bot - ( *bomb1 ).start > 5000 && ( *bomb1 ).cbomb == false ) {
        ( *( tank1 + ( *bomb1 ).t )).k += 1;
        ( *bomb1 ).e = 0;
        ( *bomb1 ).x = 0;
        ( *bomb1 ).y = 0;
        ( *bomb1 ).v = 0;
        ( *bomb1 ).s = 0;
        return 1;
    }
    if ( bot - ( *bomb1 ).start > 50 ) {
        for ( int i = 0 ; i < n ; i ++ ) {
            if (( *( tank1 + i )).e == 1 ) {
                if ( destroy (1 , ( tank1 + i ) , bomb1 , powerup1) == 1 ) {
                    ( *( tank1 + ( *bomb1 ).t )).k ++;
                }
            }
        }

    }
    // printf("b:%d\n",(*bomb1).cbomb);
    if (( *bomb1 ).cbomb == false ) {
        filledCircleRGBA (renderer , ( *bomb1 ).x , ( *bomb1 ).y , 5 , 0 , 0 , 0 , 255);
    }
    if (( *bomb1 ).cbomb == true ) {
        //    printf("bigger");
        filledCircleRGBA (renderer , ( *bomb1 ).x , ( *bomb1 ).y , 12 , 0 , 0 , 0 , 255);
    }
    struct bomb bomb = ( *bomb1 );
    int x = ( *bomb1 ).x , y = ( *bomb1 ).y;
    double ix = cos (( *bomb1 ).s) , iy = sin (( *bomb1 ).s);
    for ( int i = 0 ; i < 20 ; i ++ ) {
        int xx = x + i * ix , yy = y + i * iy;
        if ( base[ xx ][ yy ] == 1 ) {
            if (( *bomb1 ).cbomb == true ) {
                ( *bomb1 ).e = 0;
                tank1[ ( *bomb1 ).t ].cbombon = false;
                boom (all , bomb1 , bot - 3000 , - 1);
            }else {
                bombbuffer (bomb1 , i);
                break;
            }
        }
    }
    ( *bomb1 ).x += ( *bomb1 ).v * cos (( *bomb1 ).s);
    ( *bomb1 ).y += ( *bomb1 ).v * sin (( *bomb1 ).s);
}

void wallrender (struct wall wall1 , struct SDL_Renderer *renderer) {

    boxRGBA (renderer , ( wall1 ).x1 , ( wall1 ).y1 , ( wall1 ).x2 , ( wall1 ).y2 , 100 , 100 , 10 , 255);
}

void maprender (struct wall wall1[] , struct SDL_Renderer *renderer , int n) {
    for ( int i = 1 ;; i ++ ) {
        if ( wall1[ i ].e == false )break;
        wallrender (wall1[ i ] , renderer);
    }
}

void poweruprenderer (struct SDL_Renderer *renderer , struct powerup *powerup1 , struct tankk *tank1) {
    for ( int i = 0 ; i < 3 ; i ++ ) {
        switch (( *powerup1 ).mode ) {
            case 1:
                filledCircleRGBA (renderer , ( *powerup1 ).x , ( *powerup1 ).y , 18 , rand () % 256 , rand () % 256 ,
                                  rand () % 256 , 250);
                {
                    if ( hittank (( *( tank1 + i )) , ( *powerup1 ).x , ( *powerup1 ).y , 5) == 1 &&
                         tank1[ i ].e == 1 ) {
                        ( *( tank1 + i )).mode[ 0 ] = 1;
                        ( *powerup1 ).e = 0;
                        ( *powerup1 ).x = 0;
                        ( *powerup1 ).y = 0;
                    }
                }
                break;
            case 2:
                filledCircleRGBA (renderer , ( *powerup1 ).x , ( *powerup1 ).y , 18 , 200 , 40 , 200 , 255);
                {
                    if ( hittank (( *( tank1 + i )) , ( *powerup1 ).x , ( *powerup1 ).y , 5) == 1 &&
                         tank1[ i ].e == 1 ) {
                        ( *( tank1 + i )).k = 100;
                        ( *( tank1 + i )).mode[ 1 ] = 1;
                        ( *powerup1 ).e = 0;
                        ( *powerup1 ).x = 0;
                        ( *powerup1 ).y = 0;
                    }
                }
                break;
            case 3:
                filledCircleRGBA (renderer , ( *powerup1 ).x , ( *powerup1 ).y , 18 , 0 , 0 , 250 , 255);
                if ( hittank (( *( tank1 + i )) , ( *powerup1 ).x , ( *powerup1 ).y , 5) == 1 && tank1[ i ].e == 1 ) {
                    ( *( tank1 + i )).mode[ 2 ] = 1;
                    //   laserbomb(renderer,powerup1,tank1+i);
                    ( *powerup1 ).e = 0;
                    ( *powerup1 ).x = 0;
                    ( *powerup1 ).y = 0;
                }
                break;
            case 4:
                filledCircleRGBA (renderer , ( *powerup1 ).x , ( *powerup1 ).y , 18 , 50 , 50 , 50 , 255);
                if ( hittank (( *( tank1 + i )) , ( *powerup1 ).x , ( *powerup1 ).y , 5) == 1 && tank1[ i ].e == 1 ) {
                    ( *( tank1 + i )).mode[ 3 ] = 1;
                    //   laserbomb(renderer,powerup1,tank1+i);
                    ( *powerup1 ).e = 0;
                    ( *powerup1 ).x = 0;
                    ( *powerup1 ).y = 0;
                }
                break;
        }
    }
}