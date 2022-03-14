
/**
 * 
 * Kitsune Memory Manager
 * 
 * General Documentation & Useage
 * 		Welcome, brave soul, to the internal documentation of KMM. Here, you will learn how to use
 * 		this library. You can also check out the project's wiki for a much prettier formatting.
 * 
 * 		a. Why should you use this?
 * 				Need to take control of your memory management for applications optimized for
 * 				performance or longevity? Great, that's what this library is designed to do.
 * 				Utilities like new/malloc are reliant on the operating system. At any point, they
 * 				may fail or refuse to allocate on request. Additionally, it's not always performant
 * 				for applications that require intelligent and efficient use of memory space.
 * 		b. When to use this? 
 * 				The optimal place to initialize KMM is at application start-up. This is because you can
 * 				fail-fast and retry or quit before the application even gets to runtime. Nothing is more
 * 				irritating to users when an application fails to work while it is working.
 * 		c. Strategies & Arenas
 * 				KMM uses a series of pick-and-chose strategies to manage the heap. Use what fits your
 * 				use case and current situation. Arenas represent an area within memory; think "basic
 * 				building block" of the heap. An arena keeps track of how "big" an area of memory is
 * 				and how much room is available to allocated on.
 * 
 * 		Okay, enough of the preamble, let's get to the meat and potatoes:
 * 
 * 		1. Startup
 * 				In order for this library to work, a platform type must be specified in order for 
 * 				kmm_alloc() to work. Use KMM_PLATFORM_WINDOWS for Windows applications, and KMM_PLATFORM_UNIX
 * 				for linux applications. They both require headers for their respecitive systems to use
 * 				their OS-specific virtual allocation functions.
 * 
 * 				You can comment out below the header you want or define it before you include kmemory.h.
 * 
 * 				In order to begin, you must first call kmm_alloc() to fetch a lump of heap. Ideally,
 * 				you call this once with the size of memory you need for the lifetime of your application.
 * 				You may not know how much memory you actually need and this may require profiling to
 * 				determine how much is required. It's best to err on the side of too much rather than too
 * 				little. In short, fetch a lump, store it somewhere permanent. You can deallocate using
 * 				kmm_free() when your application needs to shut down.
 * 
 * 				When kmm_alloc() is called, it will allocate your requested size + a little overhead to
 * 				manage its own internal state. You can poke into this internal state to see the gritty
 * 				details, though I do not recommend modifying without using the proper utilities.
 * 
 * 		2. Initialization
 * 				The heap you retrieve back from kmm_alloc() will essentially be unformatted region of
 * 				memory. Internally, this region of memory is, by default, an bottom-top monotonic
 * 				allocator (all sub-partitions are also bottom-top monotonic allocators). You should
 * 				sub-divide this region (or use as-is) into smaller arenas which you then associate with
 * 				allocation strategy. The bottom-top monotonic allocataor is both a strategy and the
 * 				default behavior of an arena.
 * 
 * 		3. Partitioning/Creating Sub-divided Arenas
 *				You can create new arenas by using kmm_make_arena(). You can specify a fixed size for
				that arena.
 *  
 */

//#define KMM_PLATFORM_WINDOWS
//#define KMM_PLATFORM_UNIX

#ifndef KMM_KMEMORY_H
#define KMM_KMEMORY_H
#include <stdlib.h>
#include <stdint.h>
#include "./src/platform.h"

#define kmm_kilobytes(n) (1024*n)
#define kmm_megabytes(n) (1024*kmm_kilobytes(n))
#define kmm_gigabytes(n) (1024*kmm_megabytes((uint64_t)n))
#define kmm_terabytes(n) (1024*kmm_megabytes((uint64_t)n))

#define KMM_CREATE_LIFETIME_FAILED 0
#define KMM_CREATE_LIFETIME_SUCCESS 1
#define KMM_CREATE_LIFETIME_NO_VIRTADDR 2

/**
 *      This function will perform a heap allocation using the given size. Use this
 *      function to initialize the KMM memory management facilities. See parameter
 *      argument descriptions for more information.
 * 
 *      If the return value of this function is greater than 0, then it succeeded,
 *      otherwise the allocation failed. The result of the return describes
 *      the state of the allocation.
 * 
 *      This function is not a traditional "heap allocation" function. KMM will
 *      append some amount of space to the requested size of the heap to manage
 *      its own state, therefore this should not be used as a replacement for
 *      malloc/new.
 * 
 * [OUT] void** store
 *      A pointer to the void* so that the function can fill it in with the
 *      heap allocation pointer.
 * 
 * [IN] uint64_t heap_size
 *      How big of heap to allocate for the application.
 * 
 * [IN] uint64_t virt_addr_loc
 *      Where to request the "virtual address space" of the memory allocation.
 *      This does not guarantee that the user will be given that virtual address
 *      and should check the return code to determine if that is the case.
 *      
 *      Can be NULL, currently unimplemented.
 * 
 */
int32_t
kmm_alloc(void** store, int64_t heap_size, uint64_t virt_addr_loc)
{

    // TODO: To get win32's VirtualAlloc functionality on linux, see mmap.
    // https://linux.die.net/man/2/mmap

    // Allocate 
    void* _allocation_ptr = malloc(heap_size);
    *store = _allocation_ptr;

    if (_allocation_ptr != NULL) return KMM_CREATE_LIFETIME_NO_VIRTADDR;

    // Fallthrough, allocation failed... probably.
    return KMM_CREATE_LIFETIME_FAILED;
}

/**
 *      This will free the lifetime heap from memory.
 * 
 *      This function is not a traditional free operation. Do not use this
 *      as a substitute for free/delete operations. This should only be used
 *      for the pointer returned by kmm_alloc.
 * 
 * [IN] void* store
 *      The location of the heap allocation pointer.
 */
void
kmm_free(void* store)
{
    free(store);
}

#endif