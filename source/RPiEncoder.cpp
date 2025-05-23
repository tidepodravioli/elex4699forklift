#include "../headers/RPiEncoder.hpp"
#include <atomic>

RPiEncoder* RPiEncoder::instanceMap[32] = {nullptr};

RPiEncoder::RPiEncoder(int pinA, int pinB) : _pinA(pinA), _count(0) {
    gpioSetMode(_pinA, PI_INPUT);
    gpioSetPullUpDown(_pinA, PI_PUD_UP);

    instanceMap[_pinA] = this;

    gpioSetAlertFuncEx(_pinA, gpioCallback, this);
}

RPiEncoder::~RPiEncoder() {
    gpioSetAlertFunc(_pinA, nullptr);
    instanceMap[_pinA] = nullptr;
}

void RPiEncoder::gpioCallback(int gpio, int level, uint32_t tick, void* userData) {
    if (level != 1) return;  // Only rising edges
    RPiEncoder* instance = static_cast<RPiEncoder*>(userData);
    if (instance) {
        instance->handleInterrupt();
    }
}

void RPiEncoder::handleInterrupt() {
    _count++;
}

long RPiEncoder::getCount() const {
    return _count.load();
}
