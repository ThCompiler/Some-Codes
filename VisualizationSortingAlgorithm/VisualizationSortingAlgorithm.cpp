//! @file
//! \brief Программа визуализации алгоритмов сортировки
//! \author TheCompiler
//! \version alpha 0.1
//! \date 26.07.2019
//! @defgroup PreCaculation		Расчёт значений
//! @defgroup WorkWithPerson	Работа с пользователем
//! @defgroup Drawing			Рисование
#include <iostream>
#include "TXLib.h"
#include <string>
#include <vector>
#include "Buttons.h"
#include <set>
#include "SortingFunction.h"

namespace drawing
{
//Блок структур
//-----------------------------------------------------------------------------------------------------------------
	//! структура для удобства хранения результатов
	struct parameterForResults
	{
		int swaping, comparisons, numOfElements;
	};
	//! структура для удобства хранения результатов
	struct ResultValue
	{
		COLORREF color;
		std::vector<parameterForResults>result;
	};
//Блок констант
//-----------------------------------------------------------------------------------------------------------------
	const int Width = 1100; ///< ширина окна
	const int Height = Width*675/1100; ///< высота окна
	const int Boundaries = Width * 0.03; ///< унивирсальная константа, упращающая процесс расположения объектов
	const COLORREF BackColor = RGB(40, 120, 250); ///< цвет фона
	const COLORREF SandColor = RGB(255, 240, 212); ///< песочный цвет
	const int AccuracyOfDiagram = 3; ///< значение отвечающее за маштаб сетки разметки; определяет на сколько частей будут разделяться обе оси
	const int VisualizPeriod = 50; ///< определяет через сколько итераций будут обновлять результаты расчётов
	const std::pair<int, int> CoordinatesDiagramOfSwaping = std::make_pair(Width * 0.21 + Boundaries * 2, Height * 0.2);///< координаты левеого верхнего угла диаграмма обменов
	const std::pair<int, int> CoordinatesDiagramOfComparisons = std::make_pair(Width * 0.21 + Boundaries * 3.9 + Width * 0.33, Height * 0.2); ///< координаты левеого верхнего угла диаграмма сравнений
//=================================================================================================================
//! @ingroup PreCaculation
//!	\brief Заполняет массив для сортировки
//! 
//! \param isRandom		вариант заполнения массива, true - случайными числами, false - числами в убыающем порядке
//!
//! \return Массив для сортировки
//!
	std::vector<int> CreateArray(bool isRandom = 1);

//=================================================================================================================
//! @ingroup WorkWithPerson
//!	\brief Запускает функции сортировок, получает из них значение и отправляет на визиализацию
//! 
//!	структура button из библиотке Buttons.h
//! \param[in] simpleButtons		вектор параметров обычных кнопок
//! \param[in] swapButtons			вектор параметров кнопок, среди которых может быть активна только одна
//! \param[in] functionButtons		вектор параметров кнопок функций сортировки 
//!	\param[in] mainArray			сортеруемый массив
//! \param maxNumOfSwaping			максимальное число обменов 
//! \param maxNumOfComparisons		максимальное число сравнений
//! \param[out] resultValue			вектор результатов
//!
	void StartAccount(std::vector<button>* simpleButtons, std::vector<button>* functionButtons,
							std::vector<button>* swapButtons, std::vector<int>* mainArray, int* maxNumOfSwaping,
							int* maxNumOfComparisons, std::vector<drawing::ResultValue>* resultValue);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup WorkWithPerson
//!	\brief Определяет какая кнопка нажата и совершает соответствующие ей действия
//! 
//!	структура button из библиотке Buttons.h
//! \param oneButton		параметры кнопки которую нажали
//! \param[out] end			маркер окончания работы программы; true - значение окончания программы
//!	\param[in] mainArray	сортеруемый массив
//!
//! \return Маркер для запуска расчётов; true - будут запущены расчёты, false - не будут
//!
	bool ReactionOnClick(button oneButton, bool* end, std::vector<int>* mainArray);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup WorkWithPerson
//!	\brief Проверяет нажата ли какая-либо кнопка и делает соответствующее каждой действияя
//!
//!	структура button из библиотке Buttons.h
//! \param[in] simpleButtons		вектор параметров обычных кнопок
//! \param[in] functionButtons		вектор параметров кнопок функций сортировки 
//! \param[out] end					маркер окончания работы программы; true - значение окончания программы
//! \param[in] swapButtons			вектор параметров кнопок, среди которых может быть активна только одна
//!	\param[in] mainArray			сортеруемый массив
//! \param maxNumOfSwaping			максимальное число обменов 
//! \param maxNumOfComparisons		максимальное число сравнений
//! \param[out] resultValue			вектор результатов
//!	
//! \return Маркер для запуска расчётов; Значение из функции ReactionOnClick() 
//!
	bool CheckClickOrPushing(std::vector<button>* simpleButtons, std::vector<button>* functionButtons, bool* end,
								std::vector<button>* swapButtons, std::vector<int>* mainArray, int maxNumOfSwaping,
								int maxNumOfComparisons, std::vector<drawing::ResultValue>* resultValue);

//=================================================================================================================
//! @ingroup Drawing
//!	\brief Визуализирует эффект клика на кнопку
//! 
//!	структура button из библиотке Buttons.h
//! \param oneButton	параметры кнопки которую нажали
//!
	void ClickButton(button oneButton);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	\brief Рисует прямоугольник с круглёными углами радиусом R
//! 
//! \param x0, y0		координаты левего верхнего угла прямоугольника
//! \param x1, y1		координаты правого нижнего угла прямоугольника
//! \param R			радиус скругления
//! \param color		цвет рамки "мягкого" прямоугольника
//!
	void DrawGentleRectangle(int x0, int y0, int x1, int y1, int R, COLORREF color);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	\brief Визуализирует результаты расчётов
//! 
//! \param[in] resultValue			вектор результатов
//! \param maxNumOfSwaping			максимальное число обменов 
//! \param maxNumOfComparisons		максимальное число сравнений
//!
	void DrawResults(std::vector<drawing::ResultValue>* resultValue, int maxNumOfSwaping, int maxNumOfComparisons);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	\brief Рисует внутри кнопки градиент от заданого цвета до более тёмного
//! 
//! \param x0, y0		координаты левего верхнего угла кнопки
//! \param x1, y1		координаты правого нижнего угла кнопки
//! \param R			радиус скругления у кнопки
//!
	void DrawFoneOfPushedButton(int x0, int y0, int x1, int y1, int R);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	\brief Рисует кнопки
//! 
//!	структура button из библиотке Buttons.h
//! \param oneButton	параметры кнопки которую надо нарисовать
//! \param withContur	маркер наличия контура у кнопки; true - у кнопки будет контур, false - не будет
//!
	void DrawButton(button oneButton, bool withContur = true);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	\brief Рисует числа и линии оси ординат
//! 
//! \param xLine, yLine							координаты левого верхнего угла начала линий оси ординат
//! \param lenTex								длина чисел оси ординат
//! \param heightDiagram, int WidthDiagram		высота и ширина диаграмы
//! \param lenLineAndHeightText					длина линии и высота окна, в котором пишутся числа
//!	\param gapBesideTextAndLine					промежуток между текста
//! \param yMaxValue							максимальное значение чисел на оси ординат 
//! \param accuracy								число частей, на которые будут разделина ось ординат
//!
	void DrawLeftAnatationOfDiagram(int xLine, int yLine, int lenText, int heightDiagram, int widthDiagram,
								int lenLineAndHeightText, int gapBesideTextAndLine, int yMaxValue, int accuracy = 2);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	\brief Рисует числа и линии оси абцисс
//! 
//! \param xLine, yLine							координаты левого верхнего угла начала линий оси абцисс
//! \param lenLineAndHeightText					длина линии и высота окна, в котором пишутся числа
//!	\param gapBesideTextAndLine					промежуток между текста
//! \param heightDiagram, int widthDiagram		высота и ширина диаграмы
//! \param lenText								длина окна, в котором пишутся числа
//! \param xMaxValue							максимальное значение чисел на оси абцисс 
//! \param accuracy								число частей, на которые будут разделина ось абцисс
//!
	void DrawUnderAnatationOfDiagram(int xLine, int yLine, int lenLineAndHeightText, int gapBesideTextAndLine,
									int widthDiagram, int heightDiagram, int lenText, int xMaxValue, int accuracy = 2);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	\brief Рисует пустую диаграмму
//! 
//! \param coordinates					координаты верхнего левого угла окна диаграммы
//! \param MaxNumOfParameterAxesX		максимальное число элементов оси абцисс 
//!
	void CreateEmptyDiagram(std::pair<int, int>coordinates, int MaxNumOfParameterAxesX = 1200);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	Функция рисует пустой холст с кнопками, текстом и диаграммами. Если defaultDiagram = false, то диаграммы не рисуются
//! 
//! \param[in] simpleButtons		вектор параметров обычных кнопок
//! \param[in] functionButtons		вектор параметров кнопок функций сортировки 
//! \param[in] swapButtons			вектор параметров кнопок, среди которых может быть активна только одна
//!	\param defaultDiagram			маркер, отвечающий за рисования или нерисования диаграмм
//!
	void CreateEmptyCanvas(std::vector<button>* simpleButtons, std::vector<button>* functionButtons,
								std::vector<button>* swapButtons, bool defaultDiagram = true);

//=================================================================================================================
	int MaxNumOfElements = 1200; ///< переменная для хранения максимального числа элементов в сортируемом массиве
	bool RandomFilling = true; ///< перменная указывающя заполняем ли мы случайными числами сортируемый массив или нет
}

