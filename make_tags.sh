#!/bin/bash
# sudo apt install exuberant-ctags
ctags-exuberant -R --exclude=build --exclude=UtilsLib/include/catch.hpp --exclude=prisoners_dilemma_analysis
