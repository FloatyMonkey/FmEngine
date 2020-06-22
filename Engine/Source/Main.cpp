// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "ThirdParty/Glad/glad.h"

#include "Modules/Windows/Window.h"

#include "Graphics/GL/Shader.h"
#include "Graphics/GL/UniformBuffer.h"

#include "Loaders/Image.h"

#include "Graphics/Mesh.h"

#include "Physics/Rigidbody.h"

#include "Graphics/RHI/Texture.h"
#include "Graphics/RHI/OpenGL/Device.h"

#include "Graphics/RHI/Pipeline.h"
#include "Graphics/RHI/OpenGL/Format.h"

#include "Audio/AudioClip.h"
#include "Audio/AudioSource.h"
#include "Modules/DirectSound/AudioDevice.h"

#include "World/World.h"

#include "Components/Components.h"

#include "Utility/Time.h"

#include "Utility/Math/Math.h"

#include <iostream>

using namespace FM;

namespace FM::Game
{
	void Setup(World& world);
	void Update(World& world);
}

World world;
Win32Window window;
AudioDevice* audioDevice;

void Setup();
void Update();

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

	Math::Column(r, 3 - srcF0 - srcU0, Math::Cross(Math::Column(r, srcF0), Math::Column(r, srcU0)));

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
	desc.id = "FmEngine";
	desc.title = "FmEngine";
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

	window.SetMouseCallback([](int x, int y, int wheelDelta, bool leftDown, bool middleDown, bool rightDown, void* user) {
		IO* myIO = static_cast<IO*>(user);

		myIO->mouseDown[0] = leftDown;
		myIO->mouseDown[1] = rightDown;
		myIO->mouseDown[2] = middleDown;

		myIO->mousePos = Vector2I(x, y);
		myIO->sumMouseWheel += wheelDelta;
	}, &io);

	audioDevice = new AudioDevice(window.GetWindowHandle());

	Setup();
	Game::Setup(world);

	GTime.Update(); // TODO: Ugly hack to reset dt.

	while (window.Update())
	{
		GTime.Update();

		io.mouseDelta = io.mousePos - io.prevMousePos;
		io.prevMousePos = io.mousePos;

		io.mouseWheel = io.sumMouseWheel;
		io.sumMouseWheel = 0;

		Game::Update(world);
		Update();

		SwapBuffers(hDc);
	}

	wglMakeCurrent(NULL, NULL);
	ReleaseDC((HWND)window.GetWindowHandle(), hDc);
	wglDeleteContext(hRc);
}

OpenGL::Device device;

Shader shader;
UniformBuffer uboVertex, uboPixel;

unsigned int VAO;
HTexture baseColorMap;

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
	
	std::vector<InputElementDesc> inputs = {
		{ "POSITION", 0, EFormat::RGB32Float, 0 },
		{ "NORMAL",   0, EFormat::RGB32Float, 0 },
		{ "TEXCOORD", 0, EFormat::RG32Float,  0 }
	};

	VAO = SetupVertexAttributes(inputs);

	Image image("Resource/Checker.png", 3);

	TextureDesc desc;
	desc.width = image.Width();
	desc.height = image.Height();
	desc.data = image.GetPixels();
	desc.format = EFormat::RGB8UNorm;

	baseColorMap = device.CreateTexture(desc);
}

