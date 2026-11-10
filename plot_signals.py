import pandas as pd
import matplotlib.pyplot as plt

# Read CSV files
signal_data = pd.read_csv("signal.csv")
spectrum_data = pd.read_csv("spectrum.csv")

plt.figure(figsize=(12, 5))

plt.plot(signal_data["Time"], signal_data["Original Signal"], label="Original Signal")
plt.plot(signal_data["Time"], signal_data["Filtered Signal"], label="Filtered Signal")

plt.title("Original vs Filtered Signal")
plt.xlabel("Time (seconds)")
plt.ylabel("Amplitude")
plt.legend()
plt.grid(True)

plt.tight_layout()

plt.savefig("plots2.png");
plt.show()

plt.figure(figsize=(12, 5))

plt.plot(spectrum_data["Frequency"], spectrum_data["Original Magnitude"], label="Original Spectrum")
plt.plot(spectrum_data["Frequency"], spectrum_data["Filtered Magnitude"], label="Filtered Spectrum")

plt.title("Original vs Filtered Frequency Spectrum")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.legend()
plt.grid(True)

plt.tight_layout()

plt.savefig("plots.png");
plt.show()
