void Min_DFA(){

	for(int i=0;i<MAX_STATE;i++){
				for(int j=0;j<MAX_ALPHABET;j++){
					trans_table[i][j]=-1;
				}
			}
	ifstream fin("DFA1.txt");
	int final_num,num_trans;

	// Reading input file contents
	fin>>states_num>>num_alpha;
	fin>>final_num;
	for(int i=0;i<final_num;i++){
		int j;
		fin>>j;
		final_init[j]=1;
	}
	fin>>num_trans;
	//filling the transition table
	for(int i=0;i<num_trans;i++){
		int s,a;
		fin>>s>>a;
		fin>>trans_table[s][a];
	}

	//eliminate the non-reachable state

	//bitset<MAX_STATE>reachable;
	//eliminate_unreachable(reachable);

	bool mark_table[MAX_STATE][MAX_STATE];

	for(int i=0;i<states_num;i++){
		for(int j=0;j<states_num;j++){
			mark_table[i][j]=0;
		}
	}

	/*marking the final and non-final states*/
	for(int i=1;i<states_num;i++){
		for(int j=0;j<i;j++){
			if(((final_init[i]==1)&&(final_init[j]==0))||((final_init[i]==0)&&(final_init[j]==1))){
				mark_table[i][j]=1;
				mark_table[j][i]=1;
			}
		}
	}

	/* mark_table has entry 1 if i and j cannot be in the same state else 0 */

	/*This while loop runs until there are no more changes in the mark_table entries*/

	int marked=1;  //The value of marked is  1 if the mark_table entries are changed inside the while loop
	while(marked==1){
		marked=0;
		for(int i=1;i<states_num;i++){
			for(int j=0;j<i;j++){
				if(mark_table[i][j]==0){
					for(int k=1;k<=num_alpha;k++){
						if((trans_table[i][k]!=-1)&&(trans_table[j][k]!=-1)){
						 //This is an extra condition if the dfa does not have complete transition table
							if(mark_table[trans_table[i][k]][trans_table[j][k]]==1){
								mark_table[i][j]=1;
								mark_table[j][i]=1;

								marked=1;
								break;
							}
						}
						else if(((trans_table[i][k]!=-1)&&(trans_table[j][k]==-1))||((trans_table[i][k]==-1)&&(trans_table[j][k]!=-1))){
							mark_table[i][j]=1;
							marked=1;
							break;
						}

					}
				}
			}
		}

	}

		/*for(int i=1;i<states_num;i++){
			for(int j=0;j<i;j++){
				cout<<mark_table[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<"-----------------"<<endl;*/

	//done marking the entries of the mark_table


	bitset<MAX_STATE>n;//this is to make sure that all the states of the input dfa are contained in some node
	//Merging the pair of states which were not crossed out in the previous step
	for(int i=1;i<states_num;i++){
		for(int j=0;j<i;j++){
			if(mark_table[i][j]==0){
				node*nw =new node;
				nw->constituent_dfa_state[i]=1;
				nw->constituent_dfa_state[j]=1;
				if(final_init[i]==1)	//pairs have already been split based on final and non-final state
					nw->final=1;
				else
					nw->final=1;
				dfa_node[i]=nw;
				dfa_node[j]=nw;
				n[i]=1;
				n[j]=1;
				_map m;
				m.first=nw;
				m.second=0;//initialised to not-marked
				dfa_intermediate_state.push_back(m);
			}
		}
	}
	//forming nodes for those states which could not be paired
	for(int i=0;i<states_num;i++){
		if(n[i]==0){
			node*nw=new node;
			if(final_init[i]==1)
				nw->final=1;
			else
				nw->final=0;
			nw->constituent_dfa_state[i]=1;
			dfa_node[i]=nw;
			_map m;
			m.first=nw;
			m.second=0;
			dfa_intermediate_state.push_back(m);
		}
	}
	/* Displaying the nodes*/

	for(int i=0;i<dfa_intermediate_state.size();i++){
		node*st=dfa_intermediate_state[i].first;
		//cout<<st->final<<endl;
		for(int j=0;j<states_num;j++){
			if(dfa_intermediate_state[i].first->constituent_dfa_state[j]==1)
				cout<<j<<" ";
		}
		cout<<endl;
	}
	cout<<endl;


	int merge=1;



	/* dfa_intermediate_state and dfa_minimised_state are filled with the same nodes */

	for(int i=0;i<dfa_intermediate_state.size();i++){
		node*n=dfa_intermediate_state[i].first;
		_map m;
		m.first=n;
		m.second=0;
		dfa_minimised_state.push_back(m);
	}


	while(merge>0){
		merge=0;
		for(int i=0;i<dfa_intermediate_state.size();i++){//grabbing a node from the dfa_intermediate_state vector
			if(dfa_intermediate_state[i].second==0){	//not_marked => has not yet been merged/considered in this iteration
				dfa_intermediate_state[i].second=1;
				//merge=0;
				node*current=dfa_intermediate_state[i].first;
				node*nw=new node;
				nw->final=current->final;
				nw->constituent_dfa_state=current->constituent_dfa_state;
				int dfa_of_concern;
				//get a constituent dfa state of the current node from dfa_intermediate_state vector
				for(int it=0;it<states_num;it++){
					if(current->constituent_dfa_state[it]==1){
						dfa_of_concern=it;
						break;
					}
				}
				//cout<<"I am here 1 "<<endl;
				//bitset<MAX_STATE>erased;
				vector<_map>::iterator it = dfa_minimised_state.begin();
				while(it!=dfa_minimised_state.end()){
					node*st=it->first;
					int j;
					for(int pag=0;pag<states_num;pag++){	//get a constituent dfa state from dfa_minimised_state vector
						if(st->constituent_dfa_state[pag]==1){
							j=pag;
							break;
						}
					}
					//j is the constituent dfa state belong the node st
					if(it->first!=dfa_intermediate_state[i].first){	//dont consider the same nodes from dfa_minimised_state vector and dfa_intermediate_state vector
						//if(st->final==current->final){
							int a;
							for(a=1;a<=num_alpha;a++){
								if(dfa_node[trans_table[j][a]]!=dfa_node[trans_table[dfa_of_concern][a]]){
									break;
								}

							}
							//cout<<"I am here "<<endl;
							//merge if the above condition is satisfied for all the alphabets
							if((a==num_alpha)&&(st->final==current->final)){ //final and non-final nodes cannot be merged
								for(int j=0;j<states_num;j++){
									if(st->constituent_dfa_state[j]==1){
										dfa_node[j]=nw;
										nw->constituent_dfa_state[j]=1;
									}
								}
								merge=1;

								dfa_intermediate_state[it->second].second=1;

								it=dfa_minimised_state.erase(it);
							}
						//}
						else
							it++;
					}
					else
						it=dfa_minimised_state.erase(it);
				}

				int count=0;

				_map m;
				m.first=nw;
				//m.second=sz;
				dfa_minimised_state.push_back(m);
			//}
		//}

		//for(int i=0;i<dfa_intermediate_state.size();i++){

			//cout<<st->final<<endl;
				for(int j=0;j<states_num;j++){
					if(nw->constituent_dfa_state[j]==1)
						cout<<j<<" ";
				}
				/*for(int j=0;j<states_num;j++){
					if(current->constituent_dfa_state[j]==1)
						cout<<j<<" ";
				}*/
				cout<<endl;
				/*if(merge==1)
					i=0;	*/
			}
		}
		//dfa_intermediate_state and dfa_minimised_state vector are filled with the same values
		dfa_intermediate_state.clear();
		for(int i=0;i<dfa_minimised_state.size();i++){
			node* n=dfa_minimised_state[i].first;
			dfa_minimised_state[i].second=i;
			_map m;
			m.first=n;
			m.second=0;
			dfa_intermediate_state.push_back(m);
		}
		cout<<endl;
	}
	ofstream output;
	output.open("Min_DFA.txt");
	output<<"No of states are:"<<" ";
	stringstream o;
	o<<dfa_minimised_state.size();
	output<<o.str()<<endl;
	output<<"No of alphabets: 2"<<endl;

	for(int i=0;i<dfa_minimised_state.size();i++){
					node* t = dfa_minimised_state[i].first;
					int k;
								for(k=0;k<MAX_STATE;k++){
										if(t->constituent_dfa_state[k]==1)
											break;
								}
					if(final_init[k]==1){
							stringstream h;
							h<<k;
							output<<"Final State is:"<<h.str()<<endl;
					}
	}
	for(int i=0;i<dfa_minimised_state.size();i++){

					for(int j=1;j<num_alpha;j++){
								//bitset<MAX_NFA_STATES> s;
								//move_states(DFAstates[i]->nfa_states,j,s);
								//epsilon_all_state(s,s);
								node* n = dfa_minimised_state[i].first;
								int k;
								for(k=0;k<MAX_STATE;k++){
										if(n->constituent_dfa_state[k]==1)
											break;
								}
								cout<<"k is"<<k<<endl;
								//if(dfa_node[trans_table[k][j]]!=NULL){
										int search = trans_table[k][j];
								//cout<<endl<<trans_table[k][j]<<endl;
								if(search!=-1){
								for(int t=0;t<dfa_minimised_state.size();t++){
										node* p = dfa_minimised_state[t].first;

											if(p->constituent_dfa_state[search]==1){
													stringstream a,b,c;
													a<<k; b<<j; c<<search;
													output<<"Transition from state "<<a.str()<<" "<<"on "<<b.str()<<" "<<"to "<<c.str()<<endl;
													break;
												}
										}
									}
								}
					}

	output.close();

}
