#include <iostream>

#include "./Constants.h"
#include "./Game.h"

Game::Game() {
    this->isRunning = false;
}
Game::~Game() { }

bool Game::IsRunning() const {
    return this->isRunning;
}

float px = 0.0f;
float py = 0.0f;
float velx = 0.05f;
float vely = 0.05f;

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    
    window = SDL_CreateWindow(
        "Alaworld",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;   
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }
    
    isRunning = true;
    return;
}

void Game::ProcessInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
                break;
            }
        default:
            break;
    }
}

void Game::Update() {
    px += velx;
    py += vely;
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    
    SDL_Rect p {
        (int) px, (int) py,
        10, 10
    };
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &p);
    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
