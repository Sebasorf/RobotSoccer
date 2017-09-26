# RobotSoccer
This repo contains code for generating .dll for playing Robot Soccer with 5-players-teams for 'Simurosot' simulator.

For running it, it is necesary to download Microsoft Visual c++ 6 and the code on this repo. For this last, you can execute on a terminal:
- git clone https://github.com/Sebasorf/RobotSoccer.git
or download it as .zip file.

In RobotSoccer folder, you can open Strategy.dsw by right-clicking on it and choosing Microsoft Visual c++ 6. This will only work on Windows SO.
This Strategy corresponds to blue team. The Strategy.dll should be load to blue strategy folder.

In RobotSoccer-yellow folder, you can open the same Strategy as before, with some constants and logic modified for applying to yellow team strategy. The Strategy.dll should be load to yellow strategy folder.

You must compile in proyect, the Strategy.cpp and will generate the Strategy.dll on debug folder.

Then you can play by copying this .dll into SoccerSimulator install directory and opening it as c++ script.


