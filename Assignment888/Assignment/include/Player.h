#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Projectile.h"
#include <vector>

class Player : public GameEntity {
public:
    Player(SDL_Renderer* renderer, float x, float y, float speed);
    void Initialize(SDL_Renderer* renderer, float x, float y, float speed);

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    void Shoot();
    void SendProjectileToApplication(Projectile projectile);

private:
    std::vector<Projectile> mProjectiles;
    Uint64 lastShotTime{0};
    float mSpeed;
};

#endif // PLAYER_H
