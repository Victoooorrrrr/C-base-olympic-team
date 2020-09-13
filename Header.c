#include <stdio.h> 
#include "Header.h"
#include <string.h>
#include <ctype.h>
#include <io.h>
#include <malloc.h>
#pragma warning(disable : 4996)
#define filename "file_basa.txt"

int checkstr(char *str)
{
  for (unsigned int i = 0; i < strlen(str); i++)  
  if ((isspace(str[i]) == 0) && (isalpha(str[i]) == 0))
  {
    printf("Ошибка! В строке имеются недопустимые символы.\n");
    return -1;
  }
  return 0;
}

int input()
{
  FILE *f = fopen(filename, "wb"); 
  Sportakus sport;
  int n, sc;

  if (!f)
  {
    printf("Ошибка создания файла.\n");
    return -1;
  }

  printf("\nВведите количество спортсменов: ");
  sc = scanf("%d", &n);
  while ((sc != 1) || (n <= 0)) // Проверка на корректный ввод количества
  {
    printf("Ошибка! Введена не цифра/некорректное количество. Введите число заново:\n");
    sc = scanf("%d", &n);
  }

  for (int i = 0; i < n; i++)
  {
    rewind(stdin);
    printf("\nВведите данные %d-го спортсмена:\n", i + 1);
    printf("ФИО: ");
    gets(sport.fio);
    if (checkstr(sport.fio) == -1) // Проверка корректности введенной строки
    {
      fclose(f);
      return -1;
    }
    printf("Вид спорта: ");
    gets(sport.sport);
    if (checkstr(sport.sport) == -1)  // Проверка корректности введенной строки
    {
      fclose(f);
      return -1;
    }
    printf("Характеристика спортсмена: ");
    gets(sport.charact);
    if (checkstr(sport.charact) == -1)  // Проверка корректности введенной строки
    {
      fclose(f);
      return -1;
    }
    printf("Вес: ");
    if (scanf("%d", &sport.weight) != 1 || sport.weight <= 0)
    {
      printf("Ошибка! Введена не цифра/некорректное значение.\n");
      fclose(f);
      return -1;
    }
    printf("Рост: ");
    if (scanf("%d", &sport.growth) != 1 || sport.growth <= 0)
    {
      printf("Ошибка! Введена не цифра/некорректное значение.\n");
      fclose(f);
      return -1;
    }
    printf("Год рождения: ");
    // Проверка корректности ввода года рождения и самого года
    if (scanf("%d", &sport.year) != 1 || sport.year <= 0 || sport.year > 2019)
    {
      printf("Ошибка! Введена не цифра/некорректное значение.\n");
      fclose(f);
      return -1;
    }
    fwrite(&sport, sizeof(Sportakus), 1, f); // Записываем данные  в файл
  }

  printf("\nБаза данных сборной успешно заполнена.\n\n");
  fclose(f);
}

int add() // Добавление записи в базу
{
  FILE *f = fopen(filename, "ab"); // Открываем файл на дозапись
  Sportakus sport;

  if (!f)
  {
    printf("Ошибка открытия файла.\n");
    return -1;
  }

  rewind(stdin);
  printf("Введите данные нового спортсмена:\n");
  printf("ФИО: ");
  gets(sport.fio);
  if (checkstr(sport.fio) == -1) // Проверка корректности введенной строки
  {
    fclose(f);
    return -1;
  }
  printf("Вид спорта: ");
  gets(sport.sport);
  if (checkstr(sport.sport) == -1)  // Проверка корректности введенной строки
  {
    fclose(f);
    return -1;
  }
  printf("Характеристика: ");
  gets(sport.charact);
  if (checkstr(sport.charact) == -1)  // Проверка корректности введенной строки
  {
    fclose(f);
    return -1;
  }
  printf("Вес: ");
  if (scanf("%d", &sport.weight) != 1 || sport.weight <= 0)
  {
    printf("Ошибка! Введена не цифра/некорректное значение.\n");
    fclose(f);
    return -1;
  }
  printf("Рост: ");
  if (scanf("%d", &sport.growth) != 1 || sport.growth <= 0)
  {
    printf("Ошибка! Введена не цифра/некорректное значение.\n");
    fclose(f);
    return -1;
  }
  printf("Год рождения: ");
  // Проверка корректности ввода года рождения и самого года
  if (scanf("%d", &sport.year) != 1 || sport.year <= 0 || sport.year > 2019)
  {
    printf("Ошибка! Введена не цифра/некорректное значение.\n");
    fclose(f);
    return -1;
  }
  fwrite(&sport, sizeof(Sportakus), 1, f); // Записываем новые данные
  printf("\nЗапись добавлена в базу данных.\n\n");
  fclose(f);
}

