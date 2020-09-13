#pragma once
typedef struct
{
  char fio[20];
  char sport[20];
  char charact[20];
  int weight; 
  int growth; 
  int year; 
} Sportakus; // name of structure

int checkstr(char *str); 
int input(); 
int add(); 
int delete(); 
int search();
int change();
int sort(); 
int output(); 
