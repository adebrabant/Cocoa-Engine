#include "Graphics/Renderer2D.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/BufferLayout.hpp"
#include "Graphics/TextureSpec.hpp"
#include "Graphics/TextureManager.hpp"

// ToDo: Remove after DrawQuad is added
#include "Assets/AssetManager.hpp" 
#include "Assets/AssetDatabase.hpp"
#include "Assets/Image.hpp"

namespace Cocoa::Graphics
{
	Renderer2D::Renderer2D(GraphicsDevice& graphicsDevice, TextureManager& textureManager, Assets::AssetManager& assetManager, Assets::AssetDatabase& database) :
		m_graphicsDevice(graphicsDevice),
		m_textureManager(textureManager),
		m_tempAssetManager(assetManager),
		m_tempAssetDatabase(database)
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

		const auto& shaderRecord = m_tempAssetDatabase.GetShaderInfo("sprite_default_shader");
		const auto& materialRecord = m_tempAssetDatabase.GetMaterialInfo("werewolf_material");

		const auto& werewolfTextureRecord = m_tempAssetDatabase.GetTextureInfo("werewolf-idle1");
		const auto& werewolfImage = m_tempAssetManager.LoadImage(werewolfTextureRecord.Path);

		const TextureSpec werewolfTextureSpec
		{
			.Id = werewolfTextureRecord.Id,
			.Width = static_cast<uint32_t>(werewolfImage.Width),
			.Height = static_cast<uint32_t>(werewolfImage.Height),
			.Format = Graphics::TextureSpec::ParseFormat(werewolfTextureRecord.Format, werewolfImage.Channels),
			.MinFilter = Graphics::TextureSpec::ParseFilter(werewolfTextureRecord.MinFilter),
			.MagFilter = Graphics::TextureSpec::ParseFilter(werewolfTextureRecord.MagFilter),
			.WrapS = Graphics::TextureSpec::ParseWrap(werewolfTextureRecord.WrapS),
			.WrapT = Graphics::TextureSpec::ParseWrap(werewolfTextureRecord.WrapT),
			.GenerateMipmaps = werewolfTextureRecord.GenerateMipmaps
		};

		auto handle = m_textureManager.Load(werewolfTextureSpec, werewolfImage.Pixels.data());
		m_texture = &m_textureManager.Get(handle);
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