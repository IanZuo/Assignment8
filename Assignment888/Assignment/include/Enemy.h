#ifndef ENEMY_H
#define ENEMY_H

#include "GameEntity.h"
#include "Projectile.h"
#include <vector>

class Enemy : public GameEntity {
public:
    Enemy(SDL_Renderer* renderer, float x, float y, float speed);
    void Initialize(SDL_Renderer* renderer, float x, float y, float speed);

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;
    void Shoot();

private:
    float moveDirection{1.0f};
    Uint64 lastShotTime;
    std::vector<Projectile> mProjectiles;
    float mSpeed;
};

#endif // ENEMY_H
