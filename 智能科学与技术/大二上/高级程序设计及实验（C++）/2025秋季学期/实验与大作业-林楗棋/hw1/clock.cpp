#include <vector>
#include <iostream>
class  Clock {
    int hour, minute, second; 
    friend std::vector<int> timeDiff(const Clock& clock1, const Clock& clock2);
public: 
    static int Total_count, Active_count;
    Clock(int hour, int minute, int second);
    ~Clock();
    void setTime(int newH, int newM, int newS); 
    void showTime();
};

int Clock::Total_count = 0;
int Clock::Active_count = 0;

Clock::Clock(int hour, int minute, int second) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    Total_count++;
    Active_count++;
}

Clock::~Clock() {
    Active_count--;
} 

void Clock::setTime(int newH, int newM, int newS) {
    hour = newH;
    minute = newM;
    second = newS;
}

void Clock::showTime() {
    std::cout << (hour < 10 ? "0" : "") << hour << ":"
              << (minute < 10 ? "0" : "") << minute << ":"
              << (second < 10 ? "0" : "") << second << std::endl;
}

std::vector<int> timeDiff(const Clock& clock1, const Clock& clock2) {
    int totalSeconds1 = clock1.hour * 3600 + clock1.minute * 60 + clock1.second;
    int totalSeconds2 = clock2.hour * 3600 + clock2.minute * 60 + clock2.second;
    int diff = std::abs(totalSeconds1 - totalSeconds2);

    int hours = diff / 3600;
    diff %= 3600;
    int minutes = diff / 60;
    int seconds = diff % 60;

    return {hours, minutes, seconds};
}

int main() {
    Clock clock1(10, 30, 45);
    Clock clock2(12, 15, 20);

    std::cout << "Clock 1 time: ";
    clock1.showTime();
    std::cout << "Clock 2 time: ";
    clock2.showTime();

    std::vector<int> diff = timeDiff(clock1, clock2);
    std::cout << "Time difference: "
              << (diff[0] < 10 ? "0" : "") << diff[0] << ":"
              << (diff[1] < 10 ? "0" : "") << diff[1] << ":"
              << (diff[2] < 10 ? "0" : "") << diff[2] << std::endl;

    std::cout << "Total Clock instances created: " << Clock::Total_count << std::endl;
    std::cout << "Active Clock instances: " << Clock::Active_count << std::endl;

    return 0;
}