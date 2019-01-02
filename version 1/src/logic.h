//
// Created by A.M.M on 12/27/2018.
//

#ifndef LOGIC_H
#define LOGIC_H
void basemap (struct wall wall1[],int n);
int buffer (struct tankk tank1, struct SDL_Renderer* renderer);
int bombbuffer(struct bomb* bomb1,int i);
int destroy(int mode,struct tankk* tank1, struct bomb* bomb1,struct powerup powerup1);
int hittank (struct tankk tank1,double x,double y,int r);
#endif //PROJECT_LOGIC_H
