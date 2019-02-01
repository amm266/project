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

double distance (double x1 , double y1 , double x2 , double y2) {
    return sqrt ((( x1 - x2 ) * ( x1 - x2 )) + (( y1 - y2 ) * ( y1 - y2 )));
}

int max (int a , int b) {
    return a * ( a >= b ) + b * ( b > a );
}

int min (int a , int b) {
    return a + b - max (a , b);
}

void save (struct wall *wall1 , struct tankk *tank1 , struct powerup *powerup1 , int time , int pov , int number) {
    FILE *save;
    char a[50];
    save = fopen ("save.alter" , "w");
    fputs ("WALLS\n" , save);
    for ( int i = 0 ; i < 100 ; ++ i ) {
        if ( wall1[ i ].e ) {
            sprintf (a , "%d,%d,%d,%d" , wall1[ i ].x1 , wall1[ i ].y1 , wall1[ i ].x2 , wall1[ i ].y2);

            fputs (a , save);
            fprintf (save , "\n");
        }
        if ( wall1[ i ].e == false ) { break; }
    }
    fputs ("TANK\n" , save);
    for ( int i = 0 ; i < 3 ; ++ i ) {
        if ( tank1[ i ].e ) {
            sprintf (a , "%lf,%lf,%lf,%d,%d,%d,%d,%d,%d" , tank1[ i ].x , tank1[ i ].y , tank1[ i ].s ,
                     tank1[ i ].score ,
                     tank1[ i ].mode[ 0 ] , tank1[ i ].mode[ 1 ] , tank1[ i ].mode[ 2 ] , tank1[ i ].mode[ 3 ] ,
                     tank1[ i ].mode[ 4 ]);
            fputs (a , save);
            fprintf (save , "\n");
        }else {
            fputs ("0" , save);
            fprintf (save , "\n");
        }
    }
    fputs ("POWERUP\n" , save);
    for ( int i = 0 ; i < 5 ; i ++ ) {
        if ( powerup1[ i ].e ) {
            sprintf (a , "%lf,%lf,%d" , powerup1[ i ].x , powerup1[ i ].y , powerup1[ i ].mode);
            fputs (a , save);
            fprintf (save , "\n");
        }else {
            break;
        }
    }
    fprintf (save , "TIME\n%d\nPOV\n%d\nNUMBER\n%d\n" , time , pov , number);
    fclose (save);
    printf ("game saved");
}

void
load (struct wall **wall1 , struct tankk **tank1 , struct powerup **powerup1 , int *time , int *pov , int *number) {
    FILE *load;
    char r[50] = { 0 };
    load = fopen ("save.alter" , "r");
    fgets (r , 50 , load);
    for ( int j = 0 ; j < 50 ; j ++ ) {
        int x1 , x2 , y1 , y2;
        fgets (r , 50 , load);
        //puts(r);
        if ( r[ 0 ] == 'T' ) {
            //wall1[j+2].e=false;
            ( *wall1 )[ j ].e = false;
            break;
        }
        sscanf (r , "%d,%d,%d,%d" , &x1 , &y1 , &x2 , &y2);
        ( *(( *wall1 ) + j )).x1 = x1;
        ( *(( *wall1 ) + j )).y1 = y1;
        ( *(( *wall1 ) + j )).x2 = x2;
        ( *(( *wall1 ) + j )).y2 = y2;
        ( *wall1 )[ j ].e = true;
    }
    for ( int j = 0 ; j < 3 ; j ++ ) {
        fgets (r , 50 , load);
        double x , y , s;
        int score;
        bool mode[5];
        if ( r[ 0 ] == '0' ) continue;
        if ( r[ 0 ] == 'P' ) {
            ( *(( *tank1 ) + j )).e = 0;
            ( *(( *tank1 ) + j + 1 )).e = 0;
            break;
        }
        puts (r);
        sscanf (r , "%lf,%lf,%lf,%d,%d,%d,%d,%d,%d" , &x , &y , &s , &score ,
                &mode[ 0 ] , &mode[ 1 ] , &mode[ 2 ] , &mode[ 3 ] , &mode[ 4 ]);
        //  printf("p:%lf,%lf,%lf,%d,%d,%d,%d,%d,%d\n",x, y, s, score,
        //       mode[0],mode[1],mode[2], mode[3], mode[4]);
        ( *(( *tank1 ) + j )).x = x;
        ( *(( *tank1 ) + j )).y = y;
        ( *(( *tank1 ) + j )).s = s;
        ( *(( *tank1 ) + j )).score = score;
        ( *(( *tank1 ) + j )).mode[ 0 ] = mode[ 0 ];
        ( *(( *tank1 ) + j )).mode[ 1 ] = mode[ 1 ];
        ( *(( *tank1 ) + j )).mode[ 2 ] = mode[ 2 ];
        ( *(( *tank1 ) + j )).mode[ 3 ] = mode[ 3 ];
        ( *(( *tank1 ) + j )).mode[ 4 ] = mode[ 4 ];
    }
    for ( int j = 0 ; j < 50 ; j ++ ) {
        fgets (r , 50 , load);
        if ( r[ 0 ] == 'T' ) {
            ( *(( *powerup1 ) + j )).e = false;
            break;
        }
        puts (r);
        // sscanf(r,"%lf,%lf,%d",(((*powerup1)+j)).x,(((*powerup1)+j)).y,(((*powerup1)+j)).mode);
    }
    int t , p;
    //printf("s");
    fgets (r , 30 , load);
    //puts(r);
    sscanf (r , "%d" , &t);
    *time -= t;
    fgets (r , 30 , load);
    //puts(r);
    fgets (r , 30 , load);
    //  puts(r);
    sscanf (r , "%d" , pov);
    // printf("povl:%d",*pov);
    fgets (r , 30 , load);
    fgets (r , 30 , load);
    sscanf (r , "%d" , number);
    printf ("load fiinished\n");
    fclose (load);
}