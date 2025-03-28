#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

class Application {
public:
    Application();
    ~Application();

    bool Initialize();
    void Run(int targetFPS);
    void Shutdown();
    void Render();

    void SendProjectileToApplication(std::shared_ptr<Projectile> projectile);

private:
    void ProcessInput();
    void Update(float deltaTime, float& enemyMoveDirection);

    // Game properties
    int score;
    int frameCount;
    int fps;
    Uint32 lastFPSUpdate;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mRun;

    std::shared_ptr<Player> mainCharacter;               //   shared_ptr
    std::vector<std::shared_ptr<Enemy>> mEnemies;        //   shared_ptr
    std::vector<std::shared_ptr<Projectile>> mProjectiles; //  shared_ptr
};

#endif // APPLICATION_H
