# Literature Review of FCS

## Abstract

......

## List of Top Studies

...

## Reference Books

...



## Introduction



 

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

