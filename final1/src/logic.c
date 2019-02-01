//
// Created by A.M.M on 12/27/2018.
//
extern const double P;
extern int base[1600][900];

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

int buffer(struct tankk tank1 , struct SDL_Renderer *renderer) {
    int cx[17] , cy[17];
    cx[ 16 ] = tank1.x + 40 * cos (tank1.s) + 15 * sin (tank1.s);
    cy[ 16 ] = tank1.y + 40 * sin (tank1.s) - 15 * cos (tank1.s);
    cx[ 15 ] = tank1.x + 40 * cos (tank1.s) - 15 * sin (tank1.s);
    cy[ 15 ] = tank1.y + 40 * sin (tank1.s) + 15 * cos (tank1.s);
    cx[ 14 ] = tank1.x - 40 * cos (tank1.s) - 15 * sin (tank1.s);
    cy[ 14 ] = tank1.y - 40 * sin (tank1.s) + 15 * cos (tank1.s);
    cx[ 13 ] = tank1.x - 40 * cos (tank1.s) + 15 * sin (tank1.s);
    cy[ 13 ] = tank1.y - 40 * sin (tank1.s) - 15 * cos (tank1.s);
    cx[ 12 ] = tank1.x + 20 * cos (tank1.s) - 30 * sin (tank1.s);
    cy[ 12 ] = tank1.y + 20 * sin (tank1.s) + 30 * cos (tank1.s);
    cx[ 11 ] = tank1.x + 20 * cos (tank1.s) + 30 * sin (tank1.s);
    cy[ 11 ] = tank1.y + 20 * sin (tank1.s) - 30 * cos (tank1.s);
    cx[ 10 ] = tank1.x - 20 * cos (tank1.s) - 30 * sin (tank1.s);
    cy[ 10 ] = tank1.y - 20 * sin (tank1.s) + 30 * cos (tank1.s);
    cx[ 9 ] = tank1.x - 20 * cos (tank1.s) + 30 * sin (tank1.s);
    cy[ 9 ] = tank1.y - 20 * sin (tank1.s) - 30 * cos (tank1.s);
    cx[ 8 ] = tank1.x + 40 * cos (tank1.s) - 30 * sin (tank1.s);
    cy[ 8 ] = tank1.y + 40 * sin (tank1.s) + 30 * cos (tank1.s);
    cx[ 7 ] = tank1.x + 40 * cos (tank1.s) + 30 * sin (tank1.s);
    cy[ 7 ] = tank1.y + 40 * sin (tank1.s) - 30 * cos (tank1.s);
    cx[ 6 ] = tank1.x - 40 * cos (tank1.s) - 30 * sin (tank1.s);
    cy[ 6 ] = tank1.y - 40 * sin (tank1.s) + 30 * cos (tank1.s);
    cx[ 5 ] = tank1.x - 40 * cos (tank1.s) + 30 * sin (tank1.s);
    cy[ 5 ] = tank1.y - 40 * sin (tank1.s) - 30 * cos (tank1.s);
    cx[ 4 ] = tank1.x - 40 * cos (tank1.s);
    cy[ 4 ] = tank1.y - 40 * sin (tank1.s);
    cx[ 3 ] = tank1.x + 30 * sin (tank1.s);
    cy[ 3 ] = tank1.y - 30 * cos (tank1.s);
    cx[ 2 ] = tank1.x - 30 * sin (tank1.s);
    cy[ 2 ] = tank1.y + 30 * cos (tank1.s);
    cx[ 1 ] = round (tank1.x + 50 * cos (tank1.s));
    cy[ 1 ] = tank1.y + 50 * sin (tank1.s);
    for ( int i = 1 ; i < 17 ; i ++ )
        if ( base[ cx[ i ]][ cy[ i ]] == 1 ) {
            return 0;

        }
    return 1;
}

void basemap(struct wall wall1[] , int n) {
    for ( int k = 0 ; k < 1600 ; ++ k ) {
        for ( int i = 0 ; i < 900 ; ++ i ) {
            base[ k ][ i ] = 0;
        }
    }
    for ( int i = 1 ; i <= n ; i ++ ) {
        int m = min (wall1[ i ].y1 , wall1[ i ].y2);
        for ( int j = m ; j <= wall1[ i ].y1 + wall1[ i ].y2 - m ; j ++ ) {
            int m1 = min (wall1[ i ].x1 , wall1[ i ].x2);
            for ( int p = m1 ; p < wall1[ i ].x1 + wall1[ i ].x2 - m1 ; p ++ ) {
                base[ p ][ j ] = 1;
            }
        }
    }
}

int bombbuffer(struct bomb *bomb1 , int i) {
    int x = ( *bomb1 ).x , y = ( *bomb1 ).y;
    double ix = cos (( *bomb1 ).s) , iy = sin (( *bomb1 ).s);
    int xx = x + i * ix , yy = y + i * iy;
    if ( base[ xx + 1 ][ yy ] == 1 && base[ xx - 1 ][ yy ] == 1 ) {
        ( *bomb1 ).s *= - 1;
    }
    if ( base[ xx ][ yy - 1 ] == 1 && base[ xx ][ yy + 1 ] == 1 ) {
        ( *bomb1 ).s = P - ( *bomb1 ).s;
    }
}

