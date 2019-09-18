//! @file
//! \brief Программа сортирует в лексикографическом порядке письмо Онегина Татьяне
//! @mainpage
//-----------------------------------------------------------------------------------------------------------------
//! \author     TheCompiler
//! \version    alpha 3
//! \date       18.09.2019
//=================================================================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



namespace ForVectorOfStrings {

//-----------------------------------------------------------------------------------------------------------------
//! \brief Меняет одни элементы строки на другие
//!
//! \param[in] str      строка
//! \param     was      элемент который нужно заменить
//! \param     will     элемент на который заменаем
//!
//-----------------------------------------------------------------------------------------------------------------

    static void changeElem(char* str, char was, char will);

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
//! \brief Проверяет является ли символ буквой русского алфавита
//!
//! \param symbol  символ
//!
//! \return true если это буква русского алфавит, иначе false
//!
//-----------------------------------------------------------------------------------------------------------------

    static bool isalphaRus(char symbol);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Сравнивает две строки с первого элемента
//!
//! \param[in] str1     первая строка
//! \param[in] str2     вторая строка
//!
//! \return 1 если первая меньше второй, -1 если первая больше второй и 0 если строки равны
//!
//-----------------------------------------------------------------------------------------------------------------

    static int strcmpBegin (char* str1, char* str2);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Сравнивает две строки с последнего элемента
//!
//! \param[in] str1     первая строка
//! \param[in] str2     вторая строка
//!
//! \return 1 если первая меньше второй, -1 если первая больше второй и 0 если строки равны
//!
//-----------------------------------------------------------------------------------------------------------------

    static int strcmpEnd (char* str1, char* str2);

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
//! \brief Разделяет текст на строки в отдельный массив
//!
//! \param[out] buff        буфер гре хранится весь файл
//! \param      numString   число строк в файле
//!
//! \return вектор с считанным текстом
//!
//-----------------------------------------------------------------------------------------------------------------

char** TextToArrayOfStr(char* buff, size_t numString);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Записывает текст из вектора в файл
//!
//! \param[in]  filename    имя файла, в который записываем текст
//! \param[in]  vec         вектор с текстом
//! \param      numString   число строк в файле
//!
//-----------------------------------------------------------------------------------------------------------------

void WriteVectorToFile(const char* filename, char** vec, size_t numString);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Сортирует вектор с текстом
//!
//! \param[in]  vec             сортируемый вектор
//! \param      left            номер первого элемента сортируемого массива
//! \param      right           номер последнего элемента сортируемого массива
//! \param[in]  strcmp          функция сравнения двух элементов вектора
//!
//-----------------------------------------------------------------------------------------------------------------

void qsorting(char** vec, int left, int right, int (*strcmp)(char* a, char* b) = ForVectorOfStrings::strcmpEnd);


int main()
{
    printf("# Start\n\n");

    FILE* fp = fopen("Onegin.txt", "r");

    if (fp == NULL)
    {
        printf("# Error: Can't read file.");
        exit(1);
    }
    
    fseek(fp, 0, SEEK_END);

    size_t buffSize = ftell(fp);
    char*  buff     = (char*)calloc((buffSize + 1), sizeof(char));

    if (buff == NULL)
    {
        printf("# Error: Can't create buffer");
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);
    fread(buff, 1, buffSize, fp);   //читаем текст из файла
    fclose(fp);
  
    size_t  numString = ForVectorOfStrings::numStrInFile(buff);
    char**  vec       = TextToArrayOfStr(buff, numString);           // создаём массив строк файла 
    char    ans;

    std::cout << "Sort by line end?(y or n)\n";
    std::cin >> ans;

    if (ans == 'y')
        qsorting(vec, 0, numString - 1, ForVectorOfStrings::strcmpEnd);
    else
        qsorting(vec, 0, numString - 1, ForVectorOfStrings::strcmpBegin);

    WriteVectorToFile("NewOnegin.txt",  vec, numString);    //выводим результат

    printf("# Done\n");
    
    free(vec);
    free(buff);

    return 0;
}



//=================================================================================================================



namespace ForVectorOfStrings {


