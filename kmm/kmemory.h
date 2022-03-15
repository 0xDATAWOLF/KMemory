
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

/**
 * The underlying control structure behind partitions of memory. Generally speaking,
 * it defines the general size and location of a particular region.
 */
typedef struct
{
	void* base_ptr;
	size_t commit;
	size_t length;
	struct
	{
		uint64_t placeholder: 64;
	} flags;
} kmm_arena_t;

inline int32_t
kmm_alloc(void** store, size_t size, uint64_t vaddr)
{

    // TODO: To get win32's VirtualAlloc functionality on linux, see mmap.
    // https://linux.die.net/man/2/mmap

	int32_t _valloc_status = platform_valloc(store, size, vaddr, 0);
	return _valloc_status;

}

inline int32_t
kmm_free(void* store)
{
	int32_t _free_status = platform_free(store);
	return _free_status;
}

#endif