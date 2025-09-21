#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <random>
#include <algorithm>
#include <iomanip>
using namespace std;

void error(string s) 
{
    throw runtime_error(s);
}

ifstream is{"qna.txt"}; //open qna.txt  for reading 
class Stats 
{
    int heart;
    
    public:
    string name;
    Stats(int h,string n)
    {
        heart=h;
        name=n;
    }
    Stats()
    {
        heart=3;
    }
    int dispheart(){return heart;}
    void lose(){ heart--;}
};

class Mcq_ques //store question,answer and their explaination 
{
public:
vector <string> ques;
vector <char> ans;
vector <string> expl;
};

Mcq_ques shuffle_ques(Mcq_ques M); 
istream& operator >>(istream& is,Mcq_ques& M)  //input operator to input from file
{//change istream to bad state if input isn't formatted correctly
   string s,str;
   while(is>>s)
   {
    if(s!="Ques{")
    { 
        is.clear(ios_base::badbit);
        return is;
    }    
    for(is>>s;s!="}~";is>>s)
    {
        str=str+s+' ';
    }
    M.ques.push_back(str);
    str="\0";
    is>>s;
    if(s!="Ans{")
    {
        M.ques.pop_back();
        is.clear(ios_base::badbit);
        return is;
    }
    char ch1='\0';
    is>>ch1>>s;
    if(s!="}~")
    {
        M.ques.pop_back();
        is.clear(ios_base::badbit);
        return is;
    }
    else M.ans.push_back(ch1);
    string Ex,Exp;
    is>>Ex;
    if(Ex!="Expl{")
    {
        is.clear(ios_base::badbit);
        M.ques.pop_back();
        M.ans.pop_back();
        return is;
    }
    for(is>>Ex;Ex!="}~";is>>Ex)
    {
        Exp=Exp+Ex+' ';
    }
    M.expl.push_back(Exp);
   } 
   return is;
}

ostream& operator <<(ostream& os,Stats& S) //output operator for Stat
{
      return os<<setw(10)<<S.name<<'\t'<<S.dispheart()<<"❤️";
}

void printresult();
Stats MC;
Stats Enemy{5,"Skeleton"}; //create Enemy  

void battle(Mcq_ques M,int round);  
char select_option();
bool game_end();
int  main()
try{
if(!is) error("couldn't open the file qna.txt"); 
Mcq_ques M;
is>>M;
if(is.bad()) 
    error("The input isn't formatted correctly");
M={shuffle_ques(M)}; //shuffle question order
if(M.ques.size()<(MC.dispheart()+Enemy.dispheart()-1)) 
    error("Not enough questions to complete the game");
string mc_name;
cout<<"Enter your name : ";
cin>>mc_name;
MC.name=mc_name;
printresult(); 
for(int round=0;round<M.ques.size();round++) //run the game till Enemy or MC heart reaches zero
{
battle(M,round);
if(game_end())
    return 0;
}
}
catch(exception& e) //catch runtime exceptions and disp error msg
{
    cout<<"error: "<<e.what();
    return 1;
}
void printresult() //print Name,Stat of both MC and Enemy
{
   cout<<"____________________________________________________________"<<'\n'
       <<MC<<'\n'<<Enemy<<'\n'
       <<"____________________________________________________________"<<'\n';
}

void battle(Mcq_ques M,int round) //runs a round 
{//outputs the question and read an option from user
    cout<<M.ques[round]<<'\n'; 
    char answer;
    answer=select_option();
    if(M.ans[round]==answer) //if answer is correct Enemy lose a heart
    {
        Enemy.lose(); 
        cout<<"Correct!!"<<'\n'
            <<M.expl[round]<<'\n';
    }        
    else //else MC loses a heart
    {  
        MC.lose();
        cout<<"Wrong!! the correct option was "<<M.ans[round]<<'\n';
        cout<<M.expl[round]<<'\n';
    }    
    printresult();      
}

char select_option() //convert lower,upper,num to options and read till the input isn't a valid option
{
    char option;
    bool cond=true;
    while(cond)
    {
    cin.clear();
    cin>>option;
    switch(option)
    {
    case '1': case 'A': case 'a':
        option='a';
        cond=false;
        break;
    case '2': case 'B': case 'b':
        option='b';
        cond=false;
        break;
    case '3': case 'C': case 'c':
        option='c';
        cond=false;
        break;
    case '4': case 'D': case 'd':
        option='d';
        cond=false;
        break;
    default:
        cout<<"Please select a valid option ";    
    }}
    return option;
}

bool game_end() //return true if MC or Enemy heart reaches zero 
{
    if(MC.dispheart()==0)
    {
        cout<<"\n -------You lose-------\n";
        return 1;
    }
    else if(Enemy.dispheart()==0)
    {
        cout<<"\nCongratulations!!"
            <<"\n-------You Won-------\n";
        return 1;
    }
    else return 0;
}

Mcq_ques shuffle_ques(Mcq_ques M) //shuffle the order of questions and their answers and explanation
{
    Mcq_ques M2{M};
    random_device rd;
    mt19937 g(rd());
    shuffle(M.ques.begin(),M.ques.end(),g);
    for(int i=0;i<M.ques.size();i++)
    {
        for(int j=0;j<M2.ques.size();j++)
        {
            if(M.ques[i]==M2.ques[j])
            {
                M.ans[i]=M2.ans[j];
                M.expl[i]=M2.expl[j];
            }
        }
    }
    return M;
}
