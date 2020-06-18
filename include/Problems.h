// DO NOT CHANGE! FROM HERE
#ifndef PROBLEMS_H
#define PROBLEMS_H
#include<vector>
#include<string>
#include <math.h>
#include <algorithm>
#include <iostream>

#define MANHATTAN(x0,y0,x1,y1) (abs(x0-x1)+abs(y0-y1))

// A generic state, it will be inherited by other more complex states
class State{
		public:
				virtual bool isSameState (State *state)=0;
};


// A generic problem, it will be inherited by other more complex problems
#define MAX_N_ACTIONS 10                       
class Problem{
				int  nTimesExpanded;                       // number of times a node expanded during search. 
		protected:
				int nActions;                              // number of actions
				std::string actionNames[MAX_N_ACTIONS];    
				virtual State *getNextState (State *curState, int action)=0;  // returns next state, given curState and action
		public:
				Problem(){
						nActions = 0;
						nTimesExpanded=0;
				}
				void setExpanded(){nTimesExpanded++;}             // number of expanded nodes is incremented
				int  getExpandedCount(){return nTimesExpanded;}   // returns number of expanded nodes
				int  getActionCount(){ return nActions;}          // returns number of actions
				std::string    getActionName (int a){             // returns action name
								  return actionNames[a]; }
				virtual void   readFromFile (char fileName[])=0;  // reads from file, depends on the problem, should be overloaded
				virtual void   setCosts (char costDescr[])=0;
				virtual State* setInitState ()=0;                 // returns initial state, depends on state which depends on problem
				virtual double getStateActionCost (State *curState, int action)=0;  // returns action cost, depends on the problem
				virtual bool   isGoalState (State* curState)=0;   // returns if the goal is achieved
				virtual void   printState(State* s) = 0;          // prints the state, depends on the problem
				virtual void   getSuccessorStateActionPairs (std::vector<State *> &states, std::vector<int> &actions, State *curState)=0;

				virtual double heuristicFunc (State* state){return 0;}             // a heuristic function should be defined in case A* is used
				virtual char*  getCostType() = 0;
};
#endif 
