// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "World/World.h"

#include "Components/Components.h"
#include "Physics/Rigidbody.h"
#include "Audio/AudioSource.h"
#include "Audio/AudioClip.h"
#include "Graphics/Mesh.h"

namespace FM::Game
{
	Mesh meshA;
	Mesh meshB;
	AudioClip clipA;
	AudioClip clipB;

	void Setup(World& world)
	{
		meshA.Load("Resource/Monkey.fme");
		meshB.Load("Resource/Cube.fme");

		clipA.Load("Resource/HappyBackground01.wav");
		clipB.Load("Resource/HappyBackground02.wav");

		{
			Entity e = world.Create();

			world.Assign<Transform>(e);
			world.Assign<StaticMesh>(e).mesh = &meshA;
		}

		{
			Entity e = world.Create();

			Transform& tr = world.Assign<Transform>(e);
			Rigidbody& rb = world.Assign<Rigidbody>(e);
			world.Assign<StaticMesh>(e).mesh = &meshB;

			tr.position.y = 1.0f;
			tr.scale = 0.5f;

			rb.inverseMass = 1.0f / 5.0f;
			rb.linearVelocity.y = 10.0f;
		}

		{
			Entity e = world.Create();

			AudioSource& source = world.Assign<AudioSource>(e);
			source.clip = &clipA;
			source.repeat = true;
			source.volume = -3;
			source.Play();
		}

		{
			Entity e = world.Create();

			AudioSource& source = world.Assign<AudioSource>(e);
			source.clip = &clipB;
			source.repeat = true;
			source.volume = -3;
			source.Play();
		}
	}

	void Update(World& world)
	{

	}
}
