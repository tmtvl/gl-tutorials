#include "main.h"

SDL_Window *g_window = NULL;
SDL_GLContext g_context;

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
				   640,
				   480,
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

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glClearColor (0.f, 0.f, 0.f, 1.f);

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
update ()
{
  // No per frame update needed.
}

void
render ()
{
  glClear (GL_COLOR_BUFFER_BIT);

  glBegin (GL_QUADS);
  glVertex2f (-0.5f, -0.5f);
  glVertex2f (0.5f, -0.5f);
  glVertex2f (0.5f, 0.5f);
  glVertex2f (-0.5f, 0.5f);
  glEnd ();
}

void
deinit ()
{
  SDL_GL_DeleteContext (g_context);

  SDL_DestroyWindow (g_window);
  g_window = NULL;

  SDL_Quit ();
}

int
main (argc, argv)
     int argc;
     char **argv;
{
  int quit;
  int result;
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

  return result;
}
