#!/usr/bin/python
# coding: utf8

import pylab
import numpy as np
import scipy as sp
import matplotlib 
import matplotlib.pyplot as plt
from scipy.optimize import fsolve

from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)

######refresh
import matplotlib.font_manager
from matplotlib import rc
import matplotlib.font_manager as font_manager 
font_manager._rebuild() 

rc('axes', linewidth=2)
matplotlib.rcParams["legend.frameon"] = False
# Say, "the default sans-serif font is COMIC SANS"
matplotlib.rcParams['font.sans-serif'] = "Arial"
# Then, "ALWAYS use sans-serif fonts"
matplotlib.rcParams['font.family'] = "sans-serif"

########################
##########  ПАРАМЕТРЫ ##############

# число строк под заголовок в dat
num_rows_title=1  
# выходной рисунок:
out_name="histogram.png"
# входные файлы
filename="histogram_2d.dat"
#########################################


# настраиваем детали отрисовки графиков
plt.title(" ") 
plt.xlabel(r"$x$", size=36)
plt.ylabel(r"$y$", size=36)
##########

data = np.loadtxt(filename, skiprows=0)

ax1= plt.axes()
plt.imshow(data)
plt.colorbar()

ax1.tick_params(axis="x", labelsize=24, width=2, length=8)
ax1.tick_params(axis="y", labelsize=24, width=2, length=8)
plt.locator_params(nbins=4)

plt.subplots_adjust(bottom=0.22) # use a lower number to make more vertical space 
plt.subplots_adjust(left=0.22) # use a lower number to make more vertical space

legend = []

#plt.legend(legend, loc="best", fontsize=20.5)
plt.savefig(out_name, dpi=300)
