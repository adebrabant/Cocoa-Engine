#pragma once

#include <scenes/Scene.hpp>

namespace sandbox
{
	class TestScene : public cocoa::scenes::Scene
	{
	public:
		TestScene() = default;
		~TestScene() override;
		void load(cocoa::assets::ResourceLoader& loader) override;
		void unload(cocoa::assets::ResourceLoader& loader) override;
	};
}
