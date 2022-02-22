/**
* Модуль тестирования основных функций библиотеки
* @author XHermit <xhermitone@gmail.com>
* @file
* @version 0.0.0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <malloc.h>
#include <getopt.h>
#include <assert.h>

#include "ext_types.h"
#include "toolfunc.h"
#include "filefunc.h"
#include "logfunc.h"
#include "strfunc.h"

/**
* Режим отладки
*/
BOOL DebugMode = TRUE;

BOOL test_str_upper()
{
    BOOL result;
    
    char *text_value = (char *)calloc(strlen("latin Text") + 1, sizeof(char));
    char *text = NULL;
    
    strcpy(text_value, "latin Text");
    text = str_upper_lat(text_value);
    print_color_txt(GREEN_COLOR_TEXT, "Латинский текст в верхнем регистре: %s : %s\n", text, text_value);
    result = (strcmp("LATIN TEXT", text) == 0);
    print_test(result, "Привести строку к верхнему регистру");

    destroy_and_null_str(text_value);
    text = NULL;

    return result;
}

BOOL test_str_lower()
{
    BOOL result;

    char *text_value = (char *)calloc(strlen("LatiN Text") + 1, sizeof(char));
    char *text = NULL;

    strcpy(text_value, "LatiN Text");
    text = str_lower_lat(text_value);
    print_color_txt(GREEN_COLOR_TEXT, "Латинский текст в нижнем регистре: %s : %s\n", text, text_value);
    result = (strcmp("latin text", text) == 0);
    print_test(result, "Привести строку к нижнему регистру");

    destroy_and_null_str(text_value);
    text = NULL;

    return result;
}

BOOL test_str_trim()
{
    BOOL result;

    char *text_value = (char *)calloc(strlen("  \t latin Text\t\t   ") + 1, sizeof(char));
    char *text = NULL;

    strcpy(text_value, "  \t latin Text\t\t   ");
    text = str_trim(text_value);
    print_color_txt(GREEN_COLOR_TEXT, "Удаление начальных и завершающих пробелов из строки: <%s> : <%s>\n", text, text_value);
    result = strcmp("latin Text", text) == 0;
    print_test(result, "Удаление начальных и завершающих пробелов из строки");

    destroy_and_null_str(text_value);
    text = NULL;

    return result;
}

BOOL test_str_replace_char_idx()
{
    BOOL result;

    char *text_value = (char *)calloc(strlen("latin Text") + 1, sizeof(char));
    char *text = NULL;

    strcpy(text_value, "latin Text");
    text = str_replace_char_idx(text_value, 4, '*');
    print_color_txt(GREEN_COLOR_TEXT, "Заменить символ с номером char_index на new_char в строке: <%s> : <%s>\n", text, text_value);
    result = (strcmp("lati* Text", text) == 0);
    print_test(result, "Заменить символ с номером char_index на new_char в строке");

    destroy_and_null_str(text_value);
    text = NULL;

    return result;
}

BOOL test_create_str_replace()
{
    BOOL result;

    char *text_value = (char *)calloc(strlen("latin Text") + 1, sizeof(char));
    char *text = NULL;

    strcpy(text_value, "latin Text");
    text = create_str_replace(text_value, "latin", "LAT");
    print_color_txt(GREEN_COLOR_TEXT, "Произвести замену в строке: <%s> : <%s>\n", text, text_value);
    result = (strcmp("LAT Text", text) == 0);
    print_test(result, "Произвести замену в строке");

    destroy_and_null_str(text);
    destroy_and_null_str(text_value);
    return result;
}

BOOL test_is_str_empty()
{
    BOOL result1, result2;

    result1 = (is_str_empty("---") == FALSE);
    print_test(result1, "1. Проверка на пустую строку");
    result2 = (is_str_empty("") == TRUE);
    print_test(result2, "2. Проверка на пустую строку");
    return result1 && result2;
}

BOOL test_create_str_replace_all()
{
    BOOL result;
    nix_search_replace_t *replaces = (nix_search_replace_t *) calloc(3, sizeof(nix_search_replace_t));
    char *text = NULL;

    (*replaces).search = "lat";
    (*replaces).replace = "LAT";
    (*(replaces+1)).search = "text";
    (*(replaces+1)).replace = "string";
    (*(replaces+2)).search = " ";
    (*(replaces+2)).replace = "___";

    text = create_str_replace_all("latin text", replaces);
    print_color_txt(GREEN_COLOR_TEXT, "Произвести все замены в строке: <%s>\n", text);
    result = (strcmp(text, "LATin___string") == 0);
    print_test(result, "Произвести все замены в строке");

    free(replaces);
    destroy_and_null_str(text);

    return result;
}

