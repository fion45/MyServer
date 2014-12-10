#pragma once

class MySocketClient : public LogicalConnection
{
public:
	MySocketClient(std::string pseudo);
	~MySocketClient(void);
    CLIENT_KEY getKey();
private:
    std::string pseudo;
};
