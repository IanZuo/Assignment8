#include "../include/Player.h"
#include "../include/Application.h"
#include "../include/TextureComponent.h"
#include "../include/InputComponent.h"
#include "../include/TransformComponent.h"
#include "../include/Collision2DComponent.h"
#include <SDL.h>
#include <iostream>
#include <algorithm>

extern Application* gApplication;

Player::Player(SDL_Renderer* renderer, float x, float y, float speed)
    : GameEntity(), mSpeed(speed) {
}

void Player::Initialize(SDL_Renderer* renderer, float x, float y, float speed) {
       // 使用 std::make_shared 创建并管理 Player 对象
       auto player = std::make_shared<Player>(renderer, x, y, speed);
    
       // 现在可以安全地调用 GetThisPtr()
       player->GetThisPtr();  // 确保在此时调用，安全地使用 shared_from_this()


    auto textureComp = std::make_shared<TextureComponent>(renderer, "Assignment/Assets/Spaceship.bmp");
    AddComponent(textureComp);

    auto inputComp = std::make_shared<InputComponent>(speed);
    AddComponent(inputComp);

    AddDefaultTransform();
    GetTransform()->SetX(x);
    GetTransform()->SetY(y);
    GetTransform()->SetW(40);
    GetTransform()->SetH(40);

    auto collisionComp = std::make_shared<Collision2DComponent>();
    AddComponent(collisionComp); // ✅ 添加 Collision2DComponent
}

void Player::Input(float deltaTime) {
    auto inputComp = GetComponent<InputComponent>(ComponentType::InputComponent);
    if (inputComp) inputComp->Input(deltaTime);
}

void Player::Update(float deltaTime) {
    // limit delta tinme
    const float MAX_DELTA_TIME = 0.05f;  // maxDeltaTime
    if (deltaTime > MAX_DELTA_TIME) {
        deltaTime = MAX_DELTA_TIME;  
    }

    // updating
    GameEntity::Update(deltaTime);

    // updating
    for (auto& projectile : mProjectiles) {
        projectile.Update(deltaTime);
    }

    // delete bullet out edge
    mProjectiles.erase(
        std::remove_if(mProjectiles.begin(), mProjectiles.end(),
            [](Projectile& p) { return p.IsOffScreen(); }),
        mProjectiles.end()
    );
}

void Player::Render(SDL_Renderer* renderer) {
    GameEntity::Render(renderer);
    for (auto& projectile : mProjectiles) {
        projectile.Render(renderer);
    }
}


void Player::Shoot() {
    auto textureComp = GetComponent<TextureComponent>(ComponentType::TextureComponent);
    auto transform = GetTransform();
    if (!textureComp || !transform) return;

    // 设置为玩家子弹
    std::shared_ptr<Projectile> newBullet = std::make_shared<Projectile>(
        textureComp->GetRenderer(),
        transform->GetX() + 15,
        transform->GetY() - 10,
        500.0f,
        true,   // 上方向
        true    // 是玩家的子弹
    );

    gApplication->SendProjectileToApplication(newBullet);  // 发送玩家的子弹
}

