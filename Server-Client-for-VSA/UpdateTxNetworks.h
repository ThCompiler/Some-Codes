//! @file
//! \brief доп функции на основе TXNetwork.h
//=================================================================================================================

#include <iostream>
#include <vector>
#include "TXNetwork.h"


//=================================================================================================================


namespace server {

//-----------------------------------------------------------------------------------------------------------------
//! \brief Отправляет вектор через сокет
//! 
//! \param      to          сокет получателя
//! \param[in]  Array       вектор который нужно отправить
//!
//-----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void SendVector(TX_SOCKET to, std::vector<T>* Array)
    {
        assert(Array != nullptr);

        T   current;
        int lenArray = Array->size();

        txSendTo(to, &lenArray, sizeof(lenArray));

        for (int i = 0; i < lenArray; i++)
        {
            current = (*Array)[i];
            txSendTo(to, &current, sizeof(T));
        }
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Получает вектор через сокет
//! 
//! \param      from        сокет отправителя
//! \param[out] Array       вектор который нужно отправить
//!
//-----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void GetVector(TX_SOCKET from, std::vector<T>* Array)
    {
        assert(Array != nullptr);

        int lenArray = Array->size();

        txRecvFrom(from, &lenArray, sizeof(lenArray));

        Array->clear();

        for (T current; lenArray > 0; lenArray--)
        {
            txRecvFrom(from, &current, sizeof(T));
            Array->push_back(current);
        }
    }
}