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

	void TestScene::load(cocoa::assets::ResourceLoader& loader)
    {
        auto cameraEntity = m_world.createEntity();
        m_world.addComponent(cameraEntity, cocoa::scenes::CameraComponent{ true });
		m_world.addComponent(cameraEntity, cocoa::scenes::ProjectionComponent{});
		m_world.addComponent(cameraEntity, cocoa::scenes::TransformComponent{});
        m_world.addSystem<cocoa::scenes::CameraSystem>();

		const auto defaultMaterial = loader.loadMaterial("default_material");

		const auto sunEntity = m_world.createEntity();
		cocoa::scenes::TransformComponent sunsetTransform
		{
			.position = { 0.0f, 0.0f, 0.0f },
			.rotation =  { 0.0f, 0.0f, 0.0f },
			.scale = { 3.56f, 2.0f, 1.0f }
		};

		auto mountainBackgroundEntity = m_world.createEntity();
		cocoa::scenes::TransformComponent mountainBackgroundTransform
		{
			.position = { 0.0f, -0.05f, 0.0f },
			.rotation =  { 0.0f, 0.0f, 0.0f },
			.scale = { 3.56f, 2.0f, 1.0f }
		};

		auto forestFogBackground01Entity = m_world.createEntity();
		cocoa::scenes::TransformComponent forestFogBackground01Transform
		{
			.position = { 0.0f, -0.15f, 0.0f },
			.rotation =  { 0.0f, 0.0f, 0.0f },
			.scale = { 3.56f, 2.0f, 1.0f }
		};

		auto forestFogBackground02Entity = m_world.createEntity();
		cocoa::scenes::TransformComponent forestFogBackground02Transform
		{
			.position = { 0.0f, -0.25f, 0.0f },
			.rotation =  { 0.0f, 0.0f, 0.0f },
			.scale = { 3.56f, 2.0f, 1.0f }
		};

		auto cherryBlossomTree02Entity = m_world.createEntity();
		cocoa::scenes::TransformComponent cherryBlossomTree02Transform
		{
			.position = { 1.20f, -0.35f, 0.0f },
			.rotation =  { 0.0f, 0.0f, 0.0f },
			.scale = { 0.75f, 0.75f, 1.0f }
		};

		m_world.addComponent(sunEntity, sunsetTransform);
		m_world.addComponent(
			sunEntity,
			cocoa::scenes::SpriteComponent
			{
				.materialHandle = defaultMaterial,
				.spriteHandle = loader.loadSprite("sunset_background_01_sprite"),
				.sortingLayer = cocoa::graphics::SortLayer::Background,
				.sortingOrder = 0
			}
		);

		m_world.addComponent(mountainBackgroundEntity, mountainBackgroundTransform);
		m_world.addComponent(
			mountainBackgroundEntity,
			cocoa::scenes::SpriteComponent
			{
				.materialHandle = defaultMaterial,
				.spriteHandle = loader.loadSprite("mountains_background_01_sprite"),
				.sortingLayer = cocoa::graphics::SortLayer::Background,
				.sortingOrder = 1
			}
		);

		m_world.addComponent(forestFogBackground01Entity, forestFogBackground01Transform);
		m_world.addComponent(
			forestFogBackground01Entity,
			cocoa::scenes::SpriteComponent
			{
				.materialHandle = defaultMaterial,
				.spriteHandle = loader.loadSprite("forest_fog_background_01_sprite"),
				.sortingLayer = cocoa::graphics::SortLayer::Background,
				.sortingOrder = 2
			}
		);

		m_world.addComponent(forestFogBackground02Entity, forestFogBackground02Transform);
		m_world.addComponent(
			forestFogBackground02Entity,
			cocoa::scenes::SpriteComponent
			{
				.materialHandle = defaultMaterial,
				.spriteHandle = loader.loadSprite("forest_fog_background_02_sprite"),
				.sortingLayer = cocoa::graphics::SortLayer::Background,
				.sortingOrder = 3
			}
		);

		m_world.addComponent(cherryBlossomTree02Entity, cherryBlossomTree02Transform);
		m_world.addComponent(
			cherryBlossomTree02Entity,
			cocoa::scenes::SpriteComponent
			{
				.materialHandle = defaultMaterial,
				.spriteHandle = loader.loadSprite("cherry_blossom_tree_02_sprite"),
				.flipVertical = false,
				.flipHorizontal = true,
				.sortingLayer = cocoa::graphics::SortLayer::World,
				.sortingOrder = 0
			}
		);

		auto darkFloorTile01Entity = m_world.createEntity();
		cocoa::scenes::TransformComponent darkFloorTile01Transform
		{
			.position = { -0.05f, -0.72f, 0.0f },
			.rotation =  { 0.0f, 0.0f, 0.0f },
			.scale = { 3.2f, 0.4f, 1.0f }
		};

		m_world.addComponent(darkFloorTile01Entity, darkFloorTile01Transform);
		m_world.addComponent(
			darkFloorTile01Entity,
			cocoa::scenes::SpriteComponent
			{
				.materialHandle = defaultMaterial,
				.spriteHandle = loader.loadSprite("dark_floor_tile_01_sprite"),
				.tilingFactor = cocoa::math::Vector2f(4.0f, 1.0f),
				.sortingLayer = cocoa::graphics::SortLayer::World,
				.sortingOrder = 1
			}
		);

		auto cherryBlossomTree01Entity = m_world.createEntity();
		cocoa::scenes::TransformComponent cherryBlossomTree01Transform
		{
			.position = { -1.20f, -0.35f, 0.0f },
			.rotation =  { 0.0f, 0.0f, 0.0f },
			.scale = { 0.75f, 0.75f, 1.0f }
		};
		m_world.addComponent(cherryBlossomTree01Entity, cherryBlossomTree01Transform);
		m_world.addComponent(
			cherryBlossomTree01Entity,
			cocoa::scenes::SpriteComponent
			{
				.materialHandle = defaultMaterial,
				.spriteHandle = loader.loadSprite("cherry_blossom_tree_01_sprite"),
				.sortingLayer = cocoa::graphics::SortLayer::World,
				.sortingOrder = 0
			}
		);

		m_world.addSystem<cocoa::scenes::Render2DSystem>();
    }

	void TestScene::unload(cocoa::assets::ResourceLoader& loader)
	{

	}
}
