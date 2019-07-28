//! @file
//! \brief Программа визуализации алгоритмов сортировки
//! \author TheCompiler
//! \version alpha 0.2
//! \date 27.07.2019
//! @defgroup PreCaculation		Расчёт значений
//! @defgroup WorkWithPerson	Работа с пользователем
//! @defgroup Drawing			Рисование
//! @defgroup NotUsed			Не использующиеся функции
#include <iostream>
#include "TXLib.h"
#include <string>
#include <vector>
#include "Buttons.h"
#include <set>

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
	const int Width = 1300; ///< ширина окна
	const int Height = Width * 675 / 1300; ///< высота окна
	const int Boundaries = Width * 33 / 1300; ///< унивирсальная константа, упращающая процесс расположения объектов
	const COLORREF BackColor = RGB(40, 120, 250); ///< цвет фона
	const COLORREF SandColor = RGB(255, 240, 212); ///< песочный цвет
	const int AccuracyOfDiagram = 3; ///< значение отвечающее за маштаб сетки разметки; определяет на сколько частей будут разделяться обе оси
	const int VisualizPeriod = 50; ///< определяет через сколько итераций будут обновлять результаты расчётов
	const std::pair<int, int> CoordinatesDiagramOfSwaping = std::make_pair(Width * 0.21 + Boundaries * 2.7, Height * 0.2);///< координаты левеого верхнего угла диаграмма обменов
	const std::pair<int, int> CoordinatesDiagramOfComparisons = std::make_pair(Width * 0.21 + Boundaries * 5.01 + Width * 0.33, Height * 0.2); ///< координаты левеого верхнего угла диаграмма сравнений
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

	void CreateButtons(int height, int width, int boundaries,
		std::vector<button>* SimpleButtons, std::vector<button>* FunctionButtons, std::vector<button>* SwapButtons);
//-----------------------------------------------------------------------------------------------------------------
//! @ingroup WorkWithPerson
//!	\brief Проверяет нажата ли какая-либо кнопка и делает соответствующее каждой действияя
//!
//!	структура button из библиотке Buttons.h
//! \param[in] simpleButtons		вектор параметров обычных кнопок
//! \param[in] functionButtons		вектор параметров кнопок функций сортировки 
//! \param[in] swapButtons			вектор параметров кнопок, среди которых может быть активна только одна
//!	\param[out] RandomFilling		маркер способа заполнения массива; 1 - случайным числами, 0 - по убыванию
//!	\param[out] mainArray			сортеруемый массив

//! \return маркер реакции на нажатие кнопки -2 - ничего не нажали, -1 - кнопка выполнилась, 0 - выход из программы, 1 - запуск расчётов
//!
	int CheckClickOrPushing(std::vector<button>* simpleButtons, std::vector<button>* functionButtons,
							std::vector<button>* swapButtons, int* RandomFilling, std::vector<int>* mainArray);

//=================================================================================================================
//! @ingroup Drawing
//!	\brief Рисует прямоугольник с круглёными углами радиусом R
//! 
//! Используется в Buttons.h
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
//!	\brief Рисует числа и линии оси ординат
//! 
//! \param xLine, yLine							координаты левого верхнего угла начала линий оси ординат
//! \param lenTex								длина чисел оси ординат
//! \param heightDiagram, int WidthDiagram		высота и ширина диаграмы
//! \param lenLine								длина линии
//! \param heightText							высота окна, в котором пишутся числа
//!	\param gapBesideTextAndLine					промежуток между текста
//! \param yMaxValue							максимальное значение чисел на оси ординат 
//! \param accuracy								число частей, на которые будут разделина ось ординат
//!
	void DrawLeftAnatationOfDiagram(int xLine, int yLine, int lenText, int heightDiagram, int widthDiagram,
							int lenLine, int heightText, int gapBesideTextAndLine, int yMaxValue, int accuracy = 2);

//-----------------------------------------------------------------------------------------------------------------
//! @ingroup Drawing
//!	\brief Рисует числа и линии оси абцисс
//! 
//! \param xLine, yLine							координаты левого верхнего угла начала линий оси абцисс
//! \param lenLine								длина линии
//! \param heightText							высота окна, в котором пишутся числа
//!	\param gapBesideTextAndLine					промежуток между текста
//! \param heightDiagram, widthDiagram			высота и ширина диаграмы
//! \param lenText								длина окна, в котором пишутся числа
//! \param xMaxValue							максимальное значение чисел на оси абцисс 
//! \param accuracy								число частей, на которые будут разделина ось абцисс
//!
	void DrawUnderAnatationOfDiagram(int xLine, int yLine, int lenLine, int heightText, int gapBesideTextAndLine,
								int widthDiagram, int heightDiagram, int lenText, int xMaxValue, int accuracy);

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
}

