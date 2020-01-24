# TO DO

There are three main tasks to be done:

## Improve the C++ code

- Apply clean code techniques.
- Apply modern C++ techniques.
- Improve object oriented design.
- Improve code readability.
- Add TravisCI support.

## Create documentation

- Write the C++ API and documentation using Doxygen.
- Add cove coverage information.
- Add README, CONTRIBUTING, INSTALL, etc files.
- Implement installation in the CMake.
- Specify dependencies.

## Implement prisonersdilemma files analysis in Python

Use the '.prisonersdilemma' files for analysis,
create figures from them, summarize a competition,
etc.

# Corrections and Improvements

There are many issues in the code and activities
which might be interesting to implement. Some
of them will be listed here even though the goal
is not to solve any of them.

## Issues

- Some strategies need one or more parameter to be
  created (for example, `NaiveProber` needs a
  `double probabilityOfDefecting`). Because of that,
  there is no default way of checking whether two
  strategies are equals or not (it is due to the fact
  that all strategies are handled as `Strategy *`
  in the code).
- There is no way of differentiation two players which
  have the same strategy. It is okay to create
  a competition with two such players. However, it
  won't be possible to save the results in a file,
  there will be a name conflict.

## New Possible Features

- Command line tool for creating a competition.
  The user selects the strategies, run the
  competition, save its results into a file and
  is displayed with the overall result.