int delete() // Удаление заданной записи из базы
{
  FILE *f = fopen(filename, "r+b");
  Sportakus sport;
  int index, size;
  rewind(stdin);
  if (!f)
  {
    printf("Ошибка открытия файла.\n");
    return -1;
  }

  printf("Введите номер спортсмена, данные которого будут удалены: ");
  if (scanf("%d", &index) != 1)
  {
    printf("Ошибка! Введена не цифра.\n");
    fclose(f);
    return -1;
  }

  fseek(f, 0, SEEK_END);
  size = ftell(f) / sizeof(Sportakus); // Считаем кол-во записей в базе
  while (index > size || index <= 0) // Проверка, есть ли в базе запись с данным номером
  {
    printf("В базе нет спортсмена с номером %d, введите еще раз:\n", index);
    if (scanf("%d", &index) != 1)
    {
      printf("Ошибка! Введена не цифра.\n");
      fclose(f);
      return -1;
    }
  }

  for (int i = index - 1; i < size - 1; i++) // Изначально встаем перед элементом, который надо удалить
  {
    fseek(f, (i + 1) * sizeof(Sportakus), SEEK_SET);
    fread(&sport, sizeof(Sportakus), 1, f); // Считываем следующий элемент
    fseek(f, i * sizeof(Sportakus), SEEK_SET); // Возвращаемся назад
    fwrite(&sport, sizeof(Sportakus), 1, f); // Записываем следующий элемент вместо текущего
  }
  chsize(fileno(f), (size - 1) * sizeof(Sportakus)); // Уменьшаем размер файла
  printf("Запись удалена.\n\n");
  fclose(f);
}

