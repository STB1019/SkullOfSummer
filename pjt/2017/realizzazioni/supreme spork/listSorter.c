#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"
#include "stdbool.h"

#define BILLION 1000000000L

// void adjustLinks(list_element *first, list_element *second)
// {
//   list_element *tmpFirstPrev,*tmpFirstNext, *tmpSecondPrev, *tmpSecondNext;
//
//   // if(first->prev != NULL)
//   //   tmpFirstPrev = first->prev;
//   // else
//   //   tmpFirstPrev =NULL;        //sennò non posso fare =first->prev perchè è null
//   // if(first->next != NULL)
//   //   tmpFirstNext = first->next;
//   // else
//   //   tmpFirstNext = NULL;
//   // if(second->prev != NULL)
//   //   tmpSecondPrev = second->prev;
//   // else
//   //   tmpSecondPrev = NULL;
//   // if(second->next != NULL)
//   //   tmpSecondNext = second->next;
//   // else
//   //   tmpSecondNext = NULL;
//   //
//   // if(tmpFirstPrev != NULL)
//   //   first->prev->next = second;
//   // if(tmpSecondPrev != NULL)
//   //   second->prev->next = first;
//   // if(tmpFirstNext != NULL)
//   //   second->next = tmpFirstNext;
//   // else
//   //   second->next = NULL;
//   // if(tmpSecondNext != NULL)
//   //   first->next = tmpSecondNext;
//   // else
//   //   first->next = NULL;
//   //
//   // if(tmpSecondPrev != NULL)
//   //   first->prev = tmpSecondPrev;
//   // else
//   //   first->prev = NULL;
//   // if(tmpFirstPrev != NULL)
//   //   second->prev = tmpFirstPrev;
//   // else
//   //   second->prev = NULL;
//   // if(second->next != NULL)
//   //   second->next->prev = first;
//   // if(first->next != NULL)
//   //   first->next->prev = second;
//   //
//   tmpFirstPrev = first->prev;
//   tmpFirstNext = first->next;
//   tmpSecondPrev = second->prev;
//   tmpSecondNext = second->next;
//
//   first->prev->next = second;
//   second->prev->next = first;
//   second->next = tmpFirstNext;
//   first->next = tmpSecondNext;
//
//   first->prev = tmpSecondPrev;
//   second->prev = tmpFirstPrev;
//   second->next->prev = first;
//   first->next->prev = second;
// }

typedef struct list_element {
  unsigned long index;
  char label[10];
  struct list_element* prev;
  struct list_element* next;
} list_element;

typedef struct {
  list_element* head;
  list_element* tail;
  int size;
} list;

//dichiarazioni funzioni per non doverle definire in ordine dopo
list_element* create_element();
void create_label();
bool compare_label(char *str1, char *str2);
void create_list(int dimension, list *list);
void print_data(list_element *element, int pos);
void print_info(list *list);
bool has_to_swap(list_element *first, list_element *second);
void swap_fields(list_element *first, list_element *second);
void bubble_sort(list_element *head, list_element *tail);

