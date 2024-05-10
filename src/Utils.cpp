#include "Utils.h"
#include "Game.h"

void DrawText(TTF_Font *font, const char *text, SDL_Color textColor, SDL_Rect drawRect) {
    // Load surface with text
    SDL_Surface *tmp = TTF_RenderText_Solid(font, text, textColor);

    // Turn it into texture image
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::GetRenderer(), tmp);

    // Render it inside drawRect
    SDL_RenderCopy(Game::GetRenderer(), tex, nullptr, &drawRect);

    // Free resources
    SDL_FreeSurface(tmp);
    SDL_DestroyTexture(tex);
}
