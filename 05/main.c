#include "main.h"
#include "texture.h"

SDL_Window *g_window = NULL;
SDL_GLContext g_context;

Texture *g_checker_board_texture;

int
sdl_init ()
{
  int success;

  success = 1;

  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      fprintf (stderr,
	       "SDL could not initialise! SDL_Error: %s\n",
	       SDL_GetError ());

      success = 0;
    }
  else
    {
      g_window = SDL_CreateWindow ("SDL Tutorial",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   SCREEN_WIDTH,
				   SCREEN_HEIGHT,
				   SDL_WINDOW_OPENGL |
				   SDL_WINDOW_SHOWN);

      if (g_window == NULL)
	{
	  fprintf (stderr,
		   "Window could not be created! SDL_Error: %s\n",
		   SDL_GetError ());

	  success = 0;
	}
      else
	{
	  g_context = SDL_GL_CreateContext (g_window);

	  if (g_context == NULL)
	    {
	      fprintf (stderr,
		       "OpenGL context could not be created! \
	    SDL_Error: %s\n",
		       SDL_GetError ());

	      success = 0;
	    }
	  else if (!init_gl ())
	    {
	      fprintf (stderr,
		       "Unable to initialise OpenGL!\n");

	      success = 0;
	    }
	}
    }

  return success;
}

int
init_gl ()
{
  int success;
  GLenum error;

  success = 1;

  glViewport (0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  glOrtho (0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glClearColor (0.f, 0.f, 0.f, 1.f);

  glEnable (GL_TEXTURE_2D);

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

int
load_media ()
{
  const int CHECKERBOARD_WIDTH = 128;
  const int CHECKERBOARD_HEIGHT = 128;
  const int CHECKERBOARD_PIXEL_COUNT =
    CHECKERBOARD_WIDTH * CHECKERBOARD_HEIGHT;
  GLuint checkerboard[CHECKERBOARD_PIXEL_COUNT];
  int i;

  g_checker_board_texture = make_texture ();

  for (i = 0; i < CHECKERBOARD_PIXEL_COUNT; i++)
    {
      GLubyte *colors = (GLubyte *) &checkerboard[i];

      // If the 5th bit of the X and Y offsets of the pixel don't match
      if ((i / 128 & 16) ^ (i % 128 & 16))
	{
	  colors[0] = 0xFF;
	  colors[1] = 0xFF;
	  colors[2] = 0xFF;
	  colors[3] = 0xFF;
	}
      else
	{
	  colors[0] = 0xFF;
	  colors[1] = 0x00;
	  colors[2] = 0x00;
	  colors[3] = 0xFF;
	}
    }

  if (!load_texture_from_pixels (g_checker_board_texture,
				 checkerboard, CHECKERBOARD_WIDTH,
				 CHECKERBOARD_HEIGHT))
    {
      fprintf (stderr,
	       "Unable to load checkerboard texture!\n");

      return 0;
    }

  return 1;
}

void
update ()
{
  // No per frame update needed.
}

void
render ()
{
  glClear (GL_COLOR_BUFFER_BIT);

  GLfloat x = (SCREEN_WIDTH - g_checker_board_texture->width) / 2.f;
  GLfloat y = (SCREEN_HEIGHT - g_checker_board_texture->height) / 2.f;

  render_texture (g_checker_board_texture, x, y);
}

void
deinit ()
{
  free_texture (g_checker_board_texture);

  SDL_GL_DeleteContext (g_context);

  SDL_DestroyWindow (g_window);
  g_window = NULL;

  SDL_Quit ();
}

int
main (int argc, char **argv)
{
  int quit, result;
  SDL_Event ev;

  quit = 0;
  result = 0;

  if (!sdl_init ())
    {
      fprintf (stderr,
	       "Could not initialise SDL!\n");

      result = 1;
    }
  else
    {
      if (!load_media ())
	{
	  fprintf (stderr,
		   "Unable to load media!\n");

	  result = 1;
	}
      else
	{
	  while (!quit)
	    {
	      while (SDL_PollEvent (&ev))
		{
		  if (ev.type == SDL_QUIT)
		    quit = 1;
		}

	      render();

	      SDL_GL_SwapWindow (g_window);
	    }
	}
    }

  return result;
}
