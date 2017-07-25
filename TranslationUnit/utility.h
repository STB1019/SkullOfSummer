#ifndef UTILITY_H
#define UTILITY_H

 //int unused_global_variable = 5;
 char buffer[] = "                                                    ";
 typedef struct {
     char* nome;
     char* cognome;
     int eta;
 } foo;

 char* getStringOfFoo(foo f);
 #endif
