#include "utilities.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;

const char WORDFILENAME[] = "/Users/onehodge/Desktop/wordle_1/wordle/words.txt";
const char VOCABFILENAME[] = "/Users/onehodge/Desktop/wordle_1/wordle/vocabs.txt";

char w[3000][MAXWORDLEN+1],v[140000][MAXWORDLEN+1];
int n = getWords(w, 3000, WORDFILENAME);
int n2 =getWords(v, 14000, VOCABFILENAME);
int rnd=0,addrnd,randi,score,mini,maxi;double sum=0,avg;

bool checkLower(const char theWord[])
{
    for(int i=0;i<strlen(theWord);i++)
        if(!islower(theWord[i])) return false;
    return true;
}

bool checkVocab(const char theWord[])
{
    for(int i=0;i<n2;i++)
        if(strcmp(v[i],theWord)==0) return true;
    return false;
}

int playOneRound(int wordnum)
{
    char ans[MAXWORDLEN+1],jud[MAXWORDLEN+1],guess[110];
    int cnt=0,alphabet[30];memset(alphabet, 0, sizeof(alphabet));
    while(cin>>guess)
    {
        strcpy(ans,w[wordnum]);
        if(strcmp(guess,"codewordhaoji")==0)
            {cout<<ans<<endl;continue;}
        if(strlen(guess)!=strlen(ans))
            {cout<<"The hidden word is 5 letters long."<<endl;continue;}
        if(!checkLower(guess))
            {cout<<"Put them in lower case letters."<<endl;continue;}
        if(!checkVocab(guess))
            {cout<<"I don't know that word."<<endl;continue;}
        cnt++;
        if(strcmp(guess,ans)==0) break;
        strcpy(jud,"_____");
        for(int i=0;i<strlen(guess);i++)
            if(guess[i]==ans[i])
            {
                jud[i]='G';
                alphabet[guess[i]-'a']=3;
                ans[i]='X';guess[i]='Y';
            }
        for(int i=0;i<strlen(guess);i++)
            for(int j=0;j<strlen(ans);j++)
                if(guess[i]==ans[j])
                {
                    jud[i]='Y';
                    alphabet[guess[i]-'a']=2;
                    ans[j]='X';guess[i]='Y';
                }
        cout<<jud<<endl;
    }
    cout<<"THATS RIGHT!"<<endl<<endl;
    return cnt;
}

void letsPlay()
{
    cout<<endl<<"Now how many rounds do you want to play? "; cin>>addrnd;
    if(addrnd<=0) cout<<"Talk to me when you've made your mind!"<<endl;
    for(int i=rnd+1;i<=rnd+addrnd;i++)
    {
        cout<<endl<<"Round "<<i<<endl;
        randi=randInt(0,n-1);
        cout<<"Take your first guess!"<<endl;
        score=playOneRound(randi);
        if(score==1) cout<<"You got it in 1 try. Damn!"<<endl;
        else cout<<"You got it in "<<score<<" tries."<<endl;
        if(i==1) {mini=score;maxi=score;}
        else {mini=min(score,mini);maxi=max(score,maxi);}
        sum+=score;avg=sum/i;
        cout<<fixed;cout<<setprecision(2);
        cout<<"Average: "<<avg<<", minimum: "<<mini<<", maximum: "<<maxi<<endl;
    }rnd+=addrnd;
    
}

int main()
{
    if(n<1||n2<1) {cout<<"No words were loaded, so I can't play the game."<<endl;return 0;}
    
    cout<<"Welcome to the C++ Wordle game."<<endl;
    cout<<"First off let me explain the rules real quick:"<<endl;
    cout<<"It's basically the same Wordle game."<<endl;
    cout<<"But since we can't display different colors here, the green blocks are shown as \"G\", and the yellow ones as \"Y\"."<<endl;
    cout<<"Let's get it!"<<endl;
    letsPlay();
    char x,y;cout<<endl<<"Do you want to keep playing? (Y/N) ";cin>>x;
    while(x=='Y'||x=='y')
    {
        cout<<endl<<"Do you want to reset the scores? (Y/N) ";cin>>y;
        if(y=='Y'||y=='y') {sum=0;rnd=0;}
        letsPlay();
        cout<<"Do you want to keep playing? (Y/N) ";cin>>x;
    }
    cout<<endl<<"See you next time!"<<endl;
    return 0;
}
