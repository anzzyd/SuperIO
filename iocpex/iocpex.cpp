
/*
	Tianze SuperIO AMXX Module
	Author:anzzy
	2019-05-24
*/

#include "stdafx.h"
#include "iocpex.h"
#include "MyForward.h"
#include "json/json.h"
/*
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
*/
int g_response_fwd = -1;
bool g_isLoaded = false;
float g_LastTime = 0.0f;
void WriteToConsole(int colorid, char *szFormat, ...);

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

//typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

class SwooleClient {
public:
	SwooleClient(){
		std::cout << "SwooleClient init" << std::endl;
	}

	void on_open(websocketpp::connection_hdl hdl) {
		isConnecting = false;
		isConnected = true;
		std::cout << "[SuperIO] Swoole 已连接成功" << std::endl;
	}

	void on_reconnect(websocketpp::connection_hdl hdl) {
		isConnected = false;
		isConnecting = false;
		std::cout << "[SuperIO] Swoole 连接遇到问题" << std::endl;
	}

	void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
		if (msg->get_opcode() == websocketpp::frame::opcode::text) {

			try {
				//*((char*)-1) = 'x';

				Json::Reader reader;
				Json::Value jObject;
				if (reader.parse(msg->get_payload().c_str(), jObject))
				{
					if (!jObject["index"].isInt() || !jObject["uid"].isInt() || !jObject["buffer"].isString()) {
						std::cout << "[SuperIO] Invalid protocol" << std::endl;
						return;
					}
					g_MyForward.Lock();
					g_MyForward.AddDataString(jObject["index"].asInt(), jObject["uid"].asInt(), jObject["buffer"].asCString());
					g_MyForward.UnLock();
				}
				else {
					std::cout << "[SuperIO] Invalid data buffer" << std::endl;
				}
			}
			catch (exception &e) {
				std::cout << "[SuperIO] Receive exception error." << std::endl;
				std::cout << msg->get_payload() << std::endl;
				std::cout << e.what() << std::endl;
			}
			catch (...) {
				std::cout << "[SuperIO] Send exception error." << std::endl;
			}
		}
	}

	bool send(std::string payload) {

		if (isConnecting || !isConnected || !g_isLoaded)
			return false;
		websocketpp::lib::error_code ec;
		handle.send(connection->get_handle() ,payload, websocketpp::frame::opcode::text, ec);
		if (ec) {
			return false;
		}
		return true;
	}

	void init() {
		handle.clear_access_channels(websocketpp::log::alevel::all);
		handle.clear_error_channels(websocketpp::log::elevel::all);
		handle.init_asio();
		handle.set_open_handler(websocketpp::lib::bind(&SwooleClient::on_open, this, ::_1));
		//handle.set_fail_handler(bind(&SwooleClient::on_reconnect, this, ::_1));
		handle.set_close_handler(websocketpp::lib::bind(&SwooleClient::on_reconnect, this, ::_1));
		handle.set_message_handler(websocketpp::lib::bind(&SwooleClient::on_message, this, ::_1, ::_2));

		//Try first connect.
		std::cout << "[SuperIO] 准备首次连接..." << std::endl;

		while (1) {
			websocketpp::lib::error_code ec;
			client::connection_ptr con = handle.get_connection(endpointURI, ec);
			if (ec) {
				Sleep(10000);
				continue;
			}
			connection = con;
			handle.connect(con);
			std::cout << "[SuperIO] 进入事件循环..." << std::endl;
			handle.run();//entry event loop

			isConnected = false;
			isConnecting = false;

			handle.reset();
			std::cout << "[SuperIO] !!!!! End event loop !!!!!" << std::endl;
		}
	}

	~SwooleClient() {
		std::cout << "SwooleClient destory" << std::endl;
	}
private:
	client handle;
	client::connection_ptr connection;
	bool isInit = false;
	bool isConnected = false;
	bool isConnecting = false;
	std::string endpointURI = "ws://swoole.baidu.com:32088";
};

SwooleClient endpoint;
HANDLE hThread;

DWORD WINAPI subThread(LPVOID lpParameter)
{
	endpoint.init();
	while (1) {
		Sleep(3000);
		std::cout << "我被执行了" << std::endl;
	}
	return 0;
}

