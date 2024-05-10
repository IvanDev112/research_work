#ifndef UTILS_H_
#define UTILS_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void DrawText(TTF_Font *font, const char *text, SDL_Color textColor, SDL_Rect drawRect);

#endif // UTILS_H_