int main()
{
	std::vector<int>mainArray = drawing::CreateArray(); // массив который подвергается сортировки
	// вектора хранящие параметры для создания кнопок
	std::vector<drawing::button>simpleButtons, functionButtons, swapButtons; 
	std::vector<drawing::ResultValue>resultValue;// вектор хранящий результаты расчётов
	int maxNumOfSwaping = 1200; // максимальное число обменов (значение по умолчанию)
	int maxNumOfComparisons = 1200; // максимальное число сравнений (значение по умолчанию)

	drawing::CreateButtons(drawing::Height, drawing::Width, drawing::Boundaries,
											&simpleButtons, &functionButtons, &swapButtons);

	txCreateWindow(drawing::Width, drawing::Height);
	
	txBegin();
	drawing::CreateEmptyCanvas(&simpleButtons, &functionButtons, &swapButtons);
	txEnd();

	while (1)
	{
		bool end = false; // перменная запускающая выход из программы

		//перменная запускаяющая расчёты
		const bool started = drawing::CheckClickOrPushing(&simpleButtons, &functionButtons, &end, &swapButtons, 
														&mainArray, maxNumOfSwaping, maxNumOfComparisons, &resultValue);
		txSleep(50);

		if (end) // выход
			break;

		if (started)// запуск расчётов
			drawing::StartAccount(&simpleButtons, &functionButtons, &swapButtons, &mainArray, 
															&maxNumOfSwaping, &maxNumOfComparisons, &resultValue);
		if (_kbhit())
		{
			const int key = _getch();
			if (key == 0x1B) break; // если нажать Esc тоже программа прекратит работу
		}
	}
	
	return 0;
}

