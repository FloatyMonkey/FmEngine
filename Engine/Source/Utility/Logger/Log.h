// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include <iostream>

/// The default log macro.
/// This is the preferred way to log messages.

#define FM_LOG(...) \
	FM::Log(__VA_ARGS__,__FILE__,__LINE__)

namespace FM
{
	/// The severity of a log message.
	/// This enum is deliberately unscoped.

	enum ELogSeverity
	{
		Fatal,		///< A fatal error has occurred, the program will exit immediately.
		Error,		///< An error has occurred, the program may not exit.
		Warning,	///< Any situation that may not affect normal operation.
		Info,		///< Necessary information regarding program operation.
		Debug,		///< Standard debug messages.
	};

	/// The Log class represents a single log message.

	class Log
	{
	public:

		Log(ELogSeverity severity, const char* filename, int line);

		~Log();

		template <typename T>
		Log& operator<<(const T& message)
		{
			std::cout << message;
			return *this;
		}

	private:

		static std::string SeverityToString(ELogSeverity severity);
	};
}
