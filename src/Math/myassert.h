/* Copyright Jukka Jyl�nki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file myassert.h
	@author Jukka Jyl�nki
	@brief Control over assert() macro for MathGeoLib. */
#include "MathLog.h"
#include "assume.h"

#include <sstream>

#ifdef assert
#undef assert
#endif

#ifdef FAIL_USING_EXCEPTIONS
#include <stdexcept>
#define RuntimeFailure(str) throw std::runtime_error(str)
#elif defined(OPTIMIZED_RELEASE) || defined(NDEBUG)
#define RuntimeFailure(str) ((void)0)
#define RUNTIME_FAILURE_DISABLED
#elif defined(_MSC_VER)
#include <crtdbg.h>
#define RuntimeFailure(str) do { LOGE("%s", str); _CrtDbgBreak(); } while(0)
#else
#define RuntimeFailure(str) do { LOGE("%s", str); } while(0)
#endif

#ifdef RUNTIME_FAILURE_DISABLED

#define assert(x) ((void)0)
#define asserteq(x,y) ((void)0)
#define assertcmp(x, cmp, y) ((void)0)

#else

#define assert(x) \
	MULTI_LINE_MACRO_BEGIN \
		if (!(x)) \
		{ \
			const char *error = #x " in " __FILE__ ":" STRINGIZE(__LINE__); \
			RuntimeFailure(error); \
		} \
	MULTI_LINE_MACRO_END

#define asserteq(x,y) \
	MULTI_LINE_MACRO_BEGIN \
		if ((x) != (y)) \
		{ \
			std::stringstream std_stringstream; \
			std_stringstream << "Assertion '" #x "' == '" #y "' failed! (" << (x) << " != " << (y) << "!) in " __FILE__ ":" STRINGIZE(__LINE__); \
			RuntimeFailure(std_stringstream.str().c_str()); \
		} \
	MULTI_LINE_MACRO_END

#define assertcmp(x, cmp, y) \
	MULTI_LINE_MACRO_BEGIN \
		if (!((x) cmp (y))) \
		{ \
			std::stringstream std_stringstream; \
			std_stringstream << "Assertion '" #x "' " #cmp " '" #y "' failed! (" << (x) << " and " << (y) << "!) in " __FILE__ ":" STRINGIZE(__LINE__); \
			RuntimeFailure(std_stringstream.str().c_str()); \
		} \
	MULTI_LINE_MACRO_END

#endif
