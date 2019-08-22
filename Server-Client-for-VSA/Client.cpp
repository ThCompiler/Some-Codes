//! @file
//! \brief Программа визуализации алгоритмов сортировки (VSA). Клиентская сторона
//! @mainpage
//!
//! Разметка объектов происходит в виртуальных координатах окна размером 1310x675
//!
//-----------------------------------------------------------------------------------------------------------------
//! \author     TheCompiler
//! \version    alpha 2.1
//! \date       22.08.2019
//-----------------------------------------------------------------------------------------------------------------
//!
//! @defgroup PreCalculation    Расчёт значений
//! @defgroup WorkWithPerson    Работа с пользователем
//! @defgroup Drawing           Рисование
//! @defgroup ButtonsFunct      Функции кнопок
//! @defgroup ServerNeed        Сулежбные функции сервера
//=================================================================================================================


#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <ctime>
#include <iomanip>

#include "Buttons.h"



namespace drawing {

//=================================================================================================================
// Блок структур
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
//! стиль текста
//! 
//! текст структуры в UpdateTXLib.h
//!
//-----------------------------------------------------------------------------------------------------------------

    struct textStyle;

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
        COLORREF                          color;
        std::vector<parameterForResults>  result;
    };


//=================================================================================================================
// Блок констант
//=================================================================================================================

    const COLORREF  BackColor           = RGB(40, 120, 250);        ///< цвет фона
    const COLORREF  SandColor           = RGB(252, 221, 118);       ///< песочный цвет
    const int       AccuracyOfDiagram   = 3;                        ///< значение отвечающее за маштаб сетки разметки; определяет на сколько частей будут разделяться обе оси
    const int       VisualizPeriod      = 50;                       ///< определяет через сколько итераций будут обновлять результаты расчётов

    const std::pair<int, int> CoordinatesDiagramOfSwaping       = std::make_pair(362, 135);     ///< координаты левеого верхнего угла диаграмма обменов
    const std::pair<int, int> CoordinatesDiagramOfComparisons   = std::make_pair(867, 135);     ///< координаты левеого верхнего угла диаграмма сравнений


//=================================================================================================================
// Блок стилей текста
//=================================================================================================================

    const textStyle MainBeauty  = { "Comic Sans MS", 39 };
    const textStyle Middle1     = { "Georgia", 16 };
    const textStyle Middle2     = { "Georgia", 19 };
    const textStyle Huge        = { "Georgia", 26 };


//=================================================================================================================
// Функции
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup PreCaculation
//! \brief Заполняет массив для сортировки
//! 
//! \param isRandom     вариант заполнения массива, true - случайными числами, false - числами в убыающем порядке
//!
//! \return Массив для сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    std::vector<int> CreateArray(bool isRandom = 1);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup PreCaculation
//! \brief Заполняет массив для сортировки
//! 
//! \param[out] usualButtons                вектор параметров обычных кнопок
//! \param[out] buttonsOfFunction           вектор параметров кнопок функций сортировки 
//! \param[out] interchangeableButton       вектор параметров кнопок, среди которых может быть активна только одна
//!
//-----------------------------------------------------------------------------------------------------------------

    void CreateButtons(std::vector<Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction, 
                       std::vector<Buttons::button>* interchangeableButton);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup WorkWithPerson
//! \brief Полученные значения от сервера отправляет на визиализацию
//! 
//! структура Buttons::button из библиотке Buttons.h
//!
//! \param[in] usualButtons             вектор параметров обычных кнопок
//! \param[in] interchangeableButton    вектор параметров кнопок, среди которых может быть активна только одна
//! \param[in] buttonsOfFunction        вектор параметров кнопок функций сортировки 
//! \param maxNumOfSwaping              максимальное число обменов 
//! \param maxNumOfComparisons          максимальное число сравнений
//! \param[out] resultValue             вектор результатов
//!
//-----------------------------------------------------------------------------------------------------------------
    void DrawAnswerFromServer(std::vector<Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction,
                              std::vector<Buttons::button>* interchangeableButton, int* maxNumOfSwaping,
                              int* maxNumOfComparisons, std::vector<drawing::ResultValue>* resultValue);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! \brief Рисует прямоугольник с круглёными углами радиусом R
