//! @file
//! \brief библиотека инициализации кнопок
#include <string>
#include <vector>
#include "TXLib.h"
#include "SortingFunction.h"

namespace drawing
{
	//! \class button
	//! \brief клаас кнопки
	class button
	{
	public:
		int id; ///< индивидуальный код
		int x0; ///< координаты
		int y0; ///< координаты
		int x1; ///< координаты
		int y1; ///< координаты
		std::string text; ///< текст
		COLORREF boundariesColor; ///< цвет границ
		COLORREF textColor; ///<  цвет текста
		std::string nameFont; ///<  названия шрифта текста
		int sizeFont; ///<  размер шрифта
		bool isPushing; ///<  является ли кнопка активна
		bool onlyClick; ///<  имеет ли кнопка возможность быть активной
		bool isFunction; ///< является ли кнопка функцией сортировки
		int R; ///< радиус скругление углов кнопки
		int(*linkToFunction)(int left, int right, std::vector<int>parametr, int* swaping,
			int* comparisons, std::vector<int>* Array);///< ссылка на функцию сортировки
	private:

		//!	\brief Рисует прямоугольник с круглёными углами радиусом R
		//! 
		//! \param color		цвет рамки "мягкого" прямоугольника
		//!
		void DrawGentleRectangle(COLORREF color)
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

		//-----------------------------------------------------------------------------------------------------------------
		//!	\brief Рисует внутри кнопки градиент от заданого цвета до более тёмного
		//! 
		//!	\param backColor	цвет фона кнопки при её активации
		//!
		void DrawFoneOfPushedButton(COLORREF backColor)
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
				const COLORREF color = RGB(MAX(txExtractColor(backColor, TX_RED) - 1.3 * i, 0), // получаем цвет для 
					MAX(txExtractColor(backColor, TX_GREEN) - 1.3 * i, 0),                      // каждого элемента
					txExtractColor(backColor, TX_BLUE));										// градиента
				if (gap - i <= r) // если приблежаемся к границам кнопки делаем скругление, чтобы не было торчаших углов
					R = r - (gap - i);
				txSetColor(color);
				txSetFillColor(color);
				DrawGentleRectangle(color);
				//переходим к следующему элементу градиента
				x0 -= 1;
				y0 -= 1;
				x1 += 1;
				y1 += 1;
			}
		}

	public:
		//-----------------------------------------------------------------------------------------------------------------
		//!	\brief Рисует кнопки
		//! 
		//! \param backColor	цвет фона кнопки при её активации
		//! \param withContur	маркер наличия контура у кнопки; true - у кнопки будет контур, false - не будет
		void DrawButton(COLORREF backColor, bool withContur = 1)
		{
			if (isPushing) // если кнопка активнка
				DrawFoneOfPushedButton(backColor);

			if (withContur) // если нужен контур
				DrawGentleRectangle(boundariesColor);

			txSetColor(textColor);
			txSetFillColor(textColor);
			txSelectFont(nameFont.c_str(), sizeFont, FW_DONTCARE);
			txDrawText(x0, y0, x1, y1, text.c_str(), DT_CENTER | DT_VCENTER);
		}

		//-----------------------------------------------------------------------------------------------------------------
		//!	\brief Визуализирует эффект клика на кнопку
		//! 
		//! \param backColor	цвет фона кнопки при её активации
		//!
		void ClickButton(COLORREF backColor)
		{
			// рисуем нажатую кнопку
			DrawFoneOfPushedButton(backColor);
			DrawButton(0);
			txSleep(150); // ждём

			txSetColor(backColor);
			txSetFillColor(backColor);

			// рисуем обычную кнопку
			txBegin();
			txRectangle(x0, y0, x1, y1);
			DrawButton(1);
			txEnd();
		}
	};

	//!	\brief Возвращает маркер реакции на нажатия кнопки "Поехали!", то есть запуска расчётов
	int Start(int left, int right, std::vector<int>parametr, int* swaping = nullptr,
														int* comparisons = nullptr, std::vector<int>* Array = nullptr)
	{
		return 1;
	}
	//!	\brief Возвращает маркер реакции на нажатия кнопки "Выход"
	int Exit(int left, int right, std::vector<int>parametr, int* swaping = nullptr,
														int* comparisons = nullptr, std::vector<int>* Array = nullptr)
	{
		return 0;
	}
	//!	\brief Возвращает маркер реакции на нажатия кнопки "Заполнения случаными числами"
	int Random(int left, int right, std::vector<int>parametr, int* swaping = nullptr,
														int* comparisons = nullptr, std::vector<int>* Array = nullptr)
	{
		return 2;
	}
	//!	\brief Возвращает маркер реакции на нажатия кнопки "Заполнения числами по убыванию"
	int NotRandom(int left, int right, std::vector<int>parametr, int* swaping = nullptr,
		int* comparisons = nullptr, std::vector<int>* Array = nullptr)
	{
		return 3;
	}
	//!	\brief Возвращает маркер реакции на нажатия кнопки "Изменения размера сортеруемого массива"
	int Changed(int left, int right, std::vector<int>parametr, int* swaping = nullptr,
		int* comparisons = nullptr, std::vector<int>* Array = nullptr)
	{
		return 4;
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
							"Заполнение случайными \n числами", RGB(248, 0, 0), TX_WHITE,
							"Georgia", int(boundaries * 0.6), true, false, false, 10, &Random},
							{5, int(boundaries * 0.4), int(boundaries * 3.4), int(width * 0.21), int(boundaries * 4.7),
							"Заполнение числами \n по убыванию", RGB(248, 0, 0), TX_WHITE,
							"Georgia", int(boundaries * 0.6), false, false, false, 10, &NotRandom} };
		//обычные кнопки
		*SimpleButtons = { {1, int(boundaries * 0.4), int(height - boundaries * 3.2),int(width * 0.21),
								int(height - boundaries * 1.2), "Поехали!", RGB(248, 0, 0), TX_WHITE,
								"Comic Sans MS", int(boundaries * 1.2), false, true, false, 10, &Start},
								{2, int(boundaries * 0.4), int(height - boundaries * 4.2), int(width * 0.21),
								int(height - boundaries * 3.6), "Изменить число элементов", RGB(248, 0, 0), TX_WHITE,
								"Georgia", int(boundaries * 0.5), false, true, false, 10, &Changed},
								{3, int(boundaries * 0.4), int(height - boundaries), int(width * 0.21),
								int(height - boundaries * 0.4), "Выход", RGB(248, 0, 0), TX_WHITE,
								"Georgia", int(boundaries * 0.5), false, true, false, 10, &Exit} };
		// кнопки функций сортировки
		*FunctionButtons = { {6, int(boundaries * 0.4), int(boundaries * 6.6), int(width * 0.1), int(boundaries * 7.7),
								"Bubble", TX_RED, TX_RED, "Georgia", int(boundaries * 0.8), true, false, false, 10,
								&sorting::bubbleSorting},
								{7, int(width * 0.11), int(boundaries * 6.6), int(width * 0.21), int(boundaries * 7.7),
								"Heap", TX_GREEN, TX_GREEN, "Georgia", int(boundaries * 0.8), true, false, false, 10,
								&sorting::heap_sort},
								{8, int(boundaries * 0.4), int(boundaries * 8), int(width * 0.1), int(boundaries * 9.1),
								"Quick", TX_BLUE, TX_BLUE, "Georgia", int(boundaries * 0.8), true, false, false, 10,
								&sorting::quickSorting},
								{9, int(width * 0.11), int(boundaries * 8), int(width * 0.21), int(boundaries * 9.1),
								"Merge", TX_YELLOW, TX_YELLOW, "Georgia", int(boundaries * 0.8), true, false, false, 10,
								&sorting::mergeSorting},
								{10, int(boundaries * 0.4), int(boundaries * 9.4), int(width * 0.1), int(boundaries * 10.5),
								"Insertion", TX_ORANGE, TX_ORANGE, "Georgia", int(boundaries * 0.8), true, false,
								false, 10, &sorting::insertionSorting},
								{11, int(width * 0.11), int(boundaries * 9.4), int(width * 0.21), int(boundaries * 10.5),
								"Selection", TX_MAGENTA, TX_MAGENTA, "Georgia", int(boundaries * 0.8), true, false,
								false, 10, &sorting::selectionSorting} };
	}
}