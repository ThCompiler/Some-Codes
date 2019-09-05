//! @file
//! \brief библиотека работы с вектором строк
//=================================================================================================================

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define START_RECIVE_MEMORY 40;     ///< первоночальный размер выделенной памяти для вектора
#define RESIZE_MEMORY       40;     ///< размер блока памяти, добовляющегося при необходимости вектору
#define BUFFER_SIZE         110;    ///< размер буфера чтения из файла


namespace ForVectorOfStrings {

    static size_t   len     (char* str                                      );
    static bool     strcpy  (char* str1,    char* str2                      );
    static size_t   getline (FILE* fp,      char* buffer, size_t sizeBuffer );
    static int      compar  (char* str1,    char* str2                      );
}


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

//-----------------------------------------------------------------------------------------------------------------
//! \brief Выделяет дополнительную память вектору
//-----------------------------------------------------------------------------------------------------------------

    void reciveMemery()
    {
        recivedSize += RESIZE_MEMORY;
        
        char **newArray = (char**)realloc(Array, recivedSize * sizeof(char*));

        assert(newArray != NULL);

        Array = newArray;
    }

public:

//-----------------------------------------------------------------------------------------------------------------
//! \brief Конструктор вектора
//-----------------------------------------------------------------------------------------------------------------

    VectorOfStrings()
    {
        sizeOfArray = 0;
        recivedSize = START_RECIVE_MEMORY;
        Array       = (char**)malloc(recivedSize * sizeof(char*));
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Диструктор вектора
//-----------------------------------------------------------------------------------------------------------------

    ~VectorOfStrings()
    {
        for (size_t i = 0; i < sizeOfArray; ++i)
            free(Array[i]);
        free(Array);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Добавляет элемент в конец вектор
//!
//! \param[in] str  добавляемый элемент
//!
//-----------------------------------------------------------------------------------------------------------------

    void push_back(char* str)
    {
        assert(str != nullptr);

        if (sizeOfArray == recivedSize)
            reciveMemery();

        Array[sizeOfArray] = (char*)malloc((ForVectorOfStrings::len(str) + 1) * sizeof(char*));
        ForVectorOfStrings::strcpy(Array[sizeOfArray], str);
        sizeOfArray++;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Получения элемента
//!
//! \param i    номер получаемого элемента
//!
//! \return нужный элемент
//!
//-----------------------------------------------------------------------------------------------------------------

    char* get(size_t i)
    {
        return Array[i];
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Меняет элемент в векторе
//!
//! \param      i               номер изменяемого элемента
//! \param[in]  newElements     элеменет на который заменяет
//!
//-----------------------------------------------------------------------------------------------------------------

    void change(size_t i, char* newElements)
    {
        Array[i] = newElements;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Говорит размер вектора
//!
//! \return     размер вектора
//!
//-----------------------------------------------------------------------------------------------------------------

    size_t size()
    {
        return sizeOfArray;
    }
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

    static size_t len(char* str)
    {
        assert(str != nullptr);

        size_t size = 0;

        while (str[size++] != '\0');

        return --size;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Копирует строку из одной в другую
//!
//! \param[out] destination     строка, в которую копируют
//! \param[in]  source          строка, которую копируют
//!
//! \return true в случае успешного копирования
//!
//-----------------------------------------------------------------------------------------------------------------

    static bool strcpy(char* destination, char* source)
    {
        assert(destination  != nullptr);
        assert(source       != nullptr);

        if (destination == source) return true;

        size_t size = len(source);

        for (size_t i = 0; i <= size; ++i)
            destination[i] = source[i];

        return true;
    }

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
//! \brief Меняет два элемента в векторе местами
//!
//! \param[out] vc         вектор, в котором меняются элементы
//! \param      j1         номер первого элемента
//! \param      j2         номер второго элемента
//!
//-----------------------------------------------------------------------------------------------------------------

    static void swap(VectorOfStrings* vec, int j1, int j2)
    {
        assert(vec  != nullptr);

        char *swp = vec->get(j1);
        vec->change(j1, vec->get(j2));
        vec->change(j2, swp);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Сравнивает две строки
//!
//! \param[in] str1     первая строка
//! \param[in] str2     вторая строка
//!
//! \return 1 если первая меньше второй, -1 если первая больше второй и 0 если строки равны
//!
//-----------------------------------------------------------------------------------------------------------------

    static int compar(char* str1, char* str2)
    {
        assert(str1 != nullptr);
        assert(str2 != nullptr);

        size_t size1 = ForVectorOfStrings::len(str1);
        size_t size2 = ForVectorOfStrings::len(str2);

        if (size1 < size2)
            return 1;
        if (size1 > size2)
            return -1;

        for (size_t i = 0; i < size1; ++i)
            if (str1[i] > str2[i])
                return -1;
            else if (str1[i] < str2[i])
                return 1;

        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------------------
//! \brief Читает текс из файла в вектор
//!
//! \param[in]  filename    имя файла, из которого читаем текст
//!
//! \return вектор с считанным текстом
//!
//-----------------------------------------------------------------------------------------------------------------

VectorOfStrings* ReadVectorFromFile(const char* filename)
{
    assert(filename != nullptr);
    
    FILE*            fp  = fopen(filename, "r");
    VectorOfStrings* vec = new VectorOfStrings();

    if (fp == NULL)
    {
        printf("Error: Can't read file.");
        exit(1);
    }

    size_t  buffSize = BUFFER_SIZE;
    char*   buff     = (char*)malloc((buffSize + 1) * sizeof(char));

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
//! \brief Записывает текст из вектора в файл
//!
//! \param[in]  filename    имя файла, в который записываем текст
//! \param[in]  vec         вектор с текстом
//!
//! \return true если всё прошло успешно
//!
//-----------------------------------------------------------------------------------------------------------------

bool WriteVectorToFile(const char* filename, VectorOfStrings* vec)
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

    return 1;
}

//-----------------------------------------------------------------------------------------------------------------
//! \brief Сортирует вектор с текстом
//!
//! \param[in]  vec             сортируемый вектор
//! \param[in]  comparison      функция сравнения двух элементов вектора
//!
//-----------------------------------------------------------------------------------------------------------------

void insertionSorting(VectorOfStrings* vec, int (* comparison)(char* a, char* b) = ForVectorOfStrings::compar)
{
    assert(comparison   != nullptr);
    assert(vec          != nullptr);

    for (size_t i = 0; i < vec->size(); ++i)
    {
        int j = i;

        while (j > 0 && comparison(vec->get(j), vec->get(j - 1)) == 1)
        {
            ForVectorOfStrings::swap(vec, j, j - 1);

            j -= 1;
        }
    }
}