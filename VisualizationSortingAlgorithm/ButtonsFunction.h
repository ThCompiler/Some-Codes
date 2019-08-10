//! @file
//! \brief Библиотека функций для кнопок
//=================================================================================================================

#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include <queue>
#include "TXLIB.h"



namespace buttonsFunction
{

//=================================================================================================================
//! \class heap 
//! \brief Класс кучи
//-----------------------------------------------------------------------------------------------------------------

    template <typename T>
    class heap
    {
    public:
        int size = 0; ///< размер кучи

    private:
        std::vector<T> tree;

    //-----------------------------------------------------------------------------------------------------------------
    //! \brief Функция инициализации кучи
    //-----------------------------------------------------------------------------------------------------------------

        void heap_init(int Size)
        {
            std::vector<T> empty;

            size = Size;
            tree = empty;
        }

        void descent_down(int vertex, int* swaping, int* comparisons)
        {
            assert(swaping      != nullptr);
            assert(comparisons  != nullptr);
            assert(swaping      != comparisons);

            const int child     = 2 * vertex;
            int minIndexOfChild = vertex;

            if (child < size && tree[child] < tree[minIndexOfChild])
                minIndexOfChild = child;
            (*comparisons)++;

            if (child + 1 < size && tree[child + 1] < tree[minIndexOfChild])
                minIndexOfChild = child + 1;
            (*comparisons)++;

            if (minIndexOfChild != vertex)
            {
                std::swap(tree[minIndexOfChild], tree[vertex]);
                (*swaping)++;

                descent_down(minIndexOfChild, swaping, comparisons);
            }
            (*comparisons)++;
        }

    public:

        heap()
        {
            heap_init(0);
        }

    //-----------------------------------------------------------------------------------------------------------------
    //! \brief Функция получения минимального значения и удаления его
    //-----------------------------------------------------------------------------------------------------------------

        T extract_min(int* swaping, int* comparisons)
        {
            assert(swaping      != nullptr);
            assert(comparisons  != nullptr);
            assert(swaping      != comparisons);

            T minValue  = get_min();
            tree[0]     = tree[size - 1];

            (*swaping)++;

            size -= 1;

            tree.pop_back();
            descent_down(0, swaping, comparisons);

            return minValue;
        }

    //-----------------------------------------------------------------------------------------------------------------
    //! \brief Функция создания кучи
    //-----------------------------------------------------------------------------------------------------------------

        void make_heap(int* swaping, int* comparisons, std::vector<T>Array, int n)
        {
            assert(swaping      != nullptr);
            assert(comparisons  != nullptr);
            assert(swaping      != comparisons);

            heap_init(n);
            for (int i = 0; i < n; i++)
                tree.push_back(Array[i]);

            for (int i = n - 1; i >= 0; i--)
                descent_down(i, swaping, comparisons);
        }

    //-----------------------------------------------------------------------------------------------------------------
    //! \brief возрашает минимальный элемент кучи
    //-----------------------------------------------------------------------------------------------------------------

        T get_min()
        {
            return tree[0];
        }
    };

//-----------------------------------------------------------------------------------------------------------------
//! \brief Функция сортировки кучей
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! \return     Маркер нажатия кнопок функций сортировки
/*! Код функции выглядит следующим образом :
    \code
    int heap_sort(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                                                int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping != nullptr);
        assert(comparisons != nullptr);
        assert(swaping != comparisons);
        assert(Array != nullptr);

        heap<int>Heap;
        Heap.make_heap(swaping, comparisons, *Array, right + 1);
        for (int i = left; i <= right; i++)
        {
            (*Array)[i] = Heap.extract_min(swaping, comparisons);
            (*swaping)++;
        }
        return -1;
    }
    \endcode
*/
//-----------------------------------------------------------------------------------------------------------------

    int heap_sort(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                  int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping      != nullptr);
        assert(comparisons  != nullptr);
        assert(swaping      != comparisons);
        assert(Array        != nullptr);

        heap<int>Heap;

        Heap.make_heap(swaping, comparisons, *Array, right + 1);

        for (int i = left; i <= right; i++)
        {
            (*Array)[i] = Heap.extract_min(swaping, comparisons);
            (*swaping)++;
        }

        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------
//! описание в DiagramOfSorting
//-----------------------------------------------------------------------------------------------------------------

