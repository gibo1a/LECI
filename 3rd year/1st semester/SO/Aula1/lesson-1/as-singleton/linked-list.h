/**
 *  \file 
 *
 *  \brief A simple linked-list, whose elements are registers composed of
 *      a 32-bit unsigned integer, representing a student number,
 *      and a string, used to store the student name
 *
 * \details 
 *  The following operations are defined:
 *     \li insertion of a register
 *     \li search for a name by number
 *     \li removal of a register
 *     \li destruction of the list
 *     \li print the list contents 
 *     \li load list from file
 *
 * \authors (2024) Artur Pereira <artur at ua.pt>
 * \authors (2024) Miguel Oliveira e Silva <mos at ua.pt>
 */

#ifndef __SO_IPC_SLL_
#define __SO_IPC_SLL_

#include <stdio.h>
#include <stdint.h> // uint32_t

/**
 *  \brief Delete all registers in the list and initialize it 
 */
void sllDestroy();

/**
 * \brief Print the list's registers in ascending order of the \c nmec field
 * \param [in] fout stream where printing should be sent to
 */
void sllPrint(FILE *fout);

/**
 *  \brief Fill list with contents of given file
 *  \details
 *    The file is just a two-columns table, using a semi-colon as field separator,
 *    containing a name and a number.
 *    The name can be composed of several words separated by single spaces.
 *  \param [in] fin stream of the file to read from
 *  \pre fin != NULL
 *  \return indication of a successful load
 */
bool sllLoad(FILE *fin);

/**
 *  \brief Insert a new register in the list
 *  \details
 *    - The list should be kept in ascending order of the \c nmec field
 *    - A dynamic duplication of the string pointed to by \c name should be done
 *  \param [in] nmec The student's number
 *  \param [in] name The student's name
 *  \pre name != NULL && name[0] != '\0'
 *  \pre !sllExists(nmec)
 */
void sllInsert(uint32_t nmec, const char *name);

/**
 * \brief Remove a register from the list
 *  \details
 *    - The list must be traversed in order to find the register to be removed
 *    - Recall that the list is sorted in nmec ascending order, 
 *      in order to improve the algorithm used
 *  \param [in] nmec The nmec associated to the register to be removed
 *  \pre sllExists(nmec)
 */
void sllRemove(uint32_t nmec);

/**
 *  \brief Get the name of a student given its nmec
 *  \details
 *    - The list must be traversed in order to find the given nmec
 *      and the corresponding name should be returned.
 *    - Recall that the list is sorted in nmec ascending order, 
 *      in order to improve the algorithm used
 *  \param [in] nmec The nmec to be searched
 *  \pre sllExists(nmec)
 *  \return the corresponding name
 */
const char *sllGetName(uint32_t nmec);

/**
 * \brief Check the existence of a register
 *  \param [in] nmec The nmec associated to the register to be removed
 *  \return true if it exists and false otherwise
 */
bool sllExists(uint32_t nmec);

#endif /* __SO_IPC_SLL_ */