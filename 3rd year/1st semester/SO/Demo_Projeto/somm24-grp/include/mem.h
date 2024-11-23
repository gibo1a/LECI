/**
 * \defgroup mem MEM -- Memory Management
 *
 * \details
 *   Initially, the memory is empty, meaning that no process address space is hosted there.
 *   Thus, memory can be seen as a single region with a given dimension.
 *   In order for a process to be executed, one block of memory must be assigned to it,
 *   in order to host the process' address.
 *
 *   On the first allocation, the initial empty region is splitted into two blocks, 
 *   one to host a process address space and one that remains free.
 *   In the next allocations, the free region is further divided.
 *   A running process eventually terminates its execution.
 *   Then, its assigned block of memory can be released, becoming available to other processes.
 *   If this block is not adjacent to the free region, more than one free regions appear.
 *   Thus, in a next allocation more than one region big enough to hold the process address space
 *   may exist.
 *   The one to be used depends on the allocation policy in use.
 *
 *   To manage the allocation system, 2 linked lists are used, 
 *   one representing the list of occupied blocks
 *   and another representing the list of free blocks.
 *   In both lists, the elements are kept in ascending order of the block base address they represent.
 *
 *   Two different allocation policies are to be implemented in this project:
 *   **next fit** and **worst fit**.
 *   In the **worst fit** approach, the allocation is done in the biggest free block.
 *   In the **next fit** approach, the element with the biggest block base address points to the element
 *   with the smallest block base address, making the list circular.
 *   The first element of the list is the one whose block base address follows the last allocated.
 *
 *   The following table presents a list of the functions in this module, including:
 *   - the function name;
 *   - the function ID, that can be used to switch between the binary and group version;
 *   - an estimation of the effort required to implement it;
 *   - a brief description of the function role.
 *   <table>
 *   <tr> <th> \c function <th align="center"> function ID <th align="center"> level <th>role
 *   <tr> <td> \c memInit() <td align="center"> 501 <td> 2 (low) <td> Initialize the internal data structure of the MEM module
 *   <tr> <td> \c memTerm() <td align="center"> 502 <td> 2 (low) <td> Free dynamic memory used by the allocation algorithm and reset supporting data structures
 *   <tr> <td> \c memPrint() <td align="center"> 503 <td> 3 (low medium) <td> Print the internal state of the memory management module
 *   <tr> <td> \c memAlloc() <td align="center"> 504 <td> 3 (low medium) <td> Try to allocate the amount of memory required, using the active allocation policy
 *   <tr> <td> \c memBestFitAlloc() <td align="center"> 505 <td> 6 (high) <td> Allocate a block of memory of the given size, using the next fit algorithm
 *   <tr> <td> \c memWorstFitAlloc() <td align="center"> 506 <td> 6 (high) <td> Allocate a block of memory of the given size, using the worst fit algorithm
 *   <tr> <td> \c memFree() <td align="center"> 507 <td> 5 (medium high) <td> Free a previously allocated memory block
 *   </table>
 *
 *  \author Artur Pereira - 2024
 */


#ifndef __SOMM24_MEM__
#define __SOMM24_MEM__

#include "tam.h"

#include <stdint.h>

/** @{ */

// ================================================================================== //

/**
 * \brief A memory block
 */
struct MemBlock {
    uint32_t start;         ///< The frame number where the block begins
    uint32_t size;          ///< The number of frames of the block
}; 

// ================================================================================== //

/**
 * \brief The node to support the linked lists used by the allocation algorithms
 */
struct MemNode {
    MemBlock block;             ///< A block of memory
    struct MemNode *next;       ///< A pointer to the next node in list
};

// ================================================================================== //

extern MemoryAllocationPolicy memAllocationPolicy;   ///< Policy in use

#define UNDEF_MEM_NODE ((MemNode*)0xfffffffd)  ///< Indication of a non inited MEM list

extern MemNode *memFreeList;        ///< Head of the free list for first fit algorithm
extern MemNode *memOccupiedList;    ///< Head of the occupied list for first fit algorithm

// ================================================================================== //

/**
 * \brief Opens the module, initializing the internal data structure
 * \details
 *  - The module's internal data structure, defined in file \c frontend/mem.cpp, 
 *    should be initialized properly.
 *  - The kernel must occupy the lower part of the total available main memory.
 *  - In case of an error, an appropriate exception must be thrown.
 *  - All exceptions must be of the type defined in this project (Exception).
 *
 * \param [in] memSize Total amount of memory, in memory units, available
 * \param [in] memKernelSize The amount of memory used by the operating system, in memory units
 * \param [in] policy The allocation policy to be used
 */
