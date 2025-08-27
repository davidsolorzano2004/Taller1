#include "SensorTemp.h"
#include <math.h>

SensorTemp::SensorTemp(int pin, float VCC, int ADC_MAX) {
    _pin = pin;
    _VCC = VCC;
    _ADC_MAX = ADC_MAX;
    _BETA = 3950.0;
    pinMode(_pin, INPUT);
}

float SensorTemp::leerTemperatura() {
    // Promediar varias lecturas para reducir ruido
    const int n = 10;
    long sum = 0;
    
    for (int i = 0; i < n; i++) {
        sum += analogRead(_pin);
        delay(1);
    }
    
    int analogValue = sum / n;
    
    // Validar rango
    if (analogValue <= 10 || analogValue >= (_ADC_MAX - 10)) return NAN;
    
    // Fórmula exacta de Wokwi adaptada para 12 bits
    float ratio = (float)analogValue / _ADC_MAX;
    float term = log(1.0 / (1.0 / ratio - 1));
    float celsius = 1.0 / (term / _BETA + 1.0 / 298.15) - 273.15;
    
    return celsius;
}