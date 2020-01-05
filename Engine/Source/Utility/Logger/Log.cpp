// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Log.h"

namespace FM
{
	Log::Log(ELogSeverity severity, const char* filename, int line)
	{
		operator << ("[" + SeverityToString(severity) + "] ");
	}

	Log::~Log()
	{
		std::cout << std::endl;
	}

	std::string Log::SeverityToString(ELogSeverity severity)
	{
		switch (severity)
		{
		case Fatal:		return "FATAL";
		case Error:		return "ERROR";
		case Warning:	return "WARNING";
		case Info:		return "INFO";
		case Debug:		return "DEBUG";
		default:		return "UNKNOWN";
		}
	}
}