void memInit(uint32_t memSize, uint32_t memKernelSize, MemoryAllocationPolicy policy);

// ================================================================================== //

/**
 * \brief Closes the module, setting the internal data structure to the closed state
 * \details
 *   - In the closed state, the supporting data structure has well-defined values.
 *   - This function, should also release any memory it has dynamically allocated.
 */
void memTerm();

// ================================================================================== //

/**
 * \brief Print the internal state of the MEM module
 * \details
 *  - Two tables must be printed to the given file stream, 
 *    one containing the free blocks and the other the occupied blocks;
 *  - the linked-lists must be printed in natural order
 *  - In case of an error, an appropriate exception must be thrown.
 *  - All exceptions must be of the type defined in this project (Exception).
 *
 * \param [in] fout File stream where to send output 
 */
void memPrint(FILE *fout);

// ================================================================================== //

/**
 * \brief Try to allocate the required number of memory frames
 * \details
 *  - There are 2 auxiliary functions to aid in implementing the functionality of the function:
 *    \c memRetrieveNodeFromFreeList and \c memAddNodeToOccupiedList;
 *  - the allocation must be done in accordance with the active memory allocation policy.
 *  - In case of an error, an appropriate exception must be thrown.
 *  - All exceptions must be of the type defined in this project (Exception).
 *    
 * \param [in] size amount of memory to be allocated
 *
 * \return a valid memory frame number or UNDEF_ADDRESS
 */
uint32_t memAlloc(uint32_t size);

// ================================================================================== //

/**
 * \brief Add given node to the list of free blocks
 * \details
 *  - The given node must be added to the list of free blocks;
 *  - if the added block is adjacent, in terms of memory to the next, a merging must be done;
 *  - if the added block is adjacent, in terms of memory to the previous, a merging must be done;
 *  - In case of an error, an appropriate exception must be thrown.
 *  - All exceptions must be of the type defined in this project (Exception).
 *
 * \param p Pointer to the node to be added to the free list
 */
void memAddNodeToFreeList(MemNode *p);

// ================================================================================== //

/**
 * \brief Add given node to the list of occupied blocks
 * \details
 *  - The given node must be added to the list of occupied blocks;
 *  - In case of an error, an appropriate exception must be thrown.
 *  - All exceptions must be of the type defined in this project (Exception).
 *
 * \param p Pointer to the node to be added to the occupied list
 */
void memAddNodeToOccupiedList(MemNode *p);

// ================================================================================== //

/**
 * \brief Retrieve a node from the list of free blocks
 * \details
 *  - The list of free blocks must be searched in order to obtain the best suited, based on the
 *    given allocation policy, to allocated the required number of memory frames;
 *  - the block should be splitted if it bigger than required;
 *  - In case of an error, an appropriate exception must be thrown.
 *  - All exceptions must be of the type defined in this project (Exception).
 *
 * \param size Number of frames to allocate
 * \param policy Allocation policy to use
 *
 * \return A pointer to a node, representing the allocated block.
 */
MemNode *memRetrieveNodeFromFreeList(uint32_t size, MemoryAllocationPolicy policy);

// ================================================================================== //

/**
 * \brief Retrieve a node from the list of occupied blocks
 * \details
 *  - The list of occupied blocks must be searched in order to obtain the node representing 
 *    the given address;
 *  - In case of an error, an appropriate exception must be thrown.
 *  - All exceptions must be of the type defined in this project (Exception).
 *
 * \param address Number of the start memory frame to be retrieved
 *
 * \return The node representing the requested address
 */
MemNode *memRetrieveNodeFromOccupiedList(uint32_t address);

// ================================================================================== //

/**
 * \brief Free a previously allocated address space
 * \details
 *  - There are 2 auxiliary functions to aid in implementing the functionality of the function:
 *     \c memRetrieveNodeFromOccupiedList and \c memAddNodeToFreeList;
 *  - In case of an error, an appropriate exception must be thrown.
 *  - All exceptions must be of the type defined in this project (Exception).
 *
 * \param [in] address Number of the start frame of the block to be released
 */
void memFree(uint32_t address);

// ================================================================================== //

/**
 * \brief Return the size of the biggest free block
 *
 * \return The size of the biggest free block
 */
uint32_t memBiggestFreeBlockSize();

// ================================================================================== //

/** @} */

#endif /* __SOMM24_MEM__ */


