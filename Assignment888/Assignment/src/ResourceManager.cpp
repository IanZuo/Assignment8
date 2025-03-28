#include "../include/ResourceManager.h"

// getinstance
ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    if (filePath.empty() || filePath == "NoTexture") {  //  Ignore "NoTexture"
        std::cerr << "[INFO] Skipping texture loading for empty path or NoTexture.\n";
        return nullptr;
    }

    auto it = textures.find(filePath);
    if (it != textures.end()) {
        return it->second;
    }

    std::cout << "[INFO] Loading texture: " << filePath << std::endl;
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (!surface) {
        std::cerr << "[ERROR] Failed to load BMP: " << filePath << " | SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "[ERROR] Failed to create texture from BMP: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    auto sharedTexture = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
    textures[filePath] = sharedTexture;
    return sharedTexture;
}



// release resources
void ResourceManager::Shutdown() {
    textures.clear();
    std::cout << "[INFO] ResourceManager: All textures have been freed." << std::endl;
}
