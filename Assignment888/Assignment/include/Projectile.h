#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameEntity.h"
#include "TransformComponent.h"
#include "Collision2DComponent.h"
#include <SDL.h>
#include <memory>

class Projectile : public GameEntity {
public:
    // 构造函数：增加了一个新的参数 isPlayerBullet
    Projectile(SDL_Renderer* renderer, float x, float y, float speed, bool goingUp, bool isPlayerBullet);

    // Method to set the initial position of the projectile
    void SetInitialPosition(float x, float y);

    // Update the projectile's position and check its state
    void Update(float deltaTime) override;

    // Render the projectile on the screen
    void Render(SDL_Renderer* renderer) override;

    // Check if the projectile is off screen
    bool IsOffScreen();

    // Check if the projectile collided with another entity
    bool CheckCollision(GameEntity& entity);


    float mSpeed;
    bool mYDirectionUp;  // true means the projectile moves upwards
    bool mIsFiring;  // Whether the projectile is still firing
    bool isPlayerBullet;  // true means it is a player bullet, false means it's an enemy bullet

private:
    SDL_Renderer* mRenderer;
    
};

#endif // PROJECTILE_H
