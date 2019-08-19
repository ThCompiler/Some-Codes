//! @file
//! \brief Программа визуализации алгоритмов сортировки (VSA). Сервер
//! @mainpage
//!
//! Разметка объектов происходит в виртуальных координатах окна размером 1310x675 <br>
//!	
//! <b>Важно!! Сервер запускать раньше клиента и ждать пока не появится сообщение "Searching for client..."</b>
//!
//-----------------------------------------------------------------------------------------------------------------
//! \author     TheCompiler
//! \version    alpha 2
//! \date       19.08.2019
//-----------------------------------------------------------------------------------------------------------------
//!
//! @defgroup PreCalculation        Расчёт значений
//! @defgroup ServerNeed            Сулежбные функции сервера
//! @defgroup ReactionOnRequests    Функции ответа на запрос клиента
//=================================================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <set>

#include "ButtonsFunction.h"




namespace requests {

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup PreCaculation
//! \brief Заполняет массив для сортировки
//! 
//! \param isRandom             вариант заполнения массива, true - случайными числами, false - числами в убыающем порядке
//! \param MaxNumOfElements     число элементов в массиве
//!
//! \return Массив для сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    std::vector<int> CreateArray (int MaxNumOfElements, bool isRandom);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ReactionOnRequests 
//! \brief Создаёт новый массив данных по запросу клиента
//! 
//! \param client   сокет клиента для отправки и получения данных
//!
//-----------------------------------------------------------------------------------------------------------------

    void NewArray(TX_SOCKET client);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ReactionOnRequests 
//! \brief Запускает расчёты сортировок по запросу клиента
//! 
//! \param client           сокет клиента для отправки и получения данных
//! \param Functions        вектор ссылок на функции кнопоке
//!
//-----------------------------------------------------------------------------------------------------------------

    void CalculationResult(TX_SOCKET client, std::vector<int(*)(int left, int right, std::vector<int>parametrs,
                            int* swaping, int* comparisons, std::vector<int>* Array)> Functions);
}

namespace drawing {

//=================================================================================================================
// Блок структур
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
//! структура для удобства хранения результатов
//-----------------------------------------------------------------------------------------------------------------

    struct parameterForResults
    {
        int swaping, comparisons, numOfElements;
    };
}



int main()
{
    // список функций по id кнопок
    std::vector<int(*)(int left, int right, std::vector<int>parametrs, 
                int* swaping, int* comparisons, std::vector<int> * Array)>Functions;

    Functions.push_back (buttonsFunction::bubbleSorting     );
    Functions.push_back (buttonsFunction::heap_sort         );
    Functions.push_back (buttonsFunction::quickSorting      );
    Functions.push_back (buttonsFunction::mergeSorting      );
    Functions.push_back (buttonsFunction::insertionSorting  );
    Functions.push_back (buttonsFunction::selectionSorting  );

//--------------------------------------------------------------------------------------------------------------

    printf ("Searching for client...\n");
    TX_SOCKET client = txCreateSocket (TX_SERVER, ""); // ищем пользователя

    printf ("Hello\n"); // нашли пользователя

    while (1)
    {
        //проверяем наличие запроса от клиента и совершаем нужные действия

        int request = 0;

        txRecvFrom (client, &request, sizeof(int));

        printf("request %d\n", request);

        if (request == 1)
        {
            requests::NewArray(client);

            printf("Array created\n\n");
        }

        if (request == 2)
        {
            requests::CalculationResult(client, Functions);
            printf("Finished calculation\n\n");
        }


        if (_kbhit())
        {
            const int key = _getch();
            if (key == 0x1B) break;     // если нажать Esc тоже программа прекратит работу
        }
    }
}



namespace requests {

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

    void NewArray(TX_SOCKET client)
    {
        int     numOfElements   = -1;
        bool    isRandom        = 0;

        txRecvFrom (client, &numOfElements, sizeof(numOfElements));
        txRecvFrom (client, &isRandom,      sizeof(isRandom     ));

        std::vector<int> newArray = CreateArray(numOfElements, isRandom);

        server::SendVector(client, &newArray);
    }

//--------------------------------------------------------------------------------------------------------------

    void CalculationResult(TX_SOCKET client, std::vector<int(*)(int left, int right, std::vector<int>parametrs, 
                            int* swaping, int* comparisons, std::vector<int> * Array)> Functions)
    {
        std::vector<drawing::parameterForResults> resultValue;   // вектор хранящий результаты расчётов

        int                 swaping             = 0;
        int                 comparisons         = 0;
        int                 numOfElements       = -1;
        int                 minNumOfElements    = -1;
        std::vector<int>    Array;
        std::vector<int>    activeFunctions;

        txRecvFrom(client, &numOfElements,      sizeof(numOfElements    ));
        txRecvFrom(client, &minNumOfElements,   sizeof(minNumOfElements ));

        server::GetVector(client, &Array            );
        server::GetVector(client, &activeFunctions  );

        for (int each = 0; each < activeFunctions.size(); each++)
        {
            resultValue.clear();

            if (!activeFunctions[each])
            {
                server::SendVector(client, &resultValue);
                continue;
            }
            
            for (int i = minNumOfElements; i < numOfElements; i += 4)
            {
                std::vector<int>sortingArray;

                for (int i = 0; i < numOfElements; i++)
                    sortingArray.push_back(Array[i]);

                swaping     = 0;
                comparisons = 0;

                Functions[each](0, i, {}, & swaping, & comparisons, & sortingArray); // запускаем функцию сортировки

                resultValue.push_back({ swaping, comparisons, i });
            }

            server::SendVector(client, &resultValue);
        }

    }


}