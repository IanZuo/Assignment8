#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include <SDL2/SDL.h>

class TransformComponent : public Component {
public:
    TransformComponent(float x = 0.0f, float y = 0.0f, float w = 40.0f, float h = 40.0f);

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    ComponentType GetType() override { return ComponentType::TransformComponent; }

    float GetX() ;
    float GetY() ;
    float GetW() ;
    float GetH() ;

    void SetX(float x);
    void SetY(float y);
    void SetW(float w);
    void SetH(float h);

    SDL_FRect& GetRectangle();

private:
    SDL_FRect mRectangle;
};

#endif // TRANSFORM_COMPONENT_H
