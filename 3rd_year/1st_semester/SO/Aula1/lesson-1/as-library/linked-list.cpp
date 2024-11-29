#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "linked-list.h"

/*******************************************************/

SllNode* sllDestroy(SllNode* list)
{
    SllNode *current_node = list;
    SllNode *next_node = list;

    while(current_node->next != NULL){
        next_node = current_node->next;
        free(current_node->reg.name);
        free(current_node);
        current_node = next_node;
    }
    free(current_node->reg.name);
    free(current_node);

    return NULL;
}

/*******************************************************/

void sllPrint(SllNode *list, FILE *fout)
{
    if(list == NULL){
        fprintf(fout,"%s\n","List is empty");
    }
    SllNode *current_node = list;
    while(current_node != NULL){
        fprintf(fout,"%u; %s\n",current_node->reg.nmec,current_node->reg.name);
        current_node = current_node->next;
    }

}

/*******************************************************/

SllNode* sllInsert(SllNode* list, uint32_t nmec, const char *name)
{
    assert(name != NULL && name[0] != '\0');
    assert(!sllExists(list, nmec));
    
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
        return list;
    }else {
        while (current_node->next != NULL && current_node->next->reg.nmec < nmec) {
            current_node = current_node->next;
        }
        new_node->next = current_node->next;
        current_node->next = new_node;
    }
    return list;
}

/*******************************************************/

bool sllExists(SllNode* list, uint32_t nmec)
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

SllNode* sllRemove(SllNode* list, uint32_t nmec)
{
    assert(list != NULL);
    assert(sllExists(list, nmec));
    SllNode* previous_node = NULL;
    SllNode* current_node = list;

    if(list->reg.nmec == nmec){
        free(list->reg.name);
        free(list);
        list = list->next;
        return list;
    }else{
        while (current_node != NULL){
           if(current_node->reg.nmec == nmec){
                previous_node->next = current_node->next;
                free(current_node->reg.name);
                free(current_node);
                return list;
           } 
           previous_node = current_node;
           current_node = current_node->next;
        }
    }

    return list;
}

/*******************************************************/

const char *sllGetName(SllNode* list, uint32_t nmec)
{
    assert(list != NULL);
    assert(sllExists(list, nmec));

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

SllNode* sllLoad(SllNode *list, FILE *fin, bool *ok)
{
    assert(fin != NULL);
    if(fin == NULL) {
        printf("Not able to open the file.");
    }

    if (ok != NULL)
       *ok = false; // load failure

    return NULL;
}

/*******************************************************/

