#include"Util.h"
#include"AllFoodsMazeProblem.h"
#include <iostream>
#include <Agent.h>

using namespace std;

AllFoodsMazeState::AllFoodsMazeState (int agentPos, std::vector<int> foodPosList, std::vector<int> wallPosList) 
						: MazeState (agentPos, foodPosList, wallPosList)
{
        this->agentPosition = agentPos;
        this->foodPositionList = foodPosList;
}

bool AllFoodsMazeState::isSameState (State *state){
    AllFoodsMazeState *otherState = (AllFoodsMazeState*) state;

    bool foodPosChecker = true;
    if (this->foodPositionList.size() == otherState->foodPositionList.size()){
        for(int i = 0; i < otherState->foodPositionList.size(); i++ ){
            if (this->foodPositionList[i] != otherState->foodPositionList[i]) {
                foodPosChecker = false;
                break;
            }
        }
    }
    else{
        foodPosChecker = false;
    }

    return ((this->agentPos==otherState->agentPos) & foodPosChecker);
}


/******************************* ALL-FOODS-MAZE-PROBLEM ******************************/
// feel free to change
void AllFoodsMazeProblem::readFromFile (char fileName[]){
		MazeProblem::readFromFile (fileName);
}

// feel free to change
State *AllFoodsMazeProblem::setInitState (){
        State *state = new AllFoodsMazeState(initAgentPos, foodPosList, wallPosList);
        AllFoodsMazeState *cornersState = (AllFoodsMazeState *) state;
        cornersState->foodPositionList = foodPosList;

        return cornersState;
}


// feel free to change
State *AllFoodsMazeProblem::getNextState (State *curState, int action){
		int curPos = ((AllFoodsMazeState *)curState)->agentPos;
		int dC, dR, curC, curR, nextC, nextR;
		getRowColFromPos (curR, curC, curPos);
		getActionEffectRC (dR, dC, action);
		nextR = curR+dR;
		nextC = curC+dC;
		// if the next state is a wall or outside the maze, stay where you are
		if (maze[nextR][nextC] == WALL || nextR<0 || nextR>=nRows || nextC<0 || nextC>=nCols)
				return curState;
		int nextAgentPos = getPosFromRowCol (nextR, nextC);


        AllFoodsMazeState *tmpState = (AllFoodsMazeState *) curState;
        vector <int> tmp_foodPosList = tmpState->foodPositionList;
        for(int i = 0; i < tmp_foodPosList.size(); i ++) {
            if (nextAgentPos == tmp_foodPosList[i]){
                tmp_foodPosList.erase(tmp_foodPosList.begin() + i);
                break;
            }
        }
        State *nextState = new AllFoodsMazeState (nextAgentPos, tmp_foodPosList, wallPosList);
        return nextState;
}

bool AllFoodsMazeProblem::isGoalState (State *curState){
        AllFoodsMazeState *tempoState = (AllFoodsMazeState*) curState;
        return (tempoState->foodPositionList.size() == 0);
}


void AllFoodsMazeProblem::printState (State* state){
    AllFoodsMazeState *tempoState = (AllFoodsMazeState*) state;
    int agentC, agentR, mazeR, mazeC;
    int agentPos = tempoState->agentPos;
    getRowColFromPos (agentR, agentC, agentPos);
    for (int r=0;r<nRows;r++){
        for (int c=0;c<nCols;c++){
            if (agentR==r && agentC==c){
                cout << BOLDRED("A") ;
            }
            else if ((mazeItems[maze[r][c]]=='F') & foodPosFunc(r,c,state)){
                cout << BOLDGRN("F") ;
            }

            else if ((mazeItems[maze[r][c]]=='F') != foodPosFunc(r,c,state)) {
                cout << " ";
            }
            else
                cout << (char) mazeItems[maze[r][c]];

        }
        cout << endl;
    }
}

bool AllFoodsMazeProblem::foodPosFunc(int r, int c, State* state){
        AllFoodsMazeState *tempoState = (AllFoodsMazeState*) state;

        for(int i = 0; i < tempoState->foodPositionList.size(); i++){
            int tmpR, tmpC;
            getRowColFromPos(tmpR, tmpC, tempoState->foodPositionList[i]);
            if (tmpR == r & tmpC == c)
                return true;
        }
}


double AllFoodsMazeProblem::heuristicFunc (State *state){
    AllFoodsMazeState *tempoState = (AllFoodsMazeState*) state;


    int xAgent = 0, yAgent = 0, xFood = 0, yFood = 0;
    double dist=0;
    vector<double> manh_distance_vector;

    getRowColFromPos(xAgent,yAgent, tempoState->agentPosition);

    for (int i = 0; i < tempoState->foodPositionList.size(); i ++){
        getRowColFromPos(xFood,yFood, tempoState->foodPositionList[i]);
        dist = abs(xFood - xAgent) + abs(yFood - yAgent);
        manh_distance_vector.push_back(dist);
    }
    sort(manh_distance_vector.begin(), manh_distance_vector.end());
    reverse(manh_distance_vector.begin(), manh_distance_vector.end());

    return manh_distance_vector[0];
}


