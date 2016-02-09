#include "stdafx.h"
#include "httpCaller.h"
#include <windows.web.h>
#include <wininet.h>


httpCaller::httpCaller(void)
{
	httpAdress = "https://www.pythonanywhere.com/user/ConorHarney/consoles/python2.7/2150022";
}


httpCaller::~httpCaller(void)
{
}

bool CheckConnected()
{
	/*if(InternetCheckConnection(L"http://www.google.com",FLAG_ICC_FORCE_CONNECTION,0))
	{
		return true;
	}
	else
	{
		return false;
	}*/
	return true;
}


#pragma comment(lib,"ws2_32.lib")
using namespace std;
void httpCaller::caller(){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cout << "WSAStartup failed.\n";
        system("pause");
    }
    SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct hostent *host;
    host = gethostbyname("www.google.com");
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
    cout << "Connecting...\n";
    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        cout << "Could not connect";
        system("pause");
    }
    cout << "Connected.\n";
    send(Socket,"GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n", strlen("GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n"),0);
    char buffer[10000];
    int nDataLength;
    while ((nDataLength = recv(Socket,buffer,10000,0)) > 0){        
        int i = 0;
        while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
            cout << buffer[i];
            i += 1;
        }
    }
    closesocket(Socket);
        WSACleanup();
}

std::string httpCaller::getRawScoreboard()
{
	std::string retString = "";
	// Create a new HTTP client
	sf::Http http(httpAdress,8000);
	// Prepare a request to get the 'features.php' page
	sf::Http::Request request;
	request.setMethod(sf::Http::Request::Get);
	request.setUri("/test/");

	sf::Http::Response response = http.sendRequest(request);
	// Check the status code and display the result
	sf::Http::Response::Status status = response.getStatus();
	if (status == sf::Http::Response::Ok)
	{
		retString = response.getBody();
	}
	else
	{
		std::cout << "Error " << status << std::endl;
	}
	//system("pause");
	return retString;
}

list<PlayerInformationSet> httpCaller::getScoreBoard() {
	 vector<string> elems;
	 stringstream ss(getRawScoreboard());
	 string item;
	
	 //break into info set and id
     while (getline(ss, item, '"')) {
         elems.push_back(item);
     }
	//erase }
	elems.pop_back();
	//erase {
	if(elems.size() > 0){
		elems.erase(elems.begin());
	}
	
	vector<string> elems2;
	while(elems.size() > 0)
	{
		if(elems.back() == ", ")
		{
			elems.pop_back();
		}
		string playerInfo = "";
		playerInfo.append(elems.back());
		elems.pop_back();
		playerInfo.append(",");
		elems.pop_back();
		playerInfo.append(elems.back());
		elems.pop_back();
		elems2.push_back(playerInfo);
	}
	elems = elems2;
	elems2.clear();
	list<PlayerInformationSet> playersInfo;
	while(elems.size() > 0)
	{
		vector<string> elems3;
		stringstream ss2(elems.back());

		//break into info set and id
		while (getline(ss2, item, ',')) {
			elems3.push_back(item);
		}
		int id = stoi(elems3.back());
		elems3.pop_back();
		int score = stoi(elems3.back());
		elems3.pop_back();
		string name = elems3.back();
		playersInfo.push_back(PlayerInformationSet(id,name,score));
		elems.pop_back();
	}

	return playersInfo;
}

void httpCaller::postToScoreBoard(PlayerInformationSet* p_playerInfo)
{//posts the score and sets the id of the playyer information set
	// Create a new HTTP client
	sf::Http http(httpAdress,8000);
	// Prepare a request to get the 'features.php' page
	sf::Http::Request request;
	request.setMethod(sf::Http::Request::Post);
	string myuri =  "/writeToDatabase/?p_name=";
	myuri.append(p_playerInfo->getName());
	myuri.append("&p_score=");
	myuri.append(std::to_string(p_playerInfo->getScore()));
	request.setUri(myuri);

	sf::Http::Response response = http.sendRequest(request);
	// Check the status code and display the result
	sf::Http::Response::Status status = response.getStatus();
	if (status == sf::Http::Response::Ok)
	{
		string retString = response.getBody();
		retString.erase(retString.begin(),retString.begin() + 7);
		retString.erase(retString.end() - 1, retString.end());
		p_playerInfo->setId(stoi(retString));
	}
	else
	{
		std::cout << "Error " << status << std::endl;
	}
}