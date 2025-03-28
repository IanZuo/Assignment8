#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "TextureComponent.h"
#include <SDL2/SDL.h>

class InputComponent : public Component {
public:
    InputComponent(float speed);
    virtual ~InputComponent() = default;

    void Input(float deltaTime) override;
    void Update(float deltaTime) override {}
    void Render(SDL_Renderer* renderer) override {}

    ComponentType GetType() override { return ComponentType::InputComponent; }

private:
    float mSpeed;
};

#endif // INPUT_COMPONENT_H
