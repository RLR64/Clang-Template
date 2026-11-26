// This prints the C++ language standard your compiler is currently using
// Freely redistributable, courtesy of learncpp.com
// (https://www.learncpp.com/cpp-tutorial/what-language-standard-is-my-compiler-using/)

#include <array>
#include <iostream>
#include <string_view>
#include <version>

// Check if include <print> if the compiler provides it
#if __has_include(<print>)
#include <print>
#endif

namespace {

constexpr int STANDARD_NUMBERS{7};

// The C++26 ID code is a placeholder for now
constexpr std::array StandardNumberID{199711L, 201103L, 201402L, 201703L, 202002L, 202302L, 202612L};
constexpr std::array StandardName{"C++98", "C++11", "C++14", "C++17", "C++20", "C++23", "C++26"};

// Visual Studio does not report __cplusplus correctly by default.
// Since Visual Studio 2015 we can use _MSVC_LANG instead.
// See https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/

auto GetCPPStandard() -> long {
#if defined(_MSVC_LANG)
	return _MSVC_LANG;

#elif defined (_MSC_VER)
	// Older versions of Visual Studio are not supported
	return -1;
#else
	//  __cplusplus is the standard way to queary the lanuage standard code
	return __cplusplus;
#endif
}

// Prints the message with std::println if available, otherwise it will use std::cout
void Report(std::string_view prefix, std::string_view name, long code) {
    #if defined (__cpp_lib_print)
        std::println("{}{} (language standard code {}L)", prefix, name, code);
    #else
        std::cout << prefix << name << " (language standard code " << code << "L)\n";
    #endif
}

} // namespace

auto main() -> int {
	long standard = GetCPPStandard();

	if (standard == -1) {
		std::cerr << "Error: Unable to determine your language standard.  Sorry.\n";
		return 0;
	}

	for (int i = 0; i < STANDARD_NUMBERS; ++i) {
		// Exact match: the compiler is running a finalized standard
		if (standard == StandardNumberID[i]) {
			Report("Your compiler is using ", StandardName[i], standard);
			break;
		}

		// Between two finalized codes: preview or pre-release of the next standard
		if (standard < StandardNumberID[i]) {
			Report("Your compiler is using a preview/pre-release of ", StandardName[i], standard);
			break;
		}
	}

	return 0;
}