namespace drawing
{
	std::vector<int> CreateArray(bool isRandom)
	{
		std::vector<int> mainArray; // сортируемый массив
		if (isRandom) // если заполнение случайными числами
		{
			int a = -1;
			for (int i = MaxNumOfElements; i > 0; i--)
			{
				a = int(random(1, int(1e8)));
				mainArray.push_back(a);
			}
			return mainArray;
		}
		for (int i = MaxNumOfElements; i > 0; i--) // если заполнять поубыванию
			mainArray.push_back(i);
		return mainArray;
	}

	void StartAccount(std::vector<button>* simpleButtons, std::vector<button>* functionButtons,
						std::vector<button>* swapButtons, std::vector<int>* mainArray, int* maxNumOfSwaping,
						int* maxNumOfComparisons, std::vector<drawing::ResultValue>* resultValue)
	{
		assert(simpleButtons != nullptr);
		assert(functionButtons != nullptr);
		assert(swapButtons != nullptr);
		assert(mainArray != nullptr);
		assert(resultValue != nullptr);
		assert(maxNumOfComparisons != nullptr);
		assert(maxNumOfSwaping != nullptr);
		assert(maxNumOfSwaping != maxNumOfComparisons);
		assert(simpleButtons != functionButtons);
		assert(simpleButtons != swapButtons);
		assert(swapButtons != functionButtons);

		(*maxNumOfSwaping) = AccuracyOfDiagram + 1;
		(*maxNumOfComparisons) = AccuracyOfDiagram + 1;
		resultValue->clear(); // стрием старые расчёты
		resultValue->resize(functionButtons->size());
		int numOfButton = 0;

		for (button oneButton : (*functionButtons))
		{
			if (!oneButton.isPushing)// если кнопка не нажата, то функция этой кнопки не используется в расчётах
				continue;

			int j = 1; // позваляет обновлять результаты визуализации каждые 50 измерений
			for (int i = AccuracyOfDiagram; i < MaxNumOfElements; i += 4)
			{
				int swaping = 0, comparisons = 0;
				// получаем результаты
				sorting::GetResultOfAccount(&swaping, &comparisons, (*mainArray), oneButton.text, i);

				// запоминаем цвет отображения функции и результаты
				(*resultValue)[numOfButton].color = oneButton.textColor;
				(*resultValue)[numOfButton].result.push_back({ swaping, comparisons, i });

				(*maxNumOfSwaping) = MAX((*maxNumOfSwaping), swaping);
				(*maxNumOfComparisons) = MAX((*maxNumOfComparisons), comparisons);

				if (i >= j * VisualizPeriod)
				{
					// обновляем результаты
					txBegin();
					txClear();
					CreateEmptyCanvas(simpleButtons, functionButtons, swapButtons, 0);
					CreateEmptyDiagram(CoordinatesDiagramOfComparisons, (*maxNumOfComparisons));
					CreateEmptyDiagram(CoordinatesDiagramOfSwaping, (*maxNumOfSwaping));
					DrawResults(resultValue, (*maxNumOfSwaping), (*maxNumOfComparisons));
					txEnd();
					j++;
				}
			}

			txBegin();
			txClear();
			CreateEmptyCanvas(simpleButtons, functionButtons, swapButtons, 0);
			CreateEmptyDiagram(CoordinatesDiagramOfComparisons, (*maxNumOfComparisons));
			CreateEmptyDiagram(CoordinatesDiagramOfSwaping, (*maxNumOfSwaping));
			DrawResults(resultValue, (*maxNumOfSwaping), (*maxNumOfComparisons));
			txEnd();

			numOfButton++;
		}
		txMessageBox("Бухгалтеры закончили считать!", "Бюджетный отчёт"); // расчёты окончены
	}

