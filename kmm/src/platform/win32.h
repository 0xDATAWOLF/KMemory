#ifndef KMM_PLATFORM_WIN32_H
#define KMM_PLATFORM_WIN32_H
#include <windows.h>
#include <stdint.h>

#define KMM_PLATFORM_VALLOC_NOALLOC 0
#define KMM_PLATFORM_VALLOC_SUCCESS 1

/**
 * A wrapper for Win32's virtualalloc function. This function will return a non-zero
 * value if it succeeded. This function guarantee that store param will contain the proper
 * return value; NULL if failed, or the allocation pointer on success.
 */
int32_t
platform_valloc(void** store, size_t size, size_t vaddr, uint32_t flags)
{

	// We may want to offer control over the flags, such as page sizing and what not.
	// For now, we will just do the standard call.
	void* _alloc = VirtualAlloc((void*)vaddr, size, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
	if (_alloc == NULL)
	{
		*store = NULL; // Guarantee NULL.
		return KMM_PLATFORM_VALLOC_NOALLOC;
	}

	*store = _alloc;
	return KMM_PLATFORM_VALLOC_SUCCESS;
}

/**
 * A wrapper for Win32's virtualfree function. This function guarantees a non-zero return
 * value if succeeded (no diagnostics data provided).
 */
int32_t
platform_free(void* store)
{

	BOOL _release = VirtualFree(store, 0, MEM_RELEASE);
	return _release ? 1 : 0;

}


#endif