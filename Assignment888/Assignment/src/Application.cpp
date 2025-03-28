#include "../include/Application.h"
#include "../include/InputComponent.h"
#include "../include/ResourceManager.h"
#include "../include/TextureComponent.h"
#include "../include/Collision2DComponent.h"
#include "../include/Projectile.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Application* gApplication = nullptr;

Application::Application() : mWindow(nullptr), mRenderer(nullptr), mRun(true), score(0), frameCount(0), fps(0), lastFPSUpdate(SDL_GetTicks()) {}

Application::~Application() {
    Shutdown();
}

bool Application::Initialize() {
    gApplication = this;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    mWindow = SDL_CreateWindow("Assignment 05", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!mWindow || !mRenderer) {
        std::cerr << "Failed to create window or renderer." << std::endl;
        return false;
    }

    mainCharacter = std::make_shared<Player>(mRenderer, 0, 0, 300.0f);

    float startX = 50.0f, startY = 50.0f;
    float spacingX = 60.0f, spacingY = 50.0f;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 12; ++col) {
            float x = startX + col * spacingX;
            float y = startY + row * spacingY;

            auto enemy = std::make_shared<Enemy>(mRenderer, 0, 0, 100.0f);
            mEnemies.push_back(enemy);
        }
    }

    mainCharacter->Initialize(mRenderer, 380.0f, 550.0f, 300.0f);
    mainCharacter->AddComponent(std::make_shared<Collision2DComponent>());

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 12; ++col) {
            int index = row * 12 + col;
            float x = startX + col * spacingX;
            float y = startY + row * spacingY;

            mEnemies[index]->Initialize(mRenderer, x, y, 100.0f);
            mEnemies[index]->AddComponent(std::make_shared<Collision2DComponent>());
        }
    }

    return true;
}

void Application::SendProjectileToApplication(std::shared_ptr<Projectile> projectile) {
    mProjectiles.push_back(projectile);
}


void Application::Run(int targetFPS) {
    const int frameDelay = 1000 / targetFPS;
    Uint32 frameStart, frameTime, lastFrameTime = SDL_GetTicks();
    float deltaTime = 0.1f;
    float enemyMoveDirection = 1.0f;

    while (mRun) {
        frameStart = SDL_GetTicks();

        ProcessInput();

        Uint32 currentFrameTime = SDL_GetTicks();
        deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;
        if (deltaTime > 0.1f) deltaTime = 0.1f;

        if (mainCharacter) mainCharacter->Input(deltaTime);
        Update(deltaTime, enemyMoveDirection);
        Render();

        frameCount++;
        if (SDL_GetTicks() - lastFPSUpdate >= 1000) {
            fps = frameCount;
            frameCount = 0;
            lastFPSUpdate = SDL_GetTicks();
            std::stringstream title;
            title << "Assignment 05 - FPS: " << fps << " - Score: " << score;
            SDL_SetWindowTitle(mWindow, title.str().c_str());
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
    }
}

void Application::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) mRun = false;
    }
}

void Application::Update(float deltaTime, float& enemyMoveDirection) {
    // up enemy
    for (auto& enemy : mEnemies) {
        enemy->Update(deltaTime);
    }

    // player up
    if (mainCharacter) mainCharacter->Update(deltaTime);

    // update
    for (auto& projectile : mProjectiles) {
        projectile->Update(deltaTime);  // update bullet
    }

    // check colli
    for (auto& projectile : mProjectiles) {
        for (auto it = mEnemies.begin(); it != mEnemies.end();) {
            bool collisionDetected = projectile->CheckCollision(**it);  // CheckCollision
            std::cout << "Checking Collision: Bullet (" 
                      << projectile->GetTransform()->GetX() << ", " 
                      << projectile->GetTransform()->GetY() << ") vs Enemy (" 
                      << (*it)->GetTransform()->GetX() << ", "
                      << (*it)->GetTransform()->GetY() << ")\n";  // dubug info

            if (collisionDetected) {
                std::cout << "Collision detected!\n";
                // WIpe enemy add score
                it = mEnemies.erase(it);  
                score++;
            } else {
                ++it;
            }
        }
    }

    // delete
    mProjectiles.erase(std::remove_if(mProjectiles.begin(), mProjectiles.end(),
        [](std::shared_ptr<Projectile>& p) { return p->IsOffScreen(); }), mProjectiles.end());
}




    void Application::Render() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    if (mainCharacter) mainCharacter->Render(mRenderer);
    for (auto& enemy : mEnemies) enemy->Render(mRenderer);
    for (auto& projectile : mProjectiles) projectile->Render(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_Rect scoreBar = {10, 10, score * 10, 10};
    SDL_RenderFillRect(mRenderer, &scoreBar);

    SDL_RenderPresent(mRenderer);
}


void Application::Shutdown() {
    ResourceManager::GetInstance().Shutdown();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
