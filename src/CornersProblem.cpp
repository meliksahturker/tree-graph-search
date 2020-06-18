#include"CornersProblem.h"
#include"Util.h"
#include <iostream>
using namespace std;

// extend for Q4 and use it for Q5
CornersState::CornersState (int agentPos, vector<int> foodPosList, vector<int> wallPosList) 
		: MazeState(agentPos, foodPosList, wallPosList)
{
        this->agentPosition = agentPos;
        this->foodPositionList = foodPosList;
}

// extend for Q4 and use it for Q5
bool CornersState::isSameState (State *state){
    CornersState *otherState = (CornersState*) state;

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


// Feel free to change, but not required
void CornersProblem::readFromFile (char fileName[]){
		MazeProblem::readFromFile (fileName);
}

// extend for Q4 and use it for Q5
State *CornersProblem::getNextState (State *curState, int action){
    int curAgentPos = ((CornersState *)curState)->agentPos;
    int dC, dR, curC, curR, nextC, nextR;
    getRowColFromPos (curR, curC, curAgentPos);
    getActionEffectRC (dR, dC, action);
    nextR = curR+dR;
    nextC = curC+dC;
    // if the next state is a wall or outside the maze, stay where you are
    if (maze[nextR][nextC] == WALL || nextR<0 || nextR>=nRows || nextC<0 || nextC>=nCols)
        return curState;
    int nextAgentPos = getPosFromRowCol (nextR, nextC);

    CornersState *tmpState = (CornersState *) curState;
    vector <int> tmp_foodPosList = tmpState->foodPositionList;
    for(int i = 0; i < tmp_foodPosList.size(); i ++) {
        if (nextAgentPos == tmp_foodPosList[i]){
            tmp_foodPosList.erase(tmp_foodPosList.begin() + i);
            break;
        }
    }

    State *nextState = new CornersState (nextAgentPos, tmp_foodPosList, wallPosList);

    return nextState;
}




// extend for Q4 and use it for Q5
State *CornersProblem::setInitState (){
		State *state = new CornersState(initAgentPos, foodPosList, wallPosList);
		CornersState *cornersState = (CornersState *) state;
        cornersState->foodPositionList = foodPosList;

		return cornersState;
}


// extend for Q4 and use it for Q5
bool CornersProblem::isGoalState (State *curState){
        CornersState *tempoState = (CornersState*) curState;
		return (tempoState->foodPositionList.size() == 0);
}



// Q5
double CornersProblem::heuristicFunc (State *state){
    CornersState *tempoState = (CornersState*) state;

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