	bool ReactionOnClick(button oneButton, bool* end, std::vector<int>* mainArray)
	{

		if (oneButton.text == "Поехали!")
		{
			return true; // говорим что можно начинать считать
		}
		else if (oneButton.text == "Изменить число элементов") //меняем максиамльное число элементов в счетовом массиве
		{
			int input = std::atoi(txInputBox("Какие максимальное число элементов может быть в массиве?",
				"Настройки", std::to_string(MaxNumOfElements).c_str()));
			if (input > int(1e8))
				txMessageBox("Слишком много ввёл. Не дождёшься результата. Максимально можешь ввести до 10^8.", 
																									"Тех. поддержка");
			else
			{
				MaxNumOfElements = input;
				(*mainArray) = CreateArray(RandomFilling);
			}
		}
		else if (oneButton.text == "Выход")
		{
			*end = true; //выходим из программы
		}
		return false;
	}

	bool CheckClickOrPushing(std::vector<button>* simpleButtons, std::vector<button>* functionButtons, bool* end,
							std::vector<button>* swapButtons, std::vector<int>* mainArray, int maxNumOfSwaping,
							int maxNumOfComparisons, std::vector<drawing::ResultValue>* resultValue)
	{
		assert(simpleButtons != nullptr);
		assert(functionButtons != nullptr);
		assert(mainArray != nullptr);
		assert(swapButtons != nullptr);
		assert(resultValue != nullptr);
		assert(simpleButtons != functionButtons);
		assert(simpleButtons != swapButtons);
		assert(swapButtons != functionButtons);

		bool pushed = false; // нажималась ли какая-то кнопка
		bool started = false; // пора ли нам начинать считать

		if (txMouseButtons() == 1)// проверяем нажата ли левая кнока мыши
		{
			const int x = txMouseX(), y = txMouseY();
			for (int i = 0; i < (*simpleButtons).size(); i++) // проверяем обычные кнопки
				if (In(x, (*simpleButtons)[i].x0, (*simpleButtons)[i].x1)
					&& In(y, (*simpleButtons)[i].y0, (*simpleButtons)[i].y1))
				{
					pushed = true;
					if ((*simpleButtons)[i].onlyClick) // если кнопка не имеет нажатого состояния
					{
						ClickButton((*simpleButtons)[i]);
						started = ReactionOnClick((*simpleButtons)[i], end, mainArray);
						resultValue->clear();
					}
					else // если имеет
						(*simpleButtons)[i].isPushing = !(*simpleButtons)[i].isPushing;
				}

			for (int i = 0; i < (*functionButtons).size(); i++) // проверяем кнопки функций
				if (In(x, (*functionButtons)[i].x0, (*functionButtons)[i].x1)
					&& In(y, (*functionButtons)[i].y0, (*functionButtons)[i].y1))
				{
					pushed = true;
					(*functionButtons)[i].isPushing = !(*functionButtons)[i].isPushing;
				}

			int pushedSwapButton = -1;
			// проверяем множество кнопок, из которых может быть активная только одна
			for (int i = 0; i < (*swapButtons).size(); i++)
				if (In(x, (*swapButtons)[i].x0, (*swapButtons)[i].x1)
					&& In(y, (*swapButtons)[i].y0, (*swapButtons)[i].y1) && (*swapButtons)[i].isPushing == false)
				{
					(*swapButtons)[i].isPushing = !(*swapButtons)[i].isPushing;
					pushedSwapButton = i;
					pushed = true;

					resultValue->clear();

					if ((*swapButtons)[i].text == "Заполнение случайными \n числами")
					{
						(*mainArray) = CreateArray(1);
						RandomFilling = true;
						break;
					}

					if ((*swapButtons)[i].text == "Заполнение числами \n по убыванию")
					{
						(*mainArray) = CreateArray(0);
						RandomFilling = false;
					}
					break;
				}

			if (pushedSwapButton != -1) // если активировали неактивную кнопку, деактивируем остальные
				for (int i = 0; i < (*swapButtons).size(); i++)
					if (i != pushedSwapButton)
					{
						(*swapButtons)[i].isPushing = false;
					}
			if (pushed) // если мы что-то нажимали надо изменить картинку
			{
				txBegin();
				txClear();
				CreateEmptyCanvas(simpleButtons, functionButtons, swapButtons, 0);
				CreateEmptyDiagram(CoordinatesDiagramOfComparisons, maxNumOfComparisons);
				CreateEmptyDiagram(CoordinatesDiagramOfSwaping, maxNumOfSwaping);
				DrawResults(resultValue, maxNumOfSwaping, maxNumOfComparisons);
				txEnd();
			}
		}
		return started;
	}