//! 
//! код в библиотеке UpdateTXLib.h
//!
//! \param x0, y0       координаты левего верхнего угла прямоугольника
//! \param x1, y1       координаты правого нижнего угла прямоугольника
//! \param R            радиус скругления
//! \param color        цвет рамки "мягкого" прямоугольника
//!
//-----------------------------------------------------------------------------------------------------------------

    void DrawGentleRectangle(int x0, int y0, int x1, int y1, int R, COLORREF color);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! \brief Рисует внутри кнопки градиент от заданого цвета до более тёмного
//! 
//! код в библиотеке UpdateTXLib.h
//!
//! \param x0, y0       координаты левего верхнего угла кнопки
//! \param x1, y1       координаты правого нижнего угла кнопки
//! \param R            радиус скругления у кнопки
//! \param BackColor    цвет фона нажатой кнопки
//!
//-----------------------------------------------------------------------------------------------------------------

    void DrawFoneOfPushedButton(int x0, int y0, int x1, int y1, int R, COLORREF BackColor);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! \brief Визуализирует результаты расчётов
//! 
//! \param[in] resultValue          вектор результатов
//! \param maxNumOfSwaping          максимальное число обменов 
//! \param maxNumOfComparisons      максимальное число сравнений
//!
//-----------------------------------------------------------------------------------------------------------------

    void DrawResults(std::vector<drawing::ResultValue>* resultValue, int maxNumOfSwaping, int maxNumOfComparisons);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! \brief Рисует числа и линии оси ординат
//! 
//! \param xLine, yLine                         координаты левого верхнего угла начала линий оси ординат
//! \param lenTex                               длина чисел оси ординат
//! \param heightDiagram, int WidthDiagram      высота и ширина диаграмы
//! \param lenLine                              длина линии
//! \param heightText                           высота окна, в котором пишутся числа
//! \param gapBesideTextAndLine                 промежуток между текста
//! \param yMaxValue                            максимальное значение чисел на оси ординат 
//! \param accuracy                             число частей, на которые будут разделина ось ординат
//!
//-----------------------------------------------------------------------------------------------------------------

    void DrawLeftAnatationOfDiagram(int xLine, int yLine, int lenText, int heightDiagram, int widthDiagram,
                                    int lenLine, int heightText, int gapBesideTextAndLine, int yMaxValue, int accuracy = 2);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! \brief Рисует числа и линии оси абцисс
//! 
//! \param xLine, yLine                         координаты левого верхнего угла начала линий оси абцисс
//! \param lenLine                              длина линии
//! \param heightText                           высота окна, в котором пишутся числа
//! \param gapBesideTextAndLine                 промежуток между текста
//! \param heightDiagram, widthDiagram          высота и ширина диаграмы
//! \param lenText                              длина окна, в котором пишутся числа
//! \param xMaxValue                            максимальное значение чисел на оси абцисс 
//! \param accuracy                             число частей, на которые будут разделина ось абцисс
//!
//-----------------------------------------------------------------------------------------------------------------

    void DrawUnderAnatationOfDiagram(int xLine, int yLine, int lenLine, int heightText, int gapBesideTextAndLine,
                                     int widthDiagram, int heightDiagram, int lenText, int xMaxValue, int accuracy);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! \brief Рисует пустую диаграмму
//! 
//! \param coordinates                  координаты верхнего левого угла окна диаграммы
//! \param MaxNumOfParameterAxesX       максимальное число элементов оси абцисс 
//!
//-----------------------------------------------------------------------------------------------------------------

    void CreateEmptyDiagram(std::pair<int, int>coordinates, int MaxNumOfParameterAxesX = 1200);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//! Функция рисует пустой холст с кнопками, текстом и диаграммами. Если defaultDiagram = false, то диаграммы не рисуются
//! 
//! \param[in] usualButtons                 вектор параметров обычных кнопок
//! \param[in] buttonsOfFunction            вектор параметров кнопок функций сортировки 
//! \param[in] interchangeableButton        вектор параметров кнопок, среди которых может быть активна только одна
//! \param defaultDiagram                   маркер, отвечающий за рисования или нерисования диаграмм
//!
//-----------------------------------------------------------------------------------------------------------------

    void CreateEmptyCanvas(std::vector<Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction,
                           std::vector<Buttons::button>* interchangeableButton, bool defaultDiagram = true);

}

//=================================================================================================================

