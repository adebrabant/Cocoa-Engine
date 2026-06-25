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

namespace Cocoa::Graphics
{
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
		float vertices[] =
		{
			// position      // tex coord
			-0.5f, -0.5f,    0.0f, 0.0f,
			 0.5f, -0.5f,    1.0f, 0.0f,
			 0.5f,  0.5f,    1.0f, 1.0f,
			-0.5f,  0.5f,    0.0f, 1.0f
		};

		uint32_t indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		BufferLayout layout =
		{
			{ 0, ShaderDataType::Float2, "a_Position" },
			{ 1, ShaderDataType::Float2, "a_TexCoord" },
		};

		m_vao = m_graphicsDevice.CreateVertexArray();
		m_vbo = m_graphicsDevice.CreateVertexBuffer(vertices, sizeof(vertices), layout);
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
			const Shader& shader = m_shaderManager.Get(material.ShaderHandle);
			const Texture2D& texture = m_textureManager.Get(material.TextureHandle);

			shader.Bind();
			texture.Bind(0);
			shader.SetInt("u_Texture", 0);
			m_graphicsDevice.DrawIndexed(*m_vao, m_ibo->GetCount());
			shader.Unbind();
		}

		m_drawCommands.clear();
	}
}