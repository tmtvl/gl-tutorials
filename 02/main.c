#include "main.h"

SDL_Window *g_window = NULL;
SDL_GLContext g_context;

int g_color_mode = COLOR_MODE_CYAN;

GLfloat g_projection_scale = 1.f;

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

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  glOrtho (0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

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

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glTranslatef (SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);

  if (g_color_mode == COLOR_MODE_CYAN)
    {
      glBegin (GL_QUADS);
      glColor3f (0.f, 1.f, 1.f);
      glVertex2f (-50.f, -50.f);
      glVertex2f (50.f, -50.f);
      glVertex2f (50.f, 50.f);
      glVertex2f (-50.f, 50.f);
      glEnd ();
    }
  else
    {
      glBegin (GL_QUADS);
      glColor3f (1.f, 0.f, 0.f);
      glVertex2f (-50.f, -50.f);
      glColor3f (1.f, 1.f, 0.f);
      glVertex2f (50.f, -50.f);
      glColor3f (0.f, 1.f, 0.f);
      glVertex2f (50.f, 50.f);
      glColor3f (0.f, 0.f, 1.f);
      glVertex2f (-50.f, 50.f);
      glEnd ();
    }
}

void
deinit ()
{
  SDL_GL_DeleteContext (g_context);

  SDL_DestroyWindow (g_window);
  g_window = NULL;

  SDL_Quit ();
}

void
handle_keys (key, x, y)
     int key;
int x, y;
{
  if (key == 'q')
    {
      if (g_color_mode == COLOR_MODE_CYAN)
	g_color_mode = COLOR_MODE_MULTI;
      else
	g_color_mode = COLOR_MODE_CYAN;
    }
  else if (key == 'e')
    {
      if (g_projection_scale == 1.f)
	g_projection_scale = 2.f;
      else if (g_projection_scale == 2.f)
	g_projection_scale = 0.5f;
      else if (g_projection_scale == 0.5f)
	g_projection_scale = 1.f;

      glMatrixMode (GL_PROJECTION);
      glLoadIdentity ();

      glOrtho (0.0,
	       SCREEN_WIDTH * g_projection_scale,
	       SCREEN_HEIGHT * g_projection_scale,
	       0.0, 1.0, -1.0);
    }
}

int
main (argc, argv)
     int argc;
     char **argv;
{
  int quit;
  int result, x, y;
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
      SDL_StartTextInput ();

      while (!quit)
	{
	  while (SDL_PollEvent (&ev))
	    {
	      if (ev.type == SDL_QUIT)
		  quit = 1;
	      else if (ev.type == SDL_TEXTINPUT)
		{
		  x = 0;
		  y = 0;

		  SDL_GetMouseState (&x, &y);

		  handle_keys (ev.text.text[0], x, y);
		}
	    }

	  render();

	  SDL_GL_SwapWindow (g_window);
	}

      SDL_StopTextInput ();
    }

  return result;
}