namespace server {

//=================================================================================================================
// Блок констант
//=================================================================================================================

    const std::string PathToServer = "C:\\Users\\Lrnovo\\Source\\Server-Client\\Server-Client\\Debug\\Server.exe";


//=================================================================================================================
// Функции
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ServerNeed
//! \brief Запускает сервер
//! 
//! \param[in] path     путь до сервера
//!
//-----------------------------------------------------------------------------------------------------------------

    void LaunchServer(const std::string* path);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ServerNeed
//! \brief Выключает сервер
//! 
//! \param[in] filename     имя сервера в диспетчере задач
//!
//-----------------------------------------------------------------------------------------------------------------

    void KillServer(std::string* filename);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ServerNeed 
//! \brief Отправляет запрос серверу на запуск расчётов и получает от него ответ
//! 
//! \param[in]  mainArray               массив для сортировки  
//! \param[in]  buttonsOfFunction       вектор кнопок функций
//! \param[out] resultValue             вектор результатов
//!
//-----------------------------------------------------------------------------------------------------------------

    void CaculationResultByServer(std::vector<int>* mainArray, std::vector<Buttons::button>* buttonsOfFunction,
                                  std::vector<drawing::ResultValue>* resultValue);

//-----------------------------------------------------------------------------------------------------------------
//! \brief Отправляет вектор через сокет
//! 
//! \param      to          сокет получателя
//! \param[in]  Array       вектор который нужно отправить
//!
//! Код в библиотеке UpdateTxNetworks.h
//!
//-----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void SendVector(TX_SOCKET to, std::vector<T>* Array);
 
//-----------------------------------------------------------------------------------------------------------------
//! \brief Получает вектор через сокет
//! 
//! \param      from        сокет отправителя
//! \param[out] Array       вектор который нужно отправить
//!
//! Код в библиотеке UpdateTxNetworks.h
//!
//-----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void GetVector(TX_SOCKET from, std::vector<T>* Array);
}


//=================================================================================================================


namespace Buttons {
    
//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief рисует кнопки
//!
//! \param[in] Buttons массив кнопок
//! 
//! Код в библиотеке Buttons.h
//!
//-----------------------------------------------------------------------------------------------------------------

    void DrawButtons(std::vector<button>* Buttons);

//-----------------------------------------------------------------------------------------------------------------
//! \brief обрабатывает нажатие на кнопки
//!
//! \param[in] Buttons массив кнопок
//! 
//! Код в библиотеке Buttons.h
//!
//! \return ссылку на функцию кнопки
//!
//-----------------------------------------------------------------------------------------------------------------

    int(*CheckClickButtons(std::vector<button>* Buttons)) (int left, int right, std::vector<int>parametrs,
                                                           int* swaping, int* comparisons, std::vector<int>* Array);

}


//=================================================================================================================