int search() // Поиск записи по заданному полю
{
  FILE *f = fopen(filename, "rb");
  Sportakus sport;
  int pole, i, check, num;
  char str[20];

  if (!f)
  {
    printf("Ошибка открытия файла.\n");
    return -1;
  }

  printf("Выберите поле, по которому хотите искать:\n");
  printf("1. ФИО\n");
  printf("2. Вид спорта\n");
  printf("3. Характеристика\n");
  printf("4. Вес\n");
  printf("5. Рост\n");
  printf("6. Год рождения\n");
  printf("Ваш выбор: ");
  if (scanf("%d", &pole) != 1)
  {
    printf("Ошибка! Введена не цифра.\n");
    fclose(f);
    return -1;
  }
  rewind(stdin);
  switch (pole)
  {
  case 1:
  {
          i = 1;
          check = 0;
          printf("Введите ФИО: ");
          gets(str);
          printf("Найденные спортсмены:\n");
          printf("__________________________________________________________________________________________________\n");
          printf("|   |                      |               |                |          |       |                  |\n");
          printf("| № |         ФИО          |   Вид спорта  | Характеристика |    Вес   |  Рост |   Год рождения   |\n");
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          while (!feof(f)) // Пока не конец файла
          {
            fread(&sport, sizeof(Sportakus), 1, f);
            if (!feof(f) && !strcmp(sport.fio, str)) // Если найдно совпадение
            {
              printf("|%-3d|%-22s|%-15s|%-16s|%-10d|%-7d|%-18d|\n", i, sport.fio, sport.sport, sport.charact, sport.weight, sport.growth, sport.year);
              i++;
              check = 1;
            }
          }
          if (check == 0)
          {
            printf("Совпадений нет.\n");
            break;
          }
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          printf("\n");
          break;
  }
  case 2:
  {
          i = 1;
          check = 0;
          printf("Введите вид спорта: ");
          gets(str);
          printf("Найденные спортсмены:\n");
          printf("__________________________________________________________________________________________________\n");
          printf("|   |                      |               |                |          |       |                  |\n");
          printf("| № |         ФИО          |   Вид спорта  | Характеристика |    Вес   |  Рост |   Год рождения   |\n");
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          while (!feof(f)) // Пока не конец файла
          {
            fread(&sport, sizeof(Sportakus), 1, f);
            if (!feof(f) && !strcmp(sport.sport, str))
            {
              printf("|%-3d|%-22s|%-15s|%-16s|%-10d|%-7d|%-18d|\n", i, sport.fio, sport.sport, sport.charact, sport.weight, sport.growth, sport.year);
              i++;
              check = 1;
            }
          }
          if (check == 0)
          {
            printf("Совпадений нет.\n");
            break;
          }
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          printf("\n");
          break;
  }
  case 3:
  {
          i = 1;
          check = 0;
          printf("Введите характеристику: ");
          gets(str);
          printf("Найденные спортсмены:\n");
          printf("__________________________________________________________________________________________________\n");
          printf("|   |                      |               |                |          |       |                  |\n");
          printf("| № |         ФИО          |   Вид спорта  | Характеристика |    Вес   |  Рост |   Год рождения   |\n");
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          while (!feof(f)) // Пока не конец файла
          {
            fread(&sport, sizeof(Sportakus), 1, f);
            if (!feof(f) && !strcmp(sport.charact, str))
            {
              printf("|%-3d|%-22s|%-15s|%-16s|%-10d|%-7d|%-18d|\n", i, sport.fio, sport.sport, sport.charact, sport.weight, sport.growth, sport.year);
              i++;
              check = 1;
            }
          }
          if (check == 0)
          {
            printf("Совпадений нет.\n");
            break;
          }
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          printf("\n");
          break;
  }
  case 4:
  {
          i = 1;
          check = 0;
          printf("Введите вес: ");
          if (scanf("%d", &num) != 1)
          {
            printf("Ошибка! Введена не цифра.\n");
            break;
          }
          printf("Найденные спортсмены:\n");
          printf("__________________________________________________________________________________________________\n");
          printf("|   |                      |               |                |          |       |                  |\n");
          printf("| № |         ФИО          |   Вид спорта  | Характеристика |    Вес   |  Рост |   Год рождения   |\n");
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          while (!feof(f)) // Пока не конец файла
          {
            fread(&sport, sizeof(Sportakus), 1, f);
            if (!feof(f) && sport.weight == num)
            {
              printf("|%-3d|%-22s|%-15s|%-16s|%-10d|%-7d|%-18d|\n", i, sport.fio, sport.sport, sport.charact, sport.weight, sport.growth, sport.year);
              i++;
              check = 1;
            }
          }
          if (check == 0)
          {
            printf("Совпадений нет.\n");
            break;
          }
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          printf("\n");
          break;
  }
  case 5:
  {
          i = 1;
          check = 0;
          printf("Введите рост: ");
          if (scanf("%d", &num) != 1)
          {
            printf("Ошибка! Введена не цифра.\n");
            break;
          }
          printf("Найденные спортсмены:\n");
          printf("__________________________________________________________________________________________________\n");
          printf("|   |                      |               |                |          |       |                  |\n");
          printf("| № |         ФИО          |   Вид спорта  | Характеристика |    Вес   |  Рост |   Год рождения   |\n");
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          while (!feof(f)) // Пока не конец файла
          {
            fread(&sport, sizeof(Sportakus), 1, f);
            if (!feof(f) && sport.growth == num)
            {
              printf("|%-3d|%-22s|%-15s|%-16s|%-10d|%-7d|%-18d|\n", i, sport.fio, sport.sport, sport.charact, sport.weight, sport.growth, sport.year);
              i++;
              check = 1;
            }
          }
          if (check == 0)
          {
            printf("Совпадений нет.\n");
            break;
          }
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          printf("\n");
          break;
  }
  case 6:
  {
          i = 1;
          check = 0;
          printf("Введите год рождения: ");
          if (scanf("%d", &num) != 1)
          {
            printf("Ошибка! Введена не цифра.\n");
            break;
          }
          printf("Найденные спортсмены:\n");
          printf("__________________________________________________________________________________________________\n");
          printf("|   |                      |               |                |          |       |                  |\n");
          printf("| № |         ФИО          |   Вид спорта  | Характеристика |    Вес   |  Рост |   Год рождения   |\n");
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          while (!feof(f)) // Пока не конец файла
          {
            fread(&sport, sizeof(Sportakus), 1, f);
            if (!feof(f) && sport.year == num)
            {
              printf("|%-3d|%-22s|%-15s|%-16s|%-10d|%-7d|%-18d|\n", i, sport.fio, sport.sport, sport.charact, sport.weight, sport.growth, sport.year);
              i++;
              check = 1;
            }
          }
          if (check == 0)
          {
            printf("Совпадений нет.\n");
            break;
          }
          printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
          printf("\n");
          break;
  }
  default:
    printf("Ошибка! Такого поля нет.\n");
    break;
  }
  fclose(f);
}

