#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>

class ResourceManager {
public:
    // getinstance
    static ResourceManager& GetInstance();

    // ensure instance
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // load bmp
    std::shared_ptr<SDL_Texture> LoadTexture(SDL_Renderer* renderer, const std::string& filePath);

    // get loaded texture
    std::shared_ptr<SDL_Texture> GetTexture(const std::string& filePath);

    // release
    void Shutdown();

private:
    ResourceManager() = default; 
    ~ResourceManager() { Shutdown(); } // clear resources

    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textures;
};

#endif // RESOURCE_MANAGER_H
