/**
 * This header will provide platform-specific headers to the library. Simply include
 * this document with the file that requires platform-specific headers and it will provide
 * the necessary headers needed.
 */
#ifndef KMM_PLATFORM_H
#define KMM_PLATFORM_H
#include <stdint.h>

/**
 * Catch error if platform is defined improperly. We want to ensure that the user designates
 * the proper platform at compile time such that we know which memory management library to use
 * for memory allocations.
 */
#if defined(KMM_PLATFORM_WINDOWS) && defined(KMM_PLATFORM_UNIX)
#	error "Only one platform may be specified at a time"
#endif 
#if !defined(KMM_PLATFORM_WINDOWS) && !defined(KMM_PLATFORM_UNIX)
#	error "A platform must be specified before including kmemory.h"
#endif

/**
 * We are declaring the platform functions. Definitions are found in their respective platform
 * header files. This reduces the complexity the library's implementation by middle-manning
 * OS-specific calls.
 */

int32_t platform_valloc(void** store, size_t size, size_t vaddr, uint32_t flags);
int32_t platform_free(void* store);

/**
 * Get the headers required for each platform. We are including the system libraries first in-case we
 * need them, then we are including the platforms' abstracted call implementations to supply the proper
 * definitions for the functions needed by the library.
 */
#if defined(KMM_PLATFORM_WINDOWS)
#	include "platform/win32.h"
#endif

#if defined(KMM_PLATFORM_UNIX)
#	include "platform/unix.h"
#endif

#endif
