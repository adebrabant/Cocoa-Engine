#pragma once

#include "scenes/Scene.hpp"

namespace Sandbox
{
	class TestScene : public cocoa::Scenes::Scene
	{
	public:
		TestScene() = default;
		~TestScene() override;
		void Load(cocoa::Assets::ResourceLoader& loader) override;
		void Unload(cocoa::Assets::ResourceLoader& loader) override;
	};
}