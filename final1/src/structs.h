//
// Created by A.M.M on 12/27/2018.
//

#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct wall {
    int x1 ,x2 ,y1 ,y2;
    bool e;
};
typedef struct tankk {
    double x ,y ,s;
    int e ,k ,score ,ibcb;
    char color;
    bool mode[5] ,cbombon;
};
typedef struct bomb {
    double x ,y ,s ,v;
    int e ,n ,start ,t;
    bool cbomb;
};
typedef struct powerup {
    double x ,y;
    int mode;
    bool e;
};
#endif //PROJECT_STRUCTS_H
