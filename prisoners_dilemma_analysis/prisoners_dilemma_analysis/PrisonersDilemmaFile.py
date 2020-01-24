import h5py
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.family'] = 'Arial'
plt.rcParams['font.size'] = 12

class PrisonersDilemmaFile (h5py.File):

    def __init__(self, filePath, mode):
        h5py.File.__init__(self, filePath, mode)
        return
