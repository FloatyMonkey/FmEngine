// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "ThirdParty/Glad/glad.h"

#include "Platform/Window.h"

#include "Graphics/GL/Shader.h"
#include "Graphics/GL/UniformBuffer.h"

#include "Loaders/Image.h"

#include "Loaders/Model.h"

#include "Graphics/RHI/Texture.h"
#include "Graphics/RHI/OpenGL/Device.h"

#include "Graphics/RHI/Pipeline.h"
#include "Graphics/RHI/OpenGL/Format.h"

#include <iostream>

using namespace FM;

Win32Window window;

void Setup();
void Render();
void Exit();

struct IO
{
	Vector2I mousePos;
	Vector2I mouseDelta;
	bool mouseDown[3] = { false, false, false };
	int mouseWheel = 0;

	Vector2I prevMousePos;
	int sumMouseWheel = 0;
};

IO io;

enum class EAxis
{
	X = 1,
	Y = 2,
	Z = 3,

	nX = -1,
	nY = -2,
	nZ = -3
};

Matrix3 AxisConversion(EAxis srcF, EAxis srcU, EAxis dstF = EAxis::Z, EAxis dstU = EAxis::Y)
{
	if (srcF == dstF && srcU == dstU)
	{
		return Matrix3::Identity;
	}

	int srcF0 = Math::Abs((int)srcF) - 1;
	int dstF0 = Math::Abs((int)dstF) - 1;
	int srcU0 = Math::Abs((int)srcU) - 1;
	int dstU0 = Math::Abs((int)dstU) - 1;

	if (srcF0 == srcU0 || dstF0 == dstU0)
	{
		return Matrix3::Identity;
	}

	Matrix3 r;

	r(dstF0, srcF0) = Math::Sign((int)srcF * (int)dstF);
	r(dstU0, srcU0) = Math::Sign((int)srcU * (int)dstU);

	r.SetColumn(3 - srcF0 - srcU0, Vector3::Cross(r.GetColumn(srcF0), r.GetColumn(srcU0)));

	return r;
}

struct BufferVertex
{
	Matrix4 model;
	Matrix4 view;
	Matrix4 projection;
};

BufferVertex bufferVertex;

struct BufferPixel
{
	alignas(sizeof(float)*4) Vector3 viewPos;
	alignas(sizeof(float)*4) Vector3 lightPos;
};

BufferPixel bufferPixel;

int main()
{
	// Window

	WindowDesc desc;
	desc.id = "OL-engine";
	desc.title = "OL-engine";
	desc.width = 1280;
	desc.height = 720;

	window.Init(desc);

	HDC hDc = GetDC((HWND)window.GetWindowHandle());
	HGLRC hRc = wglCreateContext(hDc);
	wglMakeCurrent(hDc, hRc);

	if (!gladLoadGL())
	{
		printf("Something went wrong!\n");
		exit(-1);
	}

	Setup();

	window.SetMouseCallback([](int x, int y, int wheelDelta, bool leftDown, bool middleDown, bool rightDown, void* user) {
		IO* myIO = static_cast<IO*>(user);

		myIO->mouseDown[0] = leftDown;
		myIO->mouseDown[1] = rightDown;
		myIO->mouseDown[2] = middleDown;

		myIO->mousePos = Vector2I(x, y);
		myIO->sumMouseWheel += wheelDelta;
	}, &io);

	while (window.Update())
	{
		io.mouseDelta = io.mousePos - io.prevMousePos;
		io.prevMousePos = io.mousePos;

		io.mouseWheel = io.sumMouseWheel;
		io.sumMouseWheel = 0;

		Render();

		SwapBuffers(hDc);
	}

	Exit();

	wglMakeCurrent(NULL, NULL);
	ReleaseDC((HWND)window.GetWindowHandle(), hDc);
	wglDeleteContext(hRc);
}

OpenGL::Device device;

Shader shader;
UniformBuffer uboVertex, uboPixel;

unsigned int VBO, VAO, EBO;
HTexture baseColorMap, roughnessMap, metallicMap, normalMap;

std::vector<Vertex> vertices;
std::vector<unsigned long> indices;

unsigned int SetupVertexAttributes(std::vector<InputElementDesc> inputs)
{
	GLuint vertexArray;
	
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	int i = 0;
	int offset = 0;
	
	for (InputElementDesc& desc : inputs)
	{
		FormatInfo info = GetFormatInfo(desc.format);
		OpenGL::GLFormatInfo glInfo = OpenGL::Map(desc.format);

		if (glInfo.type == GL_HALF_FLOAT || glInfo.type == GL_FLOAT)
		{
			glVertexAttribFormat(i, info.components, glInfo.type, false, offset);
		}
		else
		{
			glVertexAttribIFormat(i, info.components, glInfo.type, offset);
		}

		glVertexAttribBinding(i, desc.slot);
		glEnableVertexAttribArray(i);

		offset += info.size;
		i++;
	}

	glBindVertexArray(0);

	return vertexArray;
}

