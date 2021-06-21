+ [ ] ACF
+ [ ] Detectivity
+ [ ] Pin Hole
+ [ ] Density Fluctuations
+ [ ] Brightness
+ [ ] PSF (With different shapes)
+ [ ] Diffusivity
+ [ ] Averaging Intervals
+ [ ] Simulation Clock and different timescales

## ACF

Measurement of physical phenomena of complex systems can be done by measuring an order parameter across the system (its various components), in space and time. The degree of order amongst the constituents of the systems can be defined statistically by correlation functions.
$$
C(r, \tau) = \langle s_1 (R,t) \cdot s_2 (R + r,t + \tau) \rangle
$$
Here, $s_1$ and $s_2$ are two different stochastic variables. Setting $r = 0$ yields the *equal-space* or *time correlation function* and similarly, setting $\tau = 0$ yields the *equal-time* or *space correlation function*.

If $s_1 = s_2$, then the correlation function is called an *autocorrelation function*, opposed to the other condition, where the function is a *cross-correlation function*.

The correlation function can be also seen as a parameter describing memory in a system. We specially consider the *time-autocorrelation function (ACF)*:
$$
G(\tau) = \langle s (t) \cdot s (t + \tau) \rangle
$$


We usually use a normalized form of the ACF, and consider the fluctuation of $F$ — $\delta F$, rather than $F$:
$$
G(\tau) = \frac{\langle \delta F (t) \cdot \delta F(t + \tau) \rangle} {\langle \delta F (t)\rangle}
$$

$$
G(0)  = G(\tau) = \frac{\langle \delta F^2 (t) \rangle} {\langle \delta F (t)\rangle^2}
$$

For a dilute system$\ref{}$,
$$
G(0) = 1/\langle N \rangle
$$
Since, $\langle N \rangle$ is small, the relative fluctuations are large.



Correlation analysis yields strength and duration of the fluctuations.





The relation for a 3D gaussian profile ACF was given by Aragon and Pecora (1976):
$$
G(\tau) = G(0) \cdot \Big( 1 + \frac{4D \tau}{r^2} \Big)^{-1} 
\Big(1 + \frac{4D \tau}{z^{2}} \Big)^{-1/2}
+ G(\infin) \label{autocorr_gauss3D}
$$
Elson and Magde (1974) showed that, the autocorrelation functions for a square prism and a 3D gaussian are rather similar. This is because, the term containing $z$ in equation ($\ref{autocorr_gauss3D}$) has a square root. $\ref{riglerFluorescenceCorrelationSpectroscopy1993}$

#### Deriving Various Parameters From ACF

+ Change in rates of diffusion can be measured qualitatively by observing the rightward shift of the ACF curve. Curves extended to the right (in the direction of increasing lag $k$), have lower diffusion rates.
+ Transit time $\tau_{D}$ is defined as the time taken on average for a molecule to move across the detection volume. It is represented on the ACF curve as the *characteristic decay time*, as at this point, the amplitude of the ACF is 50% of $G(0)$.

#### ACF Fitting

Any fitting equations must be checked for residuals. If the residuals are randomly distributed along the origin, then the fit is a good fit. Fitting can be done using non-linear least-squares regression.$\ref{10.1021/jp055840k}$



## Time Scales

Vibrational rela1xation occurs on a timescale of $10^{-14} - 10^{-11}$ s, which is fast and thus extremely likely. Hence, it occurs immediately after absorbance. 



The energy emitted during florescence is lower than the incident energy because energy is lost in internal conversion after absorbance and also during vibrational relaxation. The lifetime of fluorescence is typically in the range of $10^{-9} - 10^{-7}$ s.



Photon count rate$\ref{10.1021/jp055840k}$ per molecule can be defined as : some kHz/molecule. $$\langle N \rangle = 1\\
T_{steps} = 10^{7}$$
$$
\begin{align}


\end{align}
$$
Specific brightness is also measured in kHz per molecule.

Rectangle volume: $$<C> = 1 \space particle/ \mu m^{3}$$. The volume of rectangle PSF : $1 \space \mu m * 1 \space \mu m * 3 \space \mu m$. Hence, $<N> \approx 3$ .

>  We found that trajectories run for times greater than 200 times the characteristic diffusion time gave results independent of run time. All simulations were run at 300 °K. The system was typically equilibrated by a run of 3 s, followed by a production run of 1 s. $\ref{dixFluorescenceCorrelationSpectroscopy2006}$

## PSF (With different shapes)



> "With properly chosen parameters of the optical system the 3-dimensional Gaussian distribution (1) describes the sample profile of the FCS experiment in an epifluorescence microscope with high accuracy. " $\ref{riglerFluorescenceCorrelationSpectroscopy1993}$

Number of particles per observation volume: $N_0 = \langle C \rangle V_{eff}$

Then, applying the Gaussian Model: $N_0 = \langle C \rangle \pi^{3/ 2}r^{2}z_{0} = \langle C \rangle \pi^{3/ 2}r^{3} \cdot {sf} $ 

The estimation of $r$ of the PSF can be obtained using the above equation:
$$
r = \sqrt[3]{\frac{N_0}{\pi^{3/2} \cdot sf \cdot \langle C \rangle}}
$$

+ [ ]  ***How is PSF different from circle of confusion, which is caused by the separation of objects being imaged from  as single focal point, and results in defocusing of convergent rays to a circle instead of a point?***

  2D model:
  $$
  G(\tau) = 1 + \frac{1}{N} \Big(1 + \frac{4D\tau}{w_0^{2}}\Big)^{-1}
  $$
  The radial component of diffusion:
  $$
  \tau_{diff} = \frac{w_0^{2}}{4D}
  $$
  



## Pin Hole

The pinhole projection $s_p = r_{pin}/M$ . $M$ is the magnification of the objective.
$$
\begin{align}
s_{max} &= \frac{0.5 \space tan\alpha}{tan \delta} w_{0}\\
s_{min} &= w_{0}
\end{align}
$$
$w_{0}$ is the waist of the laser beam. If $s_p > s_{max}$ and $s_p < s_{min}$, the 3D gaussian assumption for the intensity profile cannot be made.



The transmission function of the pinhole is defined as:
$$
T({\bf r}) = circ \Big(\frac{{\bf r}}{s_p} \Big) = circ(r^{'})
$$

$$
\begin{align}
circ(r^{'}) 
&= 1 \quad (r^{'} \leq 1)\\
&= 0 \quad (r^{'} > 1)

\end{align}
$$

The pin hole also defines the *Collection Efficiency Function* ($CEF({\bf r^{'}, z})$). 

> "The fraction of light emitted by a point source, that passes through the pinhole." $\ref{riglerFluorescenceCorrelationSpectroscopy1993}$

$$
CEF(r, z) = \frac{1}{\Delta} \int {T(r) \cdot PSF(r^{'}, r, z) \cdot dr}
$$



## Molecular Detection Efficiency

The Intensity profile $I(r, z)$ is given by the PSF and the $CEF(r, z)$ is given by the pinhole.



## Experimental Comparison

+ Performance of FCS Setup: Spatial Resolution
+ Performance of FCS Setup: S/N Ratio