int main()
{
	std::vector<int>mainArray = drawing::CreateArray(); // массив который подвергается сортировки
	// вектора хранящие параметры для создания кнопок
	std::vector<drawing::button>simpleButtons, functionButtons, swapButtons; 
	int RandomFilling = 1; // перменная указывающя заполняем ли мы случайными числами сортируемый массив или нет
	std::vector<drawing::ResultValue>resultValue;// вектор хранящий результаты расчётов
	int maxNumOfSwaping = 1200; // максимальное число обменов (значение по умолчанию)
	int maxNumOfComparisons = 1200; // максимальное число сравнений (значение по умолчанию)
	int stateMouse = txMouseButtons(); // состояние кнопки мыши

	drawing::CreateButtons(drawing::Height, drawing::Width, drawing::Boundaries,
											&simpleButtons, &functionButtons, &swapButtons);

	txCreateWindow(drawing::Width, drawing::Height);
	
	txBegin();
	drawing::CreateEmptyCanvas(&simpleButtons, &functionButtons, &swapButtons);
	txEnd();

	while (1)
	{
		std::vector<int> empty = { 1 }; // пустые перменные для функций кнопок
		//перменная запускаяющая реакций на нажатие кнопки
		int res = -2;
		if (stateMouse == 1 && txMouseButtons() != 1)
		{
			auto resultSwaping = drawing::CheckClickButtons(&swapButtons);
			if (resultSwaping != nullptr)
			{
				res = resultSwaping(0, 1, empty, &RandomFilling, &drawing::MaxNumOfElements, &mainArray);
				resultValue.clear();
			}

			auto resultFunction = drawing::CheckClickButtons(&functionButtons);
			if (resultFunction != nullptr)
				res = -1;

			auto resultSimple = drawing::CheckClickButtons(&simpleButtons);
			if (resultSimple != nullptr)
			{
				res = resultSimple(0, 1, empty, &RandomFilling, &drawing::MaxNumOfElements, &mainArray);
				resultValue.clear();
			}
		}
		if (res == 0) // выход
		{
			break;
			resultValue.clear();
		}

		if (res != -2) // если мы что-то нажимали надо изменить картинку
		{
			txBegin();
			txClear();
			drawing::CreateEmptyCanvas(&simpleButtons, &functionButtons, &swapButtons, 0);
			drawing::CreateEmptyDiagram(drawing::CoordinatesDiagramOfComparisons, maxNumOfComparisons);
			drawing::CreateEmptyDiagram(drawing::CoordinatesDiagramOfSwaping, maxNumOfSwaping);
			drawing::DrawResults(&resultValue, maxNumOfSwaping, maxNumOfComparisons);
			txEnd();
		}

		if (res == 1)// запуск расчётов
			drawing::StartAccount(&simpleButtons, &functionButtons, &swapButtons, &mainArray,
													&maxNumOfSwaping, &maxNumOfComparisons, &resultValue);

		stateMouse = txMouseButtons();// обновляем состояние кнопки мыши
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
				std::vector<int>parametrs;
				std::vector<int>sortingArray = (*mainArray);
				oneButton.linkToFunction(0, i, parametrs, &swaping, &comparisons, &sortingArray);

				// запоминаем цвет отображения функции и результаты
				(*resultValue)[numOfButton].color = oneButton.textColor;
				(*resultValue)[numOfButton].result.push_back({ swaping, comparisons, i+1 });

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

	int CheckClickOrPushing(std::vector<button>* simpleButtons, std::vector<button>* functionButtons,
							std::vector<button>* swapButtons, int* RandomFilling, std::vector<int>* mainArray)
	{
		assert(simpleButtons != nullptr);
		assert(functionButtons != nullptr);
		assert(swapButtons != nullptr);
		assert(mainArray != nullptr);
		assert(RandomFilling != nullptr);
		assert(simpleButtons != functionButtons);
		assert(simpleButtons != swapButtons);
		assert(swapButtons != functionButtons);

		int swaping = 0, compar = 0; // пустые перменные для функций кнопок
		std::vector<int> empty = { 1 }; // пустые перменные для функций кнопок

		if (txMouseButtons() == 1)// проверяем нажата ли левая кнока мыши
		{
			const int x = txMouseX(), y = txMouseY();
			for (int i = 0; i < (*simpleButtons).size(); i++) // проверяем обычные кнопки
				if (In(x, (*simpleButtons)[i].x0, (*simpleButtons)[i].x1)
					&& In(y, (*simpleButtons)[i].y0, (*simpleButtons)[i].y1))
				{
					if ((*simpleButtons)[i].onlyClick) // если кнопка не имеет нажатого состояния
					{
						(*simpleButtons)[i].ClickButton();
					}
					else // если имеет
						(*simpleButtons)[i].isPushing = !(*simpleButtons)[i].isPushing;
					return (*simpleButtons)[i].linkToFunction(0, 1, empty, RandomFilling, &MaxNumOfElements, mainArray);
				}

			for (int i = 0; i < (*functionButtons).size(); i++) // проверяем кнопки функций
				if (In(x, (*functionButtons)[i].x0, (*functionButtons)[i].x1)
					&& In(y, (*functionButtons)[i].y0, (*functionButtons)[i].y1))
				{
					(*functionButtons)[i].isPushing = !(*functionButtons)[i].isPushing;
					return (*functionButtons)[i].linkToFunction(0, -1, empty, &swaping, &compar, &empty);
				}

			int pushedSwapButton = -1;
			// проверяем множество кнопок, из которых может быть активная только одна
			for (int i = 0; i < (*swapButtons).size(); i++)
				if (In(x, (*swapButtons)[i].x0, (*swapButtons)[i].x1)
					&& In(y, (*swapButtons)[i].y0, (*swapButtons)[i].y1) && (*swapButtons)[i].isPushing == false)
				{
					(*swapButtons)[i].isPushing = !(*swapButtons)[i].isPushing;
					pushedSwapButton = i;

					break;
				}

			if (pushedSwapButton != -1) // если активировали неактивную кнопку, деактивируем остальные
			{
				for (int i = 0; i < (*swapButtons).size(); i++)
					if (i != pushedSwapButton)
					{
						(*swapButtons)[i].isPushing = false;
					}
				return (*swapButtons)[pushedSwapButton].linkToFunction(0, -1, empty, &swaping, &compar, &empty);
			}
		}
		return -2;
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
		const double numElementsOnPixel = MaxNumOfElements / double(widthDiagram - 14);// число элементов на пиксель
		const double numSwapingOnPixel = maxNumOfSwaping / double(heightDiagram - 14);// число обменов на пиксель
		const double numComparisonsOnPixel = maxNumOfComparisons / double(heightDiagram - 14);// число сравнений на пиксель

		for (auto i = resultValue->begin(); i != resultValue->end(); i++)
			for (auto j = i->result.begin(); j != i->result.end(); j++)
			{
				// рисуем в диаграмме обменов
				txSetPixel(CoordinatesDiagramOfSwaping.first + j->numOfElements / (numElementsOnPixel),
					CoordinatesDiagramOfSwaping.second + heightDiagram - j->swaping / (numSwapingOnPixel),
																										i->color);
				// рисуем в диаграмме сравнений
				txSetPixel(CoordinatesDiagramOfComparisons.first + j->numOfElements / (numElementsOnPixel),
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
			txLine(xLine, yLine + heightDiagram * i / accuracy,  // линия у числа
					xLine + lenLine, yLine + heightDiagram * i / accuracy);
			txLine(xLine + lenLine, yLine + heightDiagram * i / accuracy,  // линия на диаграмме
					xLine + lenLine + widthDiagram, yLine + heightDiagram * i / accuracy);
			txDrawText(xText, yText + heightDiagram * i / accuracy, xLine - gapBesideTextAndLine, // число
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
			txLine(xLine + widthDiagram * i / accuracy, yLine, // линия у числа
					xLine + widthDiagram * i / accuracy, yLine + lenLine);
			txLine(xLine + widthDiagram * i / accuracy, yLine, // линия на диаграмме
					xLine + widthDiagram * i / accuracy, yLine - heightDiagram);
			// число
			txDrawText(xLine - lenText/2 + widthDiagram * i / accuracy, yLine + heightText + gapBesideTextAndLine,
				xLine + lenText/2 + widthDiagram * i / accuracy, yLine + 2 * heightText + gapBesideTextAndLine,
				std::to_string(xMaxValue * i / accuracy).c_str(), DT_CENTER | DT_VCENTER);
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
									heightDiagram - 15, widthDiagram, Boundaries * 0.4, Boundaries * 0.5,
									Boundaries * 0.1, MaxNumOfParameterAxesX, AccuracyOfDiagram);
		// рисуем ось абцисс
		DrawUnderAnatationOfDiagram(coordinates.first, coordinates.second + heightDiagram, Boundaries * 0.4, 
										Boundaries * 0.5, Boundaries * 0.1, widthDiagram - 10, heightDiagram, 
										Boundaries * 1.6, MaxNumOfElements, AccuracyOfDiagram);
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
		
		// прописываем слова
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
		DrawButtons(simpleButtons);
		DrawButtons(swapButtons);
		DrawButtons(functionButtons);
	}

	//! \brief   Определяет параметры для кнопок
	//!
	//! \param height					высота окна программы
	//! \param width					ширина окна программы
	//! \param boundaries				унивирсальное значение для разметки окна
	//! \param[out] SimpleButtons		вектор параметров обычных кнопок
	//! \param[out] SwapButtons			вектор параметров кнопок, среди которых может быть активна только одна
	//! \param[out] FunctionButtons		вектор параметров кнопок функций сортировки 

	void CreateButtons(int height, int width, int boundaries,
		std::vector<button>* SimpleButtons, std::vector<button>* FunctionButtons, std::vector<button>* SwapButtons) {
		assert(SimpleButtons != nullptr);
		assert(FunctionButtons != nullptr);
		assert(SwapButtons != nullptr);
		assert(SimpleButtons != FunctionButtons);
		assert(SimpleButtons != SwapButtons);
		assert(SwapButtons != FunctionButtons);

		//вектор кнопок, среди которых может быть активна только одна
		*SwapButtons = { {4, int(boundaries * 0.4), int(boundaries * 1.6), int(width * 0.21), int(boundaries * 2.9),
							"Заполнение случайными \n числами", RGB(248, 0, 0), TX_WHITE, "Georgia", 
							int(boundaries * 0.6), true, false, BackColor, 10, &buttonsFunction::Random, true},
							{5, int(boundaries * 0.4), int(boundaries * 3.4), int(width * 0.21), int(boundaries * 4.7),
							"Заполнение числами \n по убыванию", RGB(248, 0, 0), TX_WHITE, "Georgia", 
							int(boundaries * 0.6), false, false, BackColor, 10, &buttonsFunction::NotRandom, true} };
		//обычные кнопки
		*SimpleButtons = { {1, int(boundaries * 0.4), int(height - boundaries * 3.2),int(width * 0.21),
								int(height - boundaries * 1.2), "Поехали!", RGB(248, 0, 0), TX_WHITE, "Comic Sans MS",
								int(boundaries * 1.2), false, true, BackColor, 10, &buttonsFunction::Start, true},
								{2, int(boundaries * 0.4), int(height - boundaries * 4.2), int(width * 0.21),
								int(height - boundaries * 3.6), "Изменить число элементов", RGB(248, 0, 0), TX_WHITE,
								"Georgia", int(boundaries * 0.5), false, true, BackColor, 10, &buttonsFunction::Changed, false},
								{3, int(boundaries * 0.4), int(height - boundaries), int(width * 0.21),
								int(height - boundaries * 0.4), "Выход", RGB(248, 0, 0), TX_WHITE, "Georgia", 
								int(boundaries * 0.5), false, true, BackColor, 10, &buttonsFunction::Exit, false} };
		// кнопки функций сортировки
		*FunctionButtons = { {6, int(boundaries * 0.4), int(boundaries * 6.6), int(width * 0.1), int(boundaries * 7.7),
								"Bubble", TX_RED, TX_RED, "Georgia", int(boundaries * 0.8), true, false, BackColor, 10,
								&buttonsFunction::bubbleSorting, false},
								{7, int(width * 0.11), int(boundaries * 6.6), int(width * 0.21), int(boundaries * 7.7),
								"Heap", TX_GREEN, TX_GREEN, "Georgia", int(boundaries * 0.8), true, false, BackColor, 10,
								&buttonsFunction::heap_sort, false},
								{8, int(boundaries * 0.4), int(boundaries * 8), int(width * 0.1), int(boundaries * 9.1),
								"Quick", TX_BLUE, TX_BLUE, "Georgia", int(boundaries * 0.8), true, false, BackColor, 10,
								&buttonsFunction::quickSorting, false},
								{9, int(width * 0.11), int(boundaries * 8), int(width * 0.21), int(boundaries * 9.1),
								"Merge", TX_YELLOW, TX_YELLOW, "Georgia", int(boundaries * 0.8), true, false, BackColor, 10,
								&buttonsFunction::mergeSorting, false},
								{10, int(boundaries * 0.4), int(boundaries * 9.4), int(width * 0.1), int(boundaries * 10.5),
								"Insertion", TX_ORANGE, TX_ORANGE, "Georgia", int(boundaries * 0.8), true, false,
								BackColor, 10,	&buttonsFunction::insertionSorting, false},
								{11, int(width * 0.11), int(boundaries * 9.4), int(width * 0.21), int(boundaries * 10.5),
								"Selection", TX_MAGENTA, TX_MAGENTA, "Georgia", int(boundaries * 0.8), true, false,
								BackColor, 10,	&buttonsFunction::selectionSorting, false} };
	}
}