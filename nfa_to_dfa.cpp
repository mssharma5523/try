#include "common_headers.h"
#include "nfa_to_dfa.h"


void epsilon_state(int state,bitset<MAX_NFA_STATES>&e_closure){
	//cout<<state<<":";
	//cout<<state<<" "<<endl;
	e_closure[state]=1;
	for(int i=0;i<num_states_nfa;i++){
		if(NFAstates[state].trans_table[i][0]!=-1){

			if(e_closure[i]==0){
				e_closure[i]=1;
				//cout<<" "<<i<<" ";
				epsilon_state(i,e_closure);
			}
		}
	}
}

void epsilon_all_state(bitset<MAX_NFA_STATES>states,bitset<MAX_NFA_STATES>&res){
	//cout<<endl;
	for(int i=0;i<num_states_nfa;i++){
		if(states[i]==1)
			epsilon_state(i,res);
	}
}

void move(int state,int alphabet,bitset<MAX_NFA_STATES>&res){
	for(int i=0;i<num_states_nfa;i++){
		if(NFAstates[state].trans_table[i][alphabet]!=-1){
			if(res[i]==0)
				res[i]=1;
				//cout<<i<<" ";
		}

	}
	//cout<<endl;
}

void move_states(bitset<MAX_NFA_STATES>states,int alphabet,bitset<MAX_NFA_STATES>&res){
	bitset<MAX_NFA_STATES>res_nw;
	for(int i=0;i<num_states_nfa;i++){
		if(states[i]==1)
			move(i,alphabet,res);
	}
	//epsilon_all_state(res_nw,res);
}



void nfa_to_dfa(){
	int i, j, X, Y, A, num_trans, num_final_state;
	// read in the underlying NFA
	ifstream fin("NFA.txt");
	fin >> num_states_nfa >> num_alpha;
	NFAstates = new NFAstate[num_states_nfa];
	fin >> num_final_state;
	for(i=0; i<num_final_state; i++) {
		fin >> X;
		NFA_finalStates.insert(X);
	}
	fin >> num_trans;
	while(num_trans--) {
		fin >> X >> A >> Y;
		for(i=0; i<Y; i++) {
		fin >> j;
		NFAstates[X].trans_table[j][A] = 1;
	}
}


	set<int>::iterator it;

	////Done filling tables for NFA////
	DFAstate* d=new DFAstate;
	d->nfa_states[0]=1;
	q.push(d);
	d=q.front();
	q.pop();
	bitset<MAX_NFA_STATES>res;
	cout<<endl;
	epsilon_all_state(d->nfa_states,res);
	d->nfa_states=res;
	for ( it=NFA_finalStates.begin() ; it != NFA_finalStates.end(); it++ ){
    	if(res[*it]==1){
    		d->final_state=1;
    		cout<<"\nthis is a final state pushing\n";
    		DFA_finalStates.push_back(0);
    		break;
    	}
    }
    cout<<"Hey i am pushing"<<endl;
	DFAstates.push_back(d);
	q.push(d);
	//cout<<endl;
	cout<<"Printing the start state of DFA"<<endl;
	for(int i=0;i<num_states_nfa;i++){
		if(res[i]==1)
			cout<<i<<" ";
	}

	int count=0;
	while(!q.empty()){
		cout<<"i am in while"<<endl;
		 d=q.front();
		q.pop();
		//res=d->nfa_states;


		for(int i=1;i<=num_alpha;i++){
			cout<<"States in DFA:";
			for(int i1=0;i1<num_states_nfa;i1++){
				if(d->nfa_states[i1]==1)
					cout<<i1<<" ";
			}
			cout<<endl;

			bitset<MAX_NFA_STATES>res_nw,res1;
			move_states(d->nfa_states,i,res1);
			epsilon_all_state(res1,res_nw);

		//checking for nw state
			bool match=0;
			if(DFAstates.size()!=0){
				for(int k=0;k<DFAstates.size();k++){
					if(DFAstates[k]->nfa_states==res_nw){
						match=1;
						break;
					}
				}
			}
			//Inserting into DFA_STATES and queue
			if(match==0){
				DFAstate* d1=new DFAstate;
				d1->nfa_states=res_nw;
				for ( it=NFA_finalStates.begin() ; it != NFA_finalStates.end(); it++ ){
	    			if(res_nw[*it]==1){
	    				d1->final_state=1;
	    				DFA_finalStates.push_back(*it);
	    				cout<<"\nthis is a final state pushing\n";
	    				break;
	    			}
	    		}
	    		//cout<<"Hey i am pushing"<<endl;
				DFAstates.push_back(d1);
				q.push(d1);
				cout<<"pushing"<<endl;
			}
				cout<<"Move on alphabet "<<i<<":";
				for(int off=0;off<num_states_nfa;off++){
					if(res_nw[off]==1)
						cout<<off<<" ";

				}
				cout<<endl;

		}

	}


		cout<<endl;
		cout<<endl;
		ofstream p;
		p.open("DFA.txt");

		stringstream s1;
		s1<<DFAstates.size();
		p<<s1.str()<<" "<<"2"<<endl;
		int trans=0,num_final_dfa=0;
		cout<<"\nfinal states\n";
		for(int i=0;i<DFAstates.size();i++){

					for ( it=NFA_finalStates.begin() ; it != NFA_finalStates.end(); it++ ){
	    			if(DFAstates[i]->nfa_states[*it]==1){

	    				num_final_dfa++;
	    				break;
	    			}
		}
	}

		stringstream h;
		h<<num_final_dfa;
		p<<h.str()<<" ";

		for(int i=0;i<DFAstates.size();i++){

					for ( it=NFA_finalStates.begin() ; it != NFA_finalStates.end(); it++ ){
	    			if(DFAstates[i]->nfa_states[*it]==1){
	    				stringstream e;
	    				e<<i;
	    				p<<e.str()<<" ";
	    				break;
	    			}
		}
		}
		p<<endl;
		for(int i=0;i<DFAstates.size();i++){

					for(int j=1;j<=num_alpha;j++){
								bitset<MAX_NFA_STATES> s;
								move_states(DFAstates[i]->nfa_states,j,s);
								epsilon_all_state(s,s);
								for(int k=0;k<DFAstates.size();k++){
										if(DFAstates[k]->nfa_states==s){
													trans++;
													break;
										}
								}
					}
		}
		stringstream f;
		f<<trans;
		p<<f.str()<<endl;

		for(int i=0;i<DFAstates.size();i++){

					for(int j=1;j<=num_alpha;j++){
								bitset<MAX_NFA_STATES> s;
								move_states(DFAstates[i]->nfa_states,j,s);
								epsilon_all_state(s,s);
								for(int k=0;k<DFAstates.size();k++){
										if(DFAstates[k]->nfa_states==s){
													stringstream m,r,t;
													DFAstates[i]->transition[j] = k;
													cout<<"Transition from state "<<i<<" "<<"on "<<j<<" "<<"to "<<k<<endl;
													m<<i; r<<j; t<<k;
													p<<m.str()<<" "<<r.str()<<" "<<t.str()<<endl;
													break;
										}
								}
					}
		}

		p.close();
	//return 0;
}
