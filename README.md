# TicTacToe-WaterJug-Problem
in c++

#TicTacToe Problem
The AI logic is based on a rule-based strategy that prioritizes:
1)Winning if possible.
2)Blocking the opponent's winning move.
3)Occupying the center, corners, or sides strategically.
Time Complexity: O(1) (since the board size is fixed, the runtime does not grow with input size).


#WaterJug Problem using bfs
The problem:
1)You have two jugs with capacities cap1 and cap2.
2)You need to measure exactly a given target liters of water.

You can perform the following actions:
1)Fill a jug completely.
2)Empty a jug.
3)Pour water from one jug to the other until one is empty or the other is full.

As BFS visits each state once, Time Complexity: O((cap1+1)×(cap2+1))

Pour Jug1 → Jug2: 
     pour= min(x, cap2 −y)
     x′= x − pour
     y′= y + pour
Pour Jug2 → Jug1:
     pour=min(y, cap1−x)
     x′= x + pour
     y'= y - pour



