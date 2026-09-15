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

		const auto defaultMaterial = loader.LoadMaterial("default_material");

		const auto sunEntity = m_world.CreateEntity();
		Cocoa::Scenes::TransformComponent sunsetTransform
		{
			.Position = { 0.0f, 0.0f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto mountainBackgroundEntity = m_world.CreateEntity();
		Cocoa::Scenes::TransformComponent mountainBackgroundTransform
		{
			.Position = { 0.0f, -0.05f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto forestFogBackground01Entity = m_world.CreateEntity();
		Cocoa::Scenes::TransformComponent forestFogBackground01Transform
		{
			.Position = { 0.0f, -0.15f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto forestFogBackground02Entity = m_world.CreateEntity();
		Cocoa::Scenes::TransformComponent forestFogBackground02Transform
		{
			.Position = { 0.0f, -0.25f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto cherryBlossomTree01Entity = m_world.CreateEntity();
		Cocoa::Scenes::TransformComponent cherryBlossomTree01Transform
		{
			.Position = { -1.20f, -0.35f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 0.75f, 0.75f, 1.0f }
		};

		auto cherryBlossomTree02Entity = m_world.CreateEntity();
		Cocoa::Scenes::TransformComponent cherryBlossomTree02Transform
		{
			.Position = { 1.20f, -0.35f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 0.75f, 0.75f, 1.0f }
		};

		m_world.AddComponent(sunEntity, sunsetTransform);
		m_world.AddComponent(
			sunEntity,
			Cocoa::Scenes::Renderable2DComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("sunset_background_01_sprite")
			}
		);

		m_world.AddComponent(mountainBackgroundEntity, mountainBackgroundTransform);
		m_world.AddComponent(
			mountainBackgroundEntity,
			Cocoa::Scenes::Renderable2DComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("mountains_background_01_sprite")
			}
		);

		m_world.AddComponent(forestFogBackground01Entity, forestFogBackground01Transform);
		m_world.AddComponent(
			forestFogBackground01Entity,
			Cocoa::Scenes::Renderable2DComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("forest_fog_background_01_sprite")
			}
		);

		m_world.AddComponent(forestFogBackground02Entity, forestFogBackground02Transform);
		m_world.AddComponent(
			forestFogBackground02Entity,
			Cocoa::Scenes::Renderable2DComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("forest_fog_background_02_sprite")
			}
		);

		m_world.AddComponent(cherryBlossomTree01Entity, cherryBlossomTree01Transform);
		m_world.AddComponent(
			cherryBlossomTree01Entity,
			Cocoa::Scenes::Renderable2DComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("cherry_blossom_tree_01_sprite")
			}
		);

		m_world.AddComponent(cherryBlossomTree02Entity, cherryBlossomTree02Transform);
		m_world.AddComponent(
			cherryBlossomTree02Entity,
			Cocoa::Scenes::Renderable2DComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("cherry_blossom_tree_02_sprite")
			}
		);

		m_world.AddSystem<Cocoa::Scenes::RenderSystem>();
    }

	void TestScene::Unload(Cocoa::Assets::ResourceLoader& loader)
	{

	}
}