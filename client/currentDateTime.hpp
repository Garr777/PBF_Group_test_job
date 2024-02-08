#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>


std::string currentDateTime() 
{
        auto currentTime = std::chrono::system_clock::now();
        auto duration = currentTime.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

        
        std::time_t time_now = std::chrono::system_clock::to_time_t(currentTime);
        std::tm* tm_info = std::localtime(&time_now);
        
        std::ostringstream output;
       
        output << std::put_time(tm_info, "[%Y-%m-%d %H:%M:%S") << "." << std::setfill('0') << std::setw(3) << milliseconds << "] ";

        std::string result = output.str();
        return result;
}