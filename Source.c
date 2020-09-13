#include <stdio.h> 
#include "Header.h"
#include <locale.h>
#include <malloc.h> 
int main()
{
  int choice, check = 0;
  setlocale(LC_ALL, "rus");

  printf("Меню:\n");
  printf("1. Заполнение базы данных.\n");
  printf("2. Добавление записи в базу.\n");
  printf("3. Удаление заданной записи из базы.\n");
  printf("4. Поиск записи по заданному полю.\n");
  printf("5. Редактирование заданной записи в базе\n");
  printf("6. Сортировка данных в базе по заданному полю.\n");
  printf("7. Вывод на экран содержимого базы.\n");
  printf("0. Выход из программы.\n\n");

  while (check == 0)
  {
    printf("Введите ваш выбор: ");
    if (scanf("%d", &choice) != 1)
    {
      system("pause");
      printf("Ошибка! Введена не цифра.\n");
      return -1;
    }

    switch (choice)
    {
    case 1:
      input();
      break;

    case 2:
      add();
      break;

    case 3:
      delete();
      break;

    case 4:
      search();
      break;

    case 5:
      change();
      break;

    case 6:
      sort();
      break;

    case 7:
      output();
      break;

    case 0:
      check = 1;
      break;

    default:
      printf("Ошибка выбора позции меню!\n");
      break;
    }
  }

  system("pause");
  return 0;
}
