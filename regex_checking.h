#ifndef REGEX_CHECKING_H_INCLUDED
#define REGEX_CHECKING_H_INCLUDED


//using namespace std;

bool isOperator(char c);
bool isCorrect_regex(string s);
string parenthesised_regex(string s);
int precedence(char c);
string infixTopostfix(string exp);

#endif // REGEX_CHECKING_H_INCLUDED
