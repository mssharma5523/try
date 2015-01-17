#ifndef MIN_DFA_H_INCLUDED
#define MIN_DFA_H_INCLUDED

#define MAX_STATE 50
#define MAX_ALPHABET 10

using namespace std;

struct node{
	bool final;
	bitset<MAX_STATE>constituent_dfa_state;
	int transition[MAX_ALPHABET];
};
struct _map{
	node*first;
	int second;
};


int trans_table[MAX_STATE][MAX_ALPHABET];
int states_num;//num_alpha which was defined here has been already defined in nfa_to_dfa.h

bitset<MAX_STATE>final_init;//Initial final states of the input dfa
vector<_map> dfa_minimised_state;//the second here contains the index of the corresponding node in the dfa_intermediate_state vetor
vector<_map> dfa_intermediate_state;//The second is a marker which says if the corresponding entry has already been merged during the current iteration
node* dfa_node[MAX_STATE];//this array contains the node to which a state of the input dfa belongs

/*class dfa_min{
	public:
		int num_final,num_states;
		dfa_min(){
			for(int i=0;i<MAX_STATE;i++){
				for(int j=0;j<MAX_ALPHABET;j++){
					trans_table[i][j]=-1;
				}
			}
		}
};

/* this function eliminates the states that are unreachable from initial state*/
/*void eliminate_unreachable(bitset<MAX_STATE>&state){
	queue<int> q;
	q.push(0);
	while(!q.empty()){
		int s = q.front();
		q.pop();
		state[s]=1;
		for(int i=0;i<MAX_ALPHABET;i++){
			int s1=trans_table[s][i];
			if(state[s1]!=1)
				q.push(s1);
		}
	}
}*/

/*
	variables:
		states_num: Number of the states in the input dfa
		final_num:Number of final states in the input dfa
		num_alpha:Number of alphabets in the input dfa
*/



#endif // MIN_DFA_H_INCLUDED
