#include <stdlib.h>
#include "linear_sequence.h"
#define BASIC_PHYSIC_SIZE 1
#define ITERATOR ((Iterator *)iterator)
#define CONTENT ((Content *)handle)

typedef struct {
    LSQ_BaseTypeT *data;
    LSQ_IntegerIndexT physical_size;
    LSQ_IntegerIndexT logical_size;
    LSQ_IntegerIndexT delta_size;
} Content;

typedef struct {
    LSQ_IntegerIndexT index;
    Content *content;
} Iterator;

double GetFactor(Content *content){
    return (1 + 1.0 / (content->delta_size / 10 + 1));
}

int IsFull(Content *content){
    return (content->logical_size == content->physical_size);
}

int IsHalfFull(Content *content){
   // printf("logs*f >= phys? %d <= %d\n", ((int)(content->logical_size * GetFactor(content))), content->physical_size);
    return ((int)(content->logical_size * GetFactor(content)) <= content->physical_size);
}

void Resize_up(Content *content){
    if(IsFull(content)){
        content->delta_size++;
        content->physical_size = content->physical_size * GetFactor(content);
        content->data = (LSQ_BaseTypeT *) realloc(content->data, (content->physical_size) * sizeof(LSQ_BaseTypeT));
    }
}

void Resize_down(Content *content){
    if(IsHalfFull(content)){
        content->delta_size--;
        content->physical_size = content->logical_size;
        if(content->delta_size < BASIC_PHYSIC_SIZE)
            content->delta_size = BASIC_PHYSIC_SIZE;
        content->data = (LSQ_BaseTypeT *) realloc(content->data, (content->physical_size) * sizeof(LSQ_BaseTypeT));
    }
}

extern LSQ_HandleT LSQ_CreateSequence(void){
    Content *temp_content = (Content *) malloc(sizeof(Content));
    temp_content->data = (LSQ_BaseTypeT *) malloc(BASIC_PHYSIC_SIZE * sizeof(LSQ_BaseTypeT));
    temp_content->physical_size = BASIC_PHYSIC_SIZE;
    temp_content->logical_size = 0;
    temp_content->delta_size = BASIC_PHYSIC_SIZE;
    return  temp_content;
}

extern void LSQ_DestroySequence(LSQ_HandleT handle){
    if(handle == LSQ_HandleInvalid)
        return;
    free(CONTENT->data);
    free(CONTENT);
}

extern LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle){
    if(handle == LSQ_HandleInvalid)
        return 0;
    return (CONTENT->logical_size);
}

extern int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator){
    return (!LSQ_IsIteratorPastRear(iterator) && !LSQ_IsIteratorBeforeFirst(iterator));
}

extern int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator){
    if(iterator == LSQ_HandleInvalid)
        return 0;
    return (ITERATOR->index >= ITERATOR->content->logical_size);
}

extern int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator){
    if(iterator == LSQ_HandleInvalid)
        return 0;
    return (ITERATOR->index < 0);
}

extern LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator){
    if(!LSQ_IsIteratorDereferencable(iterator))
        return LSQ_HandleInvalid;
    return &(ITERATOR->content->data[ITERATOR->index]);
}

extern LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index){
    if(handle == LSQ_HandleInvalid)
        return LSQ_HandleInvalid;
    Iterator *temp_iterator = (Iterator *) malloc(sizeof(Iterator));
    temp_iterator->content = CONTENT;
    temp_iterator->index = index;
    return temp_iterator;
}

extern LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle){
    return LSQ_GetElementByIndex(handle, 0);
}

extern LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle){
    if(handle == LSQ_HandleInvalid)
        return LSQ_HandleInvalid;
    return LSQ_GetElementByIndex(handle, CONTENT->logical_size);
}

extern void LSQ_DestroyIterator(LSQ_IteratorT iterator){
    if(iterator == LSQ_HandleInvalid)
        return;
    free(ITERATOR);
}

extern void LSQ_AdvanceOneElement(LSQ_IteratorT iterator){
    if(iterator == LSQ_HandleInvalid)
        return;
    ITERATOR->index++;
}

extern void LSQ_RewindOneElement(LSQ_IteratorT iterator){
    if(iterator == LSQ_HandleInvalid)
        return;
    ITERATOR->index--;
}

extern void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift){
    if(iterator == LSQ_HandleInvalid)
        return;
    ITERATOR->index += shift;
}

extern void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos){
    if(iterator == LSQ_HandleInvalid)
        return;
    ITERATOR->index = pos;
}

extern void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element){
    if(handle == LSQ_HandleInvalid)
        return;
    Resize_up(CONTENT);
    LSQ_IntegerIndexT i;
    for(i = CONTENT->logical_size; i > 0; i--){
        CONTENT->data[i] = CONTENT->data[i - 1];
    }
    CONTENT->data[0] = element;
    CONTENT->logical_size++;
}

extern void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element){
    if(handle == LSQ_HandleInvalid)
        return;
    Resize_up(CONTENT);
    CONTENT->data[CONTENT->logical_size] = element;
    CONTENT->logical_size++;
}

