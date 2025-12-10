# Min cost flow
Time: $\mathcal{O}(FE\log V)$

If negative costs are needed (maximize cost), need to run SPFA once at the start, making the solution $\mathcal{O}(EV + FE\log V)$.