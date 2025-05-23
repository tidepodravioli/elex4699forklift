#include <pigpio.h>
#include <atomic>

class RPiEncoder {
public:
    explicit RPiEncoder(int pinA, int pinB);
    ~RPiEncoder();

    long getCount() const;

private:
    int _pinA;
    std::atomic<long> _count;

    static RPiEncoder* instanceMap[32];
    static void gpioCallback(int gpio, int level, uint32_t tick, void* userData);

    void handleInterrupt();
};

