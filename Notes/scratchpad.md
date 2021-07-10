# FCS Simulation

# Introduction

## FCS Technique

The fluorescence signal received by the detector depends on multiple factors. The list is below:

1. $p$ → polarization of light
2. xxx

Fluorescence is sensitive to environmental conditions which affect the emission of photons by the fluorophores. Thus FCS is a sensitive technique that can be used to measure:

+ changes in nan environment
  + viscosity, pH, solvation
+ size and shape of molecules
+ molecular interactions

## FCS Setup

## FCS Schematics





### Non-equilibrium Statistics

The non-equilibrium state of the system under observation can be redefined as a state that is reached by giving a small perturbation to the system in an equilibrium state. Hence, the dynamics can then be stated for a system that is returning to equilibrium. Further, the *Onsager Regression Hypothesis* can be used to extract macroscopic information about the system by using the fluctuations about the mean.

>A useful fluorescent molecule typically emits $ \geq 10^5$ photons in water  before  photobleaching,  and  at  rates  up  to $ \approx 10^9$ per second. [taken ditto - Maiti et al.]
>
>Modern photon detectors, laser excitation, and high numerical aperture  microscopy  optics  allow  collection  of $3\%$ of the emitted fluorescence photons.
>
>Recognition  and identification  of  the  individual  target  molecules  above  the background fluorescence of the matrix is readily accomplished in  appropriate  liquid  solvents.  Even  in  the  intrinsically  fluorescent  environment  of  the  living  biological  cell  surface, individual  macromolecules  labeled  with  bright  fluorophores can be detected, located to a few nanometers, and tracked as they move (10, 11).
>
>

The measurement of correlation functions of physical and biological systems is a common practice. For systems with entities in the *micrometer range*, optical microscopy is commonly used to measure these functions. For smaller entities, x-ray and neutron diffraction are commonly used.

Fluorescence Correlation Spectroscopy measures the fluorescence photon intensity count coming from a small open volume inside a reservoir. It is used to measure directly the average number of particles in the observation volume, and the diffusion time of those particles. From these direct measurements, using specific models, the concentration of the particles and their sizes can be determined.

This can be illustrated by a probailistic calculation:

We assume a large volume $V_0$ in $N_0$ particles, which gives a number density — $\rho_N = V_0/N_0$. The large volume $V_0$ contains a small open volume $V$. The number of particles $(N)$ within $V$ keeps fluctuating, hence $N$ is a stochastic variable. We can express $N$ in terms of an indicator variable $X_{i}$. For all $N_0$ particles inside $V_0$, there is a corresponding $X_i$ such that:
$$
\begin{align}
X_i &= 0 \quad if \quad N_i \not\in V_0\\
X_i &= 1 \quad if \quad N_i \in V_0
\end{align}
$$
Hence, we can express $N$ (the number of particles inside open small volume $V$) as:
$$
N = \sum_{i = 1}^{N_0}X_{i}
$$
We can also reasonably state that :
$$
\begin{align}
P(X_i = 1) &= \frac{V}{V_0}\\
P(X_i = 0) &= \frac{V_0 - V}{V_0}
\end{align}
$$
These equations helps us in trivially deriving the mean and variance for our particle incidence in the small volume $V$.
$$
\begin{align}
\langle X_{i} \rangle &= 
1^2 \times \frac{V}{V_0} +
0^2 \times \frac{V_0 - V}{V_0} =
\frac{V}{V_0}\\


\langle X_{i}^{2} \rangle &= 
1^2 \times \Big(\frac{V}{V_0}\Big)^2 +
0^2 \times \Big(\frac{V_0 - V}{V_0}\Big)^2 =
\Big(\frac{V}{V_0}\Big)^2\\
\end{align}
$$
Based on these equations, we can clearly see : $var({X_i}) = 0$.

Using the mean and variance sum theorems$\ref{}$,
$$
\langle N \rangle = N_0 \times \langle X \rangle = \frac{N_0 V}{V_0}
$$


 The sensitivity of the experiment depends on the averages number of particles in the observation volume. Too many particles result in flattening of the signal, whereas for very low concentrations, the environment noise dominates the time series signal.

A generic FCS setups usually use nano-molar or sometimes pico-molar  concentrations. The observation volume is in the order of $~1 \space fL$ and < 100 particles are present within the observation volume.



The time  vs Intensity signal or time series is used to generate an Autocorrelation function, which can be used extract system phenomena based on various models that take it as an input.



>Maiti et al.
>$$
>detectivity(\phi_i):\\
>G(0) = \frac{\phi_{i}^2N_i} {\Big(\sum\phi_i N_i^2\Big)}
>$$















# Components

### Box

The simulation is done inside a class object called **Langevin Box**. The box contains the data fields and functions for the simulation.

