#include <gtest/gtest.h>
#include "signal_generator.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

TEST(SignalGeneratorTest, GeneratesCorrectNumberOfSamples) {
    SignalGenerator generator;

    std::vector<double> signal = generator.genSignal(1024, 1024, 32);

    EXPECT_EQ(signal.size(), 1024);
}

TEST(GenInterferenceTest, GeneratesCorrectNumberOfSamples) {
    SignalGenerator generator;

    std::vector<double> signal = generator.genInterference(1024, 1024, 192);

    EXPECT_EQ(signal.size(), 1024);
}

TEST(GenNoiseTest, GeneratesCorrectNumberOfSamples) {
    SignalGenerator generator;

    std::vector<double> signal = generator.genNoise(1024);

    EXPECT_EQ(signal.size(), 1024);
}

TEST(CombineSignalsTest, GeneratesCorrectNumberOfSamples) {
    SignalGenerator generator;

    std::vector<double> desired = generator.genSignal(1024, 1024, 32);
    std::vector<double> interference = generator.genInterference(1024, 1024, 192);
    std::vector<double> noise = generator.genNoise(1024);
    std::vector<double> noiseFail = generator.genNoise(1025);

    std::vector<double> signal = generator.combineSignals(desired, interference, noise);

    EXPECT_EQ(signal.size(), 1024);

    EXPECT_THROW(generator.combineSignals(desired, interference, noiseFail), std::invalid_argument);
}

TEST(FilterTest, CalculatesAverage) {

    SignalGenerator generator;

    std::vector<double> input = {2, 4, 6, 8, 10};

    auto filtered = generator.filterSignals(input, 5);

    EXPECT_EQ(filtered.size(), 1);
    EXPECT_DOUBLE_EQ(filtered[0], 6.0);

    EXPECT_THROW(generator.filterSignals(input, 6), std::invalid_argument);
    EXPECT_THROW(generator.filterSignals(input, 0), std::invalid_argument);
}

TEST(GenSignalFileTest, CreatesCorrectCSVFile) {
    SignalGenerator generator;

    std::vector<double> original = {1.0, 2.0, 3.0};
    std::vector<double> filtered = {1.5, 2.5};

    generator.genSignalFile(original, filtered, 3, 1024, 2);

    std::ifstream file("signal.csv");

    ASSERT_TRUE(file.is_open());

    std::string header;
    std::getline(file, header);

    EXPECT_EQ(header, "Time,Original Signal,Filtered Signal");
}
