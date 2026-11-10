# Signal Processing Project

## Overview

This project is a C++17 signal-processing application that generates a synthetic signal, adds interference and random noise, applies a moving-average low-pass filter, and analyzes the frequency content using a Discrete Fourier Transform (DFT).

The application exports signal and frequency data to CSV files, which can then be visualized using Python.

## Features

- Generates a 32 Hz desired sine wave.
- Generates 192 Hz interference.
- Adds random noise using a fixed random seed.
- Combines the desired signal, interference, and noise.
- Applies a configurable moving-average low-pass filter.
- Performs a Discrete Fourier Transform (DFT).
- Exports signal and frequency data to CSV files.
- Includes unit tests using GoogleTest.
- Supports Python visualization using Pandas and Matplotlib.

## Requirements

- Linux
- C++17 compatible compiler (GCC or equivalent)
- CMake
- GoogleTest
- Python 3
- Pandas
- Matplotlib

### Installing dependencies (Ubuntu)

```bash
sudo apt update
sudo apt install build-essential cmake libgtest-dev python3 python3-pip
```

Install the Python libraries:

```bash
python3 -m pip install pandas matplotlib
```

## Project Structure

```text
signal-project/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── signal_generator.cpp
│   └── signal_generator.h
├── tests/
│   └── signal_generator_test.cpp
└── README.md
```

- `src/`: Contains the signal generation, filtering, DFT, and CSV export implementation.
- `tests/`: Contains GoogleTest unit tests.
- `CMakeLists.txt`: Defines the CMake build configuration.

## Building the Application

From the project root directory, configure the project:

```bash
cmake -S . -B build
```

Compile the application:

```bash
cmake --build build
```

## Running the Application

Run the compiled executable:

```bash
./build/signal-project
```

The application generates CSV files containing the original signal, filtered signal, and frequency analysis results.

## Running Unit Tests

Build the test executable:

```bash
cmake --build build
```

Run all registered tests:

```bash
cmake -E chdir build ctest --output-on-failure
```

The tests verify signal generation, interference generation, noise generation, signal combination, filtering, and CSV file generation.

## Python Visualization

The generated CSV files can be visualized using the Python plotting program.

Run the plotting script:

```bash
python3 YOUR_PLOTTING_SCRIPT.py
```

Replace `YOUR_PLOTTING_SCRIPT.py` with the actual name of your Python script.

The plots illustrate:

- The original signal and its frequency components.
- The filtered signal after applying the moving-average filter.
- The frequency spectrum before and after filtering.

## Expected Results

The application should demonstrate that:

1. The generated signal contains the desired 32 Hz component, 192 Hz interference, and random noise.
2. The moving-average filter attenuates higher-frequency interference.
3. The DFT identifies the expected frequency components.
4. The frequency spectrum shows a reduction in the magnitude of the interference after filtering.
5. The Python plots visually demonstrate the effects of filtering.

## Testing Status

All unit tests should pass when following the build and testing instructions above.
