import pytest
import matplotlib.pyplot as plt
import numpy as np
from prisoners_dilemma_analysis import *

dataPath = './test/data/'

@pytest.fixture(scope="module")
def pdFile():
    filePath = dataPath + 'all_strategies.prisonersdilemma'
    return PrisonersDilemmaFile(filePath, 'r')

def test_basic_test(pdFile):
    assert 3 == 3
    return
