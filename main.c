/**
 *
 * Kitsune Memory Manager Test Suite
 *      Author: Christopher DeJong
 *      Date Created: March 13, 2022
 *      
 *      This is a test suite designed to debug and test kmem.h and its performance
 *      characteristics. This file should be omitted when this library is included
 *      into projects.
 * 
 */
#define KMM_PLATFORM_WINDOWS

#include <stdio.h>
#include <assert.h>
#include <time.h> // https://create.stephan-brumme.com/windows-and-linux-code-timing/
#include "kmm/kmemory.h"

int main()
{

    /**
     * Step 1.
     *      Request the memory required for the application to run.
     */
    void* heap_allocation = NULL;
    int32_t ltheap_res = kmm_alloc(&heap_allocation, kmm_gigabytes(2), kmm_terabytes(2));
    assert(ltheap_res); // Ensure that we the heap size we requested.
    printf("Allocation of %lluKb (%lluMb) was successful.\n", kmm_gigabytes(2)/1024, kmm_gigabytes(2)/(1024*1024));

    /**
     * Post-runtime cleanup. Yes, it's that easy.
     * (You don't need to call this if you're fast-exitting. The OS should reclaim the memory once the application exits.)
     */
    kmm_free(heap_allocation);

    return 0;
}

