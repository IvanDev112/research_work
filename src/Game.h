#ifndef GAME_H_
#define GAME_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum class State {
    STATE_MENU,
    STATE_PLAY,
    STATE_OVER,
    STATE_QUIT
};

class Game {
public:
    Game() {  }
    ~Game() {  }

    void Init();
    void Run();
    void Clear();

    static SDL_Renderer *GetRenderer() { return mRenderer; }
    static int GetWidth() { return mWidth; }
    static int GetHeight() { return mHeight; }
    static void AddLives(int a) { mLives += a; }
    static void AddScore(int a) { mScore += a; }
private:
    SDL_Window *mWindow = nullptr;

    static SDL_Renderer *mRenderer;
    static int mWidth, mHeight;
    static int mLives, mScore;

    State mState = State::STATE_MENU;
    TTF_Font *mFont = nullptr;

    void HandleEvents();
    void Update(float dt);
    void Render();
};

#endif // GAME_H_
