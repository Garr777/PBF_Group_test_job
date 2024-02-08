#include <iostream>
#include <vector>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "currentDateTime.hpp"

class Client
{
private:
public:
    std::string name;
    int port;
    int period;
    int sock;
    struct sockaddr_in addr;
    Client(char* name, char* port , char* period)
    {
        this->name = name;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(std::stoi(port)); 
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        this->period = std::stoi(period);
    };
    void createSocket()
    {
        sock = socket(AF_INET,SOCK_STREAM,0);
        if(sock < 0)
        {
            std::cerr << "Error: " << strerror(errno) << std::endl;
            exit(1);
        }
    }

    void connection()
    {
        if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect");
            exit(2);
        }
    }

    void sending()
    {
        std::string str = currentDateTime() + name;
        std::vector<char> bytes(str.begin(), str.end());
        bytes.push_back('\0');
        char *c = &bytes[0];
        send(sock, c, sizeof(str), 0);
    }

    void closing()
    {
        close(sock);
    }

    ~Client()
    {

    };
};