	void ClickButton(button oneButton)
	{
		// рисуем нажатую кнопку
		DrawFoneOfPushedButton(oneButton.x0, oneButton.y0, oneButton.x1, oneButton.y1, 10);
		DrawButton(oneButton, 0);
		txSleep(150); // ждём

		txSetColor(BackColor);
		txSetFillColor(BackColor);

		// рисуем обычную кнопку
		txBegin();
		txRectangle(oneButton.x0, oneButton.y0, oneButton.x1, oneButton.y1);
		DrawButton(oneButton, 1);
		txEnd();
	}

	void DrawGentleRectangle(int x0, int y0, int x1, int y1, int R, COLORREF color) 
	{
		if (x1 - x0 < 2 * R) // если скругление слишком большое, то рисуем круг
		{
			txCircle((x1 - x0) / 2, (y1 - y0) / 2, R);
			return;
		}

		txSetColor(color);
		txSetFillColor(color);

		txLine(x0 + R - 1, y0, x1 - R, y0); // верхняя сторона
		txArc(x1 - 2 * R, y0, x1, y0 + 2 * R, 0, 90); // правый верхний угол
		txLine(x1, y0 + R - 1, x1, y1 - R); // правая сторона
		txArc(x1 - 2 * R, y1, x1, y1 - 2 * R, -90, 90); // правый нижний угол
		txLine(x0 + R - 1, y1, x1 - R, y1); // нижняя сторона
		txArc(x0, y1 - 2 * R, x0 + 2 * R, y1, 180, 90); // левый нижний угол
		txLine(x0, y0 + R - 1, x0, y1 - R); // левая сторона
		txArc(x0, y0 + 2 * R, x0 + 2 * R, y0, 90, 90); // левый верхний угол

	}

