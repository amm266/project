//
// Created by A.M.M on 12/27/2018.
//

#ifndef EVENT_H
#define EVENT_H

void boom (struct bomb *bomb1 , struct bomb *cbomb , int bot , int tank);

void movement (Uint8 *state , struct tankk *tank1 , struct bomb *bomb1 , struct SDL_Renderer *renderer);

int buffer (struct tankk tank1 , struct SDL_Renderer *renderer);

int
handleEvents (struct tankk *tank , int time , struct bomb *all , struct bomb *bomb1 , struct SDL_Renderer *renderer ,
              Uint8 *state , int bot);

void fire (int i , struct bomb *bomb1 , struct tankk *tank1 , int bot);

#endif //PROJECT_EVENT_H