int main(int argc, char const *argv[])
{
  srand(time(NULL));                               //può venire chiamato solo una volta
  int randDimension = ((rand() % 6001) + 3000);   //rand tra 3000 e 9000

  list list;
  list.size = randDimension;
  list.head = NULL;
  list.tail = NULL;

  create_list(randDimension, &list);
  printf("dimensione lista: %d\n\n", list.size);

  list_element *toPrint1 = list.head;
  int i = 0;
  while(toPrint1->next != NULL)
  {
    print_data(toPrint1, i);
    i++;
    toPrint1 = toPrint1->next;
  }
  print_data(list.tail, i);

  print_info(&list);

  // struct timespec {
  //         time_t   tv_sec;        /* seconds */
  //         long     tv_nsec;       /* nanoseconds */
  // };

  struct timespec beginning, end;
  clockid_t clk_id = CLOCK_MONOTONIC;
  int start_time = clock_gettime(clk_id, &beginning);

  bubble_sort(list.head, list.tail);

  int finish_time = clock_gettime(clk_id, &end);

  printf("first element: index = %lu | label = %s\n", list.head->index, list.head->label);
  printf("last element: index = %lu | label = %s\n", list.tail->index, list.tail->label);

  list_element *toPrint2 = list.head;
  i = 0;
  while(toPrint2->next != NULL)
  {
    print_data(toPrint2, i);
    i++;
    toPrint2 = toPrint2->next;
  }
  print_data(list.tail, i);

  print_info(&list);

  long int totNanoseconds = ((end.tv_sec - beginning.tv_sec)*BILLION) + (end.tv_nsec - beginning.tv_nsec);

  printf("\n~~~~~~~~~~~~~~~~~~~~~~~~TIME~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
  printf("Sorting time = %ld nanoseconds = %f seconds\n\n",totNanoseconds, (double)totNanoseconds/BILLION);

  return 0;
} //END MAIN

void create_list(int dimension, list *list)
{
  list_element *previous;

  for(int i = 0; i < dimension; i++)
  {
    list_element *element = create_element();
    if(i == 0)  //testa della lista
    {
      list->head = element;
      element->prev = NULL;  //head non ha prev
    }
    else if(i == dimension - 1) //coda della lista
    {
      list->tail = element;
      element->next = NULL;  //tail non ha next
      element->prev = previous;  //il suo prev è quello creato prima
      previous->next = element;  //l'elemento diventa il next di quello creato prima
    }
    else
    {
      element->prev = previous;  //il suo prev è quello creato prima
      previous->next = element;  //l'elemento diventa il next di quello creato prima
    }
    previous = element;  //salvo questo elemento per farlo diventare il prev di quello che creo dopo
  }
}

char stringa[10];   //todo: rimuovere variabile globale
void create_label()
{
  for (int i = 0; i < 10; i++)
  {
    stringa[i] = (char)((rand()%25)+97); //da 97 a 122: char in ascii
  }
}

list_element* create_element()
{
  list_element *new_element = malloc(sizeof(list_element));
  new_element->index = rand()%1000;             //index tra 0 e 999
  create_label();
  strcpy(new_element->label, stringa);
  new_element->prev = NULL;                    //li crea senza i puntatori a next e prev
  new_element->next = NULL;

  return new_element;
}

void print_data(list_element *element, int pos)
{
  printf("          ELEMENT %d\n", pos);
  pos++;
  printf("index: %lu  | label: %s\n", element->index, element->label);
  if(element->prev == NULL)
    printf("(prev -> index: NULL | label: NULL)\n");
  else
    printf("(prev -> index: %lu | label: %s)\n", element->prev->index, element->prev->label);
  if(element->next == NULL)
    printf("(next -> index: NULL | label: NULL)\n");
  else
  {
    printf("(next -> index: %lu | label: %s)\n\n", element->next->index, element->next->label);
    printf("              ^ | \n");
    printf("              | v \n\n");
  }
}

void print_info(list *list)
{
  printf("\n~~~~~~~~~~~~~~~~~~~~~~LIST_INFO~~~~~~~~~~~~~~~~~~~~~~\n\n");
  printf("head -> index: %lu  | label: %s\n", list->head->index, list->head->label);
  printf("tail -> index: %lu  | label: %s\n", list->tail->index, list->tail->label);
  printf("size = %d\n", list->size);

}
void bubble_sort(list_element *head, list_element *tail)
{
  list_element *last = tail;
  while(head->next != NULL)
  {
    tail = last;  //faccio tornare tail in fondo
    while(tail != head)
    {
      if(has_to_swap(head, tail))
        swap_fields(head, tail);
      tail = tail->prev;
    }
    head = head->next;
  }
}

void swap_fields(list_element *first, list_element *second)
{
  int tmpIndex;
  char *tmpLabel = malloc(strlen(first->label)+1);

  tmpIndex = first->index;
  first->index = second->index;
  second->index = tmpIndex;

  strcpy(tmpLabel, first->label);
  strcpy(first->label, second->label);
  strcpy(second->label,tmpLabel);

  free(tmpLabel);
}

bool has_to_swap(list_element *first, list_element *second)
//swappa se il primo è maggiore
{
  if(first->index > second->index)
  {
    return true;
  }
  else if(first->index == second->index)
  {
    if(!compare_label(first->label, second->label))
      return true;
    else
      return false;
  }
  else
    return false;
}

bool compare_label(char *str1, char *str2)
//true se prima stringa è "minore" della seconda
{
  for(int i = 0; i < 10; i++)
  {
    if(str1[i] < str2[i]) //appena 2 caratteri sono diversi controlla qual è il maggiore
      return true;
    if(str1[i] > str2[i])
      return false;
  }
  return true; //se i caratteri sono tutti uguali return true
}