void Setup()
{
	printf("FmEngine - v0.1\n");
	printf("OpenGL Version %s\n", glGetString(GL_VERSION));
	
	glEnable(GL_DEPTH_TEST);

	shader = Shader("Resource/Build/GLSL/Forward.vs.glsl", "Resource/Build/GLSL/Forward.ps.glsl");

	uboVertex = UniformBuffer(sizeof(BufferVertex));
	uboPixel = UniformBuffer(sizeof(BufferPixel));

	uboVertex.Bind(0);
	uboPixel.Bind(1);

	// LOAD 3D MODEL

	ModelLoader::Load("Resource/Model.fme", vertices, indices);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned long), &indices[0], GL_STATIC_DRAW);
	
	std::vector<InputElementDesc> inputs = {
		{ "POSITION", 0, EFormat::RGB32Float, 0 },
		{ "NORMAL",   0, EFormat::RGB32Float, 0 },
		{ "TEXCOORD", 0, EFormat::RG32Float,  0 }
	};

	VAO = SetupVertexAttributes(inputs);

	// LOAD TEXTURES

	{
		Image image("Resource/Model_COL.png", 3);

		TextureDesc desc;
		desc.width = image.Width();
		desc.height = image.Height();
		desc.data = image.GetPixels();
		desc.format = EFormat::RGB8UNorm;

		baseColorMap = device.CreateTexture(desc);
	}

	{
		Image image("Resource/Model_RGH.png", 1);

		TextureDesc desc;
		desc.width = image.Width();
		desc.height = image.Height();
		desc.data = image.GetPixels();
		desc.format = EFormat::R8UNorm;

		roughnessMap = device.CreateTexture(desc);
	}

	{
		Image image("Resource/Model_MTL.png", 1);

		TextureDesc desc;
		desc.width = image.Width();
		desc.height = image.Height();
		desc.data = image.GetPixels();
		desc.format = EFormat::R8UNorm;

		metallicMap = device.CreateTexture(desc);
	}

	{
		Image image("Resource/Model_NRM.png", 3);

		TextureDesc desc;
		desc.width = image.Width();
		desc.height = image.Height();
		desc.data = image.GetPixels();
		desc.format = EFormat::RGB8UNorm;

		normalMap = device.CreateTexture(desc);
	}
}

void Render()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, baseColorMap.id);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, roughnessMap.id);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, metallicMap.id);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, normalMap.id);

	// activate shader
	shader.Use();

	// -------------------------------------------------- Mouse Orbit --------------------------------------------------

	Vector3 at = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	Vector2I mv = io.mouseDelta;

	static float camAngleX = 0.0f;
	static float camAngleY = 0.0f;

	if (io.mouseDown[0])
	{
		camAngleX -= (float)mv.x;
		camAngleY += (float)mv.y;
	}

	static float distance = 1.5f;

	distance -= (float)io.mouseWheel * 0.03f;

	distance = Math::Max(0.5f, distance);

	float camX = distance * sinf(camAngleX * (Math::Pi<float> / 180.0f)) * cosf(camAngleY * (Math::Pi<float> / 180.0f));
	float camY = distance * sinf(camAngleY * (Math::Pi<float> / 180.0f));
	float camZ = distance * cosf(camAngleX * (Math::Pi<float> / 180.0f)) * cosf(camAngleY * (Math::Pi<float> / 180.0f));

	Matrix4 view = Matrix4::LookAt(Vector3(camX, camY, camZ), at, up);

	// -----------------------------------------------------------------------------------------------------------------

	Matrix4 cMatrix = AxisConversion(EAxis::nY, EAxis::Z, EAxis::Z, EAxis::Y);

	Matrix4 loc = Matrix4::Translation(0.0f, -0.5f, 0.0f);
	Matrix4 rot = Matrix4::RotationX(Degree(0.0f));
	Matrix4 scl = Matrix4::Identity;

	Matrix4 model = loc * rot * scl;

	Matrix4 projection = Matrix4::Perspective(Degree(65.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);

	bufferVertex.model = (model * cMatrix).Transposed();
	bufferVertex.view = view.Transposed();
	bufferVertex.projection = projection.Transposed();

	uboVertex.Update(&bufferVertex);

	bufferPixel.viewPos = Vector3(camX, camY, camZ);
	bufferPixel.lightPos = Vector3(0.0f, 0.0f, 3.0f);

	uboPixel.Update(&bufferPixel);

	glBindVertexArray(VAO);

	glBindVertexBuffer(0, VBO, 0, sizeof(Vertex));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Exit()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// TODO: Delete textures
}
