#pragma once

#include "Scenes/Scene.hpp"

namespace Sandbox
{
	class TestScene : public Cocoa::Scenes::Scene
	{
	public:
		explicit TestScene(const Cocoa::Graphics::Viewport& viewport);
		~TestScene() override;
		void Load(Cocoa::Assets::ResourceLoader& loader) override;
		void Unload(Cocoa::Assets::ResourceLoader& loader) override;
	};
}