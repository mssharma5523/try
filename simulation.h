#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

/*
 * Description :	Program to simulate a given DFA on an input string. It reads in the
			DFA from "DFA.txt" and the input strings from the console and prints out
			whether the strings are accepted or rejected on the console.

			"DFA.txt" must have the following format:
				N M
				F a1 a2 ... af
				s1 y1 t1
				s2 y2 y2
				:
				:
			Here, 	N -> No. of states in the DFA (states are numbered 0 ... N-1)
				M -> Size of input alphabet (input symbols are numbered 1 ... M)
				F -> No. of final states followed by F states ( 0 <= ai <= N-1)
				si -> Previous state
				yi -> Input symbol
				ti -> Next state
			Each line until the end of file contains one transition ( si yi ti ).
 *			'0' is the start state.
 *			The input strings contain space-separated input symbols (1 ... M).
 */


#define MAX_DFA_STATES 10
#define MAX_ALPHABET_SIZE 10
using namespace std;

int transitions[MAX_DFA_STATES][MAX_ALPHABET_SIZE];
bool finalStates[MAX_DFA_STATES];
char input_string[100000];
//void simulate();

#endif // SIMULATION_H_INCLUDED
