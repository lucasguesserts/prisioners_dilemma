""" Tools for analysing the data from prisoner's dilemma competitions.

"""

from setuptools import setup

DOCLINES = (__doc__ or '').split("\n")

setup(
    # Metadata
    name='prisoners_dilemma_analysis',
    version='0.0.0',
    url='https://github.com/lucasguesserts/prisoners_dilemma',
    download_url='https://github.com/lucasguesserts/prisoners_dilemma',
    author='Lucas Guesser Targino da Silva',
    author_email='lucasguesserts@gmail.com',
    classifiers=[
        'Intended Audience :: Education',
        'Natural Language :: English',
        'Programming Language :: Python :: 3',
        'Topic :: Scientific/Engineering',
    ],
    license='MIT',
    license_file='../LICENSE',
    description = DOCLINES[0],
    long_description = "\n".join(DOCLINES[2:]),
	keywords=[
        'prisoner\'s dilemma',
        'game theory',
    ],
    project_urls={
        'Source Code': 'https://github.com/lucasguesserts/prisoners_dilemma',
        #'Documentation': 'https://REPOSITORY.readthedocs.io/en/latest/',
        #'Build': 'https://travis-ci.org/lucasguesserts/REPOSITORY',
        #'Code Coverage': 'https://codecov.io/gh/lucasguesserts/REPOSITORY',
    },
    # Options
    install_requires=[
        'h5py',
        'numpy',
        'matplotlib',
    ],
    tests_require=[
        'pytest',
    ],
    python_requires='>=3.0',
)
