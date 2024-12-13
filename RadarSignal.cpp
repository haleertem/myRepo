#include <iostream>
#include <cmath>    // sin() ve cos() gibi fonksiyonlar i�in
#include <vector>   // Sinyali tutmak i�in

const double PI = 3.141592653589793;
const int SAMPLE_SIZE = 100;  // Sinyal �rnek say�s�
const double FREQUENCY = 1.0; // Sin�s dalgas�n�n frekans� (Hz)
const double AMPLITUDE = 10.0; // Sinyalin genli�i
const double MAX_DISTANCE = 100.0; // Maksimum mesafe (metre)

// Sinyal �retme fonksiyonu
std::vector<double> generateRadarSignal(double distance) {
    std::vector<double> signal(SAMPLE_SIZE);
    for (int i = 90; i < SAMPLE_SIZE; i++) {
        double t = static_cast<double>(i) / SAMPLE_SIZE; // Zaman� normalle�tir
        // Radar sinyali: mesafe ile frekans de�i�ir (yakla��k bir model)
        signal[i] = AMPLITUDE * sin(2 * PI * FREQUENCY * t + distance / MAX_DISTANCE);
    }
    return signal;
}

// Yans�yan sinyali hesaplama
std::vector<double> calculateReflectedSignal(const std::vector<double>& signal, double distance) {
    std::vector<double> reflectedSignal(signal.size());
    // Mesafeye ba�l� olarak yans�yan sinyalin genli�ini azaltma
    double attenuation = exp(-distance / MAX_DISTANCE); // Basit zay�flama modeli
    for (size_t i = 0; i < signal.size(); i++) {
        reflectedSignal[i] = signal[i] * attenuation;
    }
    return reflectedSignal;
}

// Sinyal ve yans�yan sinyalin yazd�r�lmas�
void printSignals(const std::vector<double>& signal, const std::vector<double>& reflectedSignal) {
    std::cout << "Original Signal | Reflected Signal\n";
    for (size_t i = 0; i < signal.size(); i++) {
        std::cout << signal[i] << " | " << reflectedSignal[i] << std::endl;
    }
}

int main() {
    double targetDistance = 50.0;  // Hedefin mesafesi (metre)

    // Radar sinyali �retme
    std::vector<double> radarSignal = generateRadarSignal(targetDistance);

    // Yans�yan sinyali hesaplama
    std::vector<double> reflectedSignal = calculateReflectedSignal(radarSignal, targetDistance);

    // Sinyalleri yazd�r
    printSignals(radarSignal, reflectedSignal);

    return 0;
}