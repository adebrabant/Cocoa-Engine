#include "Scenes/Systems/Render2DSystem.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/View.hpp"
#include "Scenes/Components/SpriteComponent.hpp"
#include "Scenes/Components/TransformComponent.hpp"
#include "Math/Matrix4f.hpp"

namespace Cocoa::Scenes
{
	void Render2DSystem::Update(World& world, float deltaTime)
	{

	}

	void Render2DSystem::Render(World& world, Graphics::Renderer2D& renderer, float alpha)
	{
		View<TransformComponent, SpriteComponent> view(world);
		for (auto [transform, spriteComponent] : view)
		{
			Math::Matrix4f translation = Math::Matrix4f::Translation(transform.Position);
			Math::Matrix4f zRotation = Math::Matrix4f::RotationZ(transform.Rotation.Z);
			Math::Matrix4f scale = Math::Matrix4f::Scale(transform.Scale);

			Math::Matrix4f modelMatrix = translation * zRotation * scale;
			renderer.DrawQuad(
				modelMatrix,
				spriteComponent.Material,
				spriteComponent.Sprite,
				spriteComponent.TilingFactor,
				spriteComponent.FlipVertical,
				spriteComponent.FlipHorizontal,
				spriteComponent.SortingLayer,
				spriteComponent.SortingOrder
			);
		}
	}
}
