//! @file
//! \brief библиотека инициализации кнопок
//=================================================================================================================

#include <string>
#include <vector>
#include "TXLib.h"
#include "SortingFunction.h"
#include "UpdateTXLib.h"

namespace Buttons
{

//-----------------------------------------------------------------------------------------------------------------
//! \brief тип действия кнопки на щелчок мыши 
//-----------------------------------------------------------------------------------------------------------------

	enum TypeOfButton
	{
		NonFixedButton = 1,		///< нефиксирующаяся кнопка
		FixedButton = 2,		///< фиксирующая кнопка
		SwapingButton = 3		///< кнопка которая единственная среди группы кнопок активна
	};

//=================================================================================================================
//! \class button
//! \brief класс кнопки
//-----------------------------------------------------------------------------------------------------------------

	class button
	{
	public:
		int id;									///< индивидуальный код
		std::string text;						///< текст
		POINT pos;								///< координаты левого верхнего угла
		POINT size;								///< координаты правого нижнего угла
		int R;									///< радиус скругление углов кнопки
		COLORREF boundariesColor;				///< цвет границ
		COLORREF backColor;						///< фон активной кнопки
		const drawing::textStyle* styleText;	///< стиль текста кнопки
		bool isPressed;							///< является ли кнопка активна
		TypeOfButton type;						///< способ работы кнопки

		int(*linkToFunction)(int left, int right, std::vector<int>parametr, int* swaping,
											int* comparisons, std::vector<int>* Array);		///< ссылка на функцию сортировки

	public:

	//-----------------------------------------------------------------------------------------------------------------
	//!	\brief Рисует кнопки
	//! 
	//! \param backColor	цвет фона кнопки при её активации
	//! \param withContur	маркер наличия контура у кнопки; true - у кнопки будет контур, false - не будет
	//!
	//-----------------------------------------------------------------------------------------------------------------

		void DrawButton(bool withContur = 1)
		{
			if (isPressed) // если кнопка активнка
				drawing::DrawFoneOfPushedButton(pos.x, pos.y, size.x, size.y, R, backColor);

			if (withContur) // если нужен контур
				drawing::DrawGentleRectangle(pos.x, pos.y, size.x, size.y, R, boundariesColor);

			txSetColor(styleText->textColor);
			txSetFillColor(styleText->textColor);
			txSelectFont(styleText->nameFont.c_str(), styleText->sizeFont, FW_DONTCARE);
			txDrawText(pos.x, pos.y, size.x, size.y, text.c_str(), DT_CENTER | DT_VCENTER);
		}

	//-----------------------------------------------------------------------------------------------------------------
	//!	\brief Визуализирует эффект клика на кнопку
	//! 
	//! \param backColor	цвет фона кнопки при её активации
	//!
	//-----------------------------------------------------------------------------------------------------------------

		void ClickButton()
		{
			// рисуем нажатую кнопку
			drawing::DrawFoneOfPushedButton(pos.x, pos.y, size.x, size.y, R, backColor);
			DrawButton(0);
			txSleep(150);	// ждём

			txSetColor(backColor);
			txSetFillColor(backColor);

			// рисуем обычную кнопку
			txBegin();
			txRectangle(pos.x, pos.y, size.x, size.y);
			DrawButton(1);
			txEnd();
		}
	};

//=================================================================================================================
//! \brief рисует кнопки
//!
//! \param[in] Buttons массив кнопок
//!
//-----------------------------------------------------------------------------------------------------------------

	void DrawButtons(std::vector<button>* Buttons)
	{
		assert(Buttons != nullptr);
		for (button oneButton : (*Buttons))
		{
			oneButton.DrawButton(1);
		}
	}

//-----------------------------------------------------------------------------------------------------------------
//! \brief обрабатывает нажатие на кнопки
//!
//! \param[in] Buttons массив кнопок
//!
//! \return ссылку на функцию кнопки
//!
//-----------------------------------------------------------------------------------------------------------------

	int(*CheckClickButtons(std::vector<button>* Buttons)) (int left, int right, std::vector<int>parametr, 
		int* swaping, int* comparisons, std::vector<int>* Array)
	{

		assert(Buttons != nullptr);

		int idSwapingButton = -1;
		const long x = txMouseX(), y = txMouseY();

		int (*result)(int left, int right, std::vector<int>parametr, int* swaping, 
											int* comparisons, std::vector<int> * Array) = nullptr;

		for (int i = 0; i < Buttons->size();i++)
			if (In(x, (*Buttons)[i].pos.x, (*Buttons)[i].size.x) && In(y, (*Buttons)[i].pos.y, (*Buttons)[i].size.y))
			{
				if ((*Buttons)[i].type == SwapingButton)
				{
					idSwapingButton = (*Buttons)[i].id;
					(*Buttons)[i].isPressed = !(*Buttons)[i].isPressed;
					result = (*Buttons)[i].linkToFunction;
					break;
				}

				if ((*Buttons)[i].type == NonFixedButton)
				{
					(*Buttons)[i].ClickButton();
					result = (*Buttons)[i].linkToFunction;
					break;
				}

				if ((*Buttons)[i].type == FixedButton)
				{
					(*Buttons)[i].isPressed = !(*Buttons)[i].isPressed;
					result = (*Buttons)[i].linkToFunction;
					break;
				}

			}

		if (idSwapingButton != -1)
			for (int i = 0; i < Buttons->size(); i++)
				if ((*Buttons)[i].id != idSwapingButton)
					(*Buttons)[i].isPressed = false;
		return result;
	}

//-----------------------------------------------------------------------------------------------------------------
//!	\brief конструктор кнопки
//-----------------------------------------------------------------------------------------------------------------

	button CreateButton(int id, std::string text, POINT pos, POINT size, int R, COLORREF boundariesColor, COLORREF backColor,
		const drawing::textStyle* styleText, bool isPressed, TypeOfButton type,
		int(*linkToFunction)(int left, int right, std::vector<int>parametr, int* swaping, int* comparisons, std::vector<int>* Array))
	{
		return { id, text, pos, size, R, boundariesColor, backColor, styleText, isPressed, type, linkToFunction };
	}
}