#ifndef DEBUG_H
#define DEBUG_H

#ifdef NDEBUG
#define RELEASE
#else
#define DEBUG
#endif

#ifdef DEBUG

#ifdef ANDROID
#include <android/log.h>
#include <stdio.h>
#define TAG "proxychains-ng"
int custom_dprintf(int stream, const char *format, ...);

#ifdef fprintf
#undef fprintf
#endif
#define fprintf( __fp ,...) custom_dprintf(fileno(__fp), __VA_ARGS__)

#ifdef dprintf
#undef dprintf
#endif
#define dprintf(__fp ,...) custom_dprintf(__fp, __VA_ARGS__)

#ifdef perror
#undef perror
#endif

#define perror(msg) dprintf(2, msg)

#endif
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

