//! @file
//! \brief Программа сортирует в лексикографическом порядке письмо Онегина Татьяне
//! @mainpage
//-----------------------------------------------------------------------------------------------------------------
//! \author     TheCompiler
//! \version    alpha 2
//! \date       11.09.2019
//=================================================================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



namespace ForVectorOfStrings {

//-----------------------------------------------------------------------------------------------------------------
//! \brief Находит длину строки
//!
//! \param[in] str      строка, длину которой надо узнать
//!
//! \return размер строки
//!
//-----------------------------------------------------------------------------------------------------------------

    static size_t len (const char* str);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Копирует строку из одной в другую
//!
//! \param[out] destination     строка, в которую копируют
//! \param[in]  source          строка, которую копируют
//!
//-----------------------------------------------------------------------------------------------------------------

    static void strcpy (char* str1, char* str2);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Читает строку из потока
//!
//! \param[in]  fp          дескриптор потока откуда читаем
//! \param[out] buffer      буфер для записи результата
//! \param[in]  sizeBuffer  максимальный размер считываемой строки
//!
//! \return длина считанной строки
//!
//-----------------------------------------------------------------------------------------------------------------

    static size_t getline (FILE* fp, char* buffer, size_t  sizeBuffer);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Меняет два элемента в векторе местами
//!
//! \param[out] vc         вектор, в котором меняются элементы
//! \param      j1         номер первого элемента
//! \param      j2         номер второго элемента
//!
//-----------------------------------------------------------------------------------------------------------------

    static void swap (char** vec, int j1, int j2);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Сравнивает две строки
//!
//! \param[in] str1     первая строка
//! \param[in] str2     вторая строка
//!
//! \return 1 если первая меньше второй, -1 если первая больше второй и 0 если строки равны
//!
//-----------------------------------------------------------------------------------------------------------------

    static int strcmp (char* str1, char* str2);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Узнаёт число не пустых строк в файле
//!
//! \param[in] fp   дескриптор файла
//!
//! \return число не пыстух строк
//!
//-----------------------------------------------------------------------------------------------------------------

    static size_t numStrInFile(char* buff);
}

//-----------------------------------------------------------------------------------------------------------------
//! \brief Читает текс из файла в вектор
//!
//! \param[in]  filename    имя файла, из которого читаем текст
//! \param[out] buff        буфер гре хранится весь файл
//! \param[out] numString   число строк в файле
//!
//! \return вектор с считанным текстом
//!
//-----------------------------------------------------------------------------------------------------------------

char** ReadVectorFromFile(const char* filename, char* buff, size_t* numString);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Записывает текст из вектора в файл
//!
//! \param[in]  filename    имя файла, в который записываем текст
//! \param[in]  vec         вектор с текстом
//! \param[in]  numString   число строк в файле
//!
//-----------------------------------------------------------------------------------------------------------------

void WriteVectorToFile(const char* filename, char** vec, size_t* numString);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Сортирует вектор с текстом
//!
//! \param[in]  vec             сортируемый вектор
//! \param[in]  numString       число строк в файле
//! \param[in]  strcmp          функция сравнения двух элементов вектора
//!
//-----------------------------------------------------------------------------------------------------------------

void insertionSorting(char** vec, size_t* numString, int (*strcmp)(char* a, char* b) = ForVectorOfStrings::strcmp);



int main()
{
    printf("# Start\n\n");

    char*   buff        = nullptr;
    size_t  numString   = 0;

    char** vec = ReadVectorFromFile("Onegin.txt", buff, &numString);

    insertionSorting(vec, &numString);

    WriteVectorToFile("NewOnegin.txt", vec, &numString);

    printf("# Done\n");
    
    free(buff);
    free(vec);

    return 0;
}



//=================================================================================================================


namespace ForVectorOfStrings {


    static size_t len(const char* str)
    {
        assert(str != nullptr);

        size_t size = 0;

        while (str[size++] != '\0');

        return --size;
    }

//-----------------------------------------------------------------------------------------------------------------

    static void strcpy(char* destination, char* source)
    {
        assert(destination  != nullptr);
        assert(source       != nullptr);

        if (destination == source) return;

        size_t i = 0;
        
        for (; source[i] != '\0'; ++i)
            destination[i] = source[i];

        destination[i] = '\0';
    }

//-----------------------------------------------------------------------------------------------------------------

    static size_t getline(FILE* fp, char* buffer, size_t sizeBuffer)
    {
        assert(fp       != nullptr);
        assert(buffer   != nullptr);

        int     input = -1;
        size_t  size  = 0;
        
        while ((input = getc(fp)) != EOF && input != '\n' && size <= sizeBuffer)
            buffer[size++] = input;

        buffer[size] = '\0';

        return size;
    }

//-----------------------------------------------------------------------------------------------------------------

