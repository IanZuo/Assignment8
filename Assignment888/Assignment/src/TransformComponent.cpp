#include "../include/TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, float w, float h) {
    mRectangle = {x, y, w, h};
}

void TransformComponent::Input(float deltaTime) {
    // empty
}

void TransformComponent::Update(float deltaTime) {
    // empty
}

void TransformComponent::Render(SDL_Renderer* renderer) {
    // empty
}

float TransformComponent::GetX()  { return mRectangle.x; }
float TransformComponent::GetY()  { return mRectangle.y; }
float TransformComponent::GetW()  { return mRectangle.w; }
float TransformComponent::GetH()  { return mRectangle.h; }

void TransformComponent::SetX(float x) { mRectangle.x = x; }
void TransformComponent::SetY(float y) { mRectangle.y = y; }
void TransformComponent::SetW(float w) { mRectangle.w = w; }
void TransformComponent::SetH(float h) { mRectangle.h = h; }

SDL_FRect& TransformComponent::GetRectangle() { return mRectangle; }