	void DrawResults(std::vector<drawing::ResultValue>* resultValue, int maxNumOfSwaping, int maxNumOfComparisons)
	{
		assert(resultValue != nullptr);

		const int heightDiagram = Height * 0.725; // высота диаграммы
		const int widthDiagram = Width * 0.33; // высота диаграммы
		const double numElementsOnPixel = MaxNumOfElements / double(heightDiagram - 14);// число элементов на пиксель
		const double numSwapingOnPixel = maxNumOfSwaping / double(widthDiagram - 14);// число обменов на пиксель
		const double numComparisonsOnPixel = maxNumOfComparisons / double(widthDiagram - 14);// число сравнений на пиксель

		for (auto i = resultValue->begin(); i != resultValue->end(); i++)
			for (auto j = i->result.begin(); j != i->result.end(); j++)
			{
				// рисуем в диаграмме обменов
				txSetPixel(CoordinatesDiagramOfSwaping.first + j->swaping / (numSwapingOnPixel), 
					CoordinatesDiagramOfSwaping.second + heightDiagram - j->numOfElements / (numElementsOnPixel),
																										i->color);
				// рисуем в диаграмме сравнений
				txSetPixel(CoordinatesDiagramOfComparisons.first + j->comparisons / (numComparisonsOnPixel),
					CoordinatesDiagramOfComparisons.second + heightDiagram - j->numOfElements / (numElementsOnPixel),
					i->color);
			}
	}

	void DrawFoneOfPushedButton(int x0, int y0, int x1, int y1, int R)
	{
		const int gap = MIN(x1 - x0, y1 - y0) / 2; // число эелементов градиента

		const int r = R;
		R = 0;
		if ((x1 - x0) < (y1 - y0)) // определяем координаты начальной позиции градиента
		{
			y1 -= (x1 - x0) / 2;
			y0 += (x1 - x0) / 2;
			x0 = (x1 + x0) / 2;
			x1 = x0;
		}
		else
		{
			x1 -= (y1 - y0) / 2;
			x0 += (y1 - y0) / 2;
			y0 = (y1 + y0) / 2;
			y1 = y0;
		}

		for (int i = 1; i <= gap; i++)
		{
			const COLORREF color = RGB(MAX(txExtractColor(BackColor, TX_RED) - 1.3 * i, 0), // получаем цвет для 
				MAX(txExtractColor(BackColor, TX_GREEN) - 1.3 * i, 0),                      // каждого элемента
				txExtractColor(BackColor, TX_BLUE));										// градиента
			if (gap - i <= r) // если приблежаемся к границам кнопки делаем скругление, чтобы не было торчаших углов
				R = r-(gap - i);
			txSetColor(color);
			txSetFillColor(color);
			DrawGentleRectangle(x0, y0, x1, y1, R, color);
			//переходим к следующему элементу градиента
			x0 -= 1;
			y0 -= 1;
			x1 += 1;
			y1 += 1;
		}
	}