int destroy(int mode , struct tankk *tank1 , struct bomb *bomb1 , struct powerup powerup1) {

    if ( hittank (*tank1 , ( *bomb1 ).x , ( *bomb1 ).y , 5) == 1 && mode == 1 ) {
        if (( *tank1 ).mode[ 0 ] == 1 ) {
            ( *bomb1 ).e = 0;
            ( *bomb1 ).v = 0;
            ( *tank1 ).mode[ 0 ] = 0;
            return 1;
        }
        ( *bomb1 ).e = 0;
        ( *bomb1 ).v = 0;
        ( *tank1 ).e = 0;
        ( *tank1 ).x = 0;
        ( *tank1 ).y = 0;
        ( *tank1 ).s = 0;
        return 1;
    }

    return 0;
}

int hittank(struct tankk tank1 , double x , double y , int r) {
    int checkx = 0 , checky = 0;
    double cx[17] , cy[17];
    cx[ 16 ] = tank1.x + 40 * cos (( tank1 ).s) + 15 * sin (( tank1 ).s);
    cy[ 16 ] = ( tank1 ).y + 40 * sin (( tank1 ).s) - 15 * cos (( tank1 ).s);
    cx[ 15 ] = ( tank1 ).x + 40 * cos (( tank1 ).s) - 15 * sin (( tank1 ).s);
    cy[ 15 ] = ( tank1 ).y + 40 * sin (( tank1 ).s) + 15 * cos (( tank1 ).s);
    cx[ 14 ] = ( tank1 ).x - 40 * cos (( tank1 ).s) - 15 * sin (( tank1 ).s);
    cy[ 14 ] = ( tank1 ).y - 40 * sin (( tank1 ).s) + 15 * cos (( tank1 ).s);
    cx[ 13 ] = ( tank1 ).x - 40 * cos (( tank1 ).s) + 15 * sin (( tank1 ).s);
    cy[ 13 ] = ( tank1 ).y - 40 * sin (( tank1 ).s) - 15 * cos (( tank1 ).s);
    cx[ 12 ] = ( tank1 ).x + 20 * cos (( tank1 ).s) - 30 * sin (( tank1 ).s);
    cy[ 12 ] = ( tank1 ).y + 20 * sin (( tank1 ).s) + 30 * cos (( tank1 ).s);
    cx[ 11 ] = ( tank1 ).x + 20 * cos (( tank1 ).s) + 30 * sin (( tank1 ).s);
    cy[ 11 ] = ( tank1 ).y + 20 * sin (( tank1 ).s) - 30 * cos (( tank1 ).s);
    cx[ 10 ] = ( tank1 ).x - 20 * cos (( tank1 ).s) - 30 * sin (( tank1 ).s);
    cy[ 10 ] = ( tank1 ).y - 20 * sin (( tank1 ).s) + 30 * cos (( tank1 ).s);
    cx[ 9 ] = ( tank1 ).x - 20 * cos (( tank1 ).s) + 30 * sin (( tank1 ).s);
    cy[ 9 ] = ( tank1 ).y - 20 * sin (( tank1 ).s) - 30 * cos (( tank1 ).s);
    cx[ 8 ] = ( tank1 ).x + 40 * cos (( tank1 ).s) - 30 * sin (( tank1 ).s);
    cy[ 8 ] = ( tank1 ).y + 40 * sin (( tank1 ).s) + 30 * cos (( tank1 ).s);
    cx[ 7 ] = ( tank1 ).x + 40 * cos (( tank1 ).s) + 30 * sin (( tank1 ).s);
    cy[ 7 ] = ( tank1 ).y + 40 * sin (( tank1 ).s) - 30 * cos (( tank1 ).s);
    cx[ 6 ] = ( tank1 ).x - 40 * cos (( tank1 ).s) - 30 * sin (( tank1 ).s);
    cy[ 6 ] = ( tank1 ).y - 40 * sin (( tank1 ).s) + 30 * cos (( tank1 ).s);
    cx[ 5 ] = ( tank1 ).x - 40 * cos (( tank1 ).s) + 30 * sin (( tank1 ).s);
    cy[ 5 ] = ( tank1 ).y - 40 * sin (( tank1 ).s) - 30 * cos (( tank1 ).s);
    cx[ 4 ] = ( tank1 ).x - 40 * cos (( tank1 ).s);
    cy[ 4 ] = ( tank1 ).y - 40 * sin (( tank1 ).s);
    cx[ 3 ] = ( tank1 ).x + 30 * sin (( tank1 ).s);
    cy[ 3 ] = ( tank1 ).y - 30 * cos (tank1.s);
    cx[ 2 ] = ( tank1 ).x - 30 * sin (( tank1 ).s);
    cy[ 2 ] = tank1.y + 30 * cos (( tank1 ).s);
    cx[ 1 ] = ( tank1 ).x + 50 * cos (( tank1 ).s);
    cy[ 1 ] = ( tank1 ).y + 50 * sin (( tank1 ).s);
    for ( int i = 1 ; i < 17 ; i ++ ) {
        checkx = 0;
        checky = 0;
        if ( distance (cx[ i ] , cy[ i ] , x , y) < 3 * r ) {
            return 1;
        }
        if ( x > ( tank1 ).x && x < cx[ i ] ) {
            checkx = 1;
        }
        if ( x < ( tank1 ).x && x > cx[ i ] ) {
            checkx = 1;
        }
        if ( y > ( tank1 ).y && y < cy[ i ] ) {
            checky = 1;
        }
        if ( y < ( tank1 ).y && y > cy[ i ] ) {
            checky = 1;
        }
        if ( checkx == 1 && checky == 1 ) {
            return 1;
        }
    }
    if ( distance (( tank1 ).x , ( tank1 ).y , x , y) < 9 * r ) {
        return 1;
    }
}