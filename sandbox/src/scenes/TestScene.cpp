#include "scenes/TestScene.hpp"
#include <assets/ResourceLoader.hpp>
#include <scenes/components/CameraComponent.hpp>
#include <scenes/components/SpriteComponent.hpp>
#include <scenes/components/TransformComponent.hpp>
#include <scenes/systems/CameraSystem.hpp>
#include <scenes/systems/Render2DSystem.hpp>
#include <scenes/components/ProjectionComponent.hpp>

namespace sandbox
{
	TestScene::~TestScene() = default;

	void TestScene::Load(cocoa::assets::ResourceLoader& loader)
    {
        auto cameraEntity = m_world.CreateEntity();
        m_world.AddComponent(cameraEntity, cocoa::scenes::CameraComponent{ true });
		m_world.AddComponent(cameraEntity, cocoa::scenes::ProjectionComponent{});
		m_world.AddComponent(cameraEntity, cocoa::scenes::TransformComponent{});
        m_world.AddSystem<cocoa::scenes::CameraSystem>();

		const auto defaultMaterial = loader.LoadMaterial("default_material");

		const auto sunEntity = m_world.CreateEntity();
		cocoa::scenes::TransformComponent sunsetTransform
		{
			.Position = { 0.0f, 0.0f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto mountainBackgroundEntity = m_world.CreateEntity();
		cocoa::scenes::TransformComponent mountainBackgroundTransform
		{
			.Position = { 0.0f, -0.05f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto forestFogBackground01Entity = m_world.CreateEntity();
		cocoa::scenes::TransformComponent forestFogBackground01Transform
		{
			.Position = { 0.0f, -0.15f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto forestFogBackground02Entity = m_world.CreateEntity();
		cocoa::scenes::TransformComponent forestFogBackground02Transform
		{
			.Position = { 0.0f, -0.25f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.56f, 2.0f, 1.0f }
		};

		auto cherryBlossomTree02Entity = m_world.CreateEntity();
		cocoa::scenes::TransformComponent cherryBlossomTree02Transform
		{
			.Position = { 1.20f, -0.35f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 0.75f, 0.75f, 1.0f }
		};

		m_world.AddComponent(sunEntity, sunsetTransform);
		m_world.AddComponent(
			sunEntity,
			cocoa::scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("sunset_background_01_sprite"),
				.SortingLayer = cocoa::graphics::SortLayer::Background,
				.SortingOrder = 0
			}
		);

		m_world.AddComponent(mountainBackgroundEntity, mountainBackgroundTransform);
		m_world.AddComponent(
			mountainBackgroundEntity,
			cocoa::scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("mountains_background_01_sprite"),
				.SortingLayer = cocoa::graphics::SortLayer::Background,
				.SortingOrder = 1
			}
		);

		m_world.AddComponent(forestFogBackground01Entity, forestFogBackground01Transform);
		m_world.AddComponent(
			forestFogBackground01Entity,
			cocoa::scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("forest_fog_background_01_sprite"),
				.SortingLayer = cocoa::graphics::SortLayer::Background,
				.SortingOrder = 2
			}
		);

		m_world.AddComponent(forestFogBackground02Entity, forestFogBackground02Transform);
		m_world.AddComponent(
			forestFogBackground02Entity,
			cocoa::scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("forest_fog_background_02_sprite"),
				.SortingLayer = cocoa::graphics::SortLayer::Background,
				.SortingOrder = 3
			}
		);

		m_world.AddComponent(cherryBlossomTree02Entity, cherryBlossomTree02Transform);
		m_world.AddComponent(
			cherryBlossomTree02Entity,
			cocoa::scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("cherry_blossom_tree_02_sprite"),
				.FlipVertical = false,
				.FlipHorizontal = true,
				.SortingLayer = cocoa::graphics::SortLayer::World,
				.SortingOrder = 0
			}
		);

		auto darkFloorTile01Entity = m_world.CreateEntity();
		cocoa::scenes::TransformComponent darkFloorTile01Transform
		{
			.Position = { -0.05f, -0.72f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 3.2f, 0.4f, 1.0f }
		};

		m_world.AddComponent(darkFloorTile01Entity, darkFloorTile01Transform);
		m_world.AddComponent(
			darkFloorTile01Entity,
			cocoa::scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("dark_floor_tile_01_sprite"),
				.TilingFactor = cocoa::math::Vector2f(4.0f, 1.0f),
				.SortingLayer = cocoa::graphics::SortLayer::World,
				.SortingOrder = 1
			}
		);

		auto cherryBlossomTree01Entity = m_world.CreateEntity();
		cocoa::scenes::TransformComponent cherryBlossomTree01Transform
		{
			.Position = { -1.20f, -0.35f, 0.0f },
			.Rotation =  { 0.0f, 0.0f, 0.0f },
			.Scale = { 0.75f, 0.75f, 1.0f }
		};
		m_world.AddComponent(cherryBlossomTree01Entity, cherryBlossomTree01Transform);
		m_world.AddComponent(
			cherryBlossomTree01Entity,
			cocoa::scenes::SpriteComponent
			{
				.Material = defaultMaterial,
				.Sprite = loader.LoadSprite("cherry_blossom_tree_01_sprite"),
				.SortingLayer = cocoa::graphics::SortLayer::World,
				.SortingOrder = 0
			}
		);

		m_world.AddSystem<cocoa::scenes::Render2DSystem>();
    }

	void TestScene::Unload(cocoa::assets::ResourceLoader& loader)
	{

	}
}
