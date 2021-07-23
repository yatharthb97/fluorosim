#!/usr/bin/env python3
# coding: utf-8


#Grammar
  #methods → all lowercase
  #function_name(*datas, *fn_attributes, param, fit)


#0 Imports
import sys
import os

import matplotlib.pyplot as plt
import numpy as np
import math

import json
import datetime

from plotlib import *


#1 Setup
plt.style.use('seaborn-darkgrid') #Set plot style


#Receive environemt from args
#ARG0 - Scriptname
parent_path = sys.argv[1] #ParentPath

# Set if the script is called independently or by C++ Simulator → "C++"
if len(sys.argv) > 2:
  operation_mode = sys.argv[2]
else:
  operation_mode = "Manual"


#Print Parent Path and Operation Mode
sys.stdout.write(f"• Parent Path: {parent_path} | Operation Mode: {operation_mode}");


#Open JSON config file
jsonname = os.path.join(parent_path, 'config.json')
with open(jsonname) as json_file:
    param = json.load(json_file)
#print(param)


#Add Local Parameters to the received parameter set
param['parent_path'] = parent_path;
param['bin_size'] = int(100) #For TimeSeries


#Misc Parameter Declarations
do_MSD_Fit = False
do_ACF_Fit = True
do_gauss_fit = True
draw_gauss_model= True

msd_log_scale = False
msd_fit_deg = 1
acf_fit_deg = 3

acf_lags = 256
psf_alpha = 0.15
tag_sample_size = 1000
#--- Setup is complete.


#2.0 Load stats file
statfilename = os.path.join(parent_path, 'stats.dat');

# if['stat_file_binary'] = False: TODO
t, msd, invol, flash = np.loadtxt(statfilename, delimiter = param['D_Sep'], unpack = True)

#fewquencies(flash)
#fewquencies(flash)

#PLOT(S) 1
#Plot Dual Time Series of whole arrays
plot_two_timeseries(invol, flash, "invol", "flash", "Count Plot", param)


#PLOT(S) 2
#plot_poisson_hist(data, bins, plot_title, param,  fit)
#plot_poisson_hist(flash, 10, "Flash Poisson", param, False)
#plot_poisson_hist(invol, 10, "InVol Poisson", param, False)


#PLOT(S) 3
#plot_msd(t, msd, log, fit=True)
plot_msd(t, msd, param, log=False, fit='plot')



TauD = param['Radius']*param['Radius'] / 4 * param['D']
print(f"[Trial] TauD: {TauD}")

                              
#Calculation of Array Sizes Average out flash bool values
tseries_size = np.size(flash)
binned_ts_size = int(tseries_size/param['bin_size'])
flash_sum = int(np.sum(flash))

# 4.2 Print Essential Statistics
stat_txt = f"""
• Length of Time Series: {tseries_size}
• Number of flashes(total): {flash_sum}
• Number of invols(total): {int(np.sum(invol))}
• Bin Size: {param['bin_size']}
• Length of Binned Time Series: {int(tseries_size/param['bin_size'])}"""
print(stat_txt)

#Time Series Binning
#bin_tseries(t_series, bin_size)
binned_ts = bin_tseries(flash, param['bin_size'])
binned_ts_mean = binned_ts.mean()
# Call Plot PCOUNTS
#plot_timeseries(time_series, plot_title, param)
plot_timeseries(binned_ts, f"Averaged Photon Count - Avg({param['bin_size']})", param)


if flash_sum == 0:
  print("• No flashes were observed. ACF cannot be calculated.")

else:

  #Calculation of ACF
  acf_y = sm.tsa.acf(binned_ts, nlags=acf_lags, fft=False, adjusted=True) #default → bartlett_confint=True
  
  acf_x = np.arange(acf_lags+1)


  print(f"• Mean of flashes (data) →  {flash.mean()}")
  print(f"• Mean of flashes (model - 3D gaussian diffusion) →  {1/acf_y[0]}")

  print(f"• Molecular Brightness →  {binned_ts.mean()/(param['bin_size']*param['Part_no'])}")
  print("(The molecular brightness is the average number of detected photons per sampling time per molecule.)") #TODO Remove

  #The molecular brightness is the average number of detected photons per sampling time per molecule.


  # Call ACF Plot Function
  #plot_acf(acf_x, acf_y, param, polyfit = False, gauss_fit = True, draw_model=True)
  plot_acf(acf_x, acf_y, param, polyfit = acf_fit_deg, gauss_fit = True, draw_model=True)



if param['do_pos_plots'] == True: #Pos Plot Animation Function
  pos_plot_animation(param,save_vid=False, psf_alpha=psf_alpha, draw_psf=True)

else:
  print(f"-> Positon Plots are disabled.")



# PARTICLE TAGGING
if param['Particle Tagging']:
  plot_taggedpart(tag_sample_size, param)



#RANDOM SAMPLING
if param['Rnd Sampling']:
  plot_rndsample_hist(100, param)


#8.0 Print Exit Message
now = datetime.datetime.now()
dt_str = now.strftime("%d-%m-%Y %H:%M:%S")
print(f"Script exited successfully: {dt_str}")