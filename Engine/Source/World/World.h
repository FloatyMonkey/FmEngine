// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/CoreTypes.h"
#include "../Utility/Assert.h"

#include "Pool.h"
#include "View.h"

#include <vector>
#include <unordered_map>
#include <memory>

namespace FM
{
	class World
	{
	public:

		/// Creates a new entity.
		Entity Create() {
			static uint64 index = 1;
			return index++;
		}

		/// Destroys an entity and all its components.
		void Destroy(Entity entity) {

		}

		/// Assigns a component to the given entity.
		template <typename Component>
		Component& Assign(Entity entity) {
			return Assure<Component>().Assign(entity);
		}

		/// Removes a component from the given entity.
		template <typename Component>
		void Remove(Entity entity) {
			return Assure<Component>().Remove(entity);
		}

		/// Checks if an entity has all the given components.
		template <typename... Component>
		bool Has(Entity entity) const {
			return (Assure<Component>().Has(entity) && ...);
		}

		template<typename... Component>
		View<Component...> GetView() {
			static_assert(sizeof...(Component) > 0);
			return { Assure<Component>()... };
		}

	private:

		template <typename Component>
		ComponentPool<Component>& Assure()
		{
			static usize index = pools.size();

			if (!(index < pools.size()))
			{
				pools.push_back(std::make_unique<ComponentPool<Component>>());
			}

			return static_cast<ComponentPool<Component>&>(*pools[index]);
		}

	private:

		std::vector<std::unique_ptr<IPool>> pools;
		std::vector<Entity> entities;
	};
}