→ The simulation uses Periodic Boundary Conditions (PBC) to mimic an infinite medium. Hence, the size of the box is only relevant when we calculate the number density of the particles. Because of the PBC, however, we also see the saturation of MSD value as the maximum displacement is restricted to the Edge of the cubic box. This saturation can be calculated  by:
$$
T_{saturation} = edge/(2 * dim * D)
$$
The particles are randomly initialized inside the boundaries of the box. The initial position is stored in order to calculate the displacements after every move, and ultimately the MSD value from those displacements.



### PSF

The PSF is described by the equation:
$$
\large
I = I_{•} e^{ \frac{-2x^{2}}{w_{x}^{2}}  \frac{-2y^{2}}{w_{y}^{2}}  \frac{-2z^{2}}{w_{z}^{2}} }
$$
 This equation describes a 3D gaussian which is symmetric along the x-y plane, but stretches along the z-axis, effectively forming an **ellipsoid**, which describes the Airy Disc if a plane is cut across the ellipsoid. The extension in *z* is described by a parameter called the **structure factor(sf)**. We say that:
$$
w_{z} = sf \times w_{x} = sf \times w_{y}
$$
Hence, the PSF can be describes by the above equation and two parameters: the radius and the structure factor(sf).

The contributions outside the Ellipsoid are small and can be ignored for optimization reasons. For a large set of particles, the optimization gives the following algorithm:

1. For each particle → detect if the particle is inside the ellipsoid. The following equation must be satisfied (Equation of ellipsoid)
   $$
   \large
   \frac{x^{2}}{w_{x}^2} + \frac{y^{2}}{w_{y}^2} + \frac{z^{2}}{w_{z}^2} \leq 1
   $$

2. For all particles, which are inside the Effective Volume → Calculate the probability of flashing.



### Laser

The Laser object is an object that describes a theoretical laser and a method Laser::prob() that gives the probabilistic contribution of the laser during photon emission. The laser object can operate in two modes:

1. Pulsing
2. Always-On

When the mode is set to "pulsing", the laser pulses with a set Period. The effect of the pulse, as there is a finite time of operation, depends on the Characteristic Decay Time of the laser which is set according to the need. The probability by the method  Laser::prob() is given by:
$$
p(laser; pulsing) = e^{-\frac{t_{now} - period}{char\_decay}}
$$


When the laser is set to "always-on":
$$
p(laser ; always-on) = 1
$$

### 







## Thermal Motion

The thermodynamic temperature is a measure of the average kinetic energy of the system. Thus the fluctuation is proportional to the temperature of the medium. Temperature is rather a quantity derived from the average fluctuation of the velocity of the particles. The temperature is assigned to the stationary value of this average.

The energy balance equation for the Langevin equation can be obtained by simply multiplying equation ($\ref{main_lang}$) by $v$ and applying the ensemble average operator:
$$
\frac{m}{2} \frac{d\langle v^{2} \rangle}{dt} + \gamma \langle v^{2} \rangle = \langle v F_\xi \rangle
$$
The first term is the average kinetic energy $K$, the evolution of this equation in time is given by: 
$$
\frac{dK}{dt} = \langle v F \rangle - 2 \gamma K \label{dKdt}
$$
The terms :

+ $\langle v F_\xi \rangle$ = average rate of work done by the random forces $F_\xi$.
+ $2 \gamma K$ = average rate of energy dissipation

Equation ($\ref{dKdt}$) can be further solved to obtain:
$$
K(t) = \frac{c_0}{4\gamma}(1 - e^{-2 \gamma t}) \label{K(t)}
$$
$c_0$ comes from equation ($\ref{gaussn_corr}$). The diagram below describes the steady state conditions. The work done by the random noise keeps the system moving, while the dissipative contribution tries to slow down the system and bring it to halt. Equilibrium refers to the condition when these two balance each other.

| !["Equilibrium Schematic (Source: Kerson Huang)"](C:\Users\Yatharth_Nitro\AppData\Roaming\Typora\typora-user-images\image-20210609171551619.png) |
| :----------------------------------------------------------: |
|         Equilibrium Schematic (Source: Kerson Huang)         |

For $t → \infin$, equation ($\ref{K(t)}$) becomes :
$$
K(t → \infin) = \frac{c_0}{4m \gamma} \label{kinf1}
$$
Over large times, the equipartition of energy also holds, hence:
$$
K(t → \infin) = \frac{1}{2} k_B T \label{kinf2}
$$
Equating these two equations, we get:
$$
c_0 = 2m \gamma k_{B} T \label{c_0T}
$$


Using equation ($\ref{c_0T}$) and $v = dx/dt$ in equation ($\ref{main_lang}$), we get:
$$
m \frac{d^2x}{dt^2} + m \gamma \frac{dx}{dt} = F_\xi
$$
We multiply both sides by $x$ and using the ensemble average operator:
$$
\biggl<{x\frac{d^{2}x}{dt^2}} \biggr> + \gamma \cdot\biggl<{x\frac{dx}{dt}} \biggr> = 0
$$
$\langle xF_\xi \rangle = 0$, solving further:
$$
\langle x^{2} \rangle = \frac{c_{0}t}{m^{2} \gamma^{2}}
$$
