#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <sys/random.h>

#include <rand.h>

#define BUFFER_BYTES (1<<8) /** Set to 1<<8 = 256 (Can be any number which is a Power of 2)*/
#define BUFFER_SIZE (BUFFER_BYTES / sizeof(unsigned int))
#define BUFFER_MASK (BUFFER_SIZE - 1)

/**
 * @brief Structure representing a buffer to store generated random values.
 * 
 * This structure contains an offset value and an array of unsigned 32-bit integers.
 * The offset represents the starting position of the buffer, and the array stores the data.
 * The size of the array is determined by the BUFFER_SIZE constant.
 * @param offset The offset value of the buffer (unsigned 64-bit integer).
 * @param n The array of unsigned 32-bit integers.
 */
typedef struct {
    uint64_t offset; /** The offset value of the buffer. */
    uint32_t n[BUFFER_SIZE]; /** The array of unsigned 32-bit integers. */
} RandomBuffer;

static RandomBuffer buffer = {.offset = 0}; /** The buffer to store generated random values. */

/**
 * @brief Generates a random number within a given range.
 * 
 * This function uses a buffer to generate random numbers using the getrandom() function.
 * It ensures that the generated number is within the specified range by discarding numbers
 * that are greater than or equal to UINT_MAX - (UINT_MAX % max).
 * 
 * @param max The upper bound of the range (exclusive).
 * @return The generated random number.
 */
unsigned int getNextRand(unsigned int max) {
    uint32_t n = 0;

    do{
        if(buffer.offset == 0) getrandom(buffer.n, BUFFER_BYTES, 0);
        n = buffer.n[buffer.offset];
        buffer.offset = (buffer.offset + 1) & BUFFER_MASK;
    } while(n >= UINT_MAX - (UINT_MAX % max));  // Ensure that the generated number is within the specified range.

    return n % max;
}