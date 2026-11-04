#include "Scenes/TestScene.hpp"
#include <Scenes/Components/TransformComponent.hpp>
#include <Scenes/Components/CameraComponent.hpp>
#include <Scenes/Components/SpriteComponent.hpp>
#include <Scenes/Components/ColorQuadComponent.hpp>
#include <Scenes/Components/ProjectionComponent.hpp>
#include <Scenes/Systems/CameraSystem.hpp>
#include <Scenes/Systems/Render2DSystem.hpp>
#include <Assets/ResourceLoader.hpp>


namespace Sandbox
{
	TestScene::~TestScene() = default;

	void TestScene::Load(Cocoa::Assets::ResourceLoader& loader)
    {
        auto cameraEntity = m_world.CreateEntity();
        m_world.AddComponent(cameraEntity, Cocoa::Scenes::CameraComponent{ true });
		m_world.AddComponent(cameraEntity, Cocoa::Scenes::ProjectionComponent{});
		m_world.AddComponent(cameraEntity, Cocoa::Scenes::TransformComponent{});
        m_world.AddSystem<Cocoa::Scenes::CameraSystem>();

		const auto defaultMaterial = loader.LoadMaterial("default_material");

		const auto sunEntity = m_world.CreateEntity();
		m_world.AddComponent(
			sunEntity,
			Cocoa::Scenes::TransformComponent
			{
				.Position = { 0.0f, 0.0f, 0.0f },
				.Rotation =  { 0.0f, 0.0f, 0.0f },
				.Scale = { 3.56f, 2.0f, 1.0f }
			}
		);
		m_world.AddComponent(
			sunEntity,
			Cocoa::Scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("sunset_background_01_sprite"),
				.SortingLayer = Cocoa::Graphics::SortLayer::Background,
				.SortingOrder = 0
			}
		);

		const auto mountainBackgroundEntity = m_world.CreateEntity();
		m_world.AddComponent(
			mountainBackgroundEntity,
			Cocoa::Scenes::TransformComponent
			{
				.Position = { 0.0f, -0.05f, 0.0f },
				.Rotation =  { 0.0f, 0.0f, 0.0f },
				.Scale = { 3.56f, 2.0f, 1.0f }
			}
		);
		m_world.AddComponent(
			mountainBackgroundEntity,
			Cocoa::Scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("mountains_background_01_sprite"),
				.SortingLayer = Cocoa::Graphics::SortLayer::Background,
				.SortingOrder = 1
			}
		);

		const auto forestFogBackground01Entity = m_world.CreateEntity();
		m_world.AddComponent(forestFogBackground01Entity,
			Cocoa::Scenes::TransformComponent
			{
				.Position = { 0.0f, -0.15f, 0.0f },
				.Rotation =  { 0.0f, 0.0f, 0.0f },
				.Scale = { 3.56f, 2.0f, 1.0f }
			}
		);
		m_world.AddComponent(
			forestFogBackground01Entity,
			Cocoa::Scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("forest_fog_background_01_sprite"),
				.SortingLayer = Cocoa::Graphics::SortLayer::Background,
				.SortingOrder = 2
			}
		);

		const auto forestFogBackground02Entity = m_world.CreateEntity();
		m_world.AddComponent(
			forestFogBackground02Entity,
			Cocoa::Scenes::TransformComponent
			{
				.Position = { 0.0f, -0.25f, 0.0f },
				.Rotation =  { 0.0f, 0.0f, 0.0f },
				.Scale = { 3.56f, 2.0f, 1.0f }
			}
		);
		m_world.AddComponent(
			forestFogBackground02Entity,
			Cocoa::Scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("forest_fog_background_02_sprite"),
				.SortingLayer = Cocoa::Graphics::SortLayer::Background,
				.SortingOrder = 3
			}
		);

		const auto cherryBlossomTree02Entity = m_world.CreateEntity();
		m_world.AddComponent(
			cherryBlossomTree02Entity,
			Cocoa::Scenes::TransformComponent
			{
				.Position = { 1.20f, -0.35f, 0.0f },
				.Rotation =  { 0.0f, 0.0f, 0.0f },
				.Scale = { 0.75f, 0.75f, 1.0f }
			}
		);
		m_world.AddComponent(
			cherryBlossomTree02Entity,
			Cocoa::Scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("cherry_blossom_tree_02_sprite"),
				.FlipVertical = false,
				.FlipHorizontal = true,
				.SortingLayer = Cocoa::Graphics::SortLayer::World,
				.SortingOrder = 0
			}
		);

		const auto darkFloorTile01Entity = m_world.CreateEntity();
		Cocoa::Scenes::TransformComponent darkFloorTile01Transform
		{
			.Position = { -0.05f, -0.72f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.2f, 0.4f, 1.0f }
		};

		m_world.AddComponent(darkFloorTile01Entity, darkFloorTile01Transform);
		m_world.AddComponent(
			darkFloorTile01Entity,
			Cocoa::Scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("dark_floor_tile_01_sprite"),
				.TilingFactor = Cocoa::Math::Vector2f(4.0f, 1.0f),
				.SortingLayer = Cocoa::Graphics::SortLayer::World,
				.SortingOrder = 1
			}
		);

		const auto cherryBlossomTree01Entity = m_world.CreateEntity();
		Cocoa::Scenes::TransformComponent cherryBlossomTree01Transform
		{
			.Position = { -1.20f, -0.35f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 0.75f, 0.75f, 1.0f }
		};
		m_world.AddComponent(cherryBlossomTree01Entity, cherryBlossomTree01Transform);
		m_world.AddComponent(
			cherryBlossomTree01Entity,
			Cocoa::Scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("cherry_blossom_tree_01_sprite"),
				.SortingLayer = Cocoa::Graphics::SortLayer::World,
				.SortingOrder = 0
			}
		);

		const auto solidColorQuadEntity = m_world.CreateEntity();
		m_world.AddComponent(
			solidColorQuadEntity,
			Cocoa::Scenes::TransformComponent
			{
				.Position = { -1.5f, 0.8f, 0.0f },
				.Rotation =  { 0.0f, 0.0f, 0.0f },
				.Scale = { 0.2f, 0.2f, 1.0f }
			}
		);
		m_world.AddComponent(
			solidColorQuadEntity,
			Cocoa::Scenes::ColorQuadComponent
			{
				.Material = defaultMaterial,
				.Color = {.R = 0.0f, .G = 1.0f, .B = 1.0f, .A = 1.0f},
				.SortingLayer = Cocoa::Graphics::SortLayer::Foreground,
				.SortingOrder = 0
			}
		);

		m_world.AddSystem<Cocoa::Scenes::Render2DSystem>();
    }

	void TestScene::Unload(Cocoa::Assets::ResourceLoader& loader)
	{

	}
}
