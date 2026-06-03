#include "Graphics/OpenGL/OpenGLGraphicsDevice.hpp"
#include "Graphics/OpenGL/OpenGLShader.hpp"
#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"
#include "Graphics/OpenGL/OpenGLVertexArray.hpp"
#include "Graphics/OpenGL/OpenGLIndexBuffer.hpp"
#include "Graphics/OpenGL/OpenGLTexture2D.hpp"
#include "Graphics/TextureSpec.hpp"
#include "Graphics/BufferElement.hpp"
#include "Graphics/BufferLayout.hpp"
//Temp include for now
#include "Assets/AssetManager.hpp"

#include <GL/glew.h>
#include <iostream>

namespace Cocoa::Graphics
{
	OpenGLGraphicsDevice::OpenGLGraphicsDevice()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	OpenGLGraphicsDevice::~OpenGLGraphicsDevice()
	{
		delete m_texture;
		m_texture = nullptr;

		delete m_vao;
		m_vao = nullptr;

		delete m_ibo;
		m_ibo = nullptr;

		delete m_vbo;
		m_vbo = nullptr;

		delete m_shader;
		m_shader = nullptr;
	}

	void OpenGLGraphicsDevice::BeginFrame()
	{
		// ToDo: Reserved for per-frame graphics device setup
	}

	void OpenGLGraphicsDevice::EndFrame()
	{
		// ToDo: Reserved for per-frame graphics device cleanup/submission
	}

	void OpenGLGraphicsDevice::SetViewport(uint32_t width, uint32_t height)
	{
		glViewport(
			0,
			0,
			static_cast<GLsizei>(width),
			static_cast<GLsizei>(height)
		);
	}

	void OpenGLGraphicsDevice::SetClearColor(float red, float green, float blue, float alpha)
	{
		glClearColor(
			red,
			green,
			blue,
			alpha
		);
	}

	void OpenGLGraphicsDevice::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLGraphicsDevice::InitTemp(Cocoa::Assets::AssetManager assetManager)
	{
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

		m_shader = new OpenGLShader(vertexShaderSource, fragmentShaderSource);

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

		m_vao = new OpenGLVertexArray();
		m_vbo = new OpenGLVertexBuffer(vertices, sizeof(vertices), layout);
		m_ibo = new OpenGLIndexBuffer(indices, static_cast<uint32_t>(std::size(indices)));
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

		auto image = assetManager.LoadImage("Fighter.png");

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

		m_texture = new OpenGLTexture2D(imageTextureSpec, image.Pixels.data());
	}

	void OpenGLGraphicsDevice::RenderTemp()
	{
		m_shader->Bind();
		m_texture->Bind(0);
		m_shader->SetInt("u_Texture", 0);
		m_vao->Bind();

		glDrawElements(
			GL_TRIANGLES,
			m_ibo->GetCount(),
			GL_UNSIGNED_INT,
			nullptr
		);

		m_vao->Unbind();
		m_shader->Unbind();
	}
}