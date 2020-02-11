// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/Math/Vector3.h"
#include "../Utility/Math/Quaternion.h"

namespace FM
{
	class Mesh;

	class Transform
	{
	public:

		Vector3 position = Vector3::Zero;
		Quaternion rotation = Quaternion::Identity;
		Vector3 scale = Vector3::One;
	};

	class StaticMesh
	{
	public:

		Mesh* mesh;
	};
}
