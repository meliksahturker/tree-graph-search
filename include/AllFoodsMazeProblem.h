#ifndef ALLFOODSMAZEPROBLEM_H
#define ALLFOODSMAZEPROBLEM_H
#include"MazeProblem.h"
#include "Agent.h"

// Q6
class AllFoodsMazeState : public MazeState{
		public:
                int agentPosition;
                std::vector <int> foodPositionList;

				AllFoodsMazeState (int agentPos, std::vector<int> foodPosList, std::vector<int> wallPosList);
				virtual bool isSameState (State *state);
};


#define MAX_FOODS 1000
class AllFoodsMazeProblem : public MazeProblem{
		public:
				virtual void   readFromFile (char fileName[]);
				virtual State* setInitState ();
				virtual bool   isGoalState (State *curState);
				virtual State* getNextState (State *curState, int action);
				virtual double heuristicFunc (State *state);
				virtual void   printState(State* s);

                bool foodPosFunc(int r, int c, State *state);


};

#endif
