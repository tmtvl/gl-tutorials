#include "texture.h"

Texture *
make_texture ()
{
  Texture *texture = (Texture *) malloc (sizeof (Texture));

  (*texture).id = 0;
  (*texture).width = 0;
  (*texture).height = 0;

  return texture;
}

int
load_texture_from_pixels (Texture *texture, GLuint *pixels,
			  GLuint width, GLuint height)
{
  int success;
  GLenum error;

  success = 1;

  if (texture->id)
    texture->id = 0;

  texture->width = width;
  texture->height = height;

  glGenTextures (1, &texture->id);

  glBindTexture (GL_TEXTURE_2D, texture->id);

  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, pixels);

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBindTexture (GL_TEXTURE_2D, 0);

  error = glGetError();

  if (error != GL_NO_ERROR)
    {
      fprintf (stderr,
	       "Error initialising OpenGL! %s\n",
	       gluErrorString (error));

      success = 0;
    }

  return success;
}

void
free_texture (Texture *texture)
{
  if (texture->id)
    glDeleteTextures (1, &texture->id);

  free (texture);
}

void
render_texture (Texture *texture, GLfloat x, GLfloat y)
{
  if (texture->id)
    {
      glLoadIdentity ();

      glTranslatef (x, y, 0.f);

      glBindTexture (GL_TEXTURE_2D, texture->id);

      glBegin (GL_QUADS);
      glTexCoord2f (0.f, 0.f);
      glVertex2f (0.f, 0.f);
      glTexCoord2f (1.f, 0.f);
      glVertex2f (texture->width, 0.f);
      glTexCoord2f (1.f, 1.f);
      glVertex2f (texture->width, texture->height);
      glTexCoord2f (0.f, 1.f);
      glVertex2f (0.f, texture->height);
      glEnd ();
    }
}
