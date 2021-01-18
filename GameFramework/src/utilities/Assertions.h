#ifndef ASSERTIONS_H_
#define ASSERTIONS_H_




#if NDEBUG 
#define GAME_ASSERT(x)

#else
#define GAME_ASSERT(x) \
if (x) { } \
else \
{ \
	logAssertFail(#x, __FILE__, __LINE__); \
	__debugbreak(); \
}

#endif



void logAssertFail(const char* function, const char* file, int line);


#endif



