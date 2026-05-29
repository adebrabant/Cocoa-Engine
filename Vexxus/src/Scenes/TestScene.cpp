#include "Scenes/TestScene.hpp"
#include "Scenes/Components/TransformComponent.hpp"
#include "Scenes/Components/CameraComponent.hpp"
#include "Scenes/Systems/CameraSystem.hpp"

namespace Vexxus
{
    void TestScene::Load()
    {
        auto cameraEntity = m_world.CreateEntity();
        m_world.AddComponent(cameraEntity, Cocoa::Scenes::TransformComponent{ 0, 0, 0, 0, 0 });
        m_world.AddComponent(cameraEntity, Cocoa::Scenes::CameraComponent{ 0, 0, 0, 60.0f });
        m_world.AddSystem<Cocoa::Scenes::CameraSystem>();
    }

	void TestScene::Unload()
	{

	}
}