void OnAmxxAttach()
{
	MF_AddNatives(IOCPEX_NATIVES);
	WriteToConsole(SCPCLR_PERPLE, "=========================================\n");
	WriteToConsole(SCPCLR_YELLOW, "\tSuperIO Client\n");
	WriteToConsole(SCPCLR_YELLOW, "\tVersion:3.2 Release\n");
	WriteToConsole(SCPCLR_YELLOW, "\tAuthor:Tianze Develop Team\n");
	WriteToConsole(SCPCLR_PERPLE, "=========================================\n");
}

void OnPluginsLoaded()
{
	//fw_DataResponse(const string[])
	g_response_fwd = MF_RegisterForward("fw_DataResponse", ET_IGNORE, FP_CELL, FP_CELL, FP_STRING, FP_DONE);
	g_isLoaded = true;
	g_LastTime = gpGlobals->time;

	if (!hThread)
	{
		hThread = CreateThread(NULL, 0, subThread, NULL, 0, NULL);
	}
}

void OnPluginsUnloading()
{
	g_isLoaded = false;
	g_response_fwd = -1;

	g_MyForward.Lock();
	g_MyForward.Clear();
	g_MyForward.UnLock();
}

void StartFrame_Post()
{
	if (g_isLoaded && g_LastTime < gpGlobals->time)
	{
		g_LastTime = gpGlobals->time + 0.35f;
		if (g_MyForward.TryLock())
		{
			try
			{
				g_MyForward.Execute();
			}
			catch (...)
			{
			}
			g_MyForward.UnLock();
		}
	}

	RETURN_META(MRES_IGNORED);
}


static cell AMX_NATIVE_CALL _isConnected(AMX* amx, cell* params) {
	return true;
}

//ok
static cell AMX_NATIVE_CALL _wsSend(AMX* amx, cell* params)
{
	if (!g_isLoaded)
		return false;
	int len;
	int pIndex = params[1];
	int pUserUid = params[2];
	std::string str = MF_FormatAmxString(amx, params, 3, &len);

	if (str[0] == '\0' || len == 0 || len > 4000) {
		return false;
	}

	try
	{
		Json::Value root;
		root["index"] = pIndex;
		root["uid"] = pUserUid;
		root["buffer"] = str;
		return endpoint.send(root.toStyledString());
	}
	catch (exception &e) {
		std::cout << "[SuperIO] Send exception error." << std::endl;
		std::cout << "[SuperIO] ID:" << pIndex << std::endl;
		std::cout << "[SuperIO] UID:" << pUserUid << std::endl;
		std::cout << "[SuperIO] RAW:" << str << std::endl;
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "[SuperIO] Send exception error." << std::endl;
	}

	return false;
}

static cell AMX_NATIVE_CALL pt_set_mapname(AMX *amx, cell *params)
{
	int len;
	char *str = MF_GetAmxString(amx, params[1], 0, &len);
	static char szData[128] = { 0 };
	_snprintf_s(szData, sizeof(szData), -1, str);
	gpGlobals->mapname = MAKE_STRING(szData);

	return 1;
}

AMX_NATIVE_INFO IOCPEX_NATIVES[] =
{
	{"pt_set_mapname"	,	pt_set_mapname			},
	{"wsSend"			,	_wsSend					},
	//兼容旧版接口，无缝升级
	//LoginAuth_amxx.dll
	{"SendLoginRequest"	,	_wsSend					},
	{"DataUpdater"		,	_wsSend					},
	{"DataReader"		,	_wsSend					},
	{"SendLoginRequest"	,	_wsSend					},
	{"LoginServerOnline",	_isConnected			},

	{NULL, NULL},
};

void WriteToConsole(int colorid, char *szFormat, ...)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	switch (colorid)
	{
	case 1:SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_RED));							break;
	case 2:SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_GREEN));							break;
	case 3:SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_BLUE));							break;
	case 4:SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE));			break;
	case 5:SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE));		break;
	case 6:SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED));		break;
	}

	va_list args;
	va_start(args, szFormat);
	vprintf(szFormat, args);
	va_end(args);

	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	SetConsoleTextAttribute(hConsole, 15);
}