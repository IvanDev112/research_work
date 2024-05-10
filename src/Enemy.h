#ifndef ENEMY_H_
#define ENEMY_H_
#include "Game.h"

#include <SDL2/SDL.h>

class Enemy {
public:
    Enemy() {  }
    ~Enemy() { Kill(); }

    void Generate();

    void Update(float dt) {
        // update Y position with dt
        mY += ENEMY_SPEED * dt;

        // If enemy exited the screen
        if (mDrawRect.y > Game::GetHeight()) {
            Kill();
            Generate();
            Game::AddLives(-1);
        }

        mDrawRect.x = mX;
        mDrawRect.y = mY;
    }
    void Render() { SDL_RenderCopy(Game::GetRenderer(), mTexture, nullptr, &mDrawRect); }

    void Kill();
private:
    SDL_Texture *mTexture = nullptr;
    SDL_Rect mDrawRect = {0, 0, 0, 0};
    float mX = 0.0f, mY = 0.0f;
    const float ENEMY_SPEED = 100.0f;
};

#endif // ENEMY_H_
