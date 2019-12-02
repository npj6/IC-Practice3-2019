# IC-Practice3-2019

`make all` (default): compiles everything

`make gameoflife`: compiles de game of life simulation

`make patterns`: compiles the pattern generation program

`make clean`: deletes temporary files (should be ignored by github anyways)

`./patterns --n 10 --s 20`: generates 10 patters of size 20x20 and saves them to the pat/ folder

`./gameoflife --i 50 --f pat/`: iterates 50 times each pattern in the pat/ folder

The time data for pattern generation is saved to patterns_report while the time data for pattern iteration is saved to gameoflife_report. Both of them are outputed when executing the programs.

The arguments can be provided in different order, and the --f argument can be ommited. If a folder is not specified, the pat/ folder will be used.