void Update()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, baseColorMap.id);

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

	static float distance = 8.0f;

	distance -= (float)io.mouseWheel * 0.03f;

	distance = Math::Max(0.5f, distance);

	float camX = distance * sinf(camAngleX * (Math::Pi<float> / 180.0f)) * cosf(camAngleY * (Math::Pi<float> / 180.0f));
	float camY = distance * sinf(camAngleY * (Math::Pi<float> / 180.0f));
	float camZ = distance * cosf(camAngleX * (Math::Pi<float> / 180.0f)) * cosf(camAngleY * (Math::Pi<float> / 180.0f));

	Matrix4 view = Math::LookAt(Vector3(camX, camY, camZ), at, up);

	// -----------------------------------------------------------------------------------------------------------------

	Matrix4 cMatrix = AxisConversion(EAxis::nY, EAxis::Z, EAxis::Z, EAxis::Y);

	Matrix4 projection = Math::Perspective(Math::ToRadians(65.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 1000.0f);

	bufferVertex.view = view;
	bufferVertex.projection = projection;

	uboVertex.Update(&bufferVertex);

	bufferPixel.viewPos = Vector3(camX, camY, camZ);
	bufferPixel.lightPos = Vector3(0.0f, 0.0f, 3.0f);

	uboPixel.Update(&bufferPixel);

	glBindVertexArray(VAO);

	float dt = GTime.GetDeltaTime();

	// ================================================================
	// AUDIO SYSTEM
	// ================================================================

	int byteToLock;
	int bytesToWrite;

	audioDevice->GetPosition(byteToLock, bytesToWrite);

	if (bytesToWrite)
	{
		// Samples, counts one for L and R together.
		int samplesToWrite = bytesToWrite / 4; // Divided by BytesPerSample.

		std::vector<int16> mixBuffer(samplesToWrite * 2, 0);

		auto aview = world.GetView<AudioSource>();

		for (Entity e : aview)
		{
			AudioSource& source = aview.Get<AudioSource>(e);

			if (!source.isPlaying) continue;

			int offset = source.sampleIndex * 2;

			for (int i = 0; i < samplesToWrite * 2; i += 2)
			{
				if (source.sampleIndex >= source.clip->mSampleCount)
				{
					if (source.repeat)
					{
						source.sampleIndex = 0;
						offset = 0;
					}
					else
					{
						source.isPlaying = false;
						source.sampleIndex = 0;
						break;
					}
				}

				float L = source.clip->mData[offset + i + 0];
				float R = source.clip->mData[offset + i + 1];

				L *= DecibelToLinear(source.volume);
				R *= DecibelToLinear(source.volume);

				mixBuffer[i + 0] += static_cast<int16>(L * 32767.0f);
				mixBuffer[i + 1] += static_cast<int16>(R * 32767.0f);

				source.sampleIndex += 1;
			}
		}

		audioDevice->SetBuffer(&mixBuffer[0], byteToLock, bytesToWrite);
	}

	// ================================================================
	// PHYSICS SYSTEM
	// ================================================================

	auto pview = world.GetView<Transform, Rigidbody>();

	for (Entity e : pview)
	{
		Transform& tr = pview.Get<Transform>(e);
		Rigidbody& rb = pview.Get<Rigidbody>(e);
		
		rb.linearAcceleration += rb.force * rb.inverseMass;
		rb.linearVelocity += rb.linearAcceleration * dt;
		rb.position += rb.linearVelocity * dt;
		rb.force = 0.0f;
		tr.translation = rb.position;

		//Quaternion Integrate(const Quaternion& rotation, const Vector3& dv, float dt) {
		//	return (rotation + 0.5f * dt * Quaternion(dv) * rotation).Normalize();
		//}
		//Vector3 angularAcceleration = rb.inverseInertiaTensor * rb.torque;
		//rb.angularVelocity += rb.angularAcceleration * dt;
		//rotation = Integrate(rotation, angularVelocity, dt);
		//rb.torque = 0.0f;
	}

	// ================================================================
	// RENDER SYSTEM
	// ================================================================

	auto cview = world.GetView<Transform, StaticMesh>();

	for (Entity e : cview)
	{
		Transform& transform = cview.Get<Transform>(e);
		StaticMesh& staticMesh = cview.Get<StaticMesh>(e);

		// TODO: This won't work for some reason.
		//auto& [transform, staticMesh] = cview.Get<Transform, StaticMesh>(entity);

		Matrix4 model = Math::Transformation(transform.translation, transform.rotation, transform.scale);

		bufferVertex.model = model * cMatrix;

		uboVertex.Update(&bufferVertex);

		glBindVertexBuffer(0, staticMesh.mesh->vertexBuffer, 0, sizeof(Mesh::Vertex));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, staticMesh.mesh->indexBuffer);

		glDrawElements(GL_TRIANGLES, staticMesh.mesh->mIndices.size(), GL_UNSIGNED_INT, 0);
	}
}