namespace buttonsFunction {

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Поехали!", то есть запуска расчётов
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int Start(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Выход"
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int Exit(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Заполнения случаными числами"
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int Random(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Заполнения числами по убыванию"
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int NotRandom(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Изменения размера сортеруемого массива"
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int Changed(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);
    
//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Функция сортировки кучей
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int heap_sort(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Сортировка вставкой
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int insertionSorting(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Сортировка пузырьком
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int bubbleSorting(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Сортировка вставкой
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! merge() функция объединяет два отсортированных участка массива в один отсортированный
//! 
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int mergeSorting(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Быстрая сортировка
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int quickSorting(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Сортировка выбором
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param      left            начало сортируемого участка
//! \param      right           конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//! 
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int selectionSorting(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array);

}


//=================================================================================================================


namespace drawing {

    int MaxNumOfElements = 1200; ///< переменная для хранения максимального числа элементов в сортируемом массиве
}



int main()
{
    printf("Search Server ...");

    while (!server::serverSocket._init)
    {
        server::serverSocket = txCreateSocket(TX_CLIENT, SERVER_IP);
    }

    printf("Connected to Server ...");
    int Width    = 1000;    // ширина окна
    int Height   = 515;     // высота окна

    txCreateWindow(Width, Height);          // создаём окно программы

    std::vector<int>                    mainArray = drawing::CreateArray();                         // массив который подвергается сортировки
    std::vector<Buttons::button>        usualButtons, buttonsOfFunction, interchangeableButton;     // вектора хранящие параметры для создания кнопок
    std::vector<drawing::ResultValue>   resultValue;                                                // вектор хранящий результаты расчётов

    int RandomFilling       = 1;                        // перменная указывающя заполняем ли мы случайными числами сортируемый массив или нет
    int maxNumOfSwaping     = 1200;                     // максимальное число обменов (значение по умолчанию)
    int maxNumOfComparisons = 1200;                     // максимальное число сравнений (значение по умолчанию)
    int stateMouse          = txMouseButtons();         // состояние мыши


    //server::LaunchServer(&server::PathToServer);
    drawing::CreateButtons(&usualButtons, &buttonsOfFunction, &interchangeableButton);
    
    txBegin();
    drawing::CreateEmptyCanvas(&usualButtons, &buttonsOfFunction, &interchangeableButton);
    txEnd();

    while (1)
    {
        std::vector<int> empty = { 1 };         // пустые перменные для функций кнопок
        
        int res = -2;                           // перменная запускаяющая реакций на нажатие кнопки


        if (stateMouse == 1 && txMouseButtons() != 1)
        {
            auto resultSwaping  =   Buttons::CheckClickButtons(&interchangeableButton);

            if (resultSwaping  != nullptr)
            {
                res = resultSwaping(0, 1, empty, &RandomFilling, &drawing::MaxNumOfElements, &mainArray);
                resultValue.clear();
            }

            auto resultFunction =   Buttons::CheckClickButtons(&buttonsOfFunction);

            if (resultFunction != nullptr)
                res = -1;

            auto resultSimple   =   Buttons::CheckClickButtons(&usualButtons);

            if (resultSimple  != nullptr)
            {
                res = resultSimple(0, 1, empty, &RandomFilling, &drawing::MaxNumOfElements, &mainArray);
                resultValue.clear();
            }
        }

        if (res != -2 ||
            (Width != txGetExtentX() || Height != txGetExtentY())) // если мы что-то нажимали надо изменить картинку
        {
            txBegin();
            txClear();
            drawing::CreateEmptyCanvas  (&usualButtons, &buttonsOfFunction, &interchangeableButton, 0);
            drawing::CreateEmptyDiagram (drawing::CoordinatesDiagramOfComparisons, maxNumOfComparisons);
            drawing::CreateEmptyDiagram (drawing::CoordinatesDiagramOfSwaping, maxNumOfSwaping);
            drawing::DrawResults        (&resultValue, maxNumOfSwaping, maxNumOfComparisons);
            txEnd();

            Width  = txGetExtentX();
            Height = txGetExtentY();

        }

        if (res == 1)   // отправляем запрос на результаты расчётов
        {
            server::CaculationResultByServer(&mainArray, &buttonsOfFunction, &resultValue);
            drawing::DrawAnswerFromServer(&usualButtons, &buttonsOfFunction, &interchangeableButton, 
                                              &maxNumOfSwaping, &maxNumOfComparisons, &resultValue);
        }

        stateMouse = txMouseButtons();  // обновляем состояние кнопки мыши

        if (res == 0) // выход
        {
            resultValue.clear();
            break;
        }


        if (_kbhit())
        {
            const int key = _getch();
            if (key == 0x1B) break;     // если нажать Esc тоже программа прекратит работу
        }
    }
    
    //server::KillServer(&(string)"Server.exe");
    return 0;
}




namespace drawing {
    
//-----------------------------------------------------------------------------------------------------------------
//! \brief   Определяет параметры для кнопок
//!
//! \param[out] usualButtons                вектор параметров обычных кнопок
//! \param[out] interchangeableButton       вектор параметров кнопок, среди которых может быть активна только одна
//! \param[out] buttonsOfFunction           вектор параметров кнопок функций сортировки 
//!
//-----------------------------------------------------------------------------------------------------------------

    void CreateButtons(std::vector<Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction, 
                       std::vector<Buttons::button>* interchangeableButton) {

        assert(usualButtons             != nullptr);
        assert(buttonsOfFunction        != nullptr);
        assert(interchangeableButton    != nullptr);
        assert(usualButtons             != buttonsOfFunction);
        assert(usualButtons             != interchangeableButton);
        assert(interchangeableButton    != buttonsOfFunction);

//  id кнопок функций всегда положительно, а остальных кнопок отрицательно (так удобней, не сохраняя ссылки на функции, знать к каким кнопкам они относятся)
//-----+----------------------------------+----+-----------------------------------------+-----+---------+-----+--------+-------+---------------+-----------+-----------+---------------+----------+-----------------------------------+------------------------------------+
//     |                                  | id | text on button                          | x0  | y0      | x1  | y1     | R     | frameColor    | backColor | textColor | style of text | IsActive | type of button                    | click response function            |
//-----+----------------------------------+----+-----------------------------------------+-----+---------+-----+--------+-------+---------------+-----------+-----------+---------------+----------+-----------------------------------+------------------------------------+
//     |                                  |    |                                         |     |         |     |        |       |               |           |           |               |          |                                   |                                    |
        interchangeableButton->push_back({ -1,  "Заполнение случайными \n числами",     { 13,   52  },  { 273,  95  },   10,     TX_SCARLET,     BackColor,  TX_WHITE,   &Middle2,       true,      Buttons::InterchangeableButton,     buttonsFunction::Random             });
        interchangeableButton->push_back({ -2,  "Заполнение числами \n по убыванию",    { 13,   112 },  { 273,  155 },   10,     TX_SCARLET,     BackColor,  TX_WHITE,   &Middle2,       false,     Buttons::InterchangeableButton,     buttonsFunction::NotRandom          });
        usualButtons->push_back         ({ -3,  "Поехали!",                             { 13,   569 },  { 273,  635 },   10,     TX_SCARLET,     BackColor,  TX_WHITE,   &MainBeauty,    false,     Buttons::NonFixedButton,            buttonsFunction::Start              });
        usualButtons->push_back         ({ -4,  "Изменить число элементов",             { 13,   536 },  { 273,  556 },   10,     TX_SCARLET,     BackColor,  TX_WHITE,   &Middle1,       false,     Buttons::NonFixedButton,            buttonsFunction::Changed            });
        usualButtons->push_back         ({ -5,  "Выход",                                { 13,   642 },  { 273,  661 },   10,     TX_SCARLET,     BackColor,  TX_WHITE,   &Middle1,       false,     Buttons::NonFixedButton,            buttonsFunction::Exit               });
        buttonsOfFunction->push_back    ({ 0,   "Bubble",                               { 13,   217 },  { 130,  254 },   10,     TX_RED,         BackColor,  TX_RED,     &Huge,          true,      Buttons::FixedButton,               buttonsFunction::bubbleSorting      });
        buttonsOfFunction->push_back    ({ 1,   "Heap",                                 { 143,  217 },  { 273,  254 },   10,     TX_GREEN,       BackColor,  TX_GREEN,   &Huge,          true,      Buttons::FixedButton,               buttonsFunction::heap_sort          });
        buttonsOfFunction->push_back    ({ 2,   "Quick",                                { 13,   264 },  { 130,  300 },   10,     TX_BLUE,        BackColor,  TX_BLUE,    &Huge,          true,      Buttons::FixedButton,               buttonsFunction::quickSorting       });
        buttonsOfFunction->push_back    ({ 3,   "Merge",                                { 143,  264 },  { 273,  300 },   10,     TX_WHITE,       BackColor,  TX_WHITE,   &Huge,          true,      Buttons::FixedButton,               buttonsFunction::mergeSorting       });
        buttonsOfFunction->push_back    ({ 4,   "Insertion",                            { 13,   310 },  { 130,  346 },   10,     TX_ORANGE,      BackColor,  TX_ORANGE,  &Huge,          true,      Buttons::FixedButton,               buttonsFunction::insertionSorting   });
        buttonsOfFunction->push_back    ({ 5,   "Selection",                            { 143,  310 },  { 273,  346 },   10,     TX_MAGENTA,     BackColor,  TX_MAGENTA, &Huge,          true,      Buttons::FixedButton,               buttonsFunction::selectionSorting   });
    }

}


//=================================================================================================================


namespace server {

    void CaculationResultByServer(std::vector<int>* mainArray, std::vector<Buttons::button>* buttonsOfFunction, 
                                  std::vector<drawing::ResultValue>* resultValue)
    {
        assert(mainArray            != nullptr);
        assert(buttonsOfFunction    != nullptr);
        assert(resultValue          != nullptr);

        txMessageBox("У бухгалтеров обед, ждите", "Справочная");

        std::vector<int>activeFunctions(buttonsOfFunction->size(), 0);

        for (auto each : (*buttonsOfFunction))
            if (each.isPressed)
                activeFunctions[each.id] = 1;
        
        int     numActiveButtons        = activeFunctions.size()    ;
        int     request                 = 2                         ;
        int     numOfElements           = drawing::MaxNumOfElements ;
        int     minNumOfElements        = drawing::AccuracyOfDiagram;


        //отправка запроса
        txSendTo(serverSocket, &request,                sizeof(request                 ));
        txSendTo(serverSocket, &numOfElements,          sizeof(numOfElements           ));
        txSendTo(serverSocket, &minNumOfElements,       sizeof(minNumOfElements        ));
       
        server::SendVector(serverSocket, mainArray);
        server::SendVector(serverSocket, &activeFunctions);


        //получение ответа
        std::vector<drawing::parameterForResults>  resultFromServer   = {};

        resultValue->clear  ();
        resultValue->resize (buttonsOfFunction->size());

        for (int i = 0; i < buttonsOfFunction->size(); i++)
        {
            server::GetVector(serverSocket, &resultFromServer);
            (*resultValue)[i] = { (*buttonsOfFunction)[i].textColor, resultFromServer};
        }
        
        txMessageBox("Бухгалтера поели. Начали работать", "Справочная");
    }

//-----------------------------------------------------------------------------------------------------------------

    void LaunchServer(const std::string* path)
    {
        assert(path != nullptr);

        ShellExecute(0, (LPCSTR)"open", (LPCSTR)path->c_str(), NULL, 0, SW_SHOW); 
    }

//-----------------------------------------------------------------------------------------------------------------

    void KillServer(std::string* filename)
    {
        assert(filename != nullptr);

        HANDLE          snapShot                = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
        PROCESSENTRY32  currentProcess;
                        currentProcess.dwSize   = sizeof (currentProcess);
        BOOL            res                     = Process32First(snapShot, &currentProcess);

        while (res)
        {
            if (strcmp(currentProcess.szExeFile, filename->c_str()) == 0)
            {
                HANDLE process = OpenProcess(PROCESS_TERMINATE, 0, (DWORD) currentProcess.th32ProcessID);

                if (process != NULL)
                {
                    TerminateProcess    (process, 9);
                }
            }
            res = Process32Next(snapShot, &currentProcess);
        }
        CloseHandle(snapShot);
    }
}


//=================================================================================================================


namespace drawing {

    std::vector<int> CreateArray(bool isRandom)
    {
        std::vector<int> mainArray;     // сортируемый массив

        if (isRandom)                   // если заполнение случайными числами
        {
            int a = -1;
            for (int i = MaxNumOfElements; i > 0; i--)
            {
                a = int(random(std::nomeow, 1, int(1e8)));
                mainArray.push_back(a);
            }
            return mainArray;
        }

        for (int i = MaxNumOfElements; i > 0; i--)  // если заполнять поубыванию
            mainArray.push_back(i);

        return mainArray;
    }

//-----------------------------------------------------------------------------------------------------------------

    void DrawAnswerFromServer(std::vector<Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction,
                              std::vector<Buttons::button>* interchangeableButton, int* maxNumOfSwaping,
                              int* maxNumOfComparisons, std::vector<drawing::ResultValue>* resultValue)
    {
        assert(usualButtons             != nullptr);
        assert(buttonsOfFunction        != nullptr);
        assert(interchangeableButton    != nullptr);
        assert(resultValue              != nullptr);
        assert(maxNumOfComparisons      != nullptr);
        assert(maxNumOfSwaping          != nullptr);
        assert(maxNumOfSwaping          != maxNumOfComparisons);
        assert(usualButtons             != buttonsOfFunction);
        assert(usualButtons             != interchangeableButton);
        assert(interchangeableButton    != buttonsOfFunction);

        if(resultValue->empty())
            return (void)txMessageBox("Бухгалтеры закончили считать!", "Бюджетный отчёт");

        (*maxNumOfSwaping)      = AccuracyOfDiagram + 1;
        (*maxNumOfComparisons)  = AccuracyOfDiagram + 1;

        std::vector<ResultValue>interimResult(buttonsOfFunction->size());

        for (Buttons::button oneButton : (*buttonsOfFunction))
        {
            if (!oneButton.isPressed) // если кнопка не нажата, то функция этой кнопки не используется в расчётах
                continue;

            interimResult[oneButton.id].color = (*resultValue)[oneButton.id].color;

            for (auto each : (*resultValue)[oneButton.id].result)
            {
                (*maxNumOfSwaping)      = max(each.swaping,     (*maxNumOfSwaping));
                (*maxNumOfComparisons)  = max(each.comparisons, (*maxNumOfComparisons));

                interimResult[oneButton.id].result.push_back(each);

                // обновляем результаты
                txBegin();
                txClear();
                CreateEmptyCanvas   (usualButtons, buttonsOfFunction, interchangeableButton, 0);
                CreateEmptyDiagram  (CoordinatesDiagramOfComparisons, (*maxNumOfComparisons));
                CreateEmptyDiagram  (CoordinatesDiagramOfSwaping, (*maxNumOfSwaping));
                DrawResults         (&interimResult, (*maxNumOfSwaping), (*maxNumOfComparisons));
                txEnd();
            }
        }

        txMessageBox("Бухгалтеры закончили считать!", "Бюджетный отчёт"); // расчёты окончены
    }

//-----------------------------------------------------------------------------------------------------------------

    void DrawResults(std::vector<drawing::ResultValue>* resultValue, int maxNumOfSwaping, int maxNumOfComparisons)
    {
        assert(resultValue != nullptr);

        const int heightDiagram = 489; // высота диаграммы
        const int widthDiagram  = 429; // ширина диаграммы

        const double numElementsOnPixel     = MaxNumOfElements      / double(widthDiagram - 14);    // число элементов на пиксель
        const double numSwapingOnPixel      = maxNumOfSwaping       / double(heightDiagram - 14);   // число обменов на пиксель
        const double numComparisonsOnPixel  = maxNumOfComparisons   / double(heightDiagram - 14);   // число сравнений на пиксель

        for (auto i = resultValue->begin(); i != resultValue->end(); i++)
            for (auto j = i->result.begin(); j != i->result.end(); j++)
            {
                // рисуем в диаграмме обменов
                tx_SetPixel(CoordinatesDiagramOfSwaping.first + j->numOfElements / (numElementsOnPixel),
                            CoordinatesDiagramOfSwaping.second + heightDiagram - j->swaping / (numSwapingOnPixel),
                            i->color);

                // рисуем в диаграмме сравнений
                tx_SetPixel(CoordinatesDiagramOfComparisons.first + j->numOfElements / (numElementsOnPixel),
                            CoordinatesDiagramOfComparisons.second + heightDiagram - j->comparisons / (numComparisonsOnPixel),
                            i->color);
            }
    }

//-----------------------------------------------------------------------------------------------------------------

    void DrawLeftAnatationOfDiagram(int xLine, int yLine, int lenText, int heightDiagram, int widthDiagram,
                                    int lenLine, int heightText, int gapBesideTextAndLine, int yMaxValue, int accuracy)
    {
        assert(accuracy > 0);

        const int xText = xLine - lenText;
        const int yText = yLine - heightText / 2 - 1;

        for (int i = 0; i <= accuracy; i++)
        {
            tx_Line(xLine, yLine + heightDiagram * i / accuracy,                                     // линия у числа
                    xLine + lenLine, yLine + heightDiagram * i / accuracy);
            tx_Line(xLine + lenLine, yLine + heightDiagram * i / accuracy,                           // линия на диаграмме
                    xLine + lenLine + widthDiagram, yLine + heightDiagram * i / accuracy);

            tx_DrawText(xText, yText + heightDiagram * i / accuracy, xLine - gapBesideTextAndLine,   // число
                        yText + heightText + heightDiagram * i / accuracy,
                        std::to_string(yMaxValue * (accuracy - i) / accuracy).c_str(), DT_RIGHT | DT_VCENTER);
        }
    }

//-----------------------------------------------------------------------------------------------------------------

    void DrawUnderAnatationOfDiagram(int xLine, int yLine, int lenLine, int heightText, int gapBesideTextAndLine,
                                     int widthDiagram,  int heightDiagram, int lenText, int xMaxValue, int accuracy)
    {
        assert(accuracy > 0);

        for (int i = 0; i <= accuracy; i++)
        {
            tx_Line(xLine + widthDiagram * i / accuracy, yLine,                      // линия у числа
                    xLine + widthDiagram * i / accuracy, yLine + lenLine);
            tx_Line(xLine + widthDiagram * i / accuracy, yLine,                      // линия на диаграмме
                    xLine + widthDiagram * i / accuracy, yLine - heightDiagram);

            // число
            tx_DrawText(xLine - lenText/2 + widthDiagram * i / accuracy, yLine + heightText + gapBesideTextAndLine,
                        xLine + lenText/2 + widthDiagram * i / accuracy, yLine + 2 * heightText + gapBesideTextAndLine,
                        std::to_string(xMaxValue * i / accuracy).c_str(), DT_CENTER | DT_VCENTER);
        }
    }

//-----------------------------------------------------------------------------------------------------------------

    void CreateEmptyDiagram(std::pair<int, int>coordinates, int MaxNumOfParameterAxesX)
    {
        const int heightDiagram = 489; // высота диаграммы
        const int widthDiagram  = 429; // ширина диаграммы

        txSetColor      (TX_BLACK);
        txSetFillColor  (TX_BLACK);

        //рисуем окно диаграммы
        tx_Rectangle(coordinates.first, coordinates.second, coordinates.first + widthDiagram, coordinates.second + heightDiagram);

        txSetColor      (SandColor);
        tx_SelectFont   ("Times New Roman", 17);

        // рисуем ось ординат
        DrawLeftAnatationOfDiagram  (coordinates.first - 13, coordinates.second + 14, 66,
                                     heightDiagram - 15, widthDiagram, 13, 16,
                                     3, MaxNumOfParameterAxesX, AccuracyOfDiagram);

        // рисуем ось абцисс
        DrawUnderAnatationOfDiagram (coordinates.first, coordinates.second + heightDiagram, 13, 
                                     16, 3, widthDiagram - 10, heightDiagram, 
                                     52, MaxNumOfElements, AccuracyOfDiagram);
    }

//-----------------------------------------------------------------------------------------------------------------

    void CreateEmptyCanvas(std::vector <Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction,
                           std::vector<Buttons::button>* interchangeableButton, bool defaultDiagram)
    {
        assert(usualButtons             != nullptr);
        assert(buttonsOfFunction        != nullptr);
        assert(interchangeableButton    != nullptr);
        assert(usualButtons             != buttonsOfFunction);
        assert(usualButtons             != interchangeableButton);
        assert(interchangeableButton    != buttonsOfFunction);

        txSetColor      (BackColor);
        txSetFillColor  (RGB(40, 120, 250));

        tx_Rectangle(0, 0, 1310, 675);

        if (defaultDiagram)
        {
            CreateEmptyDiagram(CoordinatesDiagramOfSwaping);        //диаграмма обменов
            CreateEmptyDiagram(CoordinatesDiagramOfComparisons);    //диаграмма сравнений
        }

        txSetColor      (TX_SCARLET); //красный
        txSetFillColor  (SandColor);
        
        // прописываем слова
        tx_SelectFont("Comic Sans MS", 52, FW_DONTCARE);
        tx_DrawText(339, 9, 1259, 79, "Результаты:", DT_CENTER);

        txSetColor(SandColor);

        tx_SelectFont   ("Comic Sans MS", 42, FW_DONTCARE);
        tx_DrawText     (339, 66, 768, 135, "Обмены", DT_CENTER);

        tx_SelectFont   ("Comic Sans MS", 42, FW_DONTCARE);
        tx_DrawText     (830, 66, 1259, 135, "Сравнения", DT_CENTER);

        txSetColor(TX_WHITE);
        
        tx_Line(0, 168, 286, 168);
        tx_Line(286, 0, 286, 675);

        txSetColor(RGB(252, 221, 118));

        tx_SelectFont   ("Comic Sans MS", 29, FW_DONTCARE);
        tx_TextOut      (13, 13, "Заполнение массива:");

        tx_SelectFont   ("Comic Sans MS", 29, FW_DONTCARE);
        tx_TextOut      (13, 174, "Функции сортировки:");

        // рисуем кнопки
        Buttons::DrawButtons(usualButtons);
        Buttons::DrawButtons(interchangeableButton);
        Buttons::DrawButtons(buttonsOfFunction);
    }
}