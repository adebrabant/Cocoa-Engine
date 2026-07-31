#include "Scenes/TestScene.hpp"
#include <Scenes/Components/TransformComponent.hpp>
#include <Scenes/Components/CameraComponent.hpp>
#include <Scenes/Components/Renderable2DComponent.hpp>
#include <Scenes/Systems/CameraSystem.hpp>
#include <Scenes/Systems/RenderSystem.hpp>
#include <Assets/ResourceLoader.hpp>

namespace Sandbox
{
    void TestScene::Load(Cocoa::Assets::ResourceLoader& loader)
    {
        auto cameraEntity = m_world.CreateEntity();
        m_world.AddComponent(cameraEntity, Cocoa::Scenes::CameraComponent{ 0, 0, 0, 60.0f });
        m_world.AddSystem<Cocoa::Scenes::CameraSystem>();

        auto dummyEntity = m_world.CreateEntity();
        auto materialHandle = loader.LoadMaterial("werewolf_material");
    	Cocoa::Scenes::TransformComponent wereWolfTransform
    	{
    		.Position = { 0.2f, 0.0f, 0.0f },
    		.Rotation = {0.0f, 0.0f, 0.0f },
    		.Scale =  { 0.5f, 0.5f, 0.5f }
    	};
    	m_world.AddComponent(dummyEntity, wereWolfTransform);
        m_world.AddComponent(dummyEntity, Cocoa::Scenes::Renderable2DComponent{ materialHandle });
        m_world.AddSystem<Cocoa::Scenes::RenderSystem>();
    }

	void TestScene::Unload(Cocoa::Assets::ResourceLoader& loader)
	{

	}
}