BOOL test_str_printf()
{
    BOOL result;
    int i = 100;
    char text[100];

    str_printf(text, "Test: %d", i);

    print_color_txt(GREEN_COLOR_TEXT, "Форматированный вывод в строку: <%s>\n", text);
    result = (strcmp(text, "Test: 100") == 0);
    print_test(result, "Форматированный вывод в строку");

    return result;
}

BOOL test_create_str_printf()
{
    BOOL result;

    int i = 100;
    char *text = NULL;

    text = create_str_printf("Test: %d", i);

    print_color_txt(GREEN_COLOR_TEXT, "Форматированный вывод в новую строку: <%s>\n", text);
    result = (strcmp(text, "Test: 100") == 0);
    print_test(result, "Форматированный вывод в новую строку");

    destroy_and_null_str(text);

    return result;
}

BOOL test_create_substr()
{
    BOOL result;
    char *text = NULL;

    text = create_substr("Test string", 5, 3);

    print_color_txt(GREEN_COLOR_TEXT, "It returns a pointer to the substring: <%s>\n", text);
    result = (strcmp(text, "str") == 0);
    print_test(result, "It returns a pointer to the substring");

    destroy_and_null_str(text);

    return result;
}

BOOL test_create_str_begin()
{
    BOOL result;
    char *text = NULL;

    text = create_str_begin("Test string", 4);

    print_color_txt(GREEN_COLOR_TEXT, "Взять length символов с начала строки: <%s>\n", text);
    result = (strcmp(text, "Test") == 0);
    print_test(result, "Взять length символов с начала строки");

    destroy_and_null_str(text);

    return result;
}

BOOL test_create_str_end()
{
    BOOL result;
    char *text = NULL;

    text = create_str_end("String Test", 4);

    print_color_txt(GREEN_COLOR_TEXT, "Взять length символов с конца строки: <%s>\n", text);
    result = (strcmp(text, "Test") == 0);
    print_test(result, "Взять length символов с конца строки");

    destroy_and_null_str(text);

    return result;
}

BOOL test_create_str_clone()
{
    BOOL result;
    char *text = NULL;

    text = create_str_clone("Test");

    print_color_txt(GREEN_COLOR_TEXT, "Создать копию строки: <%s>\n", text);
    result = (strcmp(text, "Test") == 0);
    print_test(result, "Создать копию строки");

    destroy_and_null_str(text);

    return result;
}

BOOL test_str_copy_limit()
{
    BOOL result;
    char *text_value = (char *)calloc(strlen("latin Text") + 1, sizeof(char));
    char *text = (char *)calloc(strlen("latin") + 1, sizeof(char));

    strcpy(text_value, "latin Text");

    str_copy_limit(text_value, text, 5);
    print_color_txt(GREEN_COLOR_TEXT, "Скопировать строку в другую с ограничением длины: <%s>\n", text);
    result = (strcmp(text, "latin") == 0);
    print_test(result, "Скопировать строку в другую с ограничением длины");

    destroy_and_null_str(text);
    destroy_and_null_str(text_value);

    return result;

}

int main(int argc, char **argv)
{
    int result = 0;
    time_t start_seconds = time(NULL);
    time_t stop_seconds;

    print_color_txt(CYAN_COLOR_TEXT, "Запуск процедуры тестирования функций ...\n");

    // Тестирование функций вывода версии
    print_test(print_version() == TRUE, "Вывод на печать версии программы");
    print_test(print_help() == TRUE, "Вывод на печать помощи");
    print_test(print_system_info() == TRUE, "Вывод на печать информации о системе");

    // Тестирование функций работы с файлами
    char *home_path = getenv("HOME");
    print_color_txt(GREEN_COLOR_TEXT, "Домашняя директория: %s : %s\n", home_path, get_home_path());
    print_test(strcmp(get_home_path(), home_path) == 0, "Получить путь к домашней директории");

    char * profile_path = get_profile_path();
    print_color_txt(GREEN_COLOR_TEXT, "Директория профиля: %s\n", profile_path);
    print_test(profile_path != NULL, "Получить путь к директории профиля");

    //Тестирование функций логирования
    nix_log_t *log = open_log(NULL);
    print_test(log != NULL, "Открытие лога");
    print_test(close_log(log) == TRUE, "Закрытие лога");
    print_test(delete_log(NULL) == TRUE, "Удаление лога");

    // Тестирование функций работы со строками
    test_str_upper();
    test_str_lower();
    test_str_trim();
    test_str_replace_char_idx();
    test_create_str_replace();
    test_is_str_empty();
    test_create_str_replace_all();
    test_str_printf();
    test_create_str_printf();
    test_create_substr();
    test_create_str_begin();
    test_create_str_end();
    test_create_str_clone();
    test_str_copy_limit();

    //Тестирование дополнительных функций


    stop_seconds = time(NULL);
    print_color_txt(CYAN_COLOR_TEXT, "... Останов процедуры тестирования функций [%ld сек.]\n", stop_seconds - start_seconds);
    return result;
}