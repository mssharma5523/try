#include "common_headers.h"
#include "nfa_construction.h"


void NFA::insert_nfa(int _size,state _start,state _last)
{
	//make a two-d transition_table of the given size and initialise that with -1
	//also set the start and the last state
	size = _size;
	if(isCorrect_state(_start) && isCorrect_state(_last) )
	{
		this->start = _start;
		this->last = _last;
		
        vector<char> temp(size,';');
        for(int i=0;i<size;i++)
            transition_table.push_back(temp);

        //cout<<"2";
	}
	else{
		cout<<"Error Initialising the NFA\n Cannot complete the process due to memory allocation\n";
		//cout<<_start<<" "<<_last<<"\n"<<_size<<"\n";
		exit(1);
	}
}


void NFA::setfinal(int a)
{
    this->last = a;
    return;
}


bool NFA::isCorrect_state(int _present)
{
	if(_present < 0 || _present >= size)
	{
		//cout<<_present<<" "<<size<<"\n";
		return false;
	}	
	return true;
}

void NFA::addNewState()
{
	vector<char> newRow(size+1,';');
	transition_table.push_back(newRow);

	for(int i=0;i<size;i++)
		transition_table[i].push_back(';');
	size +=1;
	return;
}

void NFA::new_transition(state _start,state _last, char alphabet)
{
	if(isCorrect_state(_start) && isCorrect_state(_last))
	{
		transition_table[_start][_last] = alphabet;
		alphabets.insert(alphabet);
		//if(alphabet!=' ')

	}
	else{
		cout<<"Invalid states as Input\n Exiting the Process..try again\n";
		exit(1);
	}
}

void NFA::shift_states(int _shift)
{
	int temp_size = size + _shift;

	if(_shift<1)
	{
		cout<<"Invalid shifting of states\n";
		return;
	}


	//vector<vector<char> > new_table(temp_size,std::vector<char>(temp_size,';'));
	vector<vector<char> > new_table;
	vector<char> temp(temp_size,';');
	for(int i=0;i<temp_size;i++)
        new_table.push_back(temp);
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			new_table [i+_shift][j+_shift] = transition_table[i][j];

	this->size = temp_size;
//	transition_table = new_table;
	this->start = this->start + _shift;
	this->last = this->last + _shift;
	transition_table = new_table;
	//cout<<"\n"<<transition_table.size()<<" "<<transition_table[0].size()<<"\n";
	return;
}

void NFA :: print()
{
	cout<<"The number of states in the NFA are:"<<size<<"\n";
	cout<<"The starting state is "<<start<<"\n";
	cout<<"The final state is "<<last<<"\n";

	cout<<"The transition table for the NFA is as follows \n";

	for(int i = 0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
            if(transition_table[i][j]!= ';'){
                cout<<"Transition from state "<<i<<"to state "<<j<<" is "<<transition_table[i][j];
            	if(transition_table[i][j] == ' ')
            	cout<<"e";
            	cout<<"\n";
            }
		}
		//cout<<"\n";
	}
	return;
}
void NFA::copy_transition_table(NFA& other)
{
	for(int i=0;i<other.size;i++)
	{
		for(int j=0;j<other.size;j++)
		{
			transition_table[i][j] = other.transition_table[i][j];
		}
	}

	set<char>::iterator it;
	for(it = other.alphabets.begin();it!=other.alphabets.end();it++)
	{
		alphabets.insert(*it);
	}

}

