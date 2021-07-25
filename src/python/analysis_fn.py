









def bin_tseries(t_series, bin_size, normalise = False):
  ''' For a given time series, this function adds `bin_size` number of consequitive points. Includes an option to normalise the given time-series.''' 
  
  binned_ts = np.copy(t_series) #Make a Copy
  binned_ts = np.reshape(binned_ts, newshape=(int(np.size(t_series)/bin_size), bin_size))
  binned_ts = np.sum(binned_ts, axis=1) #Sum along the row
  
  if normalise:
    binned_ts = np.divide(binned_ts, bin_size)

  return binned_ts



def plot_two_timeseries(data1, data2, label1, label2, plot_title, param):
  
  fig, ax = plt.subplots()
  tx = np.arange(max(np.size(data1), np.size(data2)))
  
  ax.set_title(plot_title)
  ax.plot(tx, data1, '-', label = label1)
  ax.plot(tx, data2, '-', label = label2)
  
  
  y_max = max(data1.max(), data2.max())


  plt.legend()
  ax.set_yticks(np.arange(0, y_max))
  ax.set_xlabel('time →')
  ax.set_ylabel('Count →')
  
  #3.4 Save Plot
  figname = os.path.join(param['parent_path'], f'{plot_title}.png')
  plt.savefig(figname)

  # 3.5 Open Live Plot
  if param['show_py_plots'] == True:
    plt.show()