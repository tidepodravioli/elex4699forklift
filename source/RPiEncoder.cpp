#include "../headers/RPiEncoder.hpp"
#include <iostream>

RPiEncoder* RPiEncoder::instanceMap[32] = {nullptr};

RPiEncoder::RPiEncoder(int pinA, int pinB) : _pinA(pinA), _pinB(pinB), _count(0) {
    gpioSetMode(_pinA, PI_INPUT);
    gpioSetMode(_pinB, PI_INPUT);

    gpioSetPullUpDown(_pinA, PI_PUD_UP);
    gpioSetPullUpDown(_pinB, PI_PUD_UP);

    instanceMap[_pinA] = this;

    gpioSetAlertFunc(_pinA, gpioCallback);
}

RPiEncoder::~RPiEncoder() {
    gpioSetAlertFunc(_pinA, nullptr);
    instanceMap[_pinA] = nullptr;
}

void RPiEncoder::gpioCallback(int gpio, int level, uint32_t tick) {
    if (level != 1) return; // Only handle rising edge
    RPiEncoder* instance = instanceMap[gpio];
    if (instance) {
        instance->handleInterrupt(level);
    }
}

void RPiEncoder::handleInterrupt(int level) {
    int b = gpioRead(_pinB);
    if (b)
        _count++;
    else
        _count--;
}

long RPiEncoder::getCount() const {
    return _count.load();
}
