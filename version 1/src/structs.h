//
// Created by A.M.M on 12/27/2018.
//

#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct wall{
    int x1,x2,y1,y2;
};
typedef struct tankk {
    double x,y,s;
    int e,k,score;
    bool mode[5];
};
typedef struct bomb{
    double x,y,s,v;
    int e,n,start,t;
};
typedef struct powerup{
    double x,y;
    int mode,e;
};
#endif //PROJECT_STRUCTS_H
