//! @file
//! \brief библиотека инициализации кнопок
//=================================================================================================================

#include <string>
#include <vector>
#include "ButtonsFunction.h"
#include "UpdateTXLib.h"

namespace Buttons {

//-----------------------------------------------------------------------------------------------------------------
//! \brief тип действия кнопки на щелчок мыши 
//-----------------------------------------------------------------------------------------------------------------

    enum TypeOfButton
    {
        NonFixedButton          = 1,             ///< нефиксирующаяся кнопка
        FixedButton             = 2,             ///< фиксирующая кнопка
        InterchangeableButton   = 3              ///< кнопка которая единственная среди группы кнопок активна
    };

//=================================================================================================================
//! \class button
//! \brief класс кнопки
//-----------------------------------------------------------------------------------------------------------------

    class button
    {
    public:
        int                         id;                             ///< индивидуальный код
        std::string                 text;                           ///< текст
        POINT                       pos;                            ///< координаты левого верхнего угла
        POINT                       size;                           ///< координаты правого нижнего угла
        int                         R;                              ///< радиус скругление углов кнопки
        COLORREF                    frameColor;                     ///< цвет границ
        COLORREF                    backColor;                      ///< фон активной кнопки
        COLORREF                    textColor;                      ///< цвет текста
        const drawing::textStyle*   styleText;                      ///< стиль текста кнопки
        bool                        isPressed;                      ///< является ли кнопка активна
        TypeOfButton                type;                           ///< способ работы кнопки

        int(*linkToFunction)(int left, int right, std::vector<int>parametrs, int* swaping, int* comparisons, std::vector<int>* Array); ///< ссылка на функцию сортировки

    public:

    //-----------------------------------------------------------------------------------------------------------------
    //! \brief Рисует кнопки
    //!
    //! \param withContur   маркер наличия контура у кнопки; true - у кнопки будет контур, false - не будет
    //!
    //-----------------------------------------------------------------------------------------------------------------

        void DrawButton(bool withContur = 1)
        {
            if (isPressed) // если кнопка активнка
                drawing::DrawFoneOfPushedButton(pos.x, pos.y, size.x, size.y, R, backColor);

            if (withContur) // если нужен контур
                drawing::DrawGentleRectangle(pos.x, pos.y, size.x, size.y, R, frameColor);

            txSetColor      (textColor);
            txSetFillColor  (textColor);

            drawing::tx_SelectFont  (styleText->nameFont.c_str(), styleText->sizeFont, FW_DONTCARE);
            drawing::tx_DrawText    (pos.x, pos.y, size.x, size.y, text.c_str(), DT_CENTER | DT_VCENTER);
        }

    //-----------------------------------------------------------------------------------------------------------------
    //! \brief Визуализирует эффект клика на кнопку
    //!
    //-----------------------------------------------------------------------------------------------------------------

        void ClickButton()
        {
            // рисуем нажатую кнопку
            drawing::DrawFoneOfPushedButton(pos.x, pos.y, size.x, size.y, R, backColor);
            DrawButton(0);

            txSleep(150);   // ждём

            txSetColor      (backColor);
            txSetFillColor  (backColor);

            // рисуем обычную кнопку
            txBegin();
            drawing::tx_Rectangle(pos.x, pos.y, size.x, size.y);
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

    int(*CheckClickButtons(std::vector<button>* Buttons)) (int left, int right, std::vector<int>parametrs, 
                                                           int* swaping, int* comparisons, std::vector<int>* Array)
    {

        assert(Buttons != nullptr);

        int         idSwapingButton = -1;
        const int   x               = txMouseX();
        const int   y               = txMouseY();

        int (*result)(int left, int right, std::vector<int>parametrs, int* swaping, 
                      int* comparisons, std::vector<int> * Array)                       = nullptr;


        for (size_t i = 0; i < Buttons->size(); i++)
            if (In(std::nomeow,  x,  drawing::RealCord((*Buttons)[i].pos.x,  1),  drawing::RealCord((*Buttons)[i].size.x,  1))
             && In(std::nomeow,  y,  drawing::RealCord((*Buttons)[i].pos.y,  0),  drawing::RealCord((*Buttons)[i].size.y,  0)))
            {
                if ((*Buttons)[i].type == InterchangeableButton && !(*Buttons)[i].isPressed)
                {
                    idSwapingButton             = (*Buttons)[i].id;
                    (*Buttons)[i].isPressed     = !(*Buttons)[i].isPressed;
                    result                      = (*Buttons)[i].linkToFunction;
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
                    (*Buttons)[i].isPressed     =  !(*Buttons)[i].isPressed;
                    result                      =   (*Buttons)[i].linkToFunction;
                    break;
                }

            }

        if (idSwapingButton != -1)
            for (size_t i = 0; i < Buttons->size(); i++)
                if ((*Buttons)[i].id != idSwapingButton)
                    (*Buttons)[i].isPressed = false;

        return result;
    }
}