extern void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement){
    if(iterator == LSQ_HandleInvalid)
        return;
    Resize_up(ITERATOR->content);
    LSQ_IntegerIndexT i;
    for(i = ITERATOR->content->logical_size; i > ITERATOR->index; i--){
        ITERATOR->content->data[i] = ITERATOR->content->data[i - 1];
    }
    ITERATOR->content->data[ITERATOR->index] = newElement;
    ITERATOR->content->logical_size++;
}

extern void LSQ_DeleteFrontElement(LSQ_HandleT handle){
    if(handle == LSQ_HandleInvalid || CONTENT->logical_size == 0)
        return;
    CONTENT->logical_size--;
    LSQ_IntegerIndexT i;
    for(i = 0; i < CONTENT->logical_size; i++){
        CONTENT->data[i] = CONTENT->data[i + 1];
    }
    Resize_down(CONTENT);
}

extern void LSQ_DeleteRearElement(LSQ_HandleT handle){
    if(handle == LSQ_HandleInvalid || CONTENT->logical_size == 0)
        return;
    CONTENT->logical_size--;
    Resize_down(CONTENT);
}

extern void LSQ_DeleteGivenElement(LSQ_IteratorT iterator){
    if(!LSQ_IsIteratorDereferencable(iterator))
        return;
    ITERATOR->content->logical_size--;
    LSQ_IntegerIndexT i;
    for(i = ITERATOR->index; i < ITERATOR->content->logical_size; i++){
        ITERATOR->content->data[i] = ITERATOR->content->data[i + 1];
    }
    Resize_down(ITERATOR->content);
}
/*
void test_iterator_position(LSQ_IteratorT iterator, int index){
    printf("Content size is %d. Iterator index is %d\n", LSQ_GetSize(((Iterator *)iterator)->content), index);
    printf("Is Iterator before first? %s\n", LSQ_IsIteratorBeforeFirst(iterator) ? "Yes" : "No");
    printf("Is Iterator dereferencable? %s\n", LSQ_IsIteratorDereferencable(iterator) ? "Yes" : "No");
    printf("Is Iterator after last? %s\n", LSQ_IsIteratorPastRear(iterator) ? "Yes" : "No");
    printf("==================================\n");
}

int main(){
        // Create handle and push some elements
    LSQ_HandleT handle = LSQ_CreateSequence();
    printf("delta %d\n", ((Content *)handle)->delta_size);
    LSQ_InsertFrontElement(handle, 1);
    LSQ_InsertFrontElement(handle, 2);
    LSQ_InsertFrontElement(handle, 3);
    LSQ_IteratorT iterator = LSQ_GetElementByIndex(handle, 0);
        // Check up sizes and one value
    printf("Iterator value is %d\n", ((Iterator *)iterator)->content->data[((Iterator *)iterator)->index]);
    printf("Handle logical and phys size is (%d, %d)\n", ((Content *)handle)->logical_size, ((Content *)handle)->physical_size);
    printf("==================================\n");
        // Test dereferences
    test_iterator_position(LSQ_GetElementByIndex(handle, -1), -1);
    test_iterator_position(LSQ_GetElementByIndex(handle, 2), 2);
    test_iterator_position(LSQ_GetElementByIndex(handle, 3), 3);
    LSQ_InsertFrontElement(handle, 4);
    test_iterator_position(LSQ_GetElementByIndex(handle, 3), 3);
        // Get front element
    iterator = LSQ_GetFrontElement(handle);
    printf("Get front element %d\n", ((Iterator *)iterator)->content->data[((Iterator *)iterator)->index]);
        // Advance get last element (With LSQ_GetFrontElement and LSQ_RewindElement)
    iterator = LSQ_GetPastRearElement(handle);
    LSQ_RewindOneElement(iterator);
    printf("Get last element %d\n", ((Iterator *)iterator)->content->data[((Iterator *)iterator)->index]);
    printf("%f\n", GetFactor(handle));
    int i;
    Content *content;
    printf("==================================\n");
    printf("Adding elements\n");
    printf("==================================\n");
    for(i = 0; i < 1024; i++){
        content = (Content *)handle;
        LSQ_InsertRearElement(handle, i);
        if(i % 10 == 0)
            printf("Log and Phys (%d, %d). Delta %d. Factor %d\n", content->logical_size, content->physical_size, content->delta_size, (int)GetFactor(content));
    }
    printf("==================================\n");
    printf("Deleting elements\n");
    printf("==================================\n");
    for(i = 0; i < 1024; i++){
        content = (Content *)handle;
        LSQ_DeleteRearElement(handle);
        if(i % 10 == 0)
            printf("Log and Phys (%d, %d). Delta %d. Factor %d\n", content->logical_size, content->physical_size, content->delta_size, (int)GetFactor(content));
    }
    for(i = 0; i < 512 * 64; i++){
        LSQ_InsertRearElement(handle, i);
    }
    printf("%d %f\n", ((Content *)handle)->delta_size, GetFactor(handle));

    for(i = 0; i < 512 * 512; i++){
        LSQ_InsertRearElement(handle, i);
    }
    printf("%d %f\n", ((Content *)handle)->delta_size, GetFactor(handle));
    printf("==================================\n");
    return 0;
}
*/