    static void swap(char** vec, int j1, int j2)
    {
        assert(vec  != nullptr);

        char *swp   = vec[j1];
        vec[j1]     = vec[j2];
        vec[j2]     = swp;
    }

//-----------------------------------------------------------------------------------------------------------------

    static int strcmp(char* str1, char* str2)
    {
        assert(str1 != nullptr);
        assert(str2 != nullptr);

        size_t i = 0;

        for (; str1[i] != '\0' && str2[i] != '\0'; ++i)
            if (str1[i] > str2[i])
                return -1;
            else if (str1[i] < str2[i])
                return 1;

        if (str1[i] == '\0')
            return 1;
        if (str2[i] == '\0')
            return -1;        

        return 0;
    }

//-----------------------------------------------------------------------------------------------------------------

    static size_t numStrInFile(char* buff)
    {
        assert(buff != nullptr);

        size_t num = 0;
        size_t i   = 0;

        while (buff[i] != '\0')
            if (buff[i++] == '\n')
                num++;

        return ++num;
    }
}


//=================================================================================================================

char** ReadVectorFromFile(const char* filename, char* buff, size_t* numString)
{
    assert(filename     != nullptr);
    assert(numString    != nullptr);

    FILE* fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Can't read file.");
        exit(1);
    }
    
    fseek(fp, 0, SEEK_END);
    free(buff);

    size_t buffSize = ftell(fp);
           buff     = (char*)calloc((buffSize + 1), sizeof(char));

    fseek(fp, 0, SEEK_SET);

    if (buff == NULL)
    {
        printf("Error: Can't create buffer");
        exit(1);
    }

    fread(buff, 1, buffSize, fp);

            buff[buffSize]  = '\0';
            (*numString)    = ForVectorOfStrings::numStrInFile(buff);
    char**  vec             = (char**)calloc(((*numString) + 1), sizeof(char*));
    size_t  i               = 0;
    size_t  j               = 0;
            vec[j++]        = buff;
    
    while (*(buff + i) != '\0')
    {
        if (*(buff + i) == '\n')
        {
            vec[j++]    = buff + i + 1;
            buff[i]     = '\0';
        }

        i++;
    }

    fclose  (fp);

    return vec;
}

//-----------------------------------------------------------------------------------------------------------------

void WriteVectorToFile(const char* filename, char** vec, size_t* numString)
{
    assert(filename     != nullptr);
    assert(vec          != nullptr);
    assert(numString    != nullptr);

    FILE*   fp  = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("# Error: Can't read file.");
        exit(1);
    }

    for (size_t i = 0; i < (*numString); ++i)
    {
        if (fprintf(fp, vec[i]) < 0)
        {
            printf("# Error: Can't write to file.");
            exit(1);
        }
        if (fprintf(fp, "\n") < 0)
        {
            printf("# Error: Can't write to file.");
            exit(1);
        }
    }

    fclose(fp);
}

//-----------------------------------------------------------------------------------------------------------------

void insertionSorting(char** vec, size_t* numString, int (* strcmp)(char* a, char* b) /* = ForVectorOfStrings::strcmp*/)
{
    assert(strcmp       != nullptr);
    assert(vec          != nullptr);
    assert(numString    != nullptr);

    for (size_t i = 0; i < (*numString); ++i)
    {
        int j = i;

        while (j > 0 && strcmp(vec[j], vec[j - 1]) == 1)
        {
            ForVectorOfStrings::swap(vec, j, j - 1);

            j -= 1;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
//! \brief Пишет ошибку в лог
//!
//! \param[in]  textError  название ошибки
//! \param[in]  func       функция где была вызвана ошибка 
//! \param      line       номер строки где произошла ошибка
//! \param[in]  nameLog    названия файла записи лога 
//! 
//! на будущее
//!
//-----------------------------------------------------------------------------------------------------------------

void logError(const char* textError, const char* func,  const int line, const char* nameLog = "err.log")
{
    FILE* fp = fopen(nameLog, "a");

    fprintf(fp, "%s found in function %s() in line %d", textError, func, line);

    fclose(fp);
}

//-----------------------------------------------------------------------------------------------------------------
//! Assert с записью ошибок в лог; на будущее
//-----------------------------------------------------------------------------------------------------------------

#define asserted(rule) logError(rule, "Assertion failed:", __func__, __LINE__), assert(rule);
