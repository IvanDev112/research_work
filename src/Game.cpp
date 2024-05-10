#include "Game.h"
#include "MathExpression.h"
#include "Utils.h"
#include "Enemy.h"

#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>

// Constants
const int MAX_INPUT_LENGTH = 5;
const SDL_Color WHITE_COLOR = {255, 255, 255, 255};

// Static variables
SDL_Renderer *Game::mRenderer = nullptr;
int Game::mWidth = 800;
int Game::mHeight = 600;
int Game::mLives = 3;
int Game::mScore = 0;

// Global varaibles
SDL_Texture *gBackground = nullptr;
MathExpression gMathExpr;
Enemy gEnemy;
std::string gInput = "";
int gAnswer = -999;

// For calculating delta time
Uint32 lastUpdate = SDL_GetTicks();

void Game::Init() {
    // Init SDL2, SDL2_image and SDL2_ttf
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    // Create window and renderer
    mWindow = SDL_CreateWindow("Math Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, 0);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Load the game font
    mFont = TTF_OpenFont("assets/fonts/OpenSans-Medium.ttf", 24);

    // Initrial generation for enemy and math expression
    gMathExpr.Generate();
    gEnemy.Generate();

    // Load background imae
    gBackground = IMG_LoadTexture(mRenderer, "assets/textures/space_bg/space0.png");
}
// Input


void Game::Run() {
    while (mState != State::STATE_QUIT) {
        // Calculating delta time
        Uint32 current = SDL_GetTicks();
        float dt = (current - lastUpdate) / 1000.0f;

        HandleEvents();
        Update(dt);
        Render();

        lastUpdate = current;
    }
}

void Game::Clear() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    TTF_CloseFont(mFont);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::HandleEvents() {
    SDL_Event e;

    // For SDL to recieve text input
    SDL_StartTextInput();
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            mState = State::STATE_QUIT;
            break;
        case SDL_TEXTINPUT:
            if (mState == State::STATE_PLAY) {
                // Only allow input if it is a digit, minus sign and if its length is not longer tha maximum
                if ((isdigit(e.text.text[0]) || e.text.text[0] == '-') && gInput.length() != MAX_INPUT_LENGTH) {
                    gInput += e.text.text;
                }
            }
            break;
        case SDL_KEYDOWN:
            if (mState == State::STATE_MENU) {
                mState = State::STATE_PLAY;
            }
            if (mState == State::STATE_PLAY) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    if (!gInput.empty()) {
                        // Trun text input into int and give it to the gAsnwer variable
                        gAnswer = std::stoi(gInput);
                        gInput = "";
                    }
                } else if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    if (gInput.length() != 0) {
                        gInput.pop_back();
                    }
                }
            }
            if (mState == State::STATE_OVER) {
                if (e.key.keysym.sym == SDLK_r) {
                    // Restart the game
                    mLives = 3;
                    mScore = 0;
                    mState = State::STATE_MENU;
                } else {
                    mState = State::STATE_QUIT;
                }
            }
            break;
        default:
            break;
        }
    }
    SDL_StopTextInput();
}

void Game::Update(float dt) {
    if (mState == State::STATE_PLAY) {
        if (gMathExpr.CheckAnswer(gAnswer)) {
            gAnswer = -999; // Drop the answer to 
            mScore += 100;
            gMathExpr.Generate();
            gEnemy.Kill();
            gEnemy.Generate();
        }
        gEnemy.Update(dt);

        if (mLives <= 0) {
            mState = State::STATE_OVER;
        }
    }
}

void Game::Render() {
    SDL_RenderClear(mRenderer);
    SDL_Rect screenRect = {0, 0, mWidth, mHeight};

    // Render background image
    SDL_RenderCopy(mRenderer, gBackground, nullptr, &screenRect);

    if (mState == State::STATE_MENU) {
        SDL_Rect centerBox = {(mWidth - 500) / 2, (mHeight - 100) / 2, 500, 100};
        DrawText(mFont, "PRESS ANY KEY TO CONTINUE", WHITE_COLOR, centerBox);
    }

    if (mState == State::STATE_PLAY) {
        // Render the expression, inputbox, lives player's score and enemy
        SDL_Rect mathExprRect = {(mWidth - 200) / 2, 0, 200, 100};
        SDL_Rect inputboxRect = {(mWidth - 50) / 2, mHeight - 75, 50, 75};
        SDL_Rect livesRect = {0, 0, 200, 100};
        SDL_Rect scoreRect = {0, 100, 200, 100};

        std::string livesText = "LIVES: " + std::to_string(mLives);
        std::string scoreText = "SCORE: " + std::to_string(mScore);

        DrawText(mFont, livesText.c_str(), WHITE_COLOR, livesRect);
        DrawText(mFont, scoreText.c_str(), WHITE_COLOR, scoreRect);

        DrawText(mFont, gMathExpr.GetExpression().c_str(), WHITE_COLOR, mathExprRect);
        DrawText(mFont, gInput.c_str(), WHITE_COLOR, inputboxRect);
        gEnemy.Render();
    }

    if (mState == State::STATE_OVER) {
        // Render "Game over" text
        SDL_Rect centerBox = {(mWidth - 200) / 2, (mHeight - 100) / 2, 200, 100};
        SDL_Rect scoreBox = {(mWidth - 200) / 2, centerBox.y + 100, 200, 100};

        std::string str = "SCORE: " + std::to_string(mScore);
        DrawText(mFont, "GAME OVER", WHITE_COLOR, centerBox);
        DrawText(mFont, str.c_str(), WHITE_COLOR, scoreBox);
    }

    SDL_RenderPresent(mRenderer);
}