	void DrawButton(button oneButton, bool withContur)
	{
		if(oneButton.isPushing) // если кнопка активнка
			DrawFoneOfPushedButton(oneButton.x0, oneButton.y0, oneButton.x1, oneButton.y1, 10);

		if(withContur) // если нужен контур
			DrawGentleRectangle(oneButton.x0, oneButton.y0, oneButton.x1, oneButton.y1, 10, oneButton.boundariesColor);

		txSetColor(oneButton.textColor);
		txSetFillColor(oneButton.textColor);
		txSelectFont(oneButton.nameFont.c_str(), oneButton.sizeFont, FW_DONTCARE);
		txDrawText(oneButton.x0, oneButton.y0, oneButton.x1, oneButton.y1, oneButton.text.c_str(), DT_CENTER | DT_VCENTER);
	}

	void DrawLeftAnatationOfDiagram(int xLine, int yLine, int lenText, int heightDiagram, int widthDiagram,
								int lenLineAndHeightText, int gapBesideTextAndLine, int yMaxValue, int accuracy)
	{
		const int xText = xLine - lenText;
		const int yText = yLine - lenLineAndHeightText / 2 - 1;
		for (int i = 0; i <= accuracy; i++)
		{
			txLine(xLine, yLine + heightDiagram * i / accuracy,  // линия у числа
					xLine + lenLineAndHeightText, yLine + heightDiagram * i / accuracy);
			txLine(xLine + lenLineAndHeightText, yLine + heightDiagram * i / accuracy,  // линия на диаграмме
					xLine + lenLineAndHeightText+widthDiagram, yLine + heightDiagram * i / accuracy);
			txDrawText(xText, yText + heightDiagram * i / accuracy, xLine - gapBesideTextAndLine, // число
						yText + lenLineAndHeightText + heightDiagram * i / accuracy,
						std::to_string(yMaxValue * (accuracy - i) / accuracy).c_str(), DT_RIGHT);
		}
	}

	void DrawUnderAnatationOfDiagram(int xLine, int yLine, int lenLineAndHeightText, int gapBesideTextAndLine, 
									int widthDiagram,  int heightDiagram, int lenText, int xMaxValue, int accuracy)
	{
		assert(accuracy > 0);
		for (int i = 0; i <= accuracy; i++)
		{
			txLine(xLine + widthDiagram * i / accuracy, yLine, // линия у числа
					xLine + widthDiagram * i / accuracy, yLine + lenLineAndHeightText);
			txLine(xLine + widthDiagram * i / accuracy, yLine, // линия на диаграмме
					xLine + widthDiagram * i / accuracy, yLine - heightDiagram);
			// число
			txDrawText(xLine - lenText/2 + widthDiagram * i / accuracy, yLine + lenLineAndHeightText + gapBesideTextAndLine,
				xLine + lenText/2 + widthDiagram * i / accuracy, yLine + 2 * lenLineAndHeightText + gapBesideTextAndLine,
				std::to_string(xMaxValue * i / accuracy).c_str(), DT_CENTER);
		}
	}

