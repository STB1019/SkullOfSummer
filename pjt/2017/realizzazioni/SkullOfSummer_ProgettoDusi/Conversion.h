#ifndef CONVERSION_H_
#define CONVERSION_H_

#include "List.h"

arraylist* ul_convertToArrayList(ulinked_list* l);
arraylist* ul_copyToArrayList(ulinked_list* l, void* (*clone)(void*));
blinked_list* ul_convertToBlinkedList(ulinked_list* l);
blinked_list* ul_coptToBLinkedList(ulinked_list* l, void* (*clone)(void*));

ulinked_list* al_convertToULinkedList(arraylist* l);
ulinked_list* al_copyToULinkedList(arraylist* l, void* (*clone)(void*));
blinked_list* al_convertToBLinkedList(arraylist* l);
blinked_list* al_copyToBLinkedList(arraylist* l, void* (*clone)(void*));

ulinked_list* bl_convertToULinkedList(blinked_list* l);
ulinked_list* bl_copyToULinkedList(blinked_list* l, void* (*clone)(void*));
arraylist* bl_convertToArrayList(blinked_list* l);
arraylist* bl_copyToArrayList(blinked_list* l, void* (*clone)(void*));

#endif
