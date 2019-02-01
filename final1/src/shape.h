//
// Created by A.M.M on 12/27/2018.
//

#ifndef SHAPE_H
#define SHAPE_H
void tank2(struct tankk tank, struct SDL_Renderer* renderer,char color);
int bomb1(struct SDL_Renderer* renderer,struct bomb* all, struct bomb* bomb1, int bot, struct tankk* tank1,int n);
void maprender (struct wall wall1[], struct SDL_Renderer* renderer,int n);
void wallrender (struct wall wall1,struct SDL_Renderer* renderer);
void poweruprenderer (struct SDL_Renderer* renderer,struct powerup* powerup1, struct tankk* tank1 );
#endif //PROJECT_SHAPE_H
