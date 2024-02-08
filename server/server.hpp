#include <iostream>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <thread>

class Server
{
    private:
    public:
        int listener;
        int sock;
        struct sockaddr_in addr;
        char buf [1024];
        int bytes_read;
        Server(int port)
        {
            listener = socket(AF_INET, SOCK_STREAM, 0);
            if(listener < 0)
            {
                std::cerr << "Error: " << strerror(errno) << std::endl;
                exit(1);
            }

            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = htonl(INADDR_ANY);

        };
        void binding()
        {
                if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
                {
                    perror("bind");
                    exit(2);
                }
        }

        void connection(int connetcionCount) // connectionCount - max numbers of clients;
        {
            if(listen(listener, connetcionCount) < 0)
            {
                perror("connection error");
            }
        }

        void accepting()
        {
            sock = accept(listener, NULL, NULL);
            if(sock < 0)
            {
                perror("accept");
                exit(3);
            }
        }

        int receving()
        {
            return bytes_read = recv(sock, buf, 1024, 0);
        }

        void sending()
        {
            send(sock, buf, bytes_read, 0);
        }

        void record(char* name)
        {
            std::ofstream out("log.txt", std::ios::app);
            if (out.is_open())
            {
                out <<  name << std::endl;
            }
            out.close(); 
        }

        void listening()
        {
            accepting();
            std::thread th( [this]()
            {
                while(receving() > 0)
                {
                    record(buf);
                }
                closingSocket();
            });
            th.detach();
        }
        void closingSocket()
        {
            close(sock);
        }
        ~Server()
        {
            
        };
};