//! @file
//! \brief Программа визуализации алгоритмов сортировки
//! @mainpage
//!
//! Разметка объектов происходит в виртуальных координатах окна размером 1300x675
//!
//! \author TheCompiler
//! \version alpha 1
//! \date 04.08.2019
//-----------------------------------------------------------------------------------------------------------------
//! @defgroup PreCalculation    Расчёт значений
//! @defgroup WorkWithPerson    Работа с пользователем
//! @defgroup Drawing           Рисование
//! @defgroup ButtonsFunct      Функции кнопок
//=================================================================================================================

#include <iostream>
#include "TXLib.h"
#include <string>
#include <vector>
#include "Buttons.h"
#include <set>

namespace drawing
{

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
        COLORREF color;
        std::vector<parameterForResults>result;
    };

//=================================================================================================================
// Блок констант
//=================================================================================================================

    const int Width             = 1000;                     ///< ширина окна
    const int Height            = 515;                      ///< высота окна
    const COLORREF BackColor    = RGB(40, 120, 250);        ///< цвет фона
    const COLORREF SandColor    = RGB(255, 240, 212);       ///< песочный цвет
    const int AccuracyOfDiagram = 3;                        ///< значение отвечающее за маштаб сетки разметки; определяет на сколько частей будут разделяться обе оси
    const int VisualizPeriod    = 50;                       ///< определяет через сколько итераций будут обновлять результаты расчётов

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
//! \brief Запускает функции сортировок, получает из них значение и отправляет на визиализацию
//! 
//! структура Buttons::button из библиотке Buttons.h
//!
//! \param[in] usualButtons             вектор параметров обычных кнопок
//! \param[in] interchangeableButton    вектор параметров кнопок, среди которых может быть активна только одна
//! \param[in] buttonsOfFunction        вектор параметров кнопок функций сортировки 
//! \param[in] mainArray                сортеруемый массив
//! \param maxNumOfSwaping              максимальное число обменов 
//! \param maxNumOfComparisons          максимальное число сравнений
//! \param[out] resultValue             вектор результатов
//!
//-----------------------------------------------------------------------------------------------------------------

    void StartCalculation(std::vector<Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction,
                          std::vector<Buttons::button>* interchangeableButton, std::vector<int>* mainArray, int* maxNumOfSwaping,
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

    int(*CheckClickButtons(std::vector<button>* Buttons)) (int left, int right, std::vector<int>parametr,
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

    int Start(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Выход"
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int Exit(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Заполнения случаными числами"
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int Random(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Заполнения числами по убыванию"
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int NotRandom(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Возвращает маркер реакции на нажатия кнопки "Изменения размера сортеруемого массива"
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//-----------------------------------------------------------------------------------------------------------------

    int Changed(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);
    
//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief Функция сортировки кучей
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param left                 начало сортируемого участка
//! \param right                конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int heap_sort(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Сортировка вставкой
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param left                 начало сортируемого участка
//! \param right                конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int insertionSorting(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Сортировка пузырьком
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param left                 начало сортируемого участка
//! \param right                конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int bubbleSorting(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Сортировка вставкой
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param left                 начало сортируемого участка
//! \param right                конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! merge() функция объединяет два отсортированных участка массива в один отсортированный
//! 
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int mergeSorting(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Быстрая сортировка
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param left                 начало сортируемого участка
//! \param right                конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//!
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int quickSorting(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup ButtonsFunct
//! \brief   Сортировка выбором
//!
//! \param[out] swaping         число обменов
//! \param[out] comparisons     число сравнений
//! \param[out] Array           сортеруемый массив
//! \param left                 начало сортируемого участка
//! \param right                конец сортируемого участка включительно
//! 
//! Код в библиотеке ButtonsFunction.h
//! 
//! \return     Маркер нажатия кнопок функций сортировки
//!
//-----------------------------------------------------------------------------------------------------------------

    int selectionSorting(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array);

}


//=================================================================================================================


namespace drawing{

    int MaxNumOfElements = 1200; ///< переменная для хранения максимального числа элементов в сортируемом массиве
}


int main()
{
    txCreateWindow(drawing::Width, drawing::Height);        // создаём окно программы


    std::vector<int>mainArray = drawing::CreateArray();                                     // массив который подвергается сортировки
    std::vector<Buttons::button>usualButtons, buttonsOfFunction, interchangeableButton;     // вектора хранящие параметры для создания кнопок
    std::vector<drawing::ResultValue>resultValue;                                           // вектор хранящий результаты расчётов


    int RandomFilling       = 1;                        // перменная указывающя заполняем ли мы случайными числами сортируемый массив или нет
    int maxNumOfSwaping     = 1200;                     // максимальное число обменов (значение по умолчанию)
    int maxNumOfComparisons = 1200;                     // максимальное число сравнений (значение по умолчанию)
    int stateMouse          = txMouseButtons();         // состояние кнопки мыши


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
            auto resultSwaping = Buttons::CheckClickButtons(&interchangeableButton);
            if (resultSwaping != nullptr)
            {
                res = resultSwaping(0, 1, empty, &RandomFilling, &drawing::MaxNumOfElements, &mainArray);
                resultValue.clear();
            }

            auto resultFunction = Buttons::CheckClickButtons(&buttonsOfFunction);
            if (resultFunction != nullptr)
                res = -1;

            auto resultSimple = Buttons::CheckClickButtons(&usualButtons);
            if (resultSimple != nullptr)
            {
                res = resultSimple(0, 1, empty, &RandomFilling, &drawing::MaxNumOfElements, &mainArray);
                resultValue.clear();
            }
        }
        if (res == 0) // выход
        {
            resultValue.clear();
            break;
        }

        if (res != -2) // если мы что-то нажимали надо изменить картинку
        {
            txBegin();
            txClear();
            drawing::CreateEmptyCanvas(&usualButtons, &buttonsOfFunction, &interchangeableButton, 0);
            drawing::CreateEmptyDiagram(drawing::CoordinatesDiagramOfComparisons, maxNumOfComparisons);
            drawing::CreateEmptyDiagram(drawing::CoordinatesDiagramOfSwaping, maxNumOfSwaping);
            drawing::DrawResults(&resultValue, maxNumOfSwaping, maxNumOfComparisons);
            txEnd();
        }

        if (res == 1)   // запуск расчётов
            drawing::StartCalculation(&usualButtons, &buttonsOfFunction, &interchangeableButton, &mainArray,
                                      &maxNumOfSwaping, &maxNumOfComparisons, &resultValue);

        stateMouse = txMouseButtons();  // обновляем состояние кнопки мыши

        if (_kbhit())
        {
            const int key = _getch();
            if (key == 0x1B) break;     // если нажать Esc тоже программа прекратит работу
        }
    }
    
    return 0;
}

namespace drawing
{

    std::vector<int> CreateArray(bool isRandom)
    {
        std::vector<int> mainArray;     // сортируемый массив

        if (isRandom)                   // если заполнение случайными числами
        {
            int a = -1;
            for (int i = MaxNumOfElements; i > 0; i--)
            {
                a = int(random(1, int(1e8)));
                mainArray.push_back(a);
            }
            return mainArray;
        }

        for (int i = MaxNumOfElements; i > 0; i--)  // если заполнять поубыванию
            mainArray.push_back(i);

        return mainArray;
    }

    void StartCalculation(std::vector<Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction,
                          std::vector<Buttons::button>* interchangeableButton, std::vector<int>* mainArray, int* maxNumOfSwaping,
                          int* maxNumOfComparisons, std::vector<drawing::ResultValue>* resultValue)
    {
        assert(usualButtons != nullptr);
        assert(buttonsOfFunction != nullptr);
        assert(interchangeableButton != nullptr);
        assert(mainArray != nullptr);
        assert(resultValue != nullptr);
        assert(maxNumOfComparisons != nullptr);
        assert(maxNumOfSwaping != nullptr);
        assert(maxNumOfSwaping != maxNumOfComparisons);
        assert(usualButtons != buttonsOfFunction);
        assert(usualButtons != interchangeableButton);
        assert(interchangeableButton != buttonsOfFunction);

        (*maxNumOfSwaping)      = AccuracyOfDiagram + 1;
        (*maxNumOfComparisons)  = AccuracyOfDiagram + 1;

        resultValue->clear();                           // стрием старые расчёты
        resultValue->resize(buttonsOfFunction->size());

        int numOfButton = 0;

        for (Buttons::button oneButton : (*buttonsOfFunction))
        {
            if (!oneButton.isPressed)// если кнопка не нажата, то функция этой кнопки не используется в расчётах
                continue;

            int j = 1; // позваляет обновлять результаты визуализации каждые 50 измерений
            for (int i = AccuracyOfDiagram; i < MaxNumOfElements; i += 4)
            {
                int swaping = 0, comparisons = 0;

                // получаем результаты
                std::vector<int>parametrs;
                std::vector<int>sortingArray = (*mainArray);
                oneButton.linkToFunction(0, i, parametrs, &swaping, &comparisons, &sortingArray);

                // запоминаем цвет отображения функции и результаты
                (*resultValue)[numOfButton].color = oneButton.textColor;
                (*resultValue)[numOfButton].result.push_back({ swaping, comparisons, i+1 });

                (*maxNumOfSwaping) = MAX((*maxNumOfSwaping), swaping);
                (*maxNumOfComparisons) = MAX((*maxNumOfComparisons), comparisons);

                if (i >= j * VisualizPeriod || i + 4 >= MaxNumOfElements)
                {
                    // обновляем результаты
                    txBegin();
                    txClear();
                    CreateEmptyCanvas(usualButtons, buttonsOfFunction, interchangeableButton, 0);
                    CreateEmptyDiagram(CoordinatesDiagramOfComparisons, (*maxNumOfComparisons));
                    CreateEmptyDiagram(CoordinatesDiagramOfSwaping, (*maxNumOfSwaping));
                    DrawResults(resultValue, (*maxNumOfSwaping), (*maxNumOfComparisons));
                    txEnd();
                    j++;
                }
            }

            numOfButton++;
        }
        txMessageBox("Бухгалтеры закончили считать!", "Бюджетный отчёт"); // расчёты окончены
    }

    void DrawResults(std::vector<drawing::ResultValue>* resultValue, int maxNumOfSwaping, int maxNumOfComparisons)
    {
        assert(resultValue != nullptr);

        const int heightDiagram = 489; // высота диаграммы
        const int widthDiagram  = 429; // ширина диаграммы

        const double numElementsOnPixel     = MaxNumOfElements / double(widthDiagram - 14);      // число элементов на пиксель
        const double numSwapingOnPixel      = maxNumOfSwaping / double(heightDiagram - 14);      // число обменов на пиксель
        const double numComparisonsOnPixel  = maxNumOfComparisons / double(heightDiagram - 14);  // число сравнений на пиксель

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

    void DrawLeftAnatationOfDiagram(int xLine, int yLine, int lenText, int heightDiagram, int widthDiagram,
                                    int lenLine, int heightText, int gapBesideTextAndLine, int yMaxValue, int accuracy)
    {
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

    void CreateEmptyDiagram(std::pair<int, int>coordinates, int MaxNumOfParameterAxesX)
    {
        const int heightDiagram = 489; // высота диаграммы
        const int widthDiagram  = 429; // ширина диаграммы

        txSetColor(TX_BLACK);
        txSetFillColor(TX_BLACK);

        //рисуем окно диаграммы
        tx_Rectangle(coordinates.first, coordinates.second, coordinates.first + widthDiagram, coordinates.second + heightDiagram);

        txSetColor(SandColor);
        tx_SelectFont("Times New Roman", 17);

        // рисуем ось ординат
        DrawLeftAnatationOfDiagram(coordinates.first - 13, coordinates.second + 14, 66,
                                   heightDiagram - 15, widthDiagram, 13, 16,
                                   3, MaxNumOfParameterAxesX, AccuracyOfDiagram);

        // рисуем ось абцисс
        DrawUnderAnatationOfDiagram(coordinates.first, coordinates.second + heightDiagram, 13, 
                                    16, 3, widthDiagram - 10, heightDiagram, 
                                    52, MaxNumOfElements, AccuracyOfDiagram);
    }

    void CreateEmptyCanvas(std::vector <Buttons::button>* usualButtons, std::vector<Buttons::button>* buttonsOfFunction,
                           std::vector<Buttons::button>* interchangeableButton, bool defaultDiagram)
    {
        assert(usualButtons != nullptr);
        assert(buttonsOfFunction != nullptr);
        assert(interchangeableButton != nullptr);
        assert(usualButtons != buttonsOfFunction);
        assert(usualButtons != interchangeableButton);
        assert(interchangeableButton != buttonsOfFunction);

        txSetColor(BackColor);
        txSetFillColor(RGB(40, 120, 250));
        tx_Rectangle(0, 0, 1310, 675);

        if (defaultDiagram)
        {
            CreateEmptyDiagram(CoordinatesDiagramOfSwaping);        //диаграмма обменов
            CreateEmptyDiagram(CoordinatesDiagramOfComparisons);    //диаграмма сравнений
        }

        txSetColor(TX_SCARLET); //красный
        txSetFillColor(SandColor);
        
        // прописываем слова
        tx_SelectFont("Comic Sans MS", 52, FW_DONTCARE);
        tx_DrawText(339, 9, 1259, 79, "Результаты:", DT_CENTER);

        txSetColor(SandColor);
        tx_SelectFont("Comic Sans MS", 42, FW_DONTCARE);
        tx_DrawText(339, 66, 768, 135, "Обмены", DT_CENTER);

        tx_SelectFont("Comic Sans MS", 42, FW_DONTCARE);
        tx_DrawText(830, 66, 1259, 135, "Сравнения", DT_CENTER);

        txSetColor(TX_WHITE);
        tx_Line(0, 168, 286, 168);
        tx_Line(286, 0, 286, 675);

        txSetColor(RGB(252, 221, 118));
        tx_SelectFont("Comic Sans MS", 29, FW_DONTCARE);
        tx_TextOut(13, 13, "Заполнение массива:");
        tx_SelectFont("Comic Sans MS", 29, FW_DONTCARE);
        tx_TextOut(13, 174, "Функции сортировки:");

        // рисуем кнопки
        Buttons::DrawButtons(usualButtons);
        Buttons::DrawButtons(interchangeableButton);
        Buttons::DrawButtons(buttonsOfFunction);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Определяет параметры для кнопок
//!
//! \param[out] usualButtons                вектор параметров обычных кнопок
//! \param[out] interchangeableButton       вектор параметров кнопок, среди которых может быть активна только одна
//! \param[out] buttonsOfFunction           вектор параметров кнопок функций сортировки 
//!
//-----------------------------------------------------------------------------------------------------------------

    void CreateButtons(std::vector<Buttons::button>* usualButtons,std::vector<Buttons::button>* buttonsOfFunction, 
                       std::vector<Buttons::button>* interchangeableButton) {

        assert(usualButtons != nullptr);
        assert(buttonsOfFunction != nullptr);
        assert(interchangeableButton != nullptr);
        assert(usualButtons != buttonsOfFunction);
        assert(usualButtons != interchangeableButton);
        assert(interchangeableButton != buttonsOfFunction);

        POINT pos = { 13, 52 };
        POINT size = { 273, 95 };

        interchangeableButton->push_back({ 1,                               // id кнопки
                                "Заполнение случайными \n числами",         // текст на кнопке
                                pos, size, 10,                              // координаты и скругление кнопки
                                TX_SCARLET, BackColor, TX_WHITE,            // цвета кнопки
                                &Middle2,                                   // стиль текста кнопки
                                true, Buttons::InterchangeableButton,       // состояние кнопки
                                buttonsFunction::Random });                 // функция кнопки

//-----------------------------------------------------------------------------------------------------------------

        pos = { 13, 112 };
        size = { 273, 155 };

        interchangeableButton->push_back({ 2,                               // id кнопки
                                "Заполнение числами \n по убыванию",        // текст на кнопке
                                pos, size, 10,                              // координаты и скругление кнопки
                                TX_SCARLET, BackColor, TX_WHITE,            // цвета кнопки
                                &Middle2,                                   // стиль текста кнопки
                                false, Buttons::InterchangeableButton,      // состояние кнопки
                                buttonsFunction::NotRandom });              // функция кнопки

//=================================================================================================================

        pos = { 13, 569 };
        size = { 273, 635 };

        usualButtons->push_back({ 3,                                        // id кнопки
                                    "Поехали!",                             // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_SCARLET, BackColor, TX_WHITE,        // цвета кнопки
                                    &MainBeauty,                            // стиль текста кнопки
                                    false, Buttons::NonFixedButton,         // состояние кнопки
                                    buttonsFunction::Start });              // функция кнопки

//-----------------------------------------------------------------------------------------------------------------

        pos = { 13, 536 };
        size = { 273, 556 };

        usualButtons->push_back({ 4,                                        // id кнопки
                                    "Изменить число элементов",             // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_SCARLET, BackColor, TX_WHITE,        // цвета кнопки
                                    &Middle1,                               // стиль текста кнопки
                                    false, Buttons::NonFixedButton,         // состояние кнопки
                                    buttonsFunction::Changed });            // функция кнопки

//-----------------------------------------------------------------------------------------------------------------

        pos = { 13, 642 };
        size = { 273, 661 };

        usualButtons->push_back({ 5,                                        // id кнопки
                                    "Выход",                                // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_SCARLET, BackColor, TX_WHITE,        // цвета кнопки
                                    &Middle1,                               // стиль текста кнопки
                                    false, Buttons::NonFixedButton,         // состояние кнопки
                                    buttonsFunction::Exit });               // функция кнопки

//=================================================================================================================

        pos = { 13, 217 };
        size = { 130, 254 };

        buttonsOfFunction->push_back({ 6,                                   // id кнопки
                                    "Bubble",                               // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_RED, BackColor, TX_RED,              // цвета кнопки
                                    &Huge,                                  // стиль текста кнопки
                                    true, Buttons::FixedButton,             // состояние кнопки
                                    buttonsFunction::bubbleSorting });      // функция кнопки

//-----------------------------------------------------------------------------------------------------------------

        pos = { 143, 217 };
        size = { 273, 254 };

        buttonsOfFunction->push_back({ 7,                                   // id кнопки
                                    "Heap",                                 // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_GREEN, BackColor, TX_GREEN,          // цвета кнопки
                                    &Huge,                                  // стиль текста кнопки
                                    true, Buttons::FixedButton,             // состояние кнопки
                                    buttonsFunction::heap_sort });          // функция кнопки

//-----------------------------------------------------------------------------------------------------------------

        pos = { 13, 264 };
        size = { 130, 300 };

        buttonsOfFunction->push_back({ 8,                                   // id кнопки
                                    "Quick",                                // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_BLUE, BackColor, TX_BLUE,            // цвета кнопки
                                    &Huge,                                  // стиль текста кнопки
                                    true, Buttons::FixedButton,             // состояние кнопки
                                    buttonsFunction::quickSorting });       // функция кнопки

//------------------------------------------------------------------------------------------------------------------

        pos = { 143, 264 };
        size = { 273, 300 };

        buttonsOfFunction->push_back({ 9,                                   // id кнопки
                                    "Merge",                                // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_WHITE, BackColor, TX_WHITE,          // цвета кнопки
                                    &Huge,                                  // стиль текста кнопки
                                    true, Buttons::FixedButton,             // состояние кнопки
                                    buttonsFunction::mergeSorting });       // функция кнопки

//-----------------------------------------------------------------------------------------------------------------

        pos = { 13, 310 };
        size = { 130, 346 };

        buttonsOfFunction->push_back({ 10,                                  // id кнопки
                                    "Insertion",                            // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_ORANGE, BackColor, TX_ORANGE,        // цвета кнопки
                                    &Huge,                                  // стиль текста кнопки
                                    true, Buttons::FixedButton,             // состояние кнопки
                                    buttonsFunction::insertionSorting });   // функция кнопки

//---------------------------------------------------------------------------------------------------------------- -

        pos = { 143, 310 };
        size = { 273, 346 };

        buttonsOfFunction->push_back({ 11,                                  // id кнопки
                                    "Selection",                            // текст на кнопке
                                    pos, size, 10,                          // координаты и скругление кнопки
                                    TX_MAGENTA, BackColor, TX_MAGENTA,      // цвета кнопки
                                    &Huge,                                  // стиль текста кнопки
                                    true, Buttons::FixedButton,             // состояние кнопки
                                    buttonsFunction::selectionSorting });   // функция кнопки
    }
}