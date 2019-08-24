//! @file
//! \brief доп функции на основе TXNetwork.h
//=================================================================================================================

#include <iostream>
#include <vector>
#include "TXNetwork.h"


//=================================================================================================================


namespace server {

//=================================================================================================================
// Дефайны
//=================================================================================================================

#define NONBLOCKREV(T) while(T == -1)


//=================================================================================================================
// Переменные
//=================================================================================================================

    static TX_SOCKET forConnectServer;


//=================================================================================================================
// Функции
//=================================================================================================================

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
//! \param[out] Array       вектор который получат
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

//-----------------------------------------------------------------------------------------------------------------
//! \brief Отправляет строку через сокет
//! 
//! \param      to          сокет получателя
//! \param[in]  String      строка которую нужно отправить
//!
//-----------------------------------------------------------------------------------------------------------------

    static void SendString(TX_SOCKET to, std::string* String)
    {
        assert(String != nullptr);

        char    current   = '\0';
        int     lenString = String->size();

        txSendTo(to, &lenString, sizeof(lenString));

        for (int i = 0; i < lenString; i++)
        {
            current = (*String)[i];
            txSendTo(to, &current, 1);
        }
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Получает строку вектор через сокет
//! 
//! \param      from        сокет отправителя
//! \param[out] String      строка которую получат
//!
//-----------------------------------------------------------------------------------------------------------------

    static void GetString(TX_SOCKET from, std::string* String)
    {
        assert(String != nullptr);

        char    current   = '\0';
        int     lenString = -1;

        String->clear();
        NONBLOCKREV(txRecvFrom(from, &lenString, sizeof(int)));
        
        for (int i = 0; i < lenString; i++)
        {
            NONBLOCKREV(txRecvFrom(from, &current, 1));
            String->push_back(current);
        }
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Ищет клиента для сервера и подключает его
//! 
//! \param[in]  description     уникальное описания сервера для клиента
//! \param[in]  ip              ip сервера
//! \param[out] clientSocket    сокет к которому подклюсится сервер
//!
//-----------------------------------------------------------------------------------------------------------------

    bool SendMessageClient(std::string* description, std::string* ip)
    {
        assert(description      != nullptr  );
        assert(ip               != nullptr  );
        assert(description      != ip       );
        

        if (txnAssert(forConnectServer) == 101) // создаём сокет для широкоформатного общения
            forConnectServer = txCreateSocket(TX_SERVER, TX_BROADCAST, TX_STD_PORT, TX_NONBLOCK, false);

        int markerOfConnect = 1;

        txSendTo(forConnectServer, &markerOfConnect, sizeof(int)); // говорим о том, что будем что-то писать

        SendString(forConnectServer, description);  // отправляем своё описания
        SendString(forConnectServer, ip);           // отправляем свой ip
        
        return true;
    }

    bool ConnectToClient(std::string* ip, TX_SOCKET* clinetSocket)
    {
        assert(ip               != nullptr  );
        assert(clinetSocket     != nullptr  );

        int         markerOfConnect = -1;
        std::string answer;

        if (txRecvFrom(forConnectServer, &markerOfConnect, sizeof(int)) == -1) //ждём чьего-нибудь ответа
            return false;
        
        GetString(forConnectServer, &answer); // получаем решение клиента

        std::string readyForConnect = "OK ";

        if (answer != (readyForConnect + (*ip))) // проверяем что он согласен
            return false;

        (*clinetSocket) = txCreateSocket(TX_SERVER, ""); // подключаемся
        return true;
    }

//-----------------------------------------------------------------------------------------------------------------
//! \brief Ищет сервер для клиента с определённым описанием и подключается к нему
//! 
//! \param[in]  descriptionOfServer     уникальное описания сервера для клиента
//! \param[out] server                  сокет к которому подклюсится сервер
//!
//-----------------------------------------------------------------------------------------------------------------

    bool findServer(const std::string* descriptionOfServer, TX_SOCKET* server)
    {
        assert(descriptionOfServer  != nullptr);
        assert(server               != nullptr);

        TX_SOCKET forConnect = txCreateSocket(TX_CLIENT, TX_BROADCAST, TX_STD_PORT, TX_NONBLOCK, false);

        std::string description;
        std::string ip;
        int         markerOfConnect = -1;

        std::vector<std::pair<std::string, std::string>> listOfServer;

        while (txRecvFrom(forConnect, &markerOfConnect, sizeof(int)) == -1); // ждём что какой-то сервер сообщит о себе
        
        do {
            GetString(forConnect, &description); // получаем описания сервера
            GetString(forConnect, &ip);          // получаем ip сервера

            listOfServer.push_back({ description,ip }); // запоминаем сервер

        } while (txRecvFrom(forConnect, &markerOfConnect, sizeof(int)) != -1);

        if (listOfServer.size() == 0)
            return false;

        for (size_t i = 0; i < listOfServer.size(); i++)
            if (listOfServer[i].first == (*descriptionOfServer)) //проверяем что это наш сервер
            {
                txSendTo(forConnect, &markerOfConnect, sizeof(int));

                std::string readyForConnect =   "OK ";
                            readyForConnect +=  ip;

                SendString(forConnect, &readyForConnect); // говорим что мы хотим подключиться

                while (txnAssert((*server)) == 101)
                    (*server) = txCreateSocket(TX_CLIENT, listOfServer[i].second.c_str()); //подключаемся

                return true;
            }
        return false;
    }
}