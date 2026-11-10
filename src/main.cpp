
#include <iostream>
#include <vector>
#include <exception>

#include "signal_generator.h"

int main() {
    try {
        // Signal parameters
        int sampleRate = 1024;
        int numOfSamples = 1024;
        int desiredFreq = 32;
        int interferenceFreq = 192;
        int windowSize = 5;

        // Create SignalGenerator object
        SignalGenerator generator;

        // Generate desired signal
        std::vector<double> desired =
            generator.genSignal(sampleRate, numOfSamples, desiredFreq);

        // Generate interference
        std::vector<double> interference =
            generator.genInterference(sampleRate, numOfSamples, interferenceFreq);

        // Generate random noise
        std::vector<double> noise =
            generator.genNoise(numOfSamples);

        // Combine desired signal, interference, and noise
        std::vector<double> combined =
            generator.combineSignals(desired, interference, noise);

        // Apply moving-average filter
        std::vector<double> filtered =
            generator.filterSignals(combined, windowSize);

        // Generate CSV files
        generator.genSignalFile(
            combined,
            filtered,
            numOfSamples,
            sampleRate,
            windowSize
        );

        std::cout << "Signal processing completed successfully!\n";
        std::cout << "Generated signal.csv and spectrum.csv\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

