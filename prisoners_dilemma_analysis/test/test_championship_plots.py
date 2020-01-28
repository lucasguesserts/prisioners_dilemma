import pytest
import os
import matplotlib.pyplot as plt
import numpy as np
from prisoners_dilemma_analysis import *

dataPath = './test/data/'

@pytest.fixture(scope="module")
def pdFile():
    filePath = dataPath + 'all_strategies.prisonersdilemma'
    return PrisonersDilemmaFile(filePath, 'All strategies')

def test_PlayerPlot(pdFile):
    pdFile.allPlayersPlot()
    folder = 'all_strategies_figures/'
    for playerName in pdFile.playerNames:
        figurePath = folder + '{:s}_all_strategies.png'.format(playerName).lower().replace(' ','_')
        assert os.path.isfile(figurePath)
        os.remove(figurePath)
    os.rmdir(folder)
    return
