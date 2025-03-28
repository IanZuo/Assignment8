// Explicit Template Instantiation
template void GameEntity::AddComponent<TextureComponent>(std::shared_ptr<TextureComponent> C);
template void GameEntity::AddComponent<InputComponent>(std::shared_ptr<InputComponent> C);
// template void GameEntity::AddComponent<TransformComponent>(std::shared_ptr<TransformComponent> C);
// template void GameEntity::AddComponent<Collision2DComponent>(std::shared_ptr<Collision2DComponent> C);

template std::shared_ptr<TextureComponent> GameEntity::GetComponent<TextureComponent>(ComponentType type);
template std::shared_ptr<InputComponent> GameEntity::GetComponent<InputComponent>(ComponentType type);
// template std::shared_ptr<TransformComponent> GameEntity::GetComponent<TransformComponent>(ComponentType type);
// template std::shared_ptr<Collision2DComponent> GameEntity::GetComponent<Collision2DComponent>(ComponentType type);