#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>

class TextureComponent : public Component {
public:
    TextureComponent(SDL_Renderer* renderer, const std::string& filePath);

    void Input(float /*deltaTime*/) override {}  // 
    void Update(float /*deltaTime*/) override {} // 
    void Render(SDL_Renderer* renderer) override;

    ComponentType GetType()  { return ComponentType::TextureComponent; }

    std::shared_ptr<SDL_Texture> GetTexture()  { return mTexture; }
    SDL_Renderer* GetRenderer()  { return mRenderer; }

private:
    std::shared_ptr<SDL_Texture> mTexture;
    SDL_Renderer* mRenderer;
};

#endif // TEXTURE_COMPONENT_H
