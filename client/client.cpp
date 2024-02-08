#include "client.hpp"



int main(int argc, char** argv)
{
    Client client(argv[1], argv[2], argv[3]);

    while(1)
    {
        client.createSocket();
        client.connection();
        client.sending();
        std::this_thread::sleep_for(std::chrono::seconds(client.period));
        client.closing();
    }
    return 0;
}