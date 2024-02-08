#include"server.hpp"



int main(int argc, char** argv)
{
    Server server(std::stoi(argv[1]));
    server.binding();
    server.connection(3);
    while(1)
    {
        server.listening();
    }
    
    return 0;
}

