#ifndef NFA_CONSTRUCTION_H_INCLUDED
#define NFA_CONSTRUCTION_H_INCLUDED

//This file contains the process for nfa construction. The nfa is constred using the postfix expression of the regex.
//

//using namespace std;

//the logic is to create a stack of NFA class and apply the concatenation,union and closure operations on these NFA's accordingly
//The data-structure used for storing the transition table is a two-d vecotr of vectors and that will be finally converted to a DFA

typedef int state;
class NFA{
public:

    //int start,last;//start and the last state, typedef used for namechange
	int size;//size of the NFA

	int start,last;
	vector<vector<char> > transition_table; //transition table for this NFA
	set<char> alphabets; //set of alphabets from which there is a transition in this NFA


	
	void insert_nfa(int _size,state _start,state _last);
	


	//function declaration for the NFA class


	//NFA operator=(const NFA& other);
	void new_transition(state _start,state _last,char alphabet);
	bool isCorrect_state(state _present);
	void print();
	void copy_NFA(const NFA& other);
	void copy_transition_table(NFA& other);
	void addNewState();
	void shift_states(int _shift);
	
	void setfinal(int a);

};


NFA first,union_nfa,concatenate_nfa,temp,second;
NFA build_nfa(char alphabet);
NFA nfa_union(NFA first,NFA second);
NFA nfa_concatenate(NFA first,NFA second);
NFA nfa_closure(NFA close);
NFA nfa_plus(NFA first);
NFA postfix_to_nfa(string postfix);
void print_to_file(NFA final_nfa_);

#endif // NFA_CONSTRUCTION_H_INCLUDED
