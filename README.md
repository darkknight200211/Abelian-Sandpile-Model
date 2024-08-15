# Abelian-Sandpile-Model
This repository is about ASM, a classic example of self-organized critical systems. The codes are used to evolve ASM from any configuration. Please explore the codes; you can just read the README file.

The ASM system is based on a N x N grid. Rules used in these codes are as follows:
1) every grid point can have _s_ = 0,1,2 or 3 grains of sand,
2) if at a grid point _s_ > 3 then that grid topples by losing 4 grains,
3) a toppling grid point adds 4 grains to its immediate 4 neighbors (x+-1, y+-1).

When all the grid points have _s_ < = 3, the system is said to be **relaxed**. If any grid point has _s_ > 3, it is called an Active site and the grid is said to be in a transient state. In the game, the system will start with some initial relaxed state. One grain of sand will be added randomly anywhere on the grid; then the system will be allowed to relax.
