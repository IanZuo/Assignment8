#include <string>
#include <unordered_map>
#include <iostream>
#include "../include/ResourceManager.hpp"

// Initialize our static member variable.
ResourceManager* ResourceManager::mInstance = nullptr;

/**
 * @struct TextureFunctorDeleter
 * @brief A custom deleter for SDL_Texture used with smart pointers.
 * 
 * This struct defines a functor (function object) that properly deletes an 
 * SDL_Texture when used with std::unique_ptr or std::shared_ptr. It ensures 
 * that SDL_DestroyTexture() is called automatically when the texture is no 
 * longer needed, preventing memory leaks.
 */
struct TextureFunctorDeleter {
    /**
     * @brief Overloaded function call operator to delete an SDL_Texture.
     * 
     * This operator is invoked when the smart pointer goes out of scope or 
     * needs to free the SDL_Texture resource. It calls SDL_DestroyTexture() 
     * to properly release the texture from memory.
     * 
     * @param texture Pointer to the SDL_Texture to be destroyed.
     */
    void operator()(SDL_Texture* texture) const {
        SDL_DestroyTexture(texture);
    }
};

/**
 * @brief Creates a shared pointer to an SDL_Texture from an SDL_Surface.
 *
 * This function takes an SDL_Renderer and an SDL_Surface, creates an SDL_Texture 
 * from the surface, and returns it as a std::shared_ptr with a custom deleter.
 *
 * @param renderer A pointer to the SDL_Renderer used to create the texture.
 * @param pixels A pointer to the SDL_Surface containing pixel data for the texture.
 * @return std::shared_ptr<SDL_Texture> A shared pointer managing the created texture.
 *         If texture creation fails, a null shared pointer is returned.
 */
std::shared_ptr<SDL_Texture> ResourceManager::make_shared_texture(SDL_Renderer* renderer, SDL_Surface* pixels) {
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pixels);

    if (pTexture == nullptr) {
        SDL_Log("Could not load texture from surface.");
    }

    return std::shared_ptr<SDL_Texture>(pTexture, TextureFunctorDeleter());
}

// Get the instance or create the only instance.
ResourceManager& ResourceManager::Instance() {
    if (mInstance == nullptr) {
        mInstance = new ResourceManager();  // Allocate the singleton instance
    }
    return *mInstance;
}

// Load in a texture.
std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(SDL_Renderer* renderer, std::string filePath) {
        std::cout << "File Path in Load Texture" << filePath << std::endl;
    // Check if texture is already loaded
    if (mTextures.contains(filePath)) {
        std::cout << "Reusing Texture: " << mTextures[filePath].get() << std::endl;
        return mTextures[filePath];
    }

    // Load BMP file
    SDL_Surface* pixels = SDL_LoadBMP(filePath.c_str());
    if (!pixels) {
        SDL_Log("Failed to load image: %s", SDL_GetError());
        return nullptr;
    }

    std::shared_ptr<SDL_Texture> texture = make_shared_texture(renderer, pixels);
    mTextures[filePath] = texture;
    SDL_FreeSurface(pixels);  // Free the surface as it's no longer needed
    std::cout << "Creating New Texture: " << mTextures[filePath].get() << std::endl;

    return texture;
}
