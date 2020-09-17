#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>

enum ViewPortMode
  {
    VIEWPORT_MODE_FULL,
    VIEWPORT_MODE_HALF_CENTER,
    VIEWPORT_MODE_HALF_TOP,
    VIEWPORT_MODE_QUAD,
    VIEWPORT_MODE_RADAR
  };

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init_gl ();

int sdl_init ();

void update ();

void render ();

void deinit ();

void handle_keys (int key, int x, int y);

#endif
