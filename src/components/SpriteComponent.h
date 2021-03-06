#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "./TransformComponent.h"

class SpriteComponent: public Component {
    public:
        TransformComponent* transform;
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
        SpriteComponent(const char* filePath) {
            SetTexture(filePath);
        }
        
        void SetTexture(std::string assetTextureId) {
            texture = Game::assetManager->GetTexture(assetTextureId);
        }
        
        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            sourceRect.x = 0;
            sourceRect.y = 0;
            sourceRect.w = transform->width;
            sourceRect.h = transform->height;
        }
        
        void Update(float deltaTime) override {
            destRect.x = (int) transform->position.x;
            destRect.y = (int) transform->position.y;
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
        }
        
        void Render() override {
            TextureManager::Draw(texture, sourceRect, destRect, spriteFlip);
        }
    
    private:
        SDL_Texture* texture;
        SDL_Rect sourceRect;
        SDL_Rect destRect;
};

#endif
