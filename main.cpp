#include "common_headers.h"
#include "regex_checking.h"
#include "nfa_construction.h"
#include "nfa_to_dfa.h"
#include "regex_checking.cpp"
#include "nfa_construction.cpp"
#include "nfa_to_dfa.cpp"
#include "min_dfa.h"
#include "min_dfa.cpp"
#include "simulation.h"
#include "simulation.cpp"

using namespace std;

int main()
{
    string regex_expression,paren_regex,postfix;
    NFA postfix_nfa;

    cout<<"Enter the regular Expression (should only contain a,b)\n";
    cin>>regex_expression;
    if(!isCorrect_regex(regex_expression))
	{
		cout<<"Invalid Regex expression inserted. Please check the characters or parenthesis\n";
	}
	else{
		cout<<"******************************************-------------------------------------*****************\n\n";
		cout<<"Correct Expression\nThe parenthesised string is: ";
		paren_regex = parenthesised_regex(regex_expression);
		cout<<paren_regex<<"\n";
		postfix = infixTopostfix(regex_expression);
		cout<<"The postfix expression is "<<postfix<<"\n";
		cout<<"************************************--------------------------------------------***************\n\n";
		cout<<"Converting postfix to NFA\n";
		postfix_nfa = postfix_to_nfa(postfix);
		cout<<"Converted to NFA\n";
		cout<<"\n\n************************************-----------------------------------------*******************************\n";
		cout<<"Converting to DFA\n";
		nfa_to_dfa();
		cout<<"Converted to DFA\n";
		cout<<"\n\n*************************************----------------------------------------**********************************\n\n";
		cout<<"Converting to minimal-DFA\n";
		Min_DFA();
		cout<<"Converted to minimal-DFA\n";
		cout<<"\n\n****************************************------------------------------------------***********************************\n\n";
		simulate();

	}
    return 0;
}
