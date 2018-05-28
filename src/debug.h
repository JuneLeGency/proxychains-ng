#ifndef DEBUG_H
#define DEBUG_H

#ifdef NDEBUG
#undef DEBUG
#else
#define DEBUG
#endif

#ifdef ANDROID
#include <android/log.h>
#include <stdio.h>
#define TAG "proxychains-ng"
int android_print(int fd, const char *format, ...);
#ifdef perror
#undef perror
#endif

#define perror(msg) android_print(2, msg)
#endif

#ifdef DEBUG

#ifdef ANDROID
#ifdef fprintf
#undef fprintf
#endif
#define fprintf( __fp ,...) android_print(fileno(__fp), __VA_ARGS__)

#ifdef dprintf
#undef dprintf
#endif
#define dprintf(__fp ,...) android_print(__fp, __VA_ARGS__)
#endif //ANDROID

# include <stdio.h>
# define PSTDERR(fmt, args...) do { dprintf(2,fmt, ## args); } while(0)
# define PDEBUG(fmt, args...) PSTDERR("DEBUG:"fmt, ## args)
# define DEBUGDECL(args...) args

# include "core.h"
void DUMP_PROXY_CHAIN(proxy_data *pchain, unsigned int count);

#else
# define PDEBUG(fmt, args...) do {} while (0)
# define DEBUGDECL(args...)
# define DUMP_PROXY_CHAIN(args...) do {} while (0)
#endif

# define PFUNC() do { PDEBUG("pid[%d]:%s\n", getpid(), __FUNCTION__); } while(0)

#endif

