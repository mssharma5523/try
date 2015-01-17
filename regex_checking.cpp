#include "common_headers.h"
#include "regex_checking.h"

//checking if the char is an operator
bool isOperator(char c)
{
	if(c=='.' || c=='|' || c== '*' || c== '(' || c== ')')
		return true;
	return false;
}

//This function checks if the input regex is of correct form
bool isCorrect_regex(string s)
{
	char allowed_char[] = {'a','b','|','.','*','+','(',')'}; //valid set of characters,add if u want to increase this set
	stack<char> paren,alpha;//stack for checking correctness of parenthesis and alphabet sequence
	bool flag; // to check the validity of the expression

	while(!paren.empty())
		paren.pop();
	while(!alpha.empty())
		alpha.pop();

	for(int i=0;i<s.length();i++)
	{
		flag = false;
		for(int j=0;j<8;j++)
		{
			if(s[i]==allowed_char[j])
			{
				flag = true;
			}
		}
		if(flag == false)
		{
			cout<<"Invalid set of characters\n";
			return false; //an invalid character has been found ,hence an invalid regex
		}
	}
/*	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='(')
		{
			paren.push('(');
		}
		else if(s[i]==')')
		{
			if(!paren.empty())
				paren.pop();
			else
			{
				cout<<"Invalid set of parenthesis\n";
				return false; //no matching parenthesis present hence a wrong expression
			}
		}
		else{
			if(s[i]=='*' || s[i]=='|' || s[i] == '+' || s[i]=='.')
			{
				char c=alpha.top();
				if(c == '*' || c== '.' || c == '|' || c == '+')
				{
					cout<<"Invalid set of symbols\n";
					return false; //two continuos set of symbols of ,.,|,+,* are not allowed
				}
			}
			alpha.push(s[i]);
		}
	}
*/
	//a new logic for matching the correctness of the expression

	if(s[0]!= '|' || s[0]!= '*' || s[0]!='.' || s[0]!='+' || s[0]!=')' )
	{
		alpha.push(s[0]);
		if(s[0] == '(')
			paren.push(s[0]);
	}
	else{
		return false;
	}
	for(int i=1;i<s.length();i++)
	{
		if(isOperator(s[i]))
		{
			if((s[i-1]=='*' && s[i]=='*') || (s[i-1]=='|' && s[i] == '*') || (s[i-1]=='(' && s[i]==')'))
			{
				cout<<"Two continuous wrong operators\n";
				return false;
			}
			else if(s[i-1]=='(' && (s[i]=='*' || s[i]=='.' || s[i]=='+' || s[i]=='|'))
			{
				cout<<"Operator after an opening parenthesis\n";
				return false;
			}
			else if(!isOperator(s[i-1]))
			{
				if(s[i] == '(')
				{
					paren.push('(');
					alpha.push('(');
				}
				else if(s[i] == ')')
				{
					if(!paren.empty())
						paren.pop();
					else{
						cout<<"Unbalanced parenthesis\n";
						return false;
					}
				}
				else{
					alpha.push(s[i]);
				}
			}
			else if(isOperator(s[i-1]))
			{
				if(s[i]=='(')
				{
					paren.push('(');
					alpha.push('(');
				}
			}
		}
		else{
			alpha.push(s[i]);
		}
	}
	if(s[s.length()-1] == '|' || s[s.length()-1] == '.')
	{
		cout<<"Invalid expression in the end\n";
		return false;
	}
	if(alpha.empty() || !paren.empty())
	{
		cout<<"No alphabets or odd no. of parenthesis\n";
		return false; //invalid set of parenthesis or only parenthesis are present
	}
	return true;
}