    static void changeElem(char* str, char was, char will)
    {
        size_t i = 0;
        while (str[i] != '\0')
        {
            if (str[i] == was)
                str[i] = will;
            i++;
        }
    }

//-----------------------------------------------------------------------------------------------------------------

    static size_t len(const char* str)
    {
        assert(str != nullptr);

        size_t size = 0;

        while (str[size++] != '\0');

        return --size;
    }

//-----------------------------------------------------------------------------------------------------------------

    static bool isalphaRus(char symbol)
    {
        if (symbol >= 'а' && symbol <= 'я' || symbol >= 'А' && symbol <= 'Я')
            return 1;
        else
            return 0;
    }

//-----------------------------------------------------------------------------------------------------------------

    static int strcmpBegin(char* str1, char* str2)
    {
        assert(str1 != nullptr);
        assert(str2 != nullptr);

        size_t i = 0;
        size_t j = 0;

        for (; str1[i] != '\0' && str2[j] != '\0'; ++i, j++)
        {
            while (!isalphaRus(str1[i]) && str1[i] != '\0') i++;
            while (!isalphaRus(str2[j]) && str2[j] != '\0') j++;

            if (str1[i] > str2[j])
                return -1;
            else if (str1[i] < str2[j])
                return 1;
        }

        if (str1[i] == '\0')
            return 1;
        if (str2[j] == '\0')
            return -1;        

        return 0;
    }

//-----------------------------------------------------------------------------------------------------------------

    static int strcmpEnd(char* str1, char* str2)
    {
        assert(str1 != nullptr);
        assert(str2 != nullptr);

        size_t i = 0;
        size_t j = 0;

        for (; str1[i] != '\0'; ++i);
        for (; str2[j] != '\0'; ++j);


        for (; j != 0 && i != 0; --i, --j)
        {
            while (!isalphaRus(str1[i]) && i != 0) i--;
            while (!isalphaRus(str2[j]) && j != 0) j--;

            if (str1[i] > str2[j])
                return -1;
            else if (str1[i] < str2[j])
                return 1;
        }

        if (str1[i] > str2[j])
            return -1;
        else if (str1[i] < str2[j])
            return 1;

        if (i == 0)
            return 1;
        if (j == 0)
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

char** TextToArrayOfStr(char* buff, size_t numString)
{
    assert(buff != nullptr);

    char**  vec = (char**)calloc((numString + 1), sizeof(char*));
    size_t  i   = 0;
    size_t  j   = 0;

    vec[j++] = buff;
    
    while (*(buff + i) != '\0' && j <= numString)
    {
        if (*(buff + i) == '\n')       //ищем когда закончится текущая строка
        {
            vec[j++] = buff + i + 1;
            buff[i] = '\0';
        }

        i++;
    }

    return vec;
}

//-----------------------------------------------------------------------------------------------------------------

void WriteVectorToFile(const char* filename, char** vec, size_t numString)
{
    assert(filename != nullptr);
    assert(vec      != nullptr);

    FILE* fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("# Error: Can't read file.");
        exit(1);
    }

    for (size_t i = 0; i < numString; ++i)
    {
        if (fprintf(fp, "%s\n", vec[i]) < 0)
        {
            printf("# Error: Can't write to file.");
            exit(1);
        }
    }

    fclose(fp);
}

//-----------------------------------------------------------------------------------------------------------------

 void qsorting(char** vec, int left, int right, int (* strcmp)(char* a, char* b) /* = ForVectorOfStrings::strcmpBegin*/)
{
    assert(strcmp != nullptr);
    assert(vec    != nullptr);

    if (right - left <= 0)
        return;

    int p = left;

    for (int i = left; i <= right - 1; i++)
    {
        if (strcmp(vec[i], vec[right]) == 1)
        {
            std::swap(vec[p], vec[i]);
            p++;
        }
    }
    
    std::swap(vec[p], vec[right]);

    qsorting(vec, left,  p - 1, strcmp);
    qsorting(vec, p + 1, right, strcmp);
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

#define asserted(rule) logError("Assertion failed:", __func__, __LINE__), assert(rule);
