#include "../headers/MDB_Screen.hpp"


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")

MDB_Screen::MDB_Screen(int width, int height, Uint32 window_flags, Uint32 rend_flags)
{
    l_window = SDL_CreateWindow("Testing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);
    if (l_window == nullptr)
    {
        throw MDB_SDL_Exception();
    }

    if ((l_gl_context = SDL_GL_CreateContext(l_window)) == NULL)
    {
        throw MDB_SDL_Exception();
    }
    
    l_renderer = SDL_CreateRenderer(l_window, -1, rend_flags);

    MDB_Common::load_mdb_screen(this);
}

MDB_Screen::~MDB_Screen()
{
    SDL_DestroyRenderer(l_renderer);
    SDL_GL_DeleteContext(l_gl_context);
    SDL_DestroyWindow(l_window);
}

void MDB_Screen::set_screen_colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(l_window);
}

void MDB_Screen::manageEvent(SDL_Event e)
{
}
