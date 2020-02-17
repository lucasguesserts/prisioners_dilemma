// Handles the filesystem library in
// different versions of GCC.
// GCC 7 has filesystem as experimental.
#if __GNUG__ == 7
	#include <experimental/filesystem>
	namespace std { namespace filesystem = std::experimental::filesystem; }
#else
	#include <filesystem>
#endif
