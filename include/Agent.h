#ifndef AGENT_H
#define AGENT_H
#include"Problems.h" 
#include"MazeProblem.h" 
#include"CornersProblem.h" 
#include"AllFoodsMazeProblem.h" 
#include<stdlib.h>
#include<vector>
#include<queue>

#define BFS 0
#define DFS 1
#define UCS 2
#define A_STAR 3
#define RAND 4

// DO NOT CHANGE! USE THIS STRUCTURE!
class Node{
				State* state;
				Node*  parentNode;
		public:
				Node (State *state);
				int    depth;
				double pathCost;
				int    action;
				
				State *getState()      {return state;}    
				Node  *getParentNode() {return parentNode;}
				void   setParentNode(Node *n) {parentNode=n;}
				void expand (Problem *problem);
				std::vector<Node *> childNodes;

				double f_n; // estimated cost to cheapest solution
				double g_n; // cost to reach the node n
				double h_n; // consistent (and admissible) heuristic function, estimated cost to reach goal from node n
};



class Agent{
				Problem* problem;
				int      searchType;
				std::vector<int>     actionList;
				std::vector<State *> stateList;

				std::vector<Node*> closedList;
				std::vector<Node*> fringe;
				State*   initState;
				Node*    solnNode;
		public:
				Agent (char searchStr[]);
				void setProblemType (char problemType[]);
				void perceive (char envFile[], char weatherType[]);
				void search();
				void printSolution(int msec);

				Node* graphSearch();
				void  randomSearch();
				void  printPath(Node *curNode, int msec);

				void  add2ClosedList(Node *node);
				void  initClosedList();
				bool  isInClosedList(Node *node);

				void  add2Fringe (Node *);
				Node* removeFromFringe ();

};

#endif
