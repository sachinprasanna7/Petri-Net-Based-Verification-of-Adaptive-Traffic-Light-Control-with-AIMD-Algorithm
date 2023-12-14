# AIMD Algorithm Simulator

## Overview

This program models the Additive Increase Multiplicative Decrease (AIMD) algorithm to simulate traffic signal control. The variables `lvl` and `plvl` can have values 1, 2, or 3, representing signal levels. The new levels are randomly chosen using the `random` function. The variables `lvl` and `plvl` store the new level and the previous level. The variable `t` represents the amount of time the signal will be green. The variable `temp` is used for internal calculations within the algorithm to determine how much the value of `t` should increase (Additive Increase). The values of `t` are stored in the set `TVals` and are later printed to ensure that all expected values of `t` are reached.

## AIMD Algorithm

```cpp
t <- 0.5
temp <- 0
plvl <- 0
lvl <- 1
Initialize empty set TVals

for num in (0, 80):
    if lvl = 1 then:
        if plvl = lvl then:
            temp <- 0
            t <- 0.5
        else:
            temp <- 0.125
    else if lvl = 2 then:
        temp <- 1/8
        if t + temp > 1 then:
            if plvl = lvl then:
                t <- 1
                temp <- 0
            else:
                t <- 0.5
    else if lvl = 3:
        temp <- 0.25
        if t + temp > 1 then:
            if plvl = lvl then:
                t <- 1
                temp <- 0
            else:
                t <- 0.5
    print lvl, plvl, t, temp, MIN(t + temp, 1)
    plvl <- lvl
    lvl <- random integer between 1 and 3
    Insert t in TVals
    t <- t + temp

for val in TVals:
    print val
```

### Usage

1. **Copy Code:** Copy the source code.

2. **Compile the Program:**
    ```bash
    g++ -o aimd_simulator aimd_simulator.cpp
    ```

3. **Run the Executable:**
    ```bash
    ../aimd_simulator
    ```

The program randomly generates 80 new values of lvl to test the working of the AIMD algorithm. The algorithm performs as expected.

