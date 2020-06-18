#include"Util.h"
#include"MazeProblem.h"
#include <iostream>
using namespace std;

/******************************* MazeState class **********************/

MazeState::MazeState (int agentPos, std::vector<int> foodPosList, std::vector<int> wallPosList) {
		this->agentPos = agentPos;
}

bool MazeState::isSameState (State *state){
		MazeState *otherState = (MazeState*) state;
		return (this->agentPos==otherState->agentPos);
}


/******************************* MazeProblem class **********************/

char MazeProblem::mazeItems[N_MAZE_ITEMS]={'@','A','F',' '};
char MazeProblem::mazeActionNames[N_MAZE_ACTIONS][20]={"^^^", "vvv", "<--", "-->"};
char MazeProblem::weatherTypeNames[9][50]={"calm",
		"wind-from-west","wind-from-east","wind-from-north","wind-from-south",
		"lightning-at-west","lightning-at-east","lightning-at-north","lightning-at-south"};

// constructor, do not change
MazeProblem::MazeProblem(){
		for (int a=0;a<N_MAZE_ACTIONS;a++)
				actionNames[a] = string (mazeActionNames[a]);
		nCols=nRows=-1;
}

// reads the layout from file, do not change
void MazeProblem::readFromFile (char fileName[]){
		FILE *fp = fopen (fileName,"r");
		if (fp==0){
				Util::Exit("Cannot open maze file for reading");
		}
		char s;
		int c;
		nFoods=0;
		nRows=c=0;
		while (fscanf(fp,"%c",&s)!=EOF){
				switch (s){
						case '@':
								wallPosList.push_back (getPosFromRowCol (nRows, c));
								maze[nRows][c++]=WALL;
								break;
						case 'A':
								initAgentPos = getPosFromRowCol (nRows, c);
								maze[nRows][c++]=FREE; 
								// = AGENT in reality, but AGENT pos is kept separately in the state
								break;
						case 'F':
								foodPosList.push_back (getPosFromRowCol (nRows, c));
								maze[nRows][c++]=FOOD;
								nFoods++;
								break;
						case ' ':
								maze[nRows][c++]=FREE;
								break;
						case '\n':
								if (nCols==-1)
										nCols = c;
								else if (nCols != c)
										Util::Exit("Problem in maze file in dimensions");
								c=0; 
								nRows++;
								break;
						default: 
								Util::Exit("Problem in maze file in characters");
				}
		}
		if (c!=0)
				nRows++;
		nActions = N_MAZE_ACTIONS;
		nFoods = foodPosList.size();
}

// sets the weather type
// do not change
void MazeProblem::setCosts (char weatherType[]){
		for (int i=0;i<N_WEATHER_TYPES;i++){
				if (!strcmp(weatherType, weatherTypeNames[i])){
						weather = i;
						return;
				}
		}
		Util::Exit("Problem in setting weather type (probably in weather naming)");
}

// returns the weather name for printing out
// do not change!
char* MazeProblem::getCostType(){
		return weatherTypeNames[weather];
}

// sets the initial state
// do not change!
State *MazeProblem::setInitState (){
		State *state = new MazeState (initAgentPos, foodPosList, wallPosList);
		return state;
}

// return successors state-action pairs in states and actions vectors
// do not change!
void  MazeProblem::getSuccessorStateActionPairs (vector<State *> &states, vector<int> &actions, State *curState){
		setExpanded();
		for (int a=0; a<nActions; a++){
				State *nextState = getNextState (curState, a);
				if (nextState->isSameState(curState))
						continue;
				states.push_back(nextState);
				actions.push_back(a);
		}
}

// find the next state given current state and action
// only used internally by getSuccessorStateActionPairs()
// do not change!
State *MazeProblem::getNextState (State *curState, int action){
		int curPos = ((MazeState *)curState)->agentPos;
		int dC, dR, curC, curR, nextC, nextR;
		getRowColFromPos (curR, curC, curPos);
		getActionEffectRC (dR, dC, action);
		nextR = curR+dR;
		nextC = curC+dC;
		if (maze[nextR][nextC] == WALL || nextR<0 || nextR>=nRows || nextC<0 || nextC>=nCols)
				return curState;
		int newPos = getPosFromRowCol (nextR, nextC);
		State *nextState = new MazeState (newPos, foodPosList, wallPosList);
		return nextState;
}

