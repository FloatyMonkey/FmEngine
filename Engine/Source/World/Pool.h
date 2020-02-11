// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/CoreTypes.h"
#include "../Utility/Assert.h"

#include <vector>
#include <unordered_map>
#include <memory>

namespace FM
{
	using Entity = uint64;

	class IPool {};

	template <typename T>
	class ComponentPool : public IPool
	{
	public:

		T& Assign(Entity entity)
		{
			FM_ASSERT(entity != 0);
			FM_ASSERT(lookup.find(entity) == lookup.end());

			lookup[entity] = components.size();

			components.emplace_back();
			entities.push_back(entity);

			return components.back();
		}

		void Remove(Entity entity)
		{
			FM_ASSERT(false); // TODO: Not implemented.
		}

		bool Has(Entity entity) const {
			return lookup.find(entity) != lookup.end();
		}

		usize Size() {
			return components.size();
		}

		T& Get(Entity entity)
		{
			auto it = lookup.find(entity);
			if (it != lookup.end())
			{
				return components[it->second];
			}
		}

		std::vector<T> components;
		std::vector<Entity> entities;
		std::unordered_map<Entity, usize> lookup;
	};
}
