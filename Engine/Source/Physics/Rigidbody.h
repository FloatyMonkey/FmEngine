// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/Math/Matrix3.h"
#include "../Utility/Math/Vector3.h"
#include "../Utility/Math/Quaternion.h"

namespace FM
{
	class Rigidbody
	{
	public:

		enum class EType : uint8
		{
			Static,		///< Mass infinite, Velocity zero, Position manual, no reaction to collision.
			Kinematic,	///< Mass infinite, Velocity manual, Position auto, no reaction to collision.
			Dynamic		///< Mass non-zero, Velocity forces, Position auto, reacts to collision.
		};

		enum class EConstraints : uint8
		{
			None = 0,

			PositionX = (1 << 0),
			PositionY = (1 << 1),
			PositionZ = (1 << 2),

			RotationX = (1 << 3),
			RotationY = (1 << 4),
			RotationZ = (1 << 5),

			Position = PositionX | PositionY | PositionZ,
			Rotation = RotationX | RotationY | RotationZ,

			All = Position | Rotation
		};

	public:

		EType type = EType::Dynamic;
		EConstraints constraints = EConstraints::None;

		Vector3 position;
		Quaternion rotation;
		
		Vector3 linearVelocity;
		Vector3 angularVelocity;

		Vector3 linearAcceleration = -Vector3::UnitY * 9.81f; // TODO: Remove hardcoded gravity.

		float inverseMass;
		Matrix3 inverseInertiaTensor;

		Vector3 force;
		Vector3 torque;

		void AddForce(const Vector3& force);
		void AddForce(const Vector3& force, const Vector3& point);
		void AddTorque(const Vector3& torque);
	};

	inline void Rigidbody::AddForce(const Vector3& force)
	{
		this->force += force;
	}

	inline void Rigidbody::AddForce(const Vector3& force, const Vector3& point)
	{
		this->force += force;
		this->torque += Vector3::Cross(point - position, force);
	}

	inline void Rigidbody::AddTorque(const Vector3& torque)
	{
		this->torque += torque;
	}
}
