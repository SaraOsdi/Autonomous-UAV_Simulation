# Autonomous Fixed-Wing UAV Simulation

A robust C++ simulation engine designed to model and control multiple fixed-wing Unmanned Aerial Vehicles (UAVs) with realistic kinematic constraints, such as a minimum turning radius, waypoint navigation, and autonomous hovering behaviors.

---

## 🚀 Key Features

- **Kinematic Modeling:** Simulates fixed-wing aircraft behavior, handling speed constraints, dynamic azimuth adjustments, and smooth circular turning paths.
- **Multi-UAV Management:** Coordinates multiple independent UAVs simultaneously within a unified simulation loop.
- **Command Parsing:** Dynamically loads simulation parameters (`SimParams.ini`) and time-stamped target commands, executing them precisely at specified intervals.
- **Automated Logging:** Exports telemetry data (time, coordinates, and real-time azimuth headings) into separate tracking files for each UAV (e.g., `UAV0.txt`, `UAV1.txt`).

---

## 🛠️ Project Architecture

The project is structured into modular components:

- **`UAV` Class (`UAV.h`, `UAV.cpp`):** Models individual UAV dynamics, including position tracking $(x, y, z)$, velocity vectors, heading calculations, target alignment algorithms, and waypoint hovering mechanics.
- **`Simulation` Class (`Simulation.h`, `Simulation.cpp`):** Handles environment initialization, configuration parsing, command scheduling, time-step stepping ($dt$), and output file stream management.
- **`Command` Structure (`Command.h`):** Defines time-stamped instructions for target updates.
- **`main.cpp`:** Entry point of the application.

---

## ⚙️ Configuration Files

### `SimParams.ini`
The simulation parameters file defines the global environment and initial UAV states in the following order:
1. Time step (`dt`)
2. Number of UAVs
3. Turning/Hovering radius
4. Initial position ($x_0, y_0, z_0$)
5. Initial speed
6. Initial azimuth (degrees)
7. Time limit

---

## 📊 Sample Trajectory Output

Visualized trajectories showcasing smooth turning radii and target tracking:

<p align="center">
  <img src="path_to_your_image.png" alt="UAV Trajectory Graph" width="600"/>
</p>

---

## 📦 Getting Started

### Prerequisites
- A C++ compiler supporting C++11 or later (MSVC, GCC, or Clang).
- Visual Studio (recommended for `.vcxproj` projects).

### Building and Running
1. Clone the repository:
   ```bash
   git clone [https://github.com/your-username/Autonomous-UAV-Simulation.git](https://github.com/your-username/Autonomous-UAV-Simulation.git)
