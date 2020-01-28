import os
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
championshipName = 'All strategies'
championship = file[championshipName]

## Competition rules
numberOfTurns = championship.attrs['numberOfTurns']

## Select one player
players = dict(championship.items())
for playerName, player in players.items():
    print('Processing competitions with: {:s}'.format(playerName))

    ## Get partners
    partners = dict(player.items())
    del partners['strategy']
    #for key, val in partners.items():
    #    print('{:30s} : {} : {}'.format(key, val, partners[key][key]['strategy'].attrs['shortName']))

    # Base plot
    figSize = (10, 5)
    plt.figure(figsize=figSize)
    plt.title((playerName + '\n' + "Championship " + championshipName).title())
    plt.ylabel('Score')
    plt.xlabel('Strategies')
    yMax = 3*numberOfTurns*1.1
    plt.ylim([0, yMax])
    xMax = 1.1*len(partners)
    plt.xlim([-0.3, xMax])
    plt.grid(which='major', color='gray', linestyle='-', linewidth=1, alpha=0.5, axis='y')

    ## reference lines
    hlines = {'linestyle':'--', 'color':'black'}
    score_and_labels = {3:'suckers', 2:'punishment', 1:'reward', 0:'temptation'}
    for score, label in score_and_labels.items():
        plt.text(y=score*numberOfTurns+0.01*yMax, x=len(partners), s=label)
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
    folder = '{:s}_figures/'.format(championshipName).lower().replace(' ','_')
    os.makedirs(folder, exist_ok=True)
    figurePath = folder + './{:s}_{:s}.png'.format(playerName, championshipName).lower().replace(' ','_')
    plt.savefig(figurePath)
    plt.close('all')
