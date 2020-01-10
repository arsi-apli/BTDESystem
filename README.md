# BTDESystem
Bowden to Direct Extruder Multi Material System

https://www.thingiverse.com/thing:4088571

The project aims to create a multi-material support for a direct extruder using bowden extruders.
It is primarily developed for the JGAURORA A5 printer fitted with the JG TITAN MKII V2 direct extruder.
But the system can be used for any direct extruder and with any bowden extruder in series. 
The goal is to maintain reasonable price and simplicity.

If two extruders are connected in series, there is a problem with their synchronization.
In fact, their perfect synchronization is not possible. And there will always be tensions on the filament.
Therefore, the main element of this project is a simple compensator that eliminates synchronization problems.
In print mode, the Bowden Extruder motors will be bang-bang controlled. When one of the two limit switches is reached,
it retracts / pushes 1.5cm of filament. In the filament exchange mode, the limit switches will be used to detect 
the introduction of the filament into the direct extruder.

First run of Extruder Compensator: https://youtu.be/dqPSfk-N7gQ

Many people are currently moving to a 32-bit board, and the plan is to use the old unnecessary board to control this system.
Initially, the SKR GEN L board will be used in this project. 
For communication with Marlin FW will be used emulation of MMU2 protocol.
