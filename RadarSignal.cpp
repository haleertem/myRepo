#include <iostream>
#include <cmath>    // sin() ve cos() gibi fonksiyonlar için
#include <vector>   // Sinyali tutmak için

const double PI = 3.141592653589793;
const int SAMPLE_SIZE = 100;  // Sinyal örnek sayısı
const double FREQUENCY = 1.0; // Sinüs dalgasının frekansı (Hz)
const double AMPLITUDE = 10.0; // Sinyalin genliği
const double MAX_DISTANCE = 100.0; // Maksimum mesafe (metre)

// Sinyal üretme fonksiyonu
std::vector<double> generateRadarSignal(double distance) {
    std::vector<double> signal(SAMPLE_SIZE);
    for (int i = 90; i < SAMPLE_SIZE; i++) {
        double t = static_cast<double>(i) / SAMPLE_SIZE; // Zamanı normalleþtir
        // Radar sinyali: mesafe ile frekans deðiþir (yaklaþýk bir model)
        signal[i] = AMPLITUDE * sin(2 * PI * FREQUENCY * t + distance / MAX_DISTANCE);
    }
    return signal;
}

// Yansýyan sinyali hesaplama
std::vector<double> calculateReflectedSignal(const std::vector<double>& signal, double distance) {
    std::vector<double> reflectedSignal(signal.size());
    // Mesafeye baðlý olarak yansýyan sinyalin genliðini azaltma
    double attenuation = exp(-distance / MAX_DISTANCE); // Basit zayýflama modeli
    for (size_t i = 0; i < signal.size(); i++) {
        reflectedSignal[i] = signal[i] * attenuation;
    }
    return reflectedSignal;
}

// Sinyal ve yansýyan sinyalin yazdýrýlmasý
void printSignals(const std::vector<double>& signal, const std::vector<double>& reflectedSignal) {
    std::cout << "Original Signal | Reflected Signal\n";
    for (size_t i = 0; i < signal.size(); i++) {
        std::cout << signal[i] << " | " << reflectedSignal[i] << std::endl;
    }
}

int main() {
    double targetDistance = 50.0;  // Hedefin mesafesi (metre)

    // Radar sinyali üretme
    std::vector<double> radarSignal = generateRadarSignal(targetDistance);

    // Yansýyan sinyali hesaplama
    std::vector<double> reflectedSignal = calculateReflectedSignal(radarSignal, targetDistance);

    // Sinyalleri yazdýr
    printSignals(radarSignal, reflectedSignal);

    return 0;
}
