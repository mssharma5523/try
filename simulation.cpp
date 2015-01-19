#include "common_headers.h"
#include "simulation.h"

//converting a character to the corresponding integer used a-'1' and b-'2' and eps-0
int conv_int(char c)
{
    if(c == 'a')
        return 1;
    else if(c == 'b')
        return 2;
    else if(c == 'e')
        return 0;
    else 
        return -1;
}

//This function simulates the DFA formed by the regex expression and tests if that string belongs to that regex or not..
void simulate()
{
    int N, M, F, X, Y, A, state, symbol;
    char* p;
    int i,j;
    int t;
    bool flag;
    // read in the underlying DFA
    ifstream fin("DFA.txt");
    fin >> N >> M >> F;
    for(i=0; i<F; i++)  {
        fin >> X;
        finalStates[X] = true;
    }
    memset(transitions, -1, MAX_DFA_STATES * MAX_ALPHABET_SIZE * sizeof(int));
   fin>>t;
    while(!fin.eof())   {
        fin >> X >> A >> Y;
        transitions[X][A] = Y;
    }
    fin.close();

    // check if the DFA is well defined
    for(i=0; i<N; i++)
        for(j=1; j<=M; j++)
            if(transitions[i][j] < 0 || transitions[i][j] >= N) {
                printf("DFA not defined properly.\n");
                return;
                //exit(1);
            }

    //  the DFA
    string str;
    printf("Enter a string ('.' to exit) : ");
    cin>>str;
    
    while(str != ".")   {
    state = 0;
    for(int i=0;i<str.length();i++){
        char ch=str[i];
        flag = true;
            //symbol = atoi(&ch);
        symbol = conv_int(str[i]);          
        if(symbol < 0 || symbol > M)   {
                printf("Invalid input symbol %c\n", str[i]);
                flag = false;
                break;
            } 
            else {
            if(symbol!=0){
                    state = transitions[state][symbol];
                
            }
                //cout<<"state is"<<state<<endl;
            }
            //p = strtok(NULL, " ");
        }
        if(finalStates[state] && flag)
            printf("String accepted.\n");
        else
            printf("String rejected.\n");
    
      
           printf("Enter a string ('.' to exit) : ");
           cin>>str;
    }
    return;
}