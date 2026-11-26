#include <iostream>

// Check if include <print> if the compiler provides it
#if __has_include(<print>)
#include <print>
#endif

int main() {
    
    #if defined(__cpp_lib_print)
        std::println("Hello world! Post-C++23.");
    #else
        std::cout << "Hello world! Pre-C++23.\n";
    #endif

    return 0;
}