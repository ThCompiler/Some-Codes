//! @file
//! \brief Программа визуализации алгоритмов сортировки (VSA). Сервер
//! @mainpage
//!
//! Разметка объектов происходит в виртуальных координатах окна размером 1310x675
//!
//-----------------------------------------------------------------------------------------------------------------
//! \author     TheCompiler
//! \version    alpha 1
//! \date       15.08.2019
//-----------------------------------------------------------------------------------------------------------------
//!
//! @defgroup PreCalculation        Расчёт значений
//! @defgroup ServerNeed            Сулежбные функции сервера
//! @defgroup ReactionOnRequests    Функции ответа на запрос клиента
//=================================================================================================================

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <set>

#include "ButtonsFunction.h"
#include "TXLib.h"


#ifdef TheCompiler                  // уникальный дефайн моей Visual Studio
    #include <nlohmann/json.hpp>
#else
    #include "json.hpp"
#endif

using json = nlohmann::json;

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
//! \param inputJson            запрос клиента в json формате
//!
//! \return ответ клиенту в json формате
//!
//-----------------------------------------------------------------------------------------------------------------

    json NewArray(json inputJson);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ReactionOnRequests 
//! \brief Запускает расчёты сортировок по запросу клиента
//! 
//! \param inputJson            запрос клиента в json формате
//!
//! \return ответ клиенту в json формате
//!
//-----------------------------------------------------------------------------------------------------------------

    json CalculationResult(json inputJson, std::vector<int(*)(int left, int right, std::vector<int>parametrs,
                            int* swaping, int* comparisons, std::vector<int>* Array)>Functions);
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

//-----------------------------------------------------------------------------------------------------------------
//! структура для удобства хранения результатов
//-----------------------------------------------------------------------------------------------------------------

    struct ResultValue
    {
        std::vector<parameterForResults>    result;
    };

//=================================================================================================================
// Функции
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ServerNeed
//! функция перевода структуры parameterForResults в json формат
//-----------------------------------------------------------------------------------------------------------------

    void to_json(json& j, const parameterForResults & p) {
        j = json{{"swaping", p.swaping}, {"comparisons", p.comparisons}, {"numOfElements", p.numOfElements}};
    }

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ServerNeed
//! функция перевода структуры ResultValues в json формат
//-----------------------------------------------------------------------------------------------------------------

    void to_json(json& j, const ResultValue& p) {
        j = json{{"result", p.result}};
    }

}


//=================================================================================================================


namespace server {

//=================================================================================================================
// Блок констант
//=================================================================================================================
   
    const std::string DirInput  = "toServer\\"; ///< директория куда приходят запросы для сервера
    const std::string DirOutput = "toClient\\"; ///< директория куда отправляются ответы на запросы клиента

//=================================================================================================================
// Функции
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ServerNeed 
//! \brief Записывает все запросы пользователя
//! 
//! \param[out] listOfInputRequests   вектор куда будет записан список запросов клиента  
//!
//-----------------------------------------------------------------------------------------------------------------

    void GetListOfInputRequests (std::vector<std::string>* listOfInputRequests);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ServerNeed 
//! \brief Отправляет ответы на запросы пользователя
//! 
//! \param outputJson   ответ на запрос в формате json  
//!
//-----------------------------------------------------------------------------------------------------------------

    void SentAnswer(json outputJson);
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

    std::vector<std::string> listOfInputRequests;

    while (1)
    {
        //проверяем наличие запроса от клиента и совершаем нужные действия

        listOfInputRequests.clear();
        server::GetListOfInputRequests(&listOfInputRequests);

        if (listOfInputRequests.empty()) continue;

        txSleep(10);

        std::string lastRequests = listOfInputRequests[0];

        json            inputJson;
        std::string     path            = server::DirInput + lastRequests;
        std::ifstream   inputfile(path);

        inputfile >> inputJson;
        inputfile.close();

        remove((server::DirInput + lastRequests).c_str());

        if (inputJson["request"] == 1)
        {
            server::SentAnswer(requests::NewArray(inputJson));
        }

        if (inputJson["request"] == 2)
        {
            server::SentAnswer(requests::CalculationResult(inputJson, Functions));
        }

        txSleep(200);
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

    json NewArray(json inputJson)
    {
        json outputJson;
        std::vector<int> newArray = CreateArray(inputJson["numOfElements"].get<int>(), inputJson["isRandom"].get<bool>());

        outputJson["answer"]   = 1;
        outputJson["newArray"]  = newArray;

        return outputJson;
    }

//--------------------------------------------------------------------------------------------------------------

    json CalculationResult(json inputJson, std::vector<int(*)(int left, int right, std::vector<int>parametrs, 
                            int* swaping, int* comparisons, std::vector<int> * Array)> Functions)
    {
        std::vector<drawing::ResultValue> resultValue(Functions.size());   // вектор хранящий результаты расчётов

        std::vector<int>    Array               = inputJson["array"].get<std::vector<int>>();
        std::set<int>       activeFunctions     = inputJson["activeFunctions"].get<std::set<int>>();
        int                 swaping             = 0;
        int                 comparisons         = 0;
        int                 numOfElements       = inputJson["numOfElements"].get<int>();
        int                 minNumOfElements    = inputJson["minNumOfElements"].get<int>();
        int                 idButton            = 0;

        for (auto each : Functions)
        {
            if (activeFunctions.find(idButton) == activeFunctions.end()) //проверяем активна ли эта кнопка
            {
                idButton++;
                continue;
            }

            for (int i = minNumOfElements; i < numOfElements; i += 4)
            {
                std::vector<int>sortingArray = Array;

                swaping     = 0;
                comparisons = 0;

                each(0, i, {}, &swaping, &comparisons, &sortingArray); // запускаем функцию сортировки

                resultValue[idButton].result.push_back({ swaping, comparisons, i });
            }

            idButton++;
        }

        json outputJson;

        outputJson["answer"] = 2;
        outputJson["resultValue"] = resultValue;

        return outputJson;
    }
}


//=================================================================================================================


namespace server {

    void SentAnswer(json outputJson)
    {
        std::string nameFile    = std::to_string(time(0)) + ".json";
        std::string path        = server::DirOutput + nameFile;

        std::ofstream newFile(nameFile);

        newFile << std::setw(4) << outputJson;
        newFile.close();

        MoveFile((LPCSTR)nameFile.c_str(), (LPCSTR)path.c_str());
    }

//--------------------------------------------------------------------------------------------------------------

    void GetListOfInputRequests(std::vector<std::string>* listOfInputRequests)
    {
        assert(listOfInputRequests != nullptr);

        WIN32_FIND_DATA findFileData;


        std::string path = server::DirInput + "*.json";

        HANDLE hf = FindFirstFile((LPCSTR)(path).c_str(), &findFileData); // ищем первый запрос в виде файла форматом json

        if (hf != INVALID_HANDLE_VALUE) {

            do {
                listOfInputRequests->push_back(findFileData.cFileName); //запоминаем что есть такой файл
            } while (FindNextFile(hf, &findFileData) != 0);             //ищем следущий файл
            FindClose(hf);
        }
    }
}
