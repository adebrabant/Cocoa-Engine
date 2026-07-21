#include "Graphics/Renderer2D.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/ShaderManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Math/Vector2f.hpp"
#include "Math/Vector3f.hpp"
#include "Math/Vector4f.hpp"
#include "Core/Color.hpp"

#include <array>

namespace Cocoa::Graphics
{
	struct QuadVertex
	{
		Math::Vector3f Position;
		Math::Vector2f TexCoord;
		Math::Vector4f Color;

		// ToDo : Need to look into this
		//float TextureIndex;
		//float TilingFactor;
	};

	Renderer2D::Renderer2D(
		GraphicsDevice& graphicsDevice,
		ShaderManager& shaderManager,
		TextureManager& textureManager,
		MaterialManager& materialManager
	) :
		m_graphicsDevice(graphicsDevice),
		m_shaderManager(shaderManager),
		m_textureManager(textureManager),
		m_materialManager(materialManager)
	{
		constexpr std::array<QuadVertex, 4> vertices =
		{
			// Bottom-left
			QuadVertex{ {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f }},
			// Bottom-right
			QuadVertex{ { 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
			// Top-right
			QuadVertex{ { 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },
			// Top-left
			QuadVertex{ {-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f},{ 1.0f, 1.0f, 1.0f, 1.0f } }
		};

		constexpr uint32_t indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		const BufferLayout layout =
		{
			{ 0, ShaderDataType::Float3, "a_Position" },
			{ 1, ShaderDataType::Float2, "a_TexCoord" },
			{ 2, ShaderDataType::Float4, "a_Color" },
		};

		m_vao = m_graphicsDevice.CreateVertexArray();
		m_vbo = m_graphicsDevice.CreateVertexBuffer(vertices.data(), sizeof(vertices), layout);
		m_ibo = m_graphicsDevice.CreateIndexBuffer(indices, static_cast<uint32_t>(std::size(indices)));
		m_vao->AddVertexBuffer(*m_vbo);
		m_vao->SetIndexBuffer(*m_ibo);
	}

	Renderer2D::~Renderer2D() = default;

	void Renderer2D::BeginScene()
	{
		//ToDo: Store camera/view-projection data
		m_drawCommands.clear();
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	void Renderer2D::DrawQuad(MaterialHandle materialHandle)
	{
		m_drawCommands.emplace_back(DrawCommand2D{ materialHandle });
	}

	void Renderer2D::Flush()
	{
		for (const auto& command : m_drawCommands)
		{
			const Material& material = m_materialManager.Get(command.Material);
			const Shader& shader = m_shaderManager.Get(material.ShaderId);
			const Texture2D& texture = m_textureManager.Get(material.TextureId);

			shader.Bind();
			texture.Bind(0);
			shader.SetInt("u_Texture", 0);
			shader.SetVector4(
				"u_Tint",
				{
					material.Tint.R,
					material.Tint.G,
					material.Tint.B,
					material.Tint.A
				}
			);
			m_graphicsDevice.DrawIndexed(*m_vao, m_ibo->GetCount());
			shader.Unbind();
		}

		m_drawCommands.clear();
	}
}