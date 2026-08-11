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
#include "Core/Color.hpp"

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
		constexpr uint32_t maxQuads = 20000;
		constexpr uint32_t maxVertices = maxQuads * 4;
		constexpr uint32_t maxIndices = maxQuads * 6;
		const auto quadIndices = new uint32_t[maxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < maxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		const BufferLayout layout =
		{
			{ 0, ShaderDataType::Float3, "a_Position" },
			{ 1, ShaderDataType::Float2, "a_TexCoord" },
			{ 2, ShaderDataType::Float4, "a_Color" },
		};

		m_vao = m_graphicsDevice.CreateVertexArray();
		m_vbo = m_graphicsDevice.CreateVertexBuffer(maxVertices * sizeof(QuadVertex), layout);
		m_ibo = m_graphicsDevice.CreateIndexBuffer(quadIndices, static_cast<uint32_t>(maxIndices));
		m_vao->AddVertexBuffer(*m_vbo);
		m_vao->SetIndexBuffer(*m_ibo);
		delete[] quadIndices;
	}

	Renderer2D::~Renderer2D() = default;

	void Renderer2D::BeginDraw(const Math::Matrix4f& viewProjectionMatrix)
	{
		m_viewProjectionMatrix = viewProjectionMatrix;
		m_quadDrawCommands.clear();
	}

	void Renderer2D::DrawQuad(const Math::Matrix4f& modelMatrix, const MaterialHandle materialHandle)
	{
		// Transform the quad's local-space corners into world space.
		const Math::Vector4f worldBottomLeft =
			modelMatrix * Math::Vector4f{-0.5f, -0.5f, 0.0f, 1.0f };

		const Math::Vector4f worldBottomRight =
			modelMatrix * Math::Vector4f{ 0.5f, -0.5f, 0.0f, 1.0f };

		const Math::Vector4f worldTopRight =
			modelMatrix * Math::Vector4f{ 0.5f, 0.5f, 0.0f, 1.0f };

		const Math::Vector4f worldTopLeft =
			modelMatrix * Math::Vector4f{ -0.5f, 0.5f, 0.0f, 1.0f };

		constexpr Math::Vector4f defaultWhiteColor{ 1.0f, 1.0f, 1.0f, 1.0f };

		const std::array<QuadVertex, 4> vertices =
		{
			// Bottom-left
			QuadVertex{ {worldBottomLeft.X, worldBottomLeft.Y, worldBottomLeft.Z}, {0.0f, 0.0f }, defaultWhiteColor},
			// Bottom-right
			QuadVertex{ {worldBottomRight.X, worldBottomRight.Y, worldBottomRight.Z}, {1.0f, 0.0f }, defaultWhiteColor},
			// Top-right
			QuadVertex{ {worldTopRight.X,  worldTopRight.Y, worldTopRight.Z}, {1.0f, 1.0f }, defaultWhiteColor},
			// Top-left
			QuadVertex{ {worldTopLeft.X, worldTopLeft.Y, worldTopLeft.Z}, {0.0f, 1.0f}, defaultWhiteColor}
		};

		m_quadDrawCommands.emplace_back(QuadDrawCommand{ .Material = materialHandle, .Vertices = vertices});
	}

	void Renderer2D::EndDraw()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{
		if (m_quadDrawCommands.empty())
			return;

		std::vector<QuadVertex> batchVertices;
		MaterialHandle currentMaterial = m_quadDrawCommands[0].Material;
		for (const QuadDrawCommand& command : m_quadDrawCommands)
		{
			if (command.Material.Id != currentMaterial.Id)
			{
				FlushQuadVertices(currentMaterial, batchVertices);
				batchVertices.clear();
				currentMaterial = command.Material;
			}

			batchVertices.insert(batchVertices.end(),
			                     command.Vertices.begin(),
			                     command.Vertices.end()
			);
		}

		if (!batchVertices.empty())
		{
			FlushQuadVertices(currentMaterial, batchVertices);
			batchVertices.clear();
		}

		m_quadDrawCommands.clear();
	}

	void Renderer2D::FlushQuadVertices(const MaterialHandle& handle, const std::vector<QuadVertex>& batchVertices) const
	{
		const Material& material = m_materialManager.Get(handle);
		const Shader& shader = m_shaderManager.Get(material.ShaderId);
		const Texture2D& texture = m_textureManager.Get(material.TextureId);
		m_vbo->SetData(
			batchVertices.data(),
			static_cast<uint32_t>(batchVertices.size() * sizeof(QuadVertex))
		);

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
		shader.SetMatrix4("u_ViewProjection", m_viewProjectionMatrix);
		const auto quadCount = static_cast<uint32_t>(batchVertices.size() / 4);
		const uint32_t indexCount = quadCount * 6;
		m_graphicsDevice.DrawIndexed(*m_vao, indexCount);
		shader.Unbind();
	}
}
