import h5py
import numpy as np
import matplotlib.pyplot as plt

#plt.rcParams['font.family'] = 'Arial'
#plt.rcParams['font.size'] = 12

# Getting data

## Open file
filePath = './test/data/all_strategies.prisonersdilemma'
mode = 'r' # read only
file = h5py.File(filePath, mode)
championshipName = 'Save Championship - Basic'
championship = file[championshipName]

## Competition rules
numberOfTurns = championship.attrs['numberOfTurns']

## Select one player
playerName = 'Tit For Tat'
player = championship[playerName]

## Get partners
partners = dict(player.items())
del partners['strategy']
#for key, val in partners.items():
#    print('{:30s} : {} : {}'.format(key, val, partners[key][key]['strategy'].attrs['shortName']))

# Base plot
figSize = (10, 5)
plt.figure(figsize=figSize)
plt.title(championshipName + '\n' + playerName)
plt.ylabel('Score')
plt.xlabel('Strategies')
plt.ylim([0, 3*numberOfTurns*1.1])
xMax = len(partners) + 1
plt.xlim([-0.3, xMax])
plt.grid(which='major', color='gray', linestyle='-', linewidth=1, alpha=0.5, axis='y')

## reference lines
hlines = {'linestyle':'--', 'color':'black'}
score_and_labels = {3:'suckers', 2:'punishment', 1:'reward', 0:'temptation'}
for score, label in score_and_labels.items():
    plt.text(y=score*numberOfTurns+0.2, x=xMax-0.48, s=label)
    plt.axhline(y=score*numberOfTurns, **hlines)

## x ticks
xtickLabels = [partners[name][name]['strategy'].attrs['shortName'] for name in partners.keys()]
plt.xticks(
    ticks = np.arange(len(partners)),
    labels = xtickLabels,
    rotation = 'vertical',
)

## Scores
for index, partnerName in enumerate(partners):
    payoff = np.sum(partners[partnerName]['payoff'])
    plt.bar(index, payoff)

## Save figure
plt.tight_layout()
figurePath = './plot.png'
plt.savefig(figurePath)
