// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "CoreTypes.h"

namespace FM
{
	class Hash
	{
	private:

		static const uint32 Fnv32Prime = 16777619;
		static const uint32 Fnv32Offset = 2166136261;

		static const uint64 Fnv64Prime = 1099511628211;
		static const uint64 Fnv64Offset = 14695981039346656037;

	public:

		static constexpr uint32 FNV1a32(const char* text)
		{
			uint32 hash = Fnv32Offset;
			while (*text) hash = (*text++ ^ hash) * Fnv32Prime;
			return hash;
		}

		static constexpr uint64 FNV1a64(const char* text)
		{
			uint64 hash = Fnv64Offset;
			while (*text) hash = (*text++ ^ hash) * Fnv64Prime;
			return hash;
		}
	};

	class StringID
	{
	public:

		template <uint32 N>
		constexpr StringID(const char(&text)[N]) noexcept
			: mHash(Hash::FNV1a32(text))
#ifdef FM_DEBUG
			, mString(text)
#endif
		{}

		explicit constexpr StringID(uint32 hash) noexcept
			: mHash(hash) {}

		inline constexpr bool operator==(const StringID& other) const { return mHash == other.mHash; }
		inline constexpr bool operator!=(const StringID& other) const { return mHash != other.mHash; }

		inline constexpr bool operator==(uint32 hash) const { return mHash == hash; }
		inline constexpr bool operator!=(uint32 hash) const { return mHash != hash; }

	private:

		const uint32 mHash = 0;

#ifdef FM_DEBUG
		const char* mString = nullptr;
#endif
	};
}
