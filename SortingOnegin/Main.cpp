//! @file
//! \brief Программа сортирует в лексикографическом порядке письмо Онегина Татьяне
//! @mainpage
//-----------------------------------------------------------------------------------------------------------------
//! \author     TheCompiler
//! \version    alpha 1
//! \date       06.09.2019
//=================================================================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define BUFFER_SIZE         110;    ///< размер буфера чтения из файла



//=================================================================================================================
//! \class VectorOfStrings
//! \brief класс вектора для хранения строк
//-----------------------------------------------------------------------------------------------------------------

class VectorOfStrings
{
private:
    size_t sizeOfArray;     ///< размер вектора
    size_t recivedSize;     ///< развер выдленной памяти для вектора
    char   **Array;         ///< массив значений вектора

public:

//-----------------------------------------------------------------------------------------------------------------
//! \brief Конструктор вектора
//! 
//! \param size размер вектора
//!
//-----------------------------------------------------------------------------------------------------------------

    VectorOfStrings(size_t size = 40);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Диструктор вектора
//-----------------------------------------------------------------------------------------------------------------

    ~VectorOfStrings();

//-----------------------------------------------------------------------------------------------------------------
//! \brief Добавляет элемент в конец вектор
//!
//! \param[in] str  добавляемый элемент
//!
//-----------------------------------------------------------------------------------------------------------------

    void push_back(char* str);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Получения элемента
//!
//! \param i    номер получаемого элемента
//!
//! \return нужный элемент
//!
//-----------------------------------------------------------------------------------------------------------------

    char* get(size_t i);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Меняет элемент в векторе
//!
//! \param      i               номер изменяемого элемента
//! \param[in]  newElements     элеменет на который заменяет
//!
//-----------------------------------------------------------------------------------------------------------------

    void change(size_t i, char* newElements);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Говорит размер вектора
//!
//! \return     размер вектора
//!
//-----------------------------------------------------------------------------------------------------------------

    size_t size();
};


namespace ForVectorOfStrings {

//-----------------------------------------------------------------------------------------------------------------
//! \brief Находит длину строки
//!
//! \param[in] str      строка, длину которой надо узнать
//!
//! \return размер строки
//!
//-----------------------------------------------------------------------------------------------------------------

    static size_t len (char* str);

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

    static void swap (VectorOfStrings* vec, int j1, int j2);

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

    static size_t numStrInFile(FILE* fp);
}

//-----------------------------------------------------------------------------------------------------------------
//! \brief Читает текс из файла в вектор
//!
//! \param[in]  filename    имя файла, из которого читаем текст
//!
//! \return вектор с считанным текстом
//!
//-----------------------------------------------------------------------------------------------------------------

VectorOfStrings* ReadVectorFromFile(const char* filename);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Записывает текст из вектора в файл
//!
//! \param[in]  filename    имя файла, в который записываем текст
//! \param[in]  vec         вектор с текстом
//!
//-----------------------------------------------------------------------------------------------------------------

void WriteVectorToFile(const char* filename, VectorOfStrings* vec);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Сортирует вектор с текстом
//!
//! \param[in]  vec             сортируемый вектор
//! \param[in]  strcmpison      функция сравнения двух элементов вектора
//!
//-----------------------------------------------------------------------------------------------------------------

void insertionSorting(VectorOfStrings* vec, int (*strcmpison)(char* a, char* b) = ForVectorOfStrings::strcmp);



