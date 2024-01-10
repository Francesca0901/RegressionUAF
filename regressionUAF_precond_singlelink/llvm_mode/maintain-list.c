#include "../android-ashmem.h"
#include "../config.h"
#include "../types.h"

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

extern u8 __afl_precond_area_initial[MAP_SIZE];
extern u8 *__afl_precond_area_ptr;

extern __thread u32 __afl_recent_free_list[5];
extern __thread u32 __afl_recent_patch_list[5];
extern __thread u32 __afl_recent_free_idx;
extern __thread u32 __afl_recent_patch_idx;

void update_bb_list(uint32_t cur_loc) {
    if(__afl_recent_patch_list[__afl_recent_patch_idx] == cur_loc >> 1) {
        return;
    }
    __afl_recent_patch_list[__afl_recent_patch_idx] = cur_loc >> 1;
    __afl_recent_patch_idx = (__afl_recent_patch_idx + 1) % 5;

    // printf("now in update_patch_list\n");

    for (int i = 0; i < 5; i++) {
        // printf("current loc: %u\n", cur_loc);
        // printf("prev free = %d: %u\n",i , __afl_recent_free_list[i]);
        if(__afl_recent_free_list[i] != 0) {
            uint32_t hashedValue = __afl_recent_free_list[i] ^ cur_loc;
            // printf("hash: %u\n", hashedValue);
            __afl_precond_area_ptr[hashedValue] += 1;
        }
    }
    // printf("\n");
}

void update_free_list(uint32_t cur_loc) {
    // printf("now in update_free_list\n");

    // SPUPDATE 6 : maybe we don't need to update preconf map when excuting free
    // for (int i = 0; i < 5; i++) {
    //     // printf("current loc: %u\n", cur_loc);
    //     // printf("prev bb = %d: %u\n",i , __afl_recent_patch_list[i]);
        
    //     if(__afl_recent_patch_list[i] != 0) {
    //         uint32_t hashedValue = __afl_recent_patch_list[i] ^ cur_loc;
    //         // printf("hash: %u\n", hashedValue);
    //         __afl_precond_area_ptr[hashedValue] += 1;
    //     }
    // }
    // printf("\n");

    __afl_recent_free_list[__afl_recent_free_idx] = cur_loc >> 1;
    __afl_recent_free_idx = (__afl_recent_free_idx + 1) % 5;
}

void printMap() {
    FILE *file = fopen("precond_map.txt", "w"); // Open a file for writing
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        if(__afl_precond_area_ptr[i] != 0){
            fprintf(file, "Map[%d] = %d\n", i, __afl_precond_area_ptr[i]); // Print to the file
        }
    }

    fclose(file); // Close the file when done
}