#include "../include/TextureComponent.h"
#include "../include/TransformComponent.h"
#include "../include/GameEntity.h"
#include "../include/ResourceManager.h"
#include <iostream>

TextureComponent::TextureComponent(SDL_Renderer* renderer, const std::string& filePath)
    : mRenderer(renderer) {

    if (!filePath.empty()) {
        mTexture = ResourceManager::GetInstance().LoadTexture(renderer, filePath);
        if (!mTexture) {
            std::cerr << "[ERROR] Failed to load texture in TextureComponent: " << filePath << std::endl;
        }
    }
}

void TextureComponent::Render(SDL_Renderer* renderer) {
    auto entity = GetGameEntity();
    if (!entity) return;

    auto transformComp = entity->GetTransform();
    if (!transformComp) return;

    SDL_FRect rect = transformComp->GetRectangle();

    if (mTexture) {
        SDL_RenderCopyF(renderer, mTexture.get(), nullptr, &rect);
    }
}
