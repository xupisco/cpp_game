#include <iostream>

#include "../lib/glm/glm.hpp"

#include "./Game.h"
#include "./Constants.h"
#include "./AssetManager.h"

#include "./components/SpriteComponent.h"
#include "./components/TransformComponent.h"

EntityManager manager;
SDL_Renderer* Game::renderer;
AssetManager* Game::assetManager = new AssetManager(&manager);

Game::Game() {
    this->isRunning = false;
}

Game::~Game() { }

bool Game::IsRunning() const {
    return this->isRunning;
}

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
    
    LoadLevel(0);
    
    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
    // Add assets
    std::string textureFilePath = "./assets/images/tank-big-right.png";
    assetManager->AddTexture("tank-image", textureFilePath.c_str());
    
    // Add entities and components
    Entity& tank(manager.AddEntity("tank"));
    tank.AddComponent<TransformComponent>(0, 100, 20, 0, 64, 64, 1);
    tank.AddComponent<SpriteComponent>("tank-image");
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
    // FPS and time management
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }
    
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();
    
    manager.Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    
    if (manager.HasNoEntities()) {
        return;
    }
    
    manager.Render();
    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
