//! @file
//! \brief библиотека инициализации кнопок
#include <string>
#include <vector>
#include "TXLib.h"

namespace drawing
{
	//! \struct button
	//! \brief структура хранения параментров кнопки
	struct button 
	{
		int x0, y0, x1, y1; ///< координаты
		std::string text; ///< текст
		COLORREF boundariesColor; ///< цвет границ
		COLORREF textColor; ///<  цвет текста
		std::string nameFont; ///<  названия шрифта текста
		int sizeFont; ///<  размер шрифта
		bool isPushing; ///<  является ли кнопка активна
		bool onlyClick; ///<  имеет ли кнопка возможность быть активной
	};

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
		*SwapButtons = { {int(boundaries * 0.4), int(boundaries * 1.6), int(width * 0.21), int(boundaries * 2.9),
							"Заполнение случайными \n числами", RGB(248, 0, 0), TX_WHITE,
							"Georgia", int(boundaries * 0.6), true, false},
							{ int(boundaries * 0.4), int(boundaries * 3.4), int(width * 0.21), int(boundaries * 4.7),
							"Заполнение числами \n по убыванию", RGB(248, 0, 0), TX_WHITE,
							"Georgia", int(boundaries * 0.6), false, false} };
		//обычные кнопки
		*SimpleButtons = { { int(boundaries * 0.4), int(height - boundaries * 3.2),int(width * 0.21),
								int(height - boundaries * 1.2), "Поехали!", RGB(248, 0, 0), TX_WHITE,
								"Comic Sans MS", int(boundaries * 1.2), false, true},
								{ int(boundaries * 0.4), int(height - boundaries * 4.2), int(width * 0.21),
								int(height - boundaries * 3.6), "Изменить число элементов", RGB(248, 0, 0), TX_WHITE,
								"Georgia", int(boundaries * 0.5), false, true},
								{ int(boundaries * 0.4), int(height - boundaries), int(width * 0.21),
								int(height - boundaries * 0.4), "Выход", RGB(248, 0, 0), TX_WHITE,
								"Georgia", int(boundaries * 0.5), false, true} };
		// кнопки функций сортировки
		*FunctionButtons = { { int(boundaries * 0.4), int(boundaries * 6.6), int(width * 0.1), int(boundaries * 7.7),
								"Bubble", TX_RED, TX_RED, "Georgia", int(boundaries * 0.8), true, false},
								{ int(width * 0.11), int(boundaries * 6.6), int(width * 0.21), int(boundaries * 7.7),
								"Heap", TX_GREEN, TX_GREEN, "Georgia", int(boundaries * 0.8), true, false},
								{ int(boundaries * 0.4), int(boundaries * 8), int(width * 0.1), int(boundaries * 9.1),
								"Quick", TX_BLUE, TX_BLUE, "Georgia", int(boundaries * 0.8), true, false},
								{ int(width * 0.11), int(boundaries * 8), int(width * 0.21), int(boundaries * 9.1),
								"Merge", TX_YELLOW, TX_YELLOW, "Georgia", int(boundaries * 0.8), true, false},
								{ int(boundaries * 0.4), int(boundaries * 9.4), int(width * 0.1), int(boundaries * 10.5),
								"Insertion", TX_ORANGE, TX_ORANGE, "Georgia", int(boundaries * 0.8), true, false},
								{ int(width * 0.11), int(boundaries * 9.4), int(width * 0.21), int(boundaries * 10.5),
								"Selection", TX_MAGENTA, TX_MAGENTA, "Georgia", int(boundaries * 0.8), true, false} };
	}
}