#!/usr/bin/env python3
# coding: utf-8

# THIS FILE is a work in progress. It is currently unused.

import math
import numpy


#pars, cov = curve_fit(f=exponential, xdata=x_dummy, ydata=y_dummy, p0=[0, 0], bounds=(-np.inf, np.inf))

#Calculate the residuals
res = y_dummy - exponential(x_dummy, *pars)

# *pars — allows us to unroll the pars array, i.e. [a, b] gets inputted as a, b
#residuals must be close to zero and rndomly distributed along y = 0

#fitorder = 0 → autofit
def MSDfit(amsd, atime, diffcoeff, dim=3):
	#Set Scale
	scale = 2*dim*diffcoeff

	#Define Power Law Function
	def power_law(x, power):
		return scale*np.power(x, power)

	#Do curve fitting
	pars, cov = curve_fit(f=power_law, xdata=atime, ydata=amsd, 
						  p0=[0, 0], bounds=(-np.inf, np.inf))

	# Get the standard deviations of the parameters (square roots of the # diagonal of the covariance)
	stdevs = np.sqrt(np.diag(cov))

	# Calculate the residuals
	residuals = amsd - power_law(amsd, *pars) #*pars unrolls the array into individual parameters

	return pars, cov, stdevs, residuals


	def VeffVol(x,y,z):
		return 1.25992104989487316476721 * x * y * z

	def GetCharResTime(diffcoeff,x , y):
		return 0.25 * x * y / diffcoeff

	def NormalGaussDiffusion(diffcoeff, radius, sf):
		TauD = GetCharResTime(D, radius, radius)
		return 1 / (1 + (T/TauD))* np.sqrt(1 + (T/TauD)/(sf*sf))

	def GaussianFit(acf, time, diffcoeff, radius, sf):

		TauD = GetCharResTime(D, radius, radius)

		def FitFn():
			return 1 / (1 + (T/TauD))* np.sqrt(1 + (T/TauD)/(sf*sf))
		

		#Do curve fitting
		pars, cov = curve_fit(f=FitFn, xdata=time, ydata=acf, 
							  p0=[0, 0], bounds=(-np.inf, np.inf))

		# Get the standard deviations of the parameters (square roots of the # diagonal of the covariance)
		stdevs = np.sqrt(np.diag(cov))

		# Calculate the residuals
		residuals = amsd - power_law(amsd, *pars) #*pars unrolls the array into individual parameters

		return pars, cov, stdevs, residuals


		param = {}
		#Plot ACF
		def plot_acf(acf_x, acf_y, polyfit = 2, gauss_fit = True, draw_model=True)
		def plot_acf(acf_x, acf_y, polyfit = 0, gauss_fit = True, draw_model=True):
		  
		  #Init Resource
		  fig, ax = plt.subplots()

		  #Plot Data
		  ax.set_title('Autocorrelation Plot')
		  ax.plot(acf_x, acf_y, '-', label = 'data')
		  #plt.fill_between(acf_x, (acf_y - ci), (acf_y+ci), color='blue', alpha=0.1)
		  
		  #TauD Estimation
		  TauD = (param['veff_radius']**2) / (param['D'] * 6.0)
		  print(f"• TauD Calculated from model → {TauD}")
		  
		  sf_sq = param['veff_sf']**2

		  #Fit Functions
		  def FitFixedTau(T): #TODO → Fix the factor on the front
		      return 1 / ((1 + (T/TauD))* np.sqrt(1 + (T/TauD)/sf_sq))
		  
		  def FitGauss2FitFn(t, G0, TauInv):
		      return G0 / ((1 + (t*TauInv))* np.sqrt(1 + (t*TauInv)/sf_sq))

		  def FitGauss3FitFn(t, G0, TauInv, GInf):
		      return (G0 / ((1 + (t*TauInv))* np.sqrt(1 + (t*TauInv)/sf_sq))) + GInf


		  if draw_model:

		    x_model_factor = param['bin_size'] * param['dt'] * acf_y[0] #Why?
		    ax.plot(acf_x, FitFixedTau(acf_x * x_model_factor), '--r', label = 'model')
		    #Plotting wrt real time

		  if polyfit > 0:
		    #4.4 ACF Curve Fitting
		    acf_coef = np.polyfit(acf_x, acf_y, polyfit) #Fit polynomial of degree 1
		    acf_fit_fn = np.poly1d(acf_coef) 
		    print(f"\n• ACF Polynomial Fit → degree [{polyfit}]: \n{acf_fit_fn}") #Print ACF Fit Polynomial
		    ax.plot(acf_x, acf_fit_fn(acf_x), '--k', label = f'poly({polyfit}) fit')


		  if gauss_fit:
		    pars, cov = curve_fit(f=FitGaussFn, xdata=acf_x, ydata=acf_y, p0=[0, 0], bounds=(-np.inf, np.inf))
		    print(f"• TauD Calculated from curve-fitting → {1/pars[1]}")
		    print(f"• Fit Parameters: {pars}")
		    #print(f"• Fit Covariance: {cov}")
		    
		    print(f"• Scale factor Calculated from curve-fitting [G(0)] → {pars[0]}")
		    #b must be inverted to get TauD
		    ax.plot(acf_x, FitGaussFn(acf_x, *pars), '--g', label = 'gauss fit')


		  plt.legend()

		  ax.set_xscale('log')
		  ax.xaxis.set_major_locator(LogLocator(base=10.0)) #Set appropriate tics

		  ax.set_xlabel(r'$log_{10}(k)$ → $log_{10}(lag)$')
		  ax.set_ylabel(r'$G(k)$ → ACF')


		  # Save Plot
		  acffigname = os.path.join(param['parent_path'], 'acfplot.png')
		  plt.savefig(acffigname)

		  # Open Live Plot
		  if param['show_py_plots'] == True:
		    plt.show()