int change() // Редактирование заданной записи в базе
{
  FILE *f = fopen(filename, "r+b");
  Sportakus sport;
  int index, size, pole;

  if (!f)
  {
    printf("Ошибка открытия файла.\n");
    return -1;
  }

  printf("Введите номер спортсмена, данные которого будут изменены: ");
  if (scanf("%d", &index) != 1)
  {
    printf("Ошибка! Введена не цифра.\n");
    fclose(f);
    return -1;
  }

  fseek(f, 0, SEEK_END);
  size = ftell(f) / sizeof(Sportakus); // Считаем кол-во записей в базе
  while (index > size || index <= 0) // Проверка, есть ли в базе запись с данным номером
  {
    printf("В базе нет спортсмена с номером %d, введите еще раз:\n", index);
    if (scanf("%d", &index) != 1 || index <= 0)
    {
      printf("Ошибка! Введена не цифра.\n");
      fclose(f);
      return -1;
    }
  }

  printf("Укажите поле, которое хотите отредактировать: \n");
  printf("1. ФИО\n");
  printf("2. Вид спорта\n");
  printf("3. Характеристика\n");
  printf("4. Вес\n");
  printf("5. Рост\n");
  printf("6. Год рождения\n");
  printf("Ваш выбор: ");
  if (scanf("%d", &pole) != 1)
  {
    printf("Ошибка! Введена не цифра.\n");
    fclose(f);
    return -1;
  }

  fseek(f, (index - 1) * sizeof(Sportakus), SEEK_SET); //Смещаемся на нужную запись
  fread(&sport, 1, sizeof(Sportakus), f);
  printf("Введите новое значение поля: \n");
  rewind(stdin);

  switch (pole)
  {
  case 1:
  {
          gets(sport.fio);
          if (checkstr(sport.fio) == -1) // Проверка корректности введенной строки
          {
            fclose(f);
            return -1;
          }
          break;
  }
  case 2:
  {
          gets(sport.sport);
          if (checkstr(sport.sport) == -1)  // Проверка корректности введенной строки
          {
            fclose(f);
            return -1;
          }
          break;
  }
  case 3:
  {
          gets(sport.charact);
          if (checkstr(sport.charact) == -1)  // Проверка корректности введенной строки
          {
            fclose(f);
            return -1;
          }
          break;
  }
  case 4:
  {
          if (scanf("%d", &sport.weight) != 1 || sport.weight <= 0)
          {
            printf("Ошибка! Введена не цифра/некорректное значение.\n");
            fclose(f);
            return -1;
          }
          break;
  }
  case 5:
  {
          if (scanf("%d", &sport.growth) != 1 || sport.growth <= 0)
          {
            printf("Ошибка! Введена не цифра/некорректное значение.\n");
            fclose(f);
            return -1;
          }
          break;
  }
  case 6:
  {
          if (scanf("%d", &sport.year) != 1 || sport.year <= 0 || sport.year > 2019)
          {
            printf("Ошибка! Введена не цифра/некорректное значение.\n");
            fclose(f);
            return -1;
          }
          break;
  }
  default:
    printf("Ошибка! Такого поля нет.\n");
    break;
  }
  fseek(f, (index - 1) * sizeof(Sportakus), SEEK_SET);
  fwrite(&sport, sizeof(Sportakus), 1, f); //Записываем изменную запись в файл 
  printf("Запись успешно изменена.\n");
  fclose(f);
}

