#ifndef KMM_KMEMORY_H
#define KMM_KMEMORY_H
#include <stdlib.h>
#include <stdint.h>

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