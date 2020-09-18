#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init_gl ();

int sdl_init ();

void update ();

void render ();

void deinit ();

void handle_keys (int key, int x, int y);

#endif
