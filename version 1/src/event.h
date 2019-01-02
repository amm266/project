//
// Created by A.M.M on 12/27/2018.
//

#ifndef EVENT_H
#define EVENT_H
int quit ();
void movement ( Uint8* state, struct tankk *tank1 , struct bomb *bomb1, struct SDL_Renderer* renderer);
int buffer (struct tankk tank1, struct SDL_Renderer* renderer);
int fireevent(int i, Uint8* state, struct tankk *tank1 , struct bomb *bomb1, struct SDL_Renderer* renderer,int bot);
int handleEvents(struct tankk *tank, struct bomb* bomb1, struct SDL_Renderer* renderer,Uint8* state, int bot);
void fire (int i, struct bomb* bomb1, struct tankk* tank1,int bot);
#endif //PROJECT_EVENT_H
