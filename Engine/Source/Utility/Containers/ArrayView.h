// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../CoreTypes.h"

namespace FM
{
	template<typename T>
	class TArrayView
	{
	public:

		constexpr TArrayView()
			: mBegin(nullptr), mEnd(nullptr) {}

		constexpr TArrayView(const T* begin, usize size)
			: mBegin(begin), mEnd(begin + size) {}

		constexpr TArrayView(const T* begin, const T* end)
			: mBegin(begin), mEnd(end) {}

		template<usize N>
		constexpr TArrayView(const T(&array)[N])
			: mBegin(array), mEnd(array[N]) {}

		constexpr usize Size() const
		{
			return mEnd - mBegin;
		}

		constexpr const T* begin() const
		{
			return mBegin;
		}

		constexpr const T* end() const
		{
			return mEnd;
		}

		constexpr const T* const cbegin() const
		{
			return mBegin;
		}

		constexpr const T* const cend() const
		{
			return mEnd;
		}

		constexpr const T& operator[] (usize i) const
		{
			return mBegin[i];
		}

	private:

		const T* mBegin;
		const T* mEnd;
	};
}