	void CreateEmptyDiagram(std::pair<int, int>coordinates, int MaxNumOfParameterAxesX)
	{
		const int heightDiagram = Height * 0.725;
		const int widthDiagram = Width * 0.33;

		txSetColor(TX_BLACK);
		txSetFillColor(TX_BLACK);
		//рисуем окно диаграммы
		txRectangle(coordinates.first, coordinates.second, coordinates.first + widthDiagram, coordinates.second + heightDiagram);

		txSetColor(SandColor);
		txSelectFont("Times New Roman", Boundaries * 0.52);
		// рисуем ось ординат
		DrawLeftAnatationOfDiagram(coordinates.first - Boundaries * 0.4, coordinates.second + 14, Boundaries * 2,
									heightDiagram - 15, widthDiagram, Boundaries * 0.4, Boundaries * 0.1,
									MaxNumOfElements, AccuracyOfDiagram);
		// рисуем ось абцисс
		DrawUnderAnatationOfDiagram(coordinates.first, coordinates.second + heightDiagram, Boundaries * 0.4,
									Boundaries * 0.1, widthDiagram - 10, heightDiagram, Boundaries * 1.6,
									MaxNumOfParameterAxesX, AccuracyOfDiagram);
	}

	void CreateEmptyCanvas(std::vector<button>* simpleButtons, std::vector<button>* functionButtons, 
																std::vector<button>* swapButtons, bool defaultDiagram)
	{
		assert(simpleButtons != nullptr);
		assert(functionButtons != nullptr);
		assert(swapButtons != nullptr);
		assert(simpleButtons != functionButtons);
		assert(simpleButtons != swapButtons);
		assert(swapButtons != functionButtons);

		txSetColor(BackColor);
		txSetFillColor(RGB(40, 120, 250));
		txRectangle(0, 0, Width, Height);

		if (defaultDiagram)
		{
			CreateEmptyDiagram(CoordinatesDiagramOfSwaping); //диаграмма обменов
			CreateEmptyDiagram(CoordinatesDiagramOfComparisons); //диаграмма сравнений
		}

		txSetColor(RGB(248, 0, 0)); //красный
		txSetFillColor(SandColor);
		
		// прописываем словаы
		txSelectFont("Comic Sans MS", Boundaries * 1.6, FW_DONTCARE);
		txDrawText(Width * 0.21 + Boundaries * 2, Boundaries * 0.3,
			Width * 0.21 + Boundaries * 3.9 + Width * 0.66, Boundaries * 2.4, "Результаты:", DT_CENTER);
		txSetColor(SandColor);
		txSelectFont("Comic Sans MS", Boundaries * 1.3, FW_DONTCARE);
		txDrawText(Width * 0.21 + Boundaries * 2, Boundaries * 2,
			Width * 0.21 + Boundaries * 2 + Width * 0.33, Height * 0.2, "Обмены", DT_CENTER);
		txSelectFont("Comic Sans MS", Boundaries * 1.3, FW_DONTCARE);
		txDrawText(Width * 0.21 + Boundaries * 3.9 + Width * 0.33, Boundaries * 2,
			Width * 0.21 + Boundaries * 3.9 + Width * 0.66, Height * 0.2, "Сравнения", DT_CENTER);

		txSetColor(TX_WHITE);
		txLine(0, Boundaries * 5.1, Width * 0.22, Boundaries * 5.1);
		txLine(Width * 0.22, 0, Width * 0.22, Height);

		txSetColor(RGB(252, 221, 118));
		txSelectFont("Comic Sans MS", Boundaries*0.9, FW_DONTCARE);
		txTextOut(Boundaries*0.4, Boundaries*0.4, "Заполнение массива:");
		txSelectFont("Comic Sans MS", Boundaries * 0.9, FW_DONTCARE);
		txTextOut(Boundaries * 0.4, Boundaries * 5.3, "Функции сортировки:");

		// рисуем кнопки
		for (button oneButton : (*simpleButtons))
			DrawButton(oneButton, 1);
		for (button oneButton : (*swapButtons))
			DrawButton(oneButton, 1);
		for (button oneButton : (*functionButtons))
			DrawButton(oneButton, 1);
	}
}