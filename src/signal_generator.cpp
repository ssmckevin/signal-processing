#include <complex>
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "signal_generator.h"

	std::vector<double> SignalGenerator::genSignal(double sampleRate, int numOfSamples, int desiredFreq){
			const double pi = std::acos(-1.0);
			// init array
			std::vector<double> samples(numOfSamples, 0);
			// from time 0 to 1024 calc a sample and insert back into array
			for(int i = 0; i < numOfSamples; i++){
				double time = static_cast<double> (i) / sampleRate;
				double calc = 2 * pi * desiredFreq * time;
				calc = std::sin(calc);
				samples[i] = calc;
			}
			return samples;
		}

	std::vector<double> SignalGenerator::genInterference(double sampleRate, int numOfSamples, int interferenceFreq){
			const double pi = std::acos(-1.0);
                        // init array
                        std::vector<double> interferenceSamples(numOfSamples, 0);
                        // from time 0 to 1024 calc a sample and insert back into array
                        for(int i = 0; i < numOfSamples; i++){
                                double time = static_cast<double> (i) / sampleRate;
                                double calc = 2 * pi * interferenceFreq * time;
                                calc = std::sin(calc);
                                interferenceSamples[i] = calc;
                        }
                        return interferenceSamples;
                }

	std::vector<double> SignalGenerator::genNoise(int numOfSamples){
                        // init array and noise random gen
			std::mt19937 generator(42);
			std::uniform_real_distribution<double> dist(-0.2, 0.2);
                        std::vector<double> noiseSamples(numOfSamples, 0);
                        // from time 0 to 1024 calc a sample and insert back into array
                        for(int i = 0; i < numOfSamples; i++){
				noiseSamples[i] = dist(generator);
                        }
                        return noiseSamples;
                }

	std::vector<double> SignalGenerator::combineSignals(const std::vector<double>& desired, const std::vector<double>& interference, const std::vector<double>& noise){
			// check if sizes match
                        if (desired.size() != interference.size() || interference.size() != noise.size()) {
    				throw std::invalid_argument("Signal vectors must have equal sizes");
			}

			// init array
                        std::size_t size = desired.size();
                        std::vector<double> combinedSamples(size, 0);

			// from time 0 to 1024 combine signals
                        for(size_t i = 0; i < size; i++){
                        	combinedSamples[i] = desired[i] + interference[i] + noise[i];
                        }
                        return combinedSamples;
                }

	std::vector<double> SignalGenerator::filterSignals(const std::vector<double>& combined, int windowSize){
		std::vector<double> filtered;
		// shortcuts before averaging arrays
		if(windowSize > 0 && combined.size() > 0 && windowSize <= combined.size()){
			// loop stops when final valid index with required neighbors exist
			for(int i = 0; i < combined.size() - windowSize + 1; i++){
				double avg = 0.0;
				// split into groups and average into filtered
				for(int j = i; j < windowSize + i; j++){
					avg += combined[j];
				}
				filtered.push_back(avg/windowSize);
			}
			return filtered;
		}
		else
			throw std::invalid_argument("Invalid window size or input signal");
	}

	std::vector<std::complex<double>> SignalGenerator::performDft(const std::vector<double>& target, int numOfSamples, int sampleRate){
		std::vector<std::complex<double>> dft;
		const double pi = std::acos(-1.0);
		// iterate freq bins
		for(int i = 0; i < numOfSamples; i++){
			std::complex<double> sum = 0.0;
			for(int j = 0; j < numOfSamples; j++){
				double angle = (2 * pi * i * j) / numOfSamples;
				std::complex<double> exp = std::exp(std::complex<double>(0, -angle));
				sum  += target[j]*exp;
			}
		dft.push_back(sum);
		}
	return dft;
	}

	void SignalGenerator::genSignalFile(const std::vector<double>& ogSignal, const std::vector<double>& filtered, int numOfSamples, int sampleRate, int windowSize){
		if (ogSignal.empty() || filtered.empty() || windowSize <= 0 || windowSize > ogSignal.size() || filtered.size() != ogSignal.size() - windowSize + 1 
			|| numOfSamples != ogSignal.size() || sampleRate <= 0) {
    				throw std::invalid_argument("Invalid signal data or parameters");
		}

		std::ofstream signalFile("signal.csv");

		if (!signalFile.is_open()) {
    			throw std::runtime_error("Could not open signal.csv");
		}

		signalFile << "Time,Original Signal,Filtered Signal\n";

		for(int i = 0; i < filtered.size(); i++){
			double time = static_cast<double>(i + windowSize - 1) / sampleRate;
			signalFile << time << "," << ogSignal[i + windowSize -1] << "," << filtered[i] << "\n";
		}
		signalFile.close();

		std::ofstream spectrumFile("spectrum.csv");

		if (!spectrumFile.is_open()) {
                        throw std::runtime_error("Could not open spectrum.csv");
                }

		spectrumFile << "Frequency,Original Magnitude,Filtered Magnitude\n";
		
		// note: filtered size is different than og because of windowSize
		std::vector<std::complex<double>> ogDft = performDft(ogSignal, numOfSamples, sampleRate);
		std::vector<std::complex<double>> filteredDft = performDft(filtered, filtered.size(), sampleRate);

        	// Only export the positive-frequency half of the spectrum
        	for (int i = 0; i <= ogDft.size() / 2; i++) {
            		double freq = (static_cast<double>(i) * sampleRate) / ogDft.size();

            		double magnitudeOg = std::abs(ogDft[i]);

            		// Find the corresponding position in the filtered DFT
            		double position = freq * filteredDft.size() / sampleRate;

            		int lower = static_cast<int>(position);
            		int upper = lower + 1;

            		double fraction = position - lower;

            		// Get magnitudes of neighboring filtered bins
            		double y1 = std::abs(filteredDft[lower]);
            		double y2 = std::abs(filteredDft[upper]);

            		// Linear interpolation
            		double magnitudeFiltered = y1 + fraction * (y2 - y1);

            		spectrumFile << freq << "," << magnitudeOg << "," << magnitudeFiltered << "\n";
        	}
		spectrumFile.close();
    	}