int sort() // Сортировка данных в базе по заданному полю
{
  FILE *f = fopen(filename, "r+b");
  int i, j, k, size, pole;

  fseek(f, 0, SEEK_END);
  size = ftell(f) / sizeof(Sportakus); // Считаем кол-во записей в базе
  fseek(f, 0, SEEK_SET);

  Sportakus *sport = (Sportakus*)malloc(size * sizeof(Sportakus)); // Массив структур
  Sportakus tmp;

  if (!f)
  {
    printf("Ошибка открытия файла.\n");
    return -1;
  }

  for (i = 0; i < size; i++)
    fread(&sport[i], sizeof(Sportakus), 1, f);

  printf("Укажите поле, которое хотите отсортировать:\n");
  printf("1. ФИО\n");
  printf("2. Вид спорта\n");
  printf("3. Характеристика\n");
  printf("4. Вес\n");
  printf("5. Рост\n");
  printf("6. Год рождения\n");
  printf("Ваш выбор: ");
  if (scanf("%d", &pole) != 1)
  {
    printf("Ошибка! Введена не цифра.\n");
    fclose(f);
    return -1;
  }

  switch (pole)
  {
  case 1:
  {
          printf("1. По алфавиту\n2. В обратном порядке алфавита\nВаш выбор: ");
          scanf("%d", &k);
          printf("\n");
          switch (k)
          {
          case 1:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (strcmp(sport[j].fio, sport[j + 1].fio) > 0)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          case 2:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (strcmp(sport[j].fio, sport[j + 1].fio) < 0)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          default:
            printf("Ошибка! Такого варианта нет.\n");
            break;
          }
          break;
  }
  case 2:
  {
          printf("1. По алфавиту\n2. В обратном порядке алфавита\nВаш выбор: ");
          scanf("%d", &k);
          printf("\n");
          switch (k)
          {
          case 1:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (strcmp(sport[j].sport, sport[j + 1].sport) > 0)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          case 2:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (strcmp(sport[j].sport, sport[j + 1].sport) < 0)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          default:
            printf("Ошибка! Такого варианта нет.\n");
            break;
          }
          break;
  }
  case 3:
  {
          printf("1. По алфавиту\n2. В обратном порядке алфавита\nВаш выбор: ");
          scanf("%d", &k);
          printf("\n");
          switch (k)
          {
          case 1:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (strcmp(sport[j].charact, sport[j + 1].charact) > 0)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          case 2:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (strcmp(sport[j].charact, sport[j + 1].charact) < 0)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          default:
            printf("Ошибка! Такого варианта нет.\n");
            break;
          }
          break;
  }
  case 4:
  {
          printf("1. По возрастанию\n2. По убывыанию\nВаш выбор: ");
          scanf("%d", &k);
          printf("\n");
          switch (k)
          {
          case 1:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (sport[j].weight > sport[j + 1].weight)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          case 2:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (sport[j].weight < sport[j + 1].weight)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          default:
            printf("Ошибка! Такого варианта нет.\n");
            break;
          }
          break;
  }
  case 5:
  {
          printf("1. По возрастанию\n2. По убывыанию\nВаш выбор: ");
          scanf("%d", &k);
          printf("\n");
          switch (k)
          {
          case 1:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (sport[j].growth > sport[j + 1].growth)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          case 2:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (sport[j].growth < sport[j + 1].growth)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          default:
            printf("Ошибка! Такого варианта нет.\n");
            break;
          }
          break;
  }
  case 6:
  {
          printf("1. По возрастанию\n2. По убывыанию\nВаш выбор: ");
          scanf("%d", &k);
          printf("\n");
          switch (k)
          {
          case 1:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (sport[j].year > sport[j + 1].year)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          case 2:
            for (i = size - 1; i >= 0; i--)
            {
              for (j = 0; j < i; j++)
              {
                if (sport[j].year < sport[j + 1].year)
                {
                  tmp = sport[j];
                  sport[j] = sport[j + 1];
                  sport[j + 1] = tmp;
                }
              }
            }
            break;
          default:
            printf("Ошибка! Такого варианта нет.\n");
            break;
          }
          break;
  }
  default:
    printf("Ошибка! Такого поля нет.\n");
    break;
  }

  fseek(f, 0, SEEK_SET);
  for (i = 0; i < size; i++)
    fwrite(&sport[i], sizeof(Sportakus), 1, f);
  free(sport);
  fclose(f);
}

int output() // Вывод на экран содержимого базы
{
  FILE *f = fopen(filename, "rb"); // Открываем файл на чтение
  Sportakus sport;
  int i = 1;

  if (!f)
  {
    printf("Ошибка открытия файла.\n");
    return -1;
  }

  printf("База данных:\n");
  printf("__________________________________________________________________________________________________\n");
  printf("|   |                      |               |                |          |       |                  |\n");
  printf("| № |         ФИО          |   Вид спорта  | Характеристика |    Вес   |  Рост |   Год рождения   |\n");
  printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");

  while (!feof(f))
  {
    fread(&sport, sizeof(Sportakus), 1, f);
    if (!feof(f))
    {
      printf("|%-3d|%-22s|%-15s|%-16s|%-10d|%-7d|%-18d|\n", i, sport.fio, sport.sport, sport.charact, sport.weight, sport.growth, sport.year);
      i++;
    }
  }

  printf("|___|______________________|_______________|________________|__________|_______|__________________|\n");
  printf("\n");
  fclose(f);
}
