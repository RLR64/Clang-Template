// This prints the C language standard your compiler is currently using
// Freely redistributable, courtesy of learncpp.com
// (https://www.learncpp.com/cpp-tutorial/what-language-standard-is-my-compiler-using/)

#include <stdio.h>

typedef struct StandardInfo {
	long code;
	const char *name;
} StandardInfo_t;

// C Standard in acsending order
static const StandardInfo_t kStandard[] = {
    {199409L, "C95"},
    {199901L, "C99"},
    {201112L, "C11"},
    {201710L, "C17"},
    {202311L, "C23"},
};

// Reports when the compiler defines __STDC__ but not __STDC_VERSION__ (90)
#define C90_CODE 0L

// Reports when the complier cannot identify itself as C
#define UNKNOWN_CODE (-1L)

static long GetCStandard() {
#if defined (__STDC_VERSION__)
	return __STDC_VERSION__;
#elif defined (__STDC__)
	return C90_CODE;
#else
	return UNKNOWN_CODE;
#endif
}

int main() {
	const long standard = GetCStandard();

	if (standard == UNKNOWN_CODE) {
		printf("Error: Unable to determine your C lanuage standard. Sorry\n");
		return 0;
	}

	// C90 has no __STDC_VERSION__, so it is handled before the table lookup
	if (standard == C90_CODE) {
		printf("Your compiler is using C90 (standard code %ldL)\n", standard);
		return 0;
	}

	const StandardInfo_t *const end  =kStandard + (sizeof kStandard / sizeof kStandard[0]);

	for (const StandardInfo_t *Cstandard = kStandard; Cstandard != end; ++Cstandard) {
		// Exact match: the compiler is running a finalized standard
		if (standard == Cstandard->code) {
			printf("Your complier is using %s (standard code %ldL)\n", Cstandard->name, standard);
			return 0;
		}

		// Between two finalized codes: preview or pre-release of the next standard
		if (standard < Cstandard->code) {
			printf("Your complier is using a preview/pre-release of %s (standard code %ldL)\n",
				Cstandard->name, standard);
			return 0;
		}
	}

	// If a newer version is used that is not in the table
	printf("Your complier is using an unknown/future C standard (standard code %ldL)\n", standard);
	return 0;
}