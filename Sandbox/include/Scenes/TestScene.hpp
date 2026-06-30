#pragma once

#include "Scenes/Scene.hpp"

namespace Sandbox
{
	class TestScene : public Cocoa::Scenes::Scene
	{
	public:
		TestScene() = default;
		~TestScene() = default;
		void Load(Cocoa::Assets::ResourceLoader& loader) override;
		void Unload(Cocoa::Assets::ResourceLoader& loader) override;
	};
}