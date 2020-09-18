#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct tex
{
  GLuint id;
  GLuint width;
  GLuint height;
} Texture;

Texture *make_texture ();

int load_texture_from_pixels (Texture *texture, GLuint *pixels, GLuint
			      width, GLuint height);

void free_texture (Texture *texture);

void render_texture (Texture *texture, GLfloat x, GLfloat y);

#endif