    std::vector<int> CreateArray(int MaxNumOfElements, bool isRandom)
    {
        std::vector<int> mainArray; // сортируемый массив

        if (isRandom) // если заполнение случайными числами
        {
            int a = -1;

            for (int i = MaxNumOfElements; i > 0; i--)
            {
                a = int(random(std::nomeow, 1, int(1e8)));
                mainArray.push_back(a);
            }

            return mainArray;
        }

        for (int i = MaxNumOfElements; i > 0; i--) // если заполнять поубыванию
            mainArray.push_back(i);

        return mainArray;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Возвращает маркер реакции на нажатия кнопки "Поехали!", то есть запуска расчётов
//-----------------------------------------------------------------------------------------------------------------

    int Start(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
              int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        return 1;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Возвращает маркер реакции на нажатия кнопки "Выход"
//-----------------------------------------------------------------------------------------------------------------

    int Exit(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
             int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        return 0;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Возвращает маркер реакции на нажатия кнопки "Заполнения случаными числами"
//-----------------------------------------------------------------------------------------------------------------

    int Random(int left, int right, std::vector<int>parametrs, int* RandomFilling = nullptr,
               int* MaxNumOfElements = nullptr, std::vector<int>* mainArray = nullptr)
    {
        assert(mainArray        != nullptr);
        assert(RandomFilling    != nullptr);
        assert(MaxNumOfElements != nullptr);

        (*mainArray)        = CreateArray((*MaxNumOfElements), 1);
        (*RandomFilling)    = true;

        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Возвращает маркер реакции на нажатия кнопки "Заполнения числами по убыванию"
//-----------------------------------------------------------------------------------------------------------------

    int NotRandom(int left, int right, std::vector<int>parametrs, int* RandomFilling = nullptr,
                  int* MaxNumOfElements = nullptr, std::vector<int>* mainArray = nullptr)
    {
        assert(mainArray        != nullptr);
        assert(RandomFilling    != nullptr);
        assert(MaxNumOfElements != nullptr);

        (*mainArray)        = CreateArray((*MaxNumOfElements), 0);
        (*RandomFilling)    = false;

        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Возвращает маркер реакции на нажатия кнопки "Изменения размера сортеруемого массива"
//-----------------------------------------------------------------------------------------------------------------

    int Changed(int left, int right, std::vector<int>parametrs, int* RandomFilling = nullptr,
                int* MaxNumOfElements = nullptr, std::vector<int>* mainArray = nullptr)
    {
        assert(mainArray        != nullptr);
        assert(RandomFilling    != nullptr);
        assert(MaxNumOfElements != nullptr);

        int input = std::atoi(txInputBox("Какие максимальное число элементов может быть в массиве?",
                                         "Настройки", std::to_string(*MaxNumOfElements).c_str()));

        if (input > 5000)
            txMessageBox("Слишком много ввёл. Не дождёшься результата. Максимально можешь ввести до 5000.", "Тех. поддержка");
        else
        {
            (*MaxNumOfElements) = input;
            (*mainArray)        = CreateArray((*MaxNumOfElements), RandomFilling);
        }

        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Сортировка вставкой
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! \return     Маркер нажатия кнопок функций сортировки
/*! Код функции выглядит следующим образом :
    \code
    int insertionSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                            int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping != nullptr);
        assert(comparisons != nullptr);
        assert(swaping != comparisons);
        assert(Array != nullptr);

        for (int i = left; i < right; i++)
        {
            int j = i;
            while (j > left && (*Array)[j] < (*Array)[j - 1])
            {
                (*comparisons)++;
                std::swap((*Array)[j], (*Array)[j - 1]);
                (*swaping)++;
                j -= 1;
            }
        }
        return -1;
    }
    \endcode
*/
//-----------------------------------------------------------------------------------------------------------------

    int insertionSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                         int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping      != nullptr);
        assert(comparisons  != nullptr);
        assert(swaping      != comparisons);
        assert(Array        != nullptr);

        for (int i = left; i < right; i++)
        {
            int j = i;

            while (j > left && (*Array)[j] < (*Array)[j - 1])
            {
                (*comparisons)++;
                std::swap((*Array)[j], (*Array)[j - 1]);
                (*swaping)++;

                j -= 1;
            }
        }

        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Сортировка пузырьком
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! \return     Маркер нажатия кнопок функций сортировки
/*! Код функции выглядит следующим образом :
    \code
    int bubbleSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                                                int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping != nullptr);
        assert(comparisons != nullptr);
        assert(swaping != comparisons);
        assert(Array != nullptr);

        bool end = false;
        while (!end)
        {
            end = true;
            for (int i = left + 1; i <= right; i++)
            {
                if ((*Array)[i] < (*Array)[i - 1])
                {
                    std::swap((*Array)[i], (*Array)[i - 1]);
                    (*swaping)++;
                    end = false;
                }
                (*comparisons)++;
            }
            right--;
        }
        return -1;
    }
    \endcode
*/
//-----------------------------------------------------------------------------------------------------------------

    int bubbleSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                      int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping      != nullptr);
        assert(comparisons  != nullptr);
        assert(swaping      != comparisons);
        assert(Array        != nullptr);

        bool end = false;

        while (!end)
        {
            end = true;

            for (int i = left + 1; i <= right; i++)
            {
                if ((*Array)[i] < (*Array)[i - 1])
                {
                    std::swap((*Array)[i], (*Array)[i - 1]);
                    (*swaping)++;

                    end = false;
                }

                (*comparisons)++;
            }

            right--;
        }

        return -1;
    }


    void merge(int* swaping, int* comparisons, std::vector<int>* Array, int left, int middle, int right)
    {
        assert(swaping      != nullptr);
        assert(comparisons  != nullptr);
        assert(swaping      != comparisons);
        assert(Array        != nullptr);

        int i = middle + 1;
        int j = left;

        std::vector<int>merged;

        while (i <= right && j <= middle)
        {
            if ((*Array)[i] <= (*Array)[j])
                merged.push_back((*Array)[i++]);
            else
                merged.push_back((*Array)[j++]);

            (*comparisons)++;
            (*swaping)++;
        }

        while (j <= middle)
        {
            merged.push_back((*Array)[j++]);
            (*swaping)++;
        }

        while (i <= right)
        {
            merged.push_back((*Array)[i++]);
            (*swaping)++;
        }

        for (i = left; i <= right; i++)
        {
            (*Array)[i] = merged[i - left];
            (*swaping)++;
        }
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Сортировка вставкой
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! merge() функция объединяет два отсортированных участка массива в один отсортированный
//! 
//! \return     Маркер нажатия кнопок функций сортировки
/*! Код функции выглядит следующим образом :
    \code
    void merge(int* swaping, int* comparisons, std::vector<int>* Array, int left, int middle, int right)
    {
        assert(swaping != nullptr);
        assert(comparisons != nullptr);
        assert(swaping != comparisons);
        assert(Array != nullptr);

        int i = middle+1;
        int j = left;
        std::vector<int>merged;

        while (i <= right && j <= middle)
        {
            if ((*Array)[i] <= (*Array)[j])
                merged.push_back((*Array)[i++]);
            else
                merged.push_back((*Array)[j++]);
            (*comparisons)++;
            (*swaping)++;
        }
        while (j <= middle)
        {
            merged.push_back((*Array)[j++]);
            (*swaping)++;
        }
        while (i <= right)
        {
            merged.push_back((*Array)[i++]);
            (*swaping)++;
        }

        for (i=left; i <= right; i++)
        {
            (*Array)[i] = merged[i - left];
            (*swaping)++;
        }
    }

    int mergeSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                                                    int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping != nullptr);
        assert(comparisons != nullptr);
        assert(swaping != comparisons);
        assert(Array != nullptr);

        if (left < right)
        {
            (*comparisons)++;
            const int middile = (left + right) / 2;
            mergeSorting(left, middile, parametrs, swaping, comparisons, Array);
            mergeSorting(middile + 1, right, parametrs, swaping, comparisons, Array);
            merge(swaping, comparisons, Array, left, middile, right);
        }
        return -1;
    }
    \endcode
*/
//-----------------------------------------------------------------------------------------------------------------

    int mergeSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                     int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping      != nullptr);
        assert(comparisons  != nullptr);
        assert(swaping      != comparisons);
        assert(Array        != nullptr);

        if (left < right)
        {
            (*comparisons)++;
            const int middile = (left + right) / 2;

            mergeSorting(left,          middile,    parametrs,   swaping,    comparisons,    Array);
            mergeSorting(middile + 1,   right,      parametrs,   swaping,    comparisons,    Array);

            merge(swaping, comparisons, Array, left, middile, right);
        }

        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Быстрая сортировка
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! \return     Маркер нажатия кнопок функций сортировки
/*! Код функции выглядит следующим образом :
    \code
    int quickSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                                                int* comparisons = nullptr, std::vector<int>* Array = nullptr)
{
    assert(swaping != nullptr);
    assert(comparisons != nullptr);
    assert(swaping != comparisons);
    assert(Array != nullptr);

    if (right - left <= 0)
        return -1;

    int p = left;
    for (int i = left + 1; i <= right - 1; i++)
    {
        if ((*Array)[i] < (*Array)[right])
        {
            std::swap((*Array)[p], (*Array)[i]);
            (*swaping)++;
            p++;
        }
        (*comparisons)++;
    }
    std::swap((*Array)[p], (*Array)[right]);
    quickSorting(left, p, parametrs, swaping, comparisons, Array);
    quickSorting(p + 1, right, parametrs, swaping, comparisons, Array);
    return -1;
}
    \endcode
*/
//-----------------------------------------------------------------------------------------------------------------

    int quickSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                     int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping      != nullptr);
        assert(comparisons  != nullptr);
        assert(swaping      != comparisons);
        assert(Array        != nullptr);

        if (right - left <= 0)
            return -1;

        int p = left;

        for (int i = left + 1; i <= right - 1; i++)
        {
            if ((*Array)[i] < (*Array)[right])
            {
                std::swap((*Array)[p], (*Array)[i]);
                (*swaping)++;
                p++;
            }
            (*comparisons)++;
        }

        std::swap((*Array)[p], (*Array)[right]);
        (*swaping)++;

        quickSorting(left,      p,      parametrs,   swaping,    comparisons,    Array);
        quickSorting(p + 1,     right,  parametrs,   swaping,    comparisons,    Array);

        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Сортировка выбором
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! \return     Маркер нажатия кнопок функций сортировки
/*! Код функции выглядит следующим образом :
    \code
    int selectionSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                                                int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping != nullptr);
        assert(comparisons != nullptr);
        assert(swaping != comparisons);
        assert(Array != nullptr);

        for (int i = left; i <=right; i++)
        {
            int min = (*Array)[i];
            int index = i;
            for (int j = i + 1; j <= right; j++)
            {
                if (min > (*Array)[j])
                {
                    min = (*Array)[j];
                    (*swaping)++;
                    index = j;
                }
                (*comparisons)++;
            }
            std::swap((*Array)[i], (*Array)[index]);
            (*swaping)++;
        }
        return -1;
    }
    \endcode
*/
//-----------------------------------------------------------------------------------------------------------------

    int selectionSorting(int left, int right, std::vector<int>parametrs, int* swaping = nullptr,
                         int* comparisons = nullptr, std::vector<int>* Array = nullptr)
    {
        assert(swaping      != nullptr);
        assert(comparisons  != nullptr);
        assert(swaping      != comparisons);
        assert(Array        != nullptr);

        for (int i = left; i <= right; i++)
        {
            int min     = (*Array)[i];
            int index   = i;

            for (int j = i + 1; j <= right; j++)
            {
                if (min > (*Array)[j])
                {
                    min     = (*Array)[j];
                    index   = j;

                    (*swaping)++;
                }

                (*comparisons)++;
            }

            std::swap((*Array)[i], (*Array)[index]);
            (*swaping)++;
        }

        return -1;
    }

//=================================================================================================================
//=================================================================================================================
//для отладки
//-----------------------------------------------------------------------------------------------------------------

    std::vector<int> GetResultOfAccount(int* swaping, int* comparisons, std::vector<int>mainArray, std::string nameFunction, int n)
    {
        assert(swaping      != nullptr);
        assert(comparisons  != nullptr);
        assert(swaping      != comparisons);

        std::vector<int>parametrs;

        if (nameFunction == "Heap")
        {
            //heap_sort(0, n - 1, parametrs, swaping, comparisons, &mainArray);
            return mainArray;
        }

        if (nameFunction == "Insertion")
        {
            insertionSorting(0, n - 1, parametrs, swaping, comparisons, &mainArray);
            return mainArray;
        }

        if (nameFunction == "Bubble")
        {
            bubbleSorting(0, n - 1, parametrs, swaping, comparisons, &mainArray);
            return mainArray;
        }

        if (nameFunction == "Merge")
        {
            mergeSorting(0, n - 1, parametrs, swaping, comparisons, &mainArray);
            return mainArray;
        }

        if (nameFunction == "Quick")
        {
            quickSorting(0, n - 1, parametrs, swaping, comparisons, &mainArray);
            return mainArray;
        }

        if (nameFunction == "Selection")
        {
            selectionSorting(0, n - 1, parametrs, swaping, comparisons, &mainArray);
            return mainArray;
        }

        return mainArray;
    }
}