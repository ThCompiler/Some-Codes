//! @file
//! \brief доп функции на основе TXLib.h
//=================================================================================================================

#include "TXLib.h"


namespace drawing
{
//=================================================================================================================
// блок структур
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
//! \brief стиль текста 
//-----------------------------------------------------------------------------------------------------------------

    struct textStyle
    {
        std::string nameFont;       ///<  названия шрифта текста
        int         sizeFont;       ///<  размер шрифта
    };

//=================================================================================================================
// блок констант
//=================================================================================================================

    const COLORREF TX_SCARLET = RGB(248, 0, 0); ///< алый цвет

//=================================================================================================================
//! \brief Преобразует виртуальные координаты программы в реальные координаты окна
//! 
//! \param cord     виртуальная координата
//! \param isX      маркер принодлежности к осям координаты; true - координата по оси x, false - по оси y
//!
//! \return     реальную координату объекта
//!
//-----------------------------------------------------------------------------------------------------------------

    int RealCord(int cord, bool isX)
    {
        if (isX)
            return int(cord*txGetExtentX() / 1310);
        else
            return int(cord*txGetExtentY() / 675);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Рисует линию
//!
//! обновлённая функция txLine из TXLib.h с учётом изменения окна
//!
//! \param   x0  X-координата начальной точки
//! \param   y0  Y-координата начальной точки
//! \param   x1  X-координата конечной  точки
//! \param   y1  Y-координата конечной  точки
//!
//! Цвет и толщина линии задается функцией txSetColor() из TXLib.h.
//!
//-----------------------------------------------------------------------------------------------------------------

    void tx_Line(int x0, int y0, int x1, int y1)
    {
        //переводим виртуальные координаты в реальные
        x0 = RealCord(x0, 1);
        x1 = RealCord(x1, 1);
        y0 = RealCord(y0, 0);
        y1 = RealCord(y1, 0);

        txLine(x0, y0, x1, y1);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Рисует пряммоугольник
//!
//! обновлённая функция txRectangle из TXLib.h с учётом изменения окна
//!
//! \param   x0  X-координата верхнего левого  угла
//! \param   y0  Y-координата верхнего левого  угла
//! \param   x1  X-координата нижнего  правого угла
//! \param   y1  Y-координата нижнего  правого угла
//!
//! Цвет и толщина линий задается функцией txSetColor(), цвет заполнения - txSetFillColor() из TXLib.h.
//!
//-----------------------------------------------------------------------------------------------------------------

    void tx_Rectangle(int x0, int y0, int x1, int y1)
    {
        //переводим виртуальные координаты в реальные
        x0 = RealCord(x0, 1);
        x1 = RealCord(x1, 1);
        y0 = RealCord(y0, 0);
        y1 = RealCord(y1, 0);

        txRectangle(x0, y0, x1, y1);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief   Рисует пиксель
//!
//! обновлённая функция txSetPixel из TXLib.h с учётом изменения окна
//!
//! \param   x      Х-координата точки
//! \param   y      Y-координата точки
//! \param   color  цвет точки
//!
//-----------------------------------------------------------------------------------------------------------------

    void tx_SetPixel(int x, int y, COLORREF color)
    {
        //переводим виртуальные координаты в реальные
        x = RealCord(x, 1);
        y = RealCord(y, 0);

        txSetPixel(x, y, color);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief  Рисует текст, размещенный в прямоугольной области
//!
//! обновлённая функция txDrawText из TXLib.h с учётом изменения окна
//!
//! \param   x0     X-координата верхнего левого  угла области
//! \param   y0     Y-координата верхнего левого  угла области
//! \param   x1     X-координата нижнего  правого угла области
//! \param   y1     Y-координата нижнего  правого угла области
//! \param   text   текстовая строка
//! \param   format флаги форматирования текста
//!
//! Цвет текста задается функцией txSetColor(), выравнивание - txSetTextAlign() из TXLib.h.
//!
//-----------------------------------------------------------------------------------------------------------------

    void tx_DrawText(int x0, int y0, int x1, int y1, const char text[], unsigned format)
    {
        //переводим виртуальные координаты в реальные
        x0 = RealCord(x0, 1);
        x1 = RealCord(x1, 1);
        y0 = RealCord(y0, 0);
        y1 = RealCord(y1, 0);

        txDrawText(x0, y0, x1, y1, text, format);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief  Рисует текст
//!
//! обновлённая функция txTextOut из TXLib.h с учётом изменения окна
//!
//! \param   x     Х-координата начальной точки текста
//! \param   y     Y-координата начальной точки текста
//! \param   text  текстовая строка
//!
//! Цвет текста задается функцией txSetColor(), выравнивание - txSetTextAlign() из TXLib.h.
//!
//-----------------------------------------------------------------------------------------------------------------

    void tx_TextOut(int x, int y, const char text[])
    {
        //переводим виртуальные координаты в реальные
        x = RealCord(x, 1);
        y = RealCord(y, 0);

        txTextOut(x, y, text);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief  Выбирает текущий шрифт
//!
//! обновлённая функция txSelectFont из TXLib.h с учётом изменения окна
//!
//! \param   name       Название шрифта
//! \param   sizeY      Высота букв (размер по Y)
//! \param   sizeX      Ширина букв
//! \param   bold       Жирность шрифта (от 0 до 1000)
//! \param   italic     Курсив
//! \param   underline  Подчеркивание
//! \param   strikeout  Зачеркивание
//! \param   angle      Угол поворота текста (в градусах)
//!
//! Цвет текста задается функцией txSetColor(), выравнивание - txSetTextAlign() из TXLib.h.
//!
//-----------------------------------------------------------------------------------------------------------------

    void tx_SelectFont(const char name[], double sizeY,
                       double sizeX     = -1,
                       int    bold      = FW_DONTCARE,
                       bool   italic    = false,
                       bool   underline = false,
                       bool   strikeout = false,
                       double angle     = 0)
    {
        //переводим виртуальные размеры в реальные
        sizeY = RealCord(sizeY, 0);
        sizeX = RealCord(sizeX, 0);

        txSelectFont(name, sizeY, sizeX, bold, italic, underline, strikeout, angle);
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Рисует прямоугольник с круглёными углами радиусом R
//! 
//! Используется в Buttons.h
//! \param x0, y0       координаты левего верхнего угла прямоугольника
//! \param x1, y1       координаты правого нижнего угла прямоугольника
//! \param R            радиус скругления
//! \param color        цвет рамки "мягкого" прямоугольника
//!
//-----------------------------------------------------------------------------------------------------------------

    void DrawGentleRectangle(int x0, int y0, int x1, int y1, int R, COLORREF color)
    {
        //переводим виртуальные координаты в реальные
        x0 = RealCord(x0, 1);
        x1 = RealCord(x1, 1);
        y0 = RealCord(y0, 0);
        y1 = RealCord(y1, 0);

        if (x1 - x0 < 2 * R) // если скругление слишком большое, то рисуем круг
        {
            txCircle((x1 - x0) / 2, (y1 - y0) / 2, R);
            return;
        }

        txSetColor      (color);
        txSetFillColor  (color);

        txLine  (x0 + R - 1,    y0,             x1 - R,     y0);                                // верхняя сторона
        txArc   (x1 - 2 * R,    y0,             x1,         y0 + 2 * R, 0,      90);            // правый верхний угол
        txLine  (x1,            y0 + R - 1,     x1,         y1 - R);                            // правая сторона
        txArc   (x1 - 2 * R,    y1,             x1,         y1 - 2 * R, -90,    90);            // правый нижний угол
        txLine  (x0 + R - 1,    y1,             x1 - R,     y1);                                // нижняя сторона
        txArc   (x0,            y1 - 2 * R,     x0 + 2 * R, y1,         180,    90);            // левый нижний угол
        txLine  (x0,            y0 + R - 1,     x0,         y1 - R);                            // левая сторона
        txArc   (x0,            y0 + 2 * R,     x0 + 2 * R, y0,         90,     90);            // левый верхний угол
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Рисует внутри кнопки градиент от заданого цвета до более тёмного
//! 
//! \param x0, y0       координаты левего верхнего угла кнопки
//! \param x1, y1       координаты правого нижнего угла кнопки
//! \param R            радиус скругления у кнопки
//! \param BackColor    цвет фона нажатой кнопки
//!
//-----------------------------------------------------------------------------------------------------------------

    void DrawFoneOfPushedButton(int x0, int y0, int x1, int y1, int R, COLORREF BackColor)
    {
        const int gap   = MIN(x1 - x0, y1 - y0) / 2; // число эелементов градиента
        const int r     = R;

        R = 0;

        if ((x1 - x0) < (y1 - y0)) // определяем координаты начальной позиции градиента
        {
            y1 -= (x1 - x0) / 2;
            y0 += (x1 - x0) / 2;
            x0  = (x1 + x0) / 2;
            x1  = x0;
        }
        else
        {
            x1 -= (y1 - y0) / 2;
            x0 += (y1 - y0) / 2;
            y0  = (y1 + y0) / 2;
            y1  = y0;
        }

        for (int i = 1; i <= gap; i++)
        {
            const COLORREF color =  RGB(MAX(txExtractColor(BackColor, TX_RED) - 1.3 * i, 0),     // получаем цвет для 
                                    MAX(txExtractColor(BackColor, TX_GREEN) - 1.3 * i, 0),       // каждого элемента
                                    txExtractColor(BackColor, TX_BLUE));                         // градиента

            if (gap - i <= r)           // если приблежаемся к границам кнопки делаем скругление, чтобы не было торчаших углов
                R = r - (gap - i);

            txSetColor      (color);
            txSetFillColor  (color);

            DrawGentleRectangle(x0, y0, x1, y1, R, color);

            //переходим к следующему элементу градиента
            x0 -= 1;
            y0 -= 1;
            x1 += 1;
            y1 += 1;
        }
    }
}