//This function converts the current regex into a parenthesised expression form
//for now assuming that if any parenthesised expression has come then its inside will be fully parenthesised ,i.e no ambiguity inside
//parenthesising because difficult to resolve issues such as in case of ab|ab*
//inserting parenthesis so as to form correct expression
//prefix and postfix expression will be easier..
string parenthesised_regex(string s)
{
	map<string,char> mapping;//used for performing a mapping between the parenthesis tokens to a single char to make it easier to code..
	string temp_regex,fin_regex,paren_sep;
	stack<int> paren;
	int start_pos,end_pos,j;
	char unused[]={'q','w','e','r','t','y','u','i','o','p','z','x','v','n','m','s','j','k','l'};
	int count=0;//for increasing the mapping counter
	mapping.clear();
	//this loop checks the already parenthesised expression such as (a|b*) and maps these to a single unused char
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='(')
		{
			paren.push(i);
			j=i+1;
			while(!paren.empty())
			{
				if(s[j]=='(')
				{
					paren.push(j);
				}
				else if(s[j]==')')
				{
					paren.pop();
				}
				j++;
			}
			paren_sep.clear(); //empties the string
			paren_sep = s.substr(i,j-i);
			mapping[paren_sep] = unused[count++];
			s.erase(i,j-i);
			s.insert(i,1,unused[count-1]);
		}
	}

	cout<<"The intermediate converted expression is "<<s<<"\n";
	//next section, to the temp_regex, firstly tokenise by |,then in each token whenever * is there, insert parenthesise it
	vector<string> tokens;
	vector<int> positions;
	vector<int>::iterator it;
	int cur;
	stack<char> fin_stk;
	while(!fin_stk.empty())
		fin_stk.pop();
	positions.push_back(0);
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='|')
			positions.push_back(i);
	}
	positions.push_back(s.length());
	cur = 0;
	char c;
	for(it = positions.begin()+1;it!=positions.end();it++)
	{
		fin_stk.push('(');
		for(int i=cur;i<*it;i++)
		{
			if(s[i]=='*')
			{
				c=fin_stk.top();
				fin_stk.pop();
				fin_stk.push('(');
				fin_stk.push(c);
				fin_stk.push('*');
				fin_stk.push(')');
			}
			else
				fin_stk.push(s[i]);
		}
		cur = *it + 1;
		fin_stk.push(')');
		if(cur != s.length()+1)
			fin_stk.push('|');
	}
	fin_regex.clear();
	cout<<"\n"<<fin_stk.size()<<"\n";
	while(!fin_stk.empty())
	{
		c = fin_stk.top();
		//fin_regex.append(&c);
		fin_regex += c;
		fin_stk.pop();
	}
	reverse(fin_regex.begin(),fin_regex.end()); //final string after proper parenthesising, now unmapping needs to be done
	cout<<fin_regex<<"\n";
	//code segment for unmapping the fin_regex expression so as to get the final expression;
	map<string,char>::iterator unmap;
	for(unmap=mapping.begin();unmap!=mapping.end();unmap++)
	{
		c = unmap->second;
		for(int i=0;i<fin_regex.length();i++)
		{
			if(fin_regex[i]==c)
			{
				fin_regex.insert(i+1,unmap->first);
				fin_regex.erase(i,1);
			}
		}
	}
	return fin_regex;
}

//code for converting the string expression to the postfix expression . This will be used in the later program during the regex to nfa conversion

int precedence(char c)
{
	if(c == '|')
		return 1;
	if(c == '.')
		return 2;
	if(c == '*')
		return 3;
}


string infixTopostfix(string exp)
{
	string s,posfix;
	std::stack<char> op;
	while(!op.empty())
	{
		op.pop();
	}
	s.clear();
	posfix.clear();
	s+=exp[0];
	for(int i=1;i<exp.length();i++)
	{
		if(!isOperator(exp[i-1]) && !isOperator(exp[i]))
		{
			s+='.';
		}
		if(exp[i-1]!='|' && exp[i]=='(')
			s+='.';
        if(exp[i-1]=='*' && (!isOperator(exp[i]) ))
            s+='.';
		s+=exp[i];

	}
	cout<<"The converted string is "<<s<<"\n";
	//converting the infix expression to postfix expression.

	for(int i=0;i<s.length();i++)
	{
		cout<<i<<"\n";
		if(isOperator(s[i]))
		{
			if(op.empty() || op.top() == '(')
			{
				op.push(s[i]);
			}
			else if(s[i] == '(')
				op.push(s[i]);
			else if(s[i] == ')')
			{
				while(op.top()!= '(')
				{
				 	posfix += op.top();
					op.pop();
				}
				op.pop();
			}
			else if(precedence(s[i])> precedence(op.top()))
			{
				op.push(s[i]);
			}
			else{
				while(!op.empty() && op.top()!='(' &&  precedence(op.top())>precedence(s[i]))
				{
					posfix += op.top();
					op.pop();
				}
				op.push(s[i]);
			}

		}
		else{
			posfix+=s[i];
		}
	}
	while(!op.empty())
	{
		posfix += op.top();
		op.pop();
	}
	return posfix;
}
