# Petri Net-Based Verification of Adaptive Traffic Light Control with AIMD Algorithm

## Overview

This repository contains the code written in the research paper titled "Petri Net-Based Verification of Adaptive Traffic Light Control with AIMD Algorithm." This repository also contains high definition pictures of the Petri Net and the Reachability Graph which could not be shown properly in the paper due to space constraints. It also contains the hash table which maps each marking to its integer equivalent as specified in the paper.

For those interested in running the code to observe the results firsthand, detailed instructions can be found in the 'Usage' section below.


## Abstract

The paper analyses the performance of the petri
net model created to simulate a traffic control system using the
Additive Increase Multiplicative Decrease (AIMD) algorithm. The
petri net model was designed using TimeNET tool. The model
was evaluated by analysing the Reachability Graph generated by
a Depth First Search (DFS) and Backtracking based algorithm.
Several criteria such as Stability, Boundedness, Deadlock, etc.
were verified by our proposed algorithm. The model was then
validated through a C++ code to ensure it performs correctly
under different situations.

## Table of Contents

1. [AIMD Algorithm](#aimd-algorithm)
2. [Petri Net Model](#petri-net-model)
3. [Reachability Graph](#reachability-graph)
6. [Marking Table](#marking-table)
7. [Conclusion](#conclusion)
8. [Usage](#usage)

## AIMD Algorithm

The Adaptive Increase Multiplicative Decrease (AIMD) algorithm is employed in this research as an adaptive traffic control mechanism as proposed by . The algorithm operates as follows:

1. **Cycle Length Adjustment:** The cycle length (T) dynamically adjusts based on the congestion level experienced by the intersection.

2. **No Congestion (Level-1):** When there is no congestion (Level-1), the algorithm suggests setting the cycle length to Tmax/2.

3. **Congestion Worsens (Level-2 or Worse):** As congestion worsens (Level-2 or worse), the cycle time increases by adding a value called "Temp" based on the congestion level. The value of "Temp" varies for different congestion levels (Tmax/8 for Level-2, Tmax/8 for Level-3, and Tmax/2 for Level-1).

4. **Additive Increase:** If congestion continues to increase, the algorithm keeps adding "Temp" to the cycle length until it reaches Tmax, representing an 'additive increase' in cycle time.

5. **Multiplicative Decrease:** When congestion decreases, a 'multiplicative decrease' occurs, and the cycle length is set to Tmax/2. It is then adjusted by "Temp" based on the congestion level.

6. **Iterative Monitoring:** This iterative process continually monitors and adjusts the cycle time based on congestion conditions.

For a visual representation of the algorithm, refer to the flowchart in the figure below. It can also be found in the folder `Paper` and opening the `flowchart.jpeg`

![AIMD Algorithm Flowchart](Paper/flowchart.jpeg)


## Petri Net Model

The Petri-net model as described in the paper is attached below. It can also be found in the folder `Paper` and opening the `petrinet.pdf`. The XML code can be found in `petrinet.xml`

![Petri-Net Model](Paper/petrinet.pdf)


## Reachability Graph

The Reachability Graph associated with the Petri-Net is attached below.  It can also be found in the folder `Paper` and opening the `reachabilitygraph.png`. 

![Reachability Graph](Paper/reachabilitygraph.png)

Please be aware that when executing the code and examining the results, the mapping between markings and their integer equivalents is randomly generated by the code. Consequently, this mapping may vary each time the code is run. However, it is important to note that the underlying graph structure will remain consistent across different runs since the reachability graph is the same for the initial marking given.


## Usage

Before running the code, ensure that you have the following prerequisites installed:

### C++ Compiler

If you don't have a C++ compiler installed, you can follow these instructions to install one:

- **Linux:** Most Linux distributions come with a C++ compiler by default. You can install it using your package manager. For example, on Ubuntu, you can use:

  ```bash
  sudo apt-get update
  sudo apt-get install g++
  ```

- **MacOS:** You can install Xcode, which includes the Clang C++ compiler. Get Xcode from the App Store or visit the [Apple Developer website](https://developer.apple.com/xcode/).

- **Windows:** For Windows, you can use MinGW (Minimalist GNU for Windows) or Visual Studio. Install MinGW using a tool like [MSYS2](https://www.msys2.org/), and download Visual Studio from the [official website](https://visualstudio.microsoft.com/visual-cpp-build-tools/).

### Python Compiler

Ensure you have Python installed on your system. Download Python from the [official Python website](https://www.python.org/).

### Required Python Libraries

You'll need the `networkx` and `matplotlib` libraries for running the Python code. Install them using the following commands:

```bash
pip install networkx
pip install matplotlib

```

Once you have the prerequisites installed, you can proceed to by following the steps given below:

1. Clone the Repository

Clone the repository to your local machine by using the following command on Command Prompt:

```bash
git clone https://github.com/sachinprasanna7/Petri-Net-Based-Verification-of-Adaptive-Traffic-Light-Control-with-AIMD-Algorithm.git
```

2. Navigate to the Project Directory

Navigate to the place where you cloned the repository. Use the following command on Command Prompt to do so:

```bash
cd your-repository
```

where `your-repository` is the absolute path to where the repository is stored in your local machine.

3. Run the Batch executable

Type the following command in on Command Prompt to observe all the results in one go:

```bash
run_program.sh
```