int main()
{
    printf("# Start\n\n");

    VectorOfStrings* vec = ReadVectorFromFile("Onegin.txt");

    insertionSorting(vec);

    WriteVectorToFile("NewOnegin.txt", vec);

    printf("# Done\n");

    vec->~VectorOfStrings();

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------

VectorOfStrings::VectorOfStrings(size_t size /*= 40*/)
{
    sizeOfArray = 0;
    recivedSize = size;
    Array       = (char**)calloc(recivedSize, sizeof(char*));
}

//-----------------------------------------------------------------------------------------------------------------

VectorOfStrings::~VectorOfStrings()
{
    for (size_t i = 0; i < sizeOfArray; ++i)
        free(Array[i]);
    free(Array);
}

//-----------------------------------------------------------------------------------------------------------------

void VectorOfStrings::push_back(char* str)
{
    assert(str          !=  nullptr);
    assert(sizeOfArray  <=  recivedSize);


    Array[sizeOfArray] = (char*)calloc((ForVectorOfStrings::len(str) + 1), sizeof(char*));
    ForVectorOfStrings::strcpy(Array[sizeOfArray], str);
    sizeOfArray++;
}

//-----------------------------------------------------------------------------------------------------------------

char* VectorOfStrings::get(size_t i)
{
    assert(i < sizeOfArray);

    return Array[i];
}

//-----------------------------------------------------------------------------------------------------------------

void VectorOfStrings::change(size_t i, char* newElements)
{
    assert(newElements  !=  nullptr);
    assert(i            <   sizeOfArray);

    Array[i] = newElements;
}

//-----------------------------------------------------------------------------------------------------------------

size_t VectorOfStrings::size()
{
    return sizeOfArray;
}


//=================================================================================================================


namespace ForVectorOfStrings {


    static size_t len(char* str)
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

    static void swap(VectorOfStrings* vec, int j1, int j2)
    {
        assert(vec  != nullptr);

        char *swp = vec->get(j1);
        vec->change(j1, vec->get(j2));
        vec->change(j2, swp);
    }

//-----------------------------------------------------------------------------------------------------------------

    static int strcmp(char* str1, char* str2)
    {
        assert(str1 != nullptr);
        assert(str2 != nullptr);

        size_t i = 0;

        for (; str1[i] != '\0' || str2[i] != '\0'; ++i)
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

    static size_t numStrInFile(FILE* fp)
    {
        assert(fp != nullptr);

        size_t  size     = 0;
        size_t  buffSize = BUFFER_SIZE;
        char*   buff     = (char*)calloc((buffSize + 1), sizeof(char));

        if (buff == NULL)
        {
            printf("Error: Can't create buffer");
            exit(1);
        }

        while (!feof(fp))
        {
            size_t numReadElements = ForVectorOfStrings::getline(fp, buff, buffSize);

            if (numReadElements > 0)
                size++;
        }

        fseek(fp, 0, SEEK_SET);
        free(buff);

        return size;
    }
}


//=================================================================================================================

VectorOfStrings* ReadVectorFromFile(const char* filename)
{
    assert(filename != nullptr);
    
    FILE* fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Can't read file.");
        exit(1);
    }

    VectorOfStrings*    vec         = new VectorOfStrings(ForVectorOfStrings::numStrInFile(fp));
    size_t              buffSize    = BUFFER_SIZE;
    char*               buff        = (char*)calloc((buffSize + 1), sizeof(char));

    if (buff == NULL)
    {
        printf("Error: Can't create buffer");
        exit(1);
    }

    while (!feof(fp))
    {
        size_t numReadElements = ForVectorOfStrings::getline(fp, buff, buffSize);

        if (numReadElements > 0)
            vec->push_back(buff);
    }

    fclose  (fp);
    free    (buff);

    return vec;
}

//-----------------------------------------------------------------------------------------------------------------

void WriteVectorToFile(const char* filename, VectorOfStrings* vec)
{
    assert(filename != nullptr);
    assert(vec      != nullptr);

    FILE*   fp  = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("# Error: Can't read file.");
        exit(1);
    }

    for (size_t i = 0; i < vec->size(); ++i)
    {
        if (fprintf(fp, vec->get(i)) < 0)
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

void insertionSorting(VectorOfStrings* vec, int (* strcmpison)(char* a, char* b) /* = ForVectorOfStrings::strcmp*/)
{
    assert(strcmpison   != nullptr);
    assert(vec          != nullptr);

    for (size_t i = 0; i < vec->size(); ++i)
    {
        int j = i;

        while (j > 0 && strcmpison(vec->get(j), vec->get(j - 1)) == 1)
        {
            ForVectorOfStrings::swap(vec, j, j - 1);

            j -= 1;
        }
    }
}