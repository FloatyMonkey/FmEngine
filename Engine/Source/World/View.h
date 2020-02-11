// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "Pool.h"

#include <array>
#include <algorithm>
#include <tuple>

namespace FM
{
	template<typename...>
	class View;

	template <typename ...Component>
	class View
	{
	public:

		template<typename Comp>
		using component_iterator_type = decltype(std::declval<ComponentPool<Comp>>().begin());

		using underlying_iterator_type = typename std::vector<Entity>::const_iterator;
		using unchecked_type = std::array<const std::vector<Entity>*, (sizeof...(Component) - 1)>;

		class Iterator
		{
		public:

			Iterator() = default;

			Iterator(const std::vector<Entity>* candidate, unchecked_type other, underlying_iterator_type curr)
				: view(candidate), unchecked(other), it(curr) {}

			bool IsValid() const {
				return std::all_of(unchecked.cbegin(), unchecked.cend(), [entt = *it](const std::vector<Entity>* curr) { return std::find(curr->begin(), curr->end(), entt) != curr->end(); });
			}

		public:

			Iterator& operator++() {
				while (++it != view->end() && !IsValid());
				return *this;
			}

			Iterator operator++(int) {
				Iterator prev = *this;
				return ++*this, prev;
			}

			Iterator& operator--() {
				while (--it != view->begin() && !IsValid());
				return *this;
			}

			Iterator operator--(int) {
				Iterator prev = *this;
				return --*this, prev;
			}

			bool operator==(const Iterator& rhs) const {
				return rhs.it == it;
			}

			bool operator!=(const Iterator& rhs) const {
				return !(*this == rhs);
			}

			const Entity* operator->() const {
				return it.operator->();
			}

			const Entity& operator*() const {
				return *operator->();
			}

		private:

			const std::vector<Entity>* view;
			unchecked_type unchecked;
			underlying_iterator_type it;
		};

		View(ComponentPool<Component>&... pools)
			: mPools{ &pools... }
		{}

		const std::vector<Entity>* candidate() const {
			return std::min({ &std::get<ComponentPool<Component>*>(mPools)->entities... }, [](const auto* lhs, const auto* rhs) {
				return lhs->size() < rhs->size();
			});
		}

		unchecked_type unchecked(const std::vector<Entity>* view) const {
			usize pos = 0;
			unchecked_type other{};
			((&std::get<ComponentPool<Component>*>(mPools)->entities == view ? nullptr : (other[pos++] = &std::get<ComponentPool<Component>*>(mPools)->entities)), ...);
			return other;
		}

		/// Estimates the number of entities iterated by the view.
		usize Size() const {
			return std::min({ std::get<ComponentPool<Component>*>(mPools)->Size()... });
		}

		Iterator begin() const {
			const auto* view = candidate();
			return Iterator(view, unchecked(view), view->begin());
		}

		Iterator end() const {
			const auto* view = candidate();
			return Iterator(view, unchecked(view), view->end());
		}

		template<typename Comp, typename Other>
		decltype(auto) get([[maybe_unused]] component_iterator_type<Comp> it, [[maybe_unused]] ComponentPool<Other>* cpool, [[maybe_unused]] const Entity entt) const {
			if constexpr (std::is_same_v<Comp, Other>) {
				return *it;
			}
			else {
				return cpool->Get(entt);
			}
		}

		template<typename... Comp>
		decltype(auto) Get(const Entity entt) const {
			if constexpr (sizeof...(Comp) == 0) {
				static_assert(sizeof...(Component) == 1);
				return (std::get<ComponentPool<Component>*>(mPools)->Get(entt), ...);
			}
			else if constexpr (sizeof...(Comp) == 1) {
				return (std::get<ComponentPool<Comp>*>(mPools)->Get(entt), ...);
			}
			else {
				return std::tuple<decltype(get<Comp>({}))... > {get<Comp>(entt)...};
			}
		}

	private:

		const std::tuple<ComponentPool<Component>*...> mPools;
	};
}
