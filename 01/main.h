#ifndef HELLO_H
#define HELLO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>

int init_gl ();

int sdl_init ();

void update ();

void render ();

void deinit ();

#endif
