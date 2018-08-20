# SFML-Packets
Short example program of using packets and sockets using sfml to create a local network "game"

## Summary

This is to allow me to learn some basic networking programming in c++.
I will eventually be adding more and more to this overtime to get a better
and more complex example able to run on a mac or ubuntu sytem.
For now it will be mostly focused for mac.

## Setup

First clone this project to a chosen dir
```
git clone https://github.com/Moondog360/SFML-Packets.git && cd SFML-Packets
```

To setup this program in ubuntu make sure you have sfml installed
and then compile it will the required flags
```
sudo apt-get install libsfml-dev
g++ main.c -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
```

For mac users I am busy with the makefile to download sfml locally.
In future you should be able to run 
```
make download
make
```
this will download sfml and then compile it

#### note this is a work in progress

#### author - Marco Fernandes
