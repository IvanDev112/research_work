#include "Enemy.h"
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>

void Enemy::Generate() {
    // Set random seed for generating random numbers
    srand(time(nullptr));

    // Get random enemy image
    char path[64];
    int option = rand() % 4;
    sprintf(path, "assets/textures/aliens/alien%d.png", option);

    // Load enemy texture
    SDL_Surface *tmp = IMG_Load(path);
    mDrawRect.w = tmp->w;
    mDrawRect.h = tmp->h;
    mTexture = SDL_CreateTextureFromSurface(Game::GetRenderer(), tmp);

    // Set random position
    const int HIGHER_BOUND = 800 - mDrawRect.w;
    mDrawRect.x = (rand() % HIGHER_BOUND);
    mDrawRect.y = -mDrawRect.h;

    mX = mDrawRect.x;
    mY = mDrawRect.y;
}

void Enemy::Kill() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mDrawRect.y = -mDrawRect.h;
    }
}
