
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Problems.h"
#include"Util.h"
#include"Agent.h"
using namespace std;



void parseCmdLine (int argc, char *argv[], 
				char *problemType, char *layoutFileName, char *weatherConditions, 
				char *searchType, int  &msec);

int main(int argc, char *argv[]){
		//srand(23456789);
		srand(time(NULL));

		char problemType[100];
		char layoutFileName[100];
		char weatherType[100];
		char searchType[100];
		int  msec;
		parseCmdLine(argc, argv,problemType,layoutFileName,weatherType,searchType,msec);

		Agent agent (searchType);
		agent.setProblemType (problemType);
		agent.perceive (layoutFileName, weatherType);
		agent.search ();
		agent.printSolution (msec);
}


void parseCmdLine (int argc, char *argv[], 
				char *problemType,
				char *layoutFileName, 
				char *weatherConditions, 
				char *searchType,
				int  &msec
				){
		if (argc!=11 
						|| strcmp(argv[1],"-p") 
						|| strcmp(argv[3],"-l") 
						|| strcmp(argv[5],"-w") 
						|| strcmp(argv[7],"-s")
						|| strcmp(argv[9],"-u")
						){
				cout << "Usage:" << endl;
				cout << "./p1 -p eat-food/visit-corners/eat-all-foods -l <layout-file> -w <weather-condition> -s RAND/BFS/DFS/UCS/A_STAR -u <msec>" << endl << endl;
				cout << "where <weather-condition> might be:" << endl;
				cout << "    calm/wind-from-west/wind-from-east/wind-from-north/wind-from-south/" << endl;
				cout << "        /lightning-at-west/lightning-at-east/lightning-at-north/lightning-at-south/" <<endl;
				cout << "-p for problem" << endl;
				cout << "-l for layout file" << endl;
				cout << "-w for weather conditions" << endl;
				cout << "-s for search algorithm" << endl;
				cout << "-u for update speed in printing the solution path (no printing if -1) " << endl;
				Util::Exit("Wrong command line arguments");
		}

		strcpy(problemType,argv[2]);
		strcpy(layoutFileName,argv[4]);
		strcpy(weatherConditions,argv[6]);
		strcpy(searchType,argv[8]);
		msec = atoi (argv[10]);
}
