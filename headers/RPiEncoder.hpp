#include <pigpio.h>
#include <atomic>

class RPiEncoder {
public:
    RPiEncoder(int pinA, int pinB);
    ~RPiEncoder();

    long getCount() const;

private:
    int _pinA, _pinB;
    static void gpioCallback(int gpio, int level, uint32_t tick);
    void handleInterrupt(int level);

    static RPiEncoder* instanceMap[32];  // Supports GPIO 0–31
    std::atomic<long> _count;
};
