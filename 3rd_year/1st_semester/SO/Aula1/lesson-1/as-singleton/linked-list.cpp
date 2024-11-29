#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "linked-list.h"

/*******************************************************/

/**
 * \brief The data to be stored in the list
 */
struct Student
{
    uint32_t nmec;        ///< Student number
    char *name;     ///< Student name
};

/**
 * \brief The linked-list support data structure:
 */
struct SllNode 
{
    Student reg;          ///< Student data
    struct SllNode *next;    ///< Pointer to next node
};

/*******************************************************/

static SllNode *list = NULL;

/*******************************************************/

void sllDestroy()
{
    SllNode *current_node = list;
    SllNode *next_node = current_node->next;

    while(current_node->next != NULL){
        free(current_node->reg.name);
        free(current_node->next);
        free(current_node);
        current_node = next_node;
        next_node = current_node->next;
    }
}

/*******************************************************/

void sllPrint(FILE *fout)
{
    SllNode *current_node = list;
    while(current_node != NULL){
        fprintf(fout,"%u; %s\n",current_node->reg.nmec,current_node->reg.name);
        current_node = current_node->next;
    }
}

/*******************************************************/

void sllInsert(uint32_t nmec, const char *name)
{
    assert(name != NULL && name[0] != '\0');
    assert(!sllExists(nmec));
    SllNode *current_node = list;

    Student* new_student = (Student*) malloc(sizeof(Student));
    new_student->nmec = nmec;
    new_student->name = (char*) malloc(sizeof(name));
    strcpy(new_student->name,name);

    SllNode* new_node = (SllNode*) malloc(sizeof(SllNode));
    new_node->reg = *new_student;

     if (list == NULL || (list->reg).nmec >= nmec) {
        list = new_node;
        new_node->next = current_node;
    }else {
        while (current_node->next != NULL && current_node->next->reg.nmec < nmec) {
            current_node = current_node->next;
        }
        new_node->next = current_node->next;
        current_node->next = new_node;
    }

}

/*******************************************************/

bool sllExists(uint32_t nmec)
{
    SllNode *current_node = list;
    
    while (current_node != NULL){
        if(current_node->reg.nmec == nmec){
            return true;
        }else{
            current_node = current_node->next;
        }
    }
    
    return false;
}

/*******************************************************/

void sllRemove(uint32_t nmec)
{
    assert(sllExists(nmec));
    SllNode* previous_node = list;
    SllNode* current_node = list->next;

    if(list->reg.nmec == nmec){
        free(list->reg.name);
        free(list);
        list = list->next;
    }else{
        while (current_node != NULL){
           if(current_node->reg.nmec == nmec){
                previous_node->next = current_node->next;
                free(current_node->reg.name);
                free(current_node->next);
                free(current_node);
           } 
           previous_node = previous_node->next;
           current_node = current_node->next;
        }
    }

}

/*******************************************************/

const char *sllGetName(uint32_t nmec)
{
    assert(sllExists(nmec));
    SllNode *current_node = list;
    
    while (current_node != NULL){
        if(current_node->reg.nmec == nmec){
            return current_node->reg.name;
        }else{
            continue;
        }
    }

    return NULL;
}

/*******************************************************/

bool sllLoad(FILE *fin)
{
    assert(fin != NULL);

    return false;
}

/*******************************************************/

