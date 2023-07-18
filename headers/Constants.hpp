#ifndef BNS_CONSTANTS_H

#define BNS_CONSTANTS_H

// check if windows
#ifndef OS_WIN
#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
#define OS_WIN 1
#endif
#endif

#if OS_WIN
#define SDL_MAIN_HANDLED
#endif

#ifndef ROOT_DIRECTORY
#define ROOT_DIRECTORY ""
#endif

#ifndef COMMON_DIRECTORY
#define COMMON_DIRECTORY ""
#endif

#ifndef USER_COMMON_DIRECTORY
#define USER_COMMON_DIRECTORY "."
#endif

#endif // !BNS_CONSTANTS_H