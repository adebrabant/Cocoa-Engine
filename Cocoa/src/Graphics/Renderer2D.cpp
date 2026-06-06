#include "Graphics/Renderer2D.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/TextureSpec.hpp"

// ToDo: Needs to be removed once real workflow is in place
#include "Assets/AssetManager.hpp" 

namespace Cocoa::Graphics
{
	Renderer2D::Renderer2D(GraphicsDevice& graphicsDevice, Assets::AssetManager& assetManager) :
		m_graphicsDevice(graphicsDevice),
		m_tempAssetManager(assetManager)
	{
		// ToDo: Refactor all this temp into a real workflow
		const char* vertexShaderSource = R"(
			#version 330 core

			layout(location = 0) in vec2 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			out vec2 TexCoord;
			
			void main()
			{
				gl_Position = vec4(a_Position, 0.0, 1.0);
				TexCoord = a_TexCoord;
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core
			
			out vec4 FragColor;

			in vec2 TexCoord;

			uniform sampler2D u_Texture;
			
			void main()
			{
				FragColor = texture(u_Texture, TexCoord);
			}
		)";

		m_shader = m_graphicsDevice.CreateShader(vertexShaderSource, fragmentShaderSource);

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

		TextureSpec textureSpec
		{
			.Width = 2,
			.Height = 2,
			.Format = TextureFormat::RGBA8,
			.MinFilter = TextureFilter::Nearest,
			.MagFilter = TextureFilter::Nearest,
			.WrapS = TextureWrap::ClampToEdge,
			.WrapT = TextureWrap::ClampToEdge,
			.GenerateMipmaps = true
		};

		unsigned char pixels[] =
		{
			// top row
			255, 255, 255, 255,   // white
			0,   0,   0,   255,   // black

			// bottom row
			0,   0,   0,   255,   // black
			255, 255, 255, 255    // white
		};

		auto image = m_tempAssetManager.LoadImage("Fighter.png");

		TextureSpec imageTextureSpec
		{
			.Width = static_cast<uint32_t>(image.Width),
			.Height = static_cast<uint32_t>(image.Height),
			.Format = TextureFormat::RGBA8,
			.MinFilter = TextureFilter::Nearest,
			.MagFilter = TextureFilter::Nearest,
			.WrapS = TextureWrap::ClampToEdge,
			.WrapT = TextureWrap::ClampToEdge,
			.GenerateMipmaps = true
		};

		m_texture = m_graphicsDevice.CreateTexture2D(imageTextureSpec, image.Pixels.data());
	}

	Renderer2D::~Renderer2D() = default;

	void Renderer2D::BeginScene()
	{
		//ToDo: Store camera/view-projection data
		//ToDo: Reset batch/queue state
	}

	void Renderer2D::EndScene()
	{
		// ToDo: Flush queued 2D draw commands
		Flush();
	}

	void Renderer2D::Flush()
	{
		m_shader->Bind();
		m_texture->Bind(0);
		m_shader->SetInt("u_Texture", 0);
		m_graphicsDevice.DrawIndexed(*m_vao, m_ibo->GetCount());
		m_shader->Unbind();
	}
}