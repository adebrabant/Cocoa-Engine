#include "Scenes/Systems/RenderSystem.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Scenes/ECS/World.hpp"
#include "Scenes/ECS/View.hpp"
#include "Scenes/Components/Renderable2DComponent.hpp"
#include "Scenes/Components/TransformComponent.hpp"
#include "Math/Matrix4f.hpp"

namespace Cocoa::Scenes
{
	void RenderSystem::Update(World& world, float deltaTime)
	{

	}

	void RenderSystem::Render(World& world, Graphics::Renderer2D& renderer, float alpha)
	{
		View<TransformComponent, Renderable2DComponent> view(world);
		for (auto [transform, renderable] : view)
		{
			Math::Matrix4f translation = Math::Matrix4f::Translation(transform.Position);
			Math::Matrix4f zRotation = Math::Matrix4f::RotationZ(transform.Rotation.Z);
			Math::Matrix4f scale = Math::Matrix4f::Scale(transform.Scale);

			Math::Matrix4f modelMatrix = translation * zRotation * scale;
			renderer.DrawQuad(modelMatrix, renderable.Material);
		}
	}
}
