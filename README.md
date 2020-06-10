# graphive
A next attempt to a graph database<br>

To install and run:
1. Download all sources from here
2. Make sure following software is on your machine
   * gcc
   * make
3. on the cli
   1. cd to the location where you downloaded the sources
   2. Type make
4. create a configuration file
   This file must at least consist og the following:
   * port: [9999] Port number you wish to listen graphive on
   * log: <logfile> name of the file you widh graphive send it's log messages to
   * startup_delay: <n> For debugging purposes. Make it 0 is a safe choice
   * data_dir: <datadir> Where is your data located
5. on a commandline start graphive
   1. It will spawn into the background
   3. Have fun with graphive
