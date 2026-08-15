#include "Scenes/TestScene.hpp"
#include <Scenes/Components/TransformComponent.hpp>
#include <Scenes/Components/CameraComponent.hpp>
#include <Scenes/Components/Renderable2DComponent.hpp>
#include <Scenes/Systems/CameraSystem.hpp>
#include <Scenes/Systems/RenderSystem.hpp>
#include <Assets/ResourceLoader.hpp>

namespace Sandbox
{
	TestScene::TestScene(const Cocoa::Graphics::Viewport& viewport)
		: Scene(viewport)
	{

	}

	TestScene::~TestScene() = default;

	void TestScene::Load(Cocoa::Assets::ResourceLoader& loader)
    {
        auto cameraEntity = m_world.CreateEntity();
        m_world.AddComponent(cameraEntity, Cocoa::Scenes::CameraComponent{ 0, 0, 0, 60.0f });
        m_world.AddSystem<Cocoa::Scenes::CameraSystem>();

		auto sunEntity = m_world.CreateEntity();
		auto sunMaterialHandle = loader.LoadMaterial("sunset_background_01_material");
		Cocoa::Scenes::TransformComponent sunsetTransform
		{
			.Position = { 0.0f, 0.0f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto mountainBackgroundEntity = m_world.CreateEntity();
		auto mountainBackgroundMaterialHandle = loader.LoadMaterial("mountains_background_01_material");
		Cocoa::Scenes::TransformComponent mountainBackgroundTransform
		{
			.Position = { 0.0f, -0.05f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto forestFogBackground01Entity = m_world.CreateEntity();
		auto forestFogBackground01MaterialHandle = loader.LoadMaterial("forest_fog_background_01_material");
		Cocoa::Scenes::TransformComponent forestFogBackground01Transform
		{
			.Position = { 0.0f, -0.15f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto forestFogBackground02Entity = m_world.CreateEntity();
		auto forestFogBackground02MaterialHandle = loader.LoadMaterial("forest_fog_background_02_material");
		Cocoa::Scenes::TransformComponent forestFogBackground02Transform
		{
			.Position = { 0.0f, -0.25f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		m_world.AddComponent(sunEntity, sunsetTransform);
		m_world.AddComponent(sunEntity, Cocoa::Scenes::Renderable2DComponent{ sunMaterialHandle });

		m_world.AddComponent(mountainBackgroundEntity, mountainBackgroundTransform);
		m_world.AddComponent(mountainBackgroundEntity, Cocoa::Scenes::Renderable2DComponent{ mountainBackgroundMaterialHandle });

		m_world.AddComponent(forestFogBackground01Entity, forestFogBackground01Transform);
		m_world.AddComponent(forestFogBackground01Entity, Cocoa::Scenes::Renderable2DComponent{ forestFogBackground01MaterialHandle });

		m_world.AddComponent(forestFogBackground02Entity, forestFogBackground02Transform);
		m_world.AddComponent(forestFogBackground02Entity, Cocoa::Scenes::Renderable2DComponent{ forestFogBackground02MaterialHandle });

		m_world.AddSystem<Cocoa::Scenes::RenderSystem>();
    }

	void TestScene::Unload(Cocoa::Assets::ResourceLoader& loader)
	{

	}
}