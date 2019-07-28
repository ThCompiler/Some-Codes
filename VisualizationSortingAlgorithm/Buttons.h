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
		COLORREF backColor; ///< фон активной кнопки
		int R; ///< радиус скругление углов кнопки
		int(*linkToFunction)(int left, int right, std::vector<int>parametr, int* swaping,
			int* comparisons, std::vector<int>* Array);///< ссылка на функцию сортировки
		bool swapingButton; ///< относится ли кнопка к группе кнопок, среди которых может быть нажат только одна кнопка
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
		void DrawFoneOfPushedButton()
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
		void DrawButton(bool withContur = 1)
		{
			if (isPushing) // если кнопка активнка
				DrawFoneOfPushedButton();

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
		void ClickButton()
		{
			// рисуем нажатую кнопку
			DrawFoneOfPushedButton();
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
	//Функция рисует кнопки
	void DrawButtons(std::vector<button>* Buttons)
	{
		assert(Buttons != nullptr);
		for (button oneButton : (*Buttons))
		{
			oneButton.DrawButton(1);
		}
	}
	//Обрабатывает нажатие на кнопки
	int(*CheckClickButtons(std::vector<button>* Buttons)) (int left, int right, std::vector<int>parametr, 
		int* swaping, int* comparisons, std::vector<int>* Array)
	{
		assert(Buttons != nullptr);
		int idSwapingButton = -1;
		const int x = txMouseX(), y = txMouseY();
		int (*result)(int left, int right, std::vector<int>parametr, int* swaping, 
											int* comparisons, std::vector<int> * Array) = nullptr;
		for (int i = 0; i < Buttons->size();i++)
			if (In(x, (*Buttons)[i].x0, (*Buttons)[i].x1) && In(y, (*Buttons)[i].y0, (*Buttons)[i].y1))
			{
				if ((*Buttons)[i].swapingButton)
					idSwapingButton = (*Buttons)[i].id;
				if ((*Buttons)[i].onlyClick)
				{
					(*Buttons)[i].ClickButton();
					result = (*Buttons)[i].linkToFunction;
					break;
				}
				else
					{
						(*Buttons)[i].isPushing = !(*Buttons)[i].isPushing;
						result = (*Buttons)[i].linkToFunction;
						break;
					}

			}

		if (idSwapingButton != -1)
			for (int i = 0; i < Buttons->size(); i++)
				if ((*Buttons)[i].id != idSwapingButton)
					(*Buttons)[i].isPushing = false;
		return result;
	}
}