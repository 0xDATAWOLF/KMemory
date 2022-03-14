/**
 * This header will provide platform-specific headers to the library. Simply include
 * this document with the file that requires platform-specific headers and it will provide
 * the necessary headers needed.
 */
#ifndef KMM_PLATFORM_H
#define KMM_PLATFORM_H

/**
 * Catch error if platform is defined improperly.
 */
#if defined(KMM_PLATFORM_WINDOWS) && defined(KMM_PLATFORM_UNIX)
#	error "Only one platform may be specified at a time"
#endif

/**
 * Catch errors if no platform is defined.
 */
#if !defined(KMM_PLATFORM_WINDOWS) && !defined(KMM_PLATFORM_UNIX)
#	error "A platform must be specified before including kmemory.h"
#endif

/**
 * Get the headers required for Windows.
 */
#if defined(KMM_PLATFORM_WINDOWS)
#	include <windows.h>
#endif

/**
 * Get the headers required for Linux.
 */
#if defined(KMM_PLATFORM_UNIX)
#	include <sys/mman.h>
#endif

#endif
