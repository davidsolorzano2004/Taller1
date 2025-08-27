#ifndef SENSORTEMP_H
#define SENSORTEMP_H

#include <Arduino.h>

class SensorTemp {
  public:
    SensorTemp(int pin, float VCC = 3.3, int ADC_MAX = 4095);
    float leerTemperatura();

  private:
    int _pin;
    float _VCC;
    int _ADC_MAX;
    float _BETA;  // Solo necesitamos Beta para Wokwi
};

#endif