// utility function that returns 1d index from 2d position
int  MazeProblem::getPosFromRowCol (int r, int c){
		return (r*nCols + c);
}

// utility function that returns 2d position from 1d index
void MazeProblem::getRowColFromPos (int &r, int &c, int index){
		c = index%nCols;
		r = floor(1.0*index/nCols);
}

// returns the change in 2d position with an action
// do not change
void MazeProblem::getActionEffectRC (int &dr, int &dc, int action){
		dr=dc=0;
		switch (action){
				case (MOVE_UP):    dr = -1; break;
				case (MOVE_DOWN):  dr = +1; break;
				case (MOVE_LEFT):  dc = -1; break;
				case (MOVE_RIGHT): dc = +1; break;
		}
}

// calm weather is nice
// wind is good if blowing in the movement direction, bad if blowing in opposite direction
// avoid lightning direction/areas 
// do not change
double  MazeProblem::getStateActionCost (State *curState, int action){
		double cost;
		if (weather==CALM){ 
				cost=1;
		}else if (weather==WIND_FROM_WEST){
				if (action==MOVE_LEFT) cost=1.5;
				else if (action==MOVE_RIGHT) cost=0.5;
				else cost=1;
		}else if (weather==WIND_FROM_EAST){
				if (action==MOVE_RIGHT) cost=1.5;
				else if (action==MOVE_LEFT) cost=0.5;
				else cost=1;
		}else if (weather==WIND_FROM_NORTH){
				if (action==MOVE_UP) cost=1.5;
				else if (action==MOVE_DOWN) cost=0.5;
				else cost=1;
		}else if (weather==WIND_FROM_SOUTH){
				if (action==MOVE_DOWN) cost=1.5;
				else if (action==MOVE_UP) cost=0.5;
				else cost=1;
		}else{
				MazeState *mazeState = (MazeState *)curState;
				int agentPos = mazeState->agentPos;
				int r,c;
				getRowColFromPos (r,c,agentPos);
				if (weather==LIGHTNING_AT_WEST){
						cost = pow((nCols-c),2);
				}else if (weather==LIGHTNING_AT_EAST){
						cost = pow(c,2);
				}else if (weather==LIGHTNING_AT_NORTH){
						cost = pow(r,2);
				}else if (weather==LIGHTNING_AT_SOUTH){
						cost = pow((nRows-r),2);
				}
		}
		return cost;
}

// checks if current state is goal state
// do not change
bool  MazeProblem::isGoalState (State *curState){
		return (foodPosList[0] == ((MazeState*)curState)->agentPos);
}



// implement for Q3
double MazeProblem::heuristicFunc (State *state){
		double cost=0;
		int xFood = 0, yFood = 0, xAgent = 0, yAgent = 0;
        getRowColFromPos(xAgent,yAgent, ((MazeState*)state)->agentPos);
        getRowColFromPos(xFood,yFood, foodPosList.front());
		cost = abs(xFood - xAgent) + abs(yFood - yAgent);
        /********************* FILL-IN FROM HERE *********************/
        /********************* FILL-IN UNTIL HERE *********************/

		return cost;
}

// prints out state
// do not change
void MazeProblem::printState (State* state){
		int agentC, agentR;
		int agentPos = ((MazeState*)state)->agentPos;
		getRowColFromPos (agentR, agentC, agentPos);
		for (int r=0;r<nRows;r++){
				for (int c=0;c<nCols;c++){
						if (agentR==r && agentC==c){
								cout << BOLDRED("A") ;
						}
						else if (mazeItems[maze[r][c]]=='F'){
								cout << BOLDGRN("F") ;
						}
						else
								cout << (char) mazeItems[maze[r][c]];
				}
				cout << endl;
		}
}


