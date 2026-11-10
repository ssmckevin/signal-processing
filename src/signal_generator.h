
#pragma once

#include <vector>
#include <complex>

class SignalGenerator {
public:
    // Generate desired sine wave
    std::vector<double> genSignal(
        double sampleRate,
        int numOfSamples,
        int desiredFreq
    );

    // Generate interference sine wave
    std::vector<double> genInterference(
        double sampleRate,
        int numOfSamples,
        int interferenceFreq
    );

    // Generate random noise
    std::vector<double> genNoise(
        int numOfSamples
    );

    // Combine desired signal, interference, and noise
    std::vector<double> combineSignals(
        const std::vector<double>& desired,
        const std::vector<double>& interference,
        const std::vector<double>& noise
    );

    // Apply moving-average filter
    std::vector<double> filterSignals(
        const std::vector<double>& combined,
        int windowSize
    );

    // Perform Discrete Fourier Transform
    std::vector<std::complex<double>> performDft(
        const std::vector<double>& target,
        int numOfSamples,
        int sampleRate
    );

    // Export signal and spectrum CSV files
    void genSignalFile(
        const std::vector<double>& ogSignal,
        const std::vector<double>& filtered,
        int numOfSamples,
        int sampleRate,
        int windowSize
    );
};

