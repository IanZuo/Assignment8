#include "../include/GameEntity.h"
#include "../include/InputComponent.h"
#include "../include/TextureComponent.h"
#include "../include/TransformComponent.h"
#include "../include/Collision2DComponent.h"
#include <iostream>


GameEntity::GameEntity() {}

void GameEntity::Input(float deltaTime) {
    for (auto& [type, component] : mComponents) {
        component->Input(deltaTime);
    }
}

void GameEntity::Update(float deltaTime) {
    // make sure updating component
    for (auto& [type, component] : mComponents) {
        component->Update(deltaTime);
    }

    // updating components data
    auto collisionComp = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent);
    if (collisionComp) {
        collisionComp->Update(deltaTime);
    }

    // updating components
    auto transformComp = GetComponent<TransformComponent>(ComponentType::TransformComponent);
    if (transformComp) {
        transformComp->Update(deltaTime);  //updating
    }
}

void GameEntity::Render(SDL_Renderer* renderer) {
    for (auto& [type, component] : mComponents) {
        component->Render(renderer);
    }
}

void GameEntity::AddComponent(std::shared_ptr<Component> component) {
    auto self = GetThisPtr();
    if (self) {
        component->SetGameEntity(self);
    } else {
        std::cerr << "[WARNING] GameEntity not managed by shared_ptr yet!\n";

        // output component 
        std::cerr << "[DEBUG] Adding component of type: "
                  << static_cast<int>(component->GetType()) << "\n";
    }
    mComponents[component->GetType()] = component;
}


void GameEntity::AddDefaultTransform(float x, float y, float w, float h) {
    auto transform = std::make_shared<TransformComponent>(x, y, w, h);
    AddComponent(transform);
}

std::shared_ptr<TransformComponent> GameEntity::GetTransform() {
    return GetComponent<TransformComponent>(ComponentType::TransformComponent);
}

// Explicit Template Instantiation
template std::shared_ptr<TransformComponent> GameEntity::GetComponent<TransformComponent>(ComponentType type);

template <typename T>
std::shared_ptr<T> GameEntity::GetComponent(ComponentType type) {
    auto it = mComponents.find(type);
    if (it != mComponents.end()) {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
}

std::shared_ptr<GameEntity> GameEntity::GetThisPtr() {
    try {
        return shared_from_this();
    } catch (const std::bad_weak_ptr& e) {
        std::cerr << "[ERROR] shared_from_this failed: " << e.what() << "\n";
        return nullptr;
    }
}


template std::shared_ptr<TextureComponent> GameEntity::GetComponent<TextureComponent>(ComponentType type);
template std::shared_ptr<InputComponent> GameEntity::GetComponent<InputComponent>(ComponentType type);
template std::shared_ptr<Collision2DComponent> GameEntity::GetComponent<Collision2DComponent>(ComponentType type);