void NFA::copy_NFA(const NFA& other)
{
	if(this == &other)
		return;
	this->size = other.size;
	this->start = other.start;
	this->last = other.last;
	this->transition_table = other.transition_table;
	this->alphabets = other.alphabets;
	return;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//last of NFA class


//building an NFA..just create an NFA with two state and use th einsert function of NFA class

//NFA first,union_nfa,concatenate_nfa,temp,second;

NFA build_nfa(char alphabet)
{
    NFA	mata;
	//cout<<"hi\n";
    mata.insert_nfa(2,0,1);
	//cout<<"hello\n";
    first = mata;
	first.new_transition(0,1,alphabet);
	return first;
}

//unions two NFA by first shifting the states by 1 and adding the first NFA to the second NFA accordingly
//A new final State is added and then the current NFA size are changed accordingly
//epsilon has been represented by a space character
NFA nfa_union(NFA first,NFA second)
{
	int nfa_size = first.size+second.size;
	first.shift_states(1);
	second.shift_states(first.size);
    second.copy_transition_table(first);
    union_nfa = second;
	//union_nfa.start= 0;

	union_nfa.new_transition(0,first.start,' '); //Epsilon has to be represented
	union_nfa.new_transition(0,second.start,' ');
	union_nfa.addNewState();
    union_nfa.start = 0;
	union_nfa.new_transition(second.last,union_nfa.size-1,' '); //adding transition with the final new state
	union_nfa.new_transition(first.last,union_nfa.size-1, ' ');
	//cout<<union_nfa.size<<"\n";
	union_nfa.setfinal(union_nfa.size-1);
	//cout<<"The last state is "<<union_nfa.last<<"\n";
	return union_nfa;
}

//using the thompson construction construct the concatenation by first adding a state with that of the existing and then 
//appending the first state with that of second
NFA nfa_concatenate(NFA first,NFA second)
{
	//concatenate first and second
	//first is before and second is after

	second.shift_states(first.size-1);

    concatenate_nfa = second;
	concatenate_nfa.copy_transition_table(first);
	concatenate_nfa.start = first.start;
	return concatenate_nfa;
}

//the thompson model of closure has been used 
NFA nfa_closure(NFA close)
{
    NFA mata = close;
    first = mata;
	first.shift_states(1);
	first.addNewState();
	//NFA closure_nfa(first);
	//closure_nfa.start = first.start;
	//cout<<first.start<<" gjg"<<first.last<<"\n";
	first.new_transition(first.last,first.start,' '); //adding of new eps transition
	first.new_transition(first.last,first.size-1,' ');//same as above
	first.new_transition(0,first.start,' ');//same
	first.new_transition(0,first.size-1,' ');//same
	first.start = 0;
	first.last = first.size-1;
	//cout<<first.last<<"\n";
	return first;
}

//concatenation and closure..:D
NFA nfa_plus(NFA first)
{
	//concatenation of first and closure(first)
	NFA mata;
	mata.copy_NFA(first);
	second = nfa_closure(mata);
	return nfa_concatenate(first,second );

}
//last of the NFA building block functions
//function for postfix to nfa...
//use the simple postfix method of calculating the values of numerical logic is applied
//precedencde no issue
//for closure only one pop else two pop and a push
NFA postfix_to_nfa(string postfix)
{
	stack<NFA> automata;
	while(!automata.empty())
		automata.pop();

	NFA first_,second_,to_insert_,final_nfa_,to_concatenate_,to_push_char_;
	char c;
	for(int i=0;i<postfix.length();i++)
	{
		if(postfix[i]=='.') //concatenate requires two pop
		{

			second_ = automata.top();
			automata.pop();
			first_ = automata.top() ;
			automata.pop();
			to_concatenate_ = nfa_concatenate(first_,second_);
			automata.push(to_concatenate_);
		}
		else if(postfix[i] == '|') //requires two pop
		{
			second_ = automata.top();
			automata.pop();
			first_ = automata.top();
			automata.pop();
			to_insert_ = nfa_union(first_,second_);
			automata.push(to_insert_);
		}
		else if(postfix[i] == '*') //single pop
		{
			first_ = automata.top();
			automata.pop();
			to_insert_ = nfa_closure(first_);
			//cout<<to_insert_.last<<"\n";
			automata.push(to_insert_);
		}
		else if(postfix[i] == '+')
		{
            first_ = automata.top();
            automata.pop();
            to_insert_ = nfa_plus(first_);
            automata.push(to_insert_);
		}
		else{
			 to_push_char_ = build_nfa(postfix[i]);
		//	 cout<<to_push_char_.start<<" afa"<<to_push_char_.last<<"af\n";
			 automata.push(to_push_char_);

		}
	}
	final_nfa_ = automata.top();
	automata.pop();
	final_nfa_.print();
    print_to_file(final_nfa_);

	return final_nfa_;

}

//prints the NFA in the required format to NFA.txt..
void print_to_file(NFA final_nfa_)
{
    ofstream out_nfa;
	out_nfa.open("NFA.txt");
	out_nfa<<final_nfa_.size<<" 2\n";
	cout<<"Writing to file\n";
	out_nfa<<"1 "<<final_nfa_.last<<"\n";
    //cout<<"Writing to file\n";
	int no_of_transitions = 0,char_input,count_transition;//e-0,a-1,b-2
    //cout<<"Printing to file";
   // cout<<final_nfa_.size<<"\n";
    count_transition = 0;
    for(int i =0;i<final_nfa_.size;i++)
        for(int j=0;j<final_nfa_.size;j++)
        {
            if(final_nfa_.transition_table[i][j]!=';')
                count_transition +=1;
        }
    out_nfa<<count_transition<<"\n";
	for(int i=0;i<final_nfa_.size;i++)
    {
        count_transition = 0;
        char_input = -1;
      //  cout<<"Writing to file\n";
        for(int j=0;j<final_nfa_.size;j++)
        {
            if(final_nfa_.transition_table[i][j]!=';'){
                    count_transition += 1;
                    if(final_nfa_.transition_table[i][j] == ' ')
                        char_input = 0;
                    else if(final_nfa_.transition_table[i][j] == 'a')
                        char_input = 1;
                    else if(final_nfa_.transition_table[i][j] == 'b')
                        char_input = 2;
                }
        }
        if(char_input == 0 || char_input == 1 || char_input == 2)
            out_nfa<<i<<" "<<char_input<<" "<<count_transition;
        for(int j=0;j<final_nfa_.size;j++)
            if(final_nfa_.transition_table[i][j] != ';')
                out_nfa<<" "<<j;
        out_nfa<<"\n";
    }
    out_nfa.close();
    cout<<"Writing to file finished\n";
    return;
}
