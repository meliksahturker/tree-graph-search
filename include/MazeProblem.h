#ifndef MAZEPROBLEM_H
#define MAZEPROBLEM_H
#include"Problems.h"
// types of items in mazes. New items might be added later.
#define WALL   0
#define AGENT  1
#define FOOD   2
#define FREE   3
#define N_MAZE_ITEMS 4

// actions available to the agent.
#define MOVE_UP    0
#define MOVE_DOWN  1
#define MOVE_LEFT  2
#define MOVE_RIGHT 3
#define N_MAZE_ACTIONS 4
#define MAX_MAP_SIZE 500

#define CALM 0
#define WIND_FROM_WEST  1
#define WIND_FROM_EAST  2
#define WIND_FROM_NORTH 3
#define WIND_FROM_SOUTH 4
#define LIGHTNING_AT_WEST  5
#define LIGHTNING_AT_EAST  6
#define LIGHTNING_AT_NORTH 7
#define LIGHTNING_AT_SOUTH 8
#define N_WEATHER_TYPES 9



// state for maze with one food only depends on agent position
class MazeState : public State{
		public:
				int agentPos;
				MazeState (int agentPos, std::vector<int> foodPosList, std::vector<int> wallPosList) ;
				virtual bool isSameState (State *state);
};

class MazeProblem : public Problem{
				static char weatherTypeNames[9][50];                 // weather affects the state-action costs

		protected:
				int maze[MAX_MAP_SIZE][MAX_MAP_SIZE];                // items in the map (WALL/AGENT/FOOD/FREE)
				static char mazeItems[N_MAZE_ITEMS];                 // item codes for file input/output
				static char mazeActionNames[N_MAZE_ACTIONS][20];     // use arrows for action names, more easy to understand
				int nCols;     // column number of the maze
				int nRows;     // row number of the maze

				int initAgentPos;               // initial agent position
				std::vector<int> foodPosList;   // list of food positions 
				std::vector<int> wallPosList;   // list of wall positions
				int nFoods;                     // number of foods
				int nWalls;                     // number of walls

				int weather;

				int  getPosFromRowCol (int r, int c);                       // position: mapping from 2d index to 1d index
				void getRowColFromPos (int &r, int &c, int index);          // position: mapping from 1d index to 2d index
				void getActionEffectRC (int &dr, int &dc, int action);      // (delta) position change with action
				
				virtual State *getNextState (State *curState, int action);  // return the next state, internally used by getSuccessorStateActionPairs()
		public:
				MazeProblem();
				virtual void   readFromFile (char fileName[]);                    // reads the maze file. 
				virtual State* setInitState ();                                   // returns the initial (maze) state
				virtual double getStateActionCost (State *curState, int action);  // returns the action cost
				virtual bool   isGoalState (State* curState);                     // checks if state is reached
				virtual void   printState(State* s);                              // prints the state
				virtual void   getSuccessorStateActionPairs (std::vector<State *> &states, std::vector<int> &actions, State *curState);
				virtual double heuristicFunc (State *state);                    // heuristic function used in maze problem for A* search
				virtual void   setCosts (char weatherType[]);
				virtual char*  getCostType();

};

#endif
