//
// Created by A.M.M on 12/27/2018.
//

#ifndef PROJECT_OTHER_H
#define PROJECT_OTHER_H

int max (int a , int b);

double distance (double x1 , double y1 , double x2 , double y2);

int min (int a , int b);

void save (struct wall *wall1 , struct tankk *tank1 , struct powerup *powerup1 , int time , int pov , int number);

void load (struct wall **wall1 , struct tankk **tank1 , struct powerup **powerup1 , int *time , int *pov , int *number);

#endif //PROJECT_OTHER_H
