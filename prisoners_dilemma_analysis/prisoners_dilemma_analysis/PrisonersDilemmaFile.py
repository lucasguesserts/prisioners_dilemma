import os
import h5py
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.family'] = 'Arial'
plt.rcParams['font.size'] = 12

class PrisonersDilemmaFile:

    def __init__(self, filePath, championshipName):
        # HDF5 File
        self.filePath = filePath
        self.file = h5py.File(filePath, 'r')
        # Championship
        self.championshipName = championshipName
        self.championship = self.file[championshipName]
        self.numberOfTurns = self.championship.attrs['numberOfTurns']
        # Players
        self.playerNames = self.__getPlayerNames()
        return

    def playerPlot(self, playerName):
        fig, ax = self.__createBasicPlayerPlot(playerName)
        self.__plotScorePlayerPlot(playerName, ax)
        self.__savePlayerPlot(playerName, fig)
        return

    def allPlayersPlot(self):
        for playerName in self.playerNames:
            self.playerPlot(playerName)
        return

    def __getPlayerNames(self):
        return list(self.championship.keys())

    def __createBasicPlayerPlot(self, playerName):
        figSize = (10, 5)
        fig, ax = plt.subplots(figsize=figSize)
        ax.set_title((playerName + '\n' + "Championship " + self.championshipName).title())
        ax.set_ylabel('Score')
        ax.set_xlabel('Strategy')
        yMax = 3*self.numberOfTurns*1.1
        ax.set_ylim([0, yMax])
        xMax = 1.15*len(self.__getPartners(playerName))
        ax.set_xlim([-0.3, xMax])
        ax.grid(which='major', color='gray', linestyle='-', linewidth=1, alpha=0.5, axis='y')
        hlines = {'linestyle':'--', 'color':'black'}
        score_and_labels = {3:'suckers', 2:'punishment', 1:'reward', 0:'temptation'}
        for score, label in score_and_labels.items():
            plt.text(y=score*self.numberOfTurns+0.01*yMax, x=len(self.__getPartners(playerName)), s=label)
            plt.axhline(y=score*self.numberOfTurns, **hlines)
        return fig, ax

    def __plotScorePlayerPlot(self, playerName, ax):
        for index, partnerName in enumerate(self.__getPartners(playerName)):
            payoff = np.sum(self.championship[playerName][partnerName]['payoff'])
            ax.bar(index, payoff)
 
    def __getPartners(self, playerName):
        partnerNames = list(self.championship[playerName].keys())
        partnerNames.remove('strategy')
        return partnerNames

    def __savePlayerPlot(self, playerName, fig):
        fig.tight_layout()
        folder = '{:s}_figures/'.format(self.championshipName).lower().replace(' ','_')
        os.makedirs(folder, exist_ok=True)
        figurePath = folder + '{:s}_{:s}.png'.format(playerName, self.championshipName).lower().replace(' ','_')
        plt.savefig(figurePath)
        plt.close(fig)
        return
