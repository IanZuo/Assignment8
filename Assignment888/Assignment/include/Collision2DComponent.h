#ifndef COLLISION2D_COMPONENT_H
#define COLLISION2D_COMPONENT_H

#include "Component.h"
#include <SDL.h>

class Collision2DComponent : public Component {
public:
    Collision2DComponent(float x = 0.0f, float y = 0.0f, float w = 40.0f, float h = 40.0f);

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    ComponentType GetType() override { return ComponentType::Collision2DComponent; }

    SDL_FRect& GetRectangle();

private:
    SDL_FRect mRectangle;
};

#endif // COLLISION2D_COMPONENT_H