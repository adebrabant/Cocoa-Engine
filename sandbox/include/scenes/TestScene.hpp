#pragma once

#include <scenes/Scene.hpp>

namespace sandbox
{
	class TestScene : public cocoa::scenes::Scene
	{
	public:
		TestScene() = default;
		~TestScene() override;
		void Load(cocoa::assets::ResourceLoader& loader) override;
		void Unload(cocoa::assets::ResourceLoader& loader) override;
	};
}
