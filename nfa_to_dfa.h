#ifndef NFA_TO_DFA_H_INCLUDED
#define NFA_TO_DFA_H_INCLUDED


#define MAX_NFA_STATES 100
#define MAX_ALPHABETS 3

//using namespace std;

class NFAstate{
	public:
		int trans_table[MAX_NFA_STATES][MAX_ALPHABETS];
		NFAstate(){
			for(int i=0;i<MAX_NFA_STATES;i++)
				for(int j=0;j<MAX_ALPHABETS;j++)
					trans_table[i][j]=-1;
		}
}*NFAstates;

struct DFAstate{
	bool final_state;
	bitset<MAX_NFA_STATES> nfa_states;
	bitset<MAX_ALPHABETS> transitions;
	int transition[MAX_ALPHABETS];
};

set<int>NFA_finalStates;
vector <int> DFA_finalStates;
vector <DFAstate*> DFAstates;
queue <DFAstate*> q;
int num_states_nfa,num_alpha;


#endif // NFA_TO_DFA_H_INCLUDED
