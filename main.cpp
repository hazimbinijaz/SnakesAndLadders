#include <iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
using namespace std;

void gotoRowCol(int rpos, int cpos)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    int xpos=cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

void wait(int d)
{
    for(int j=1;j<d;j++)
    {
        for(int i=1; i<=99999; i++)
            {

            }
    }
}

void Init(int Ppos[],int NOP,int Turn)
{
    for(int i=0;i<NOP;i++)
    {
        Ppos[i]=0;
    }
}

void PrintBox(int sr,int sc,int rdim,int cdim,char S)
{
  for(int ri=0;ri<rdim;ri++)
  {
      for(int ci=0;ci<cdim;ci++)
      {
          if(ri==0 || ri==rdim-1 || ci==0 || ci==cdim-1)
          {
              gotoRowCol(sr+ri,sc+ci);
              cout<<S;
          }
      }
  }
}

void PrintBoxNumber(int rdim,int cdim,int BN)
{
   int sr=((BN-1)/10)*rdim;
   int sc=((BN-1)%10)*cdim;
    PrintBox(sr,sc,rdim,cdim,-37);
}

void PrintNoInBox(int rdim,int cdim,int BN,int Num)
{
    int sr=((BN-1)/10)*rdim+(rdim/2);
    int sc=((BN-1)%10)*cdim+(cdim/2)-1;
    gotoRowCol(sr,sc);
    cout<<Num;
}

int BoxNumberToNumber(int num)
{
    int ri,ci;
    if(((num-1)/10)%2==0)
    {
        return num;
    }
    else
    {
        ri=(((num-1)/10)*10);
        ci=10-((num-1)%10);
        return ri+ci;
    }

}

void PrintGrid(int rdim,int cdim)
{
    int Num=100;
    for(int BN=1;BN<=100;BN++)
    {
        PrintBoxNumber(rdim,cdim,BN);
        PrintNoInBox(rdim,cdim,BN,101-BoxNumberToNumber(BN));
    }



}

void PrintBoxForSnakes(int sr,int sc,int rdim,int cdim,char S)
{
  for(int ri=0;ri<rdim;ri++)
  {
      for(int ci=0;ci<cdim;ci++)
      {
          if(ri==0 || ri==rdim-1 || ci==0 || ci==cdim-1)
          {
              gotoRowCol(sr+ri,sc+ci);
              cout<<S;
          }
      }
  }
}



void PrintCenter(int ri,int ci,int rdim,int cdim,int S)
{
 int   sr=ri+rdim/2;
 int  se=ci+cdim/2;
   gotoRowCol(sr,se);
   cout<<S;
}

void PrintSnakes(int rdim,int cdim,int Snakes[][2],int Ladders[][2],int NOL,int NOS,int ri,int ci)
{
    gotoRowCol(1,88);
    cout<<"SNAKES!";
    for(int s=0;s<NOS;s++)
    {
     int ss=Snakes[s][0],se=Snakes[s][1];
     PrintBox(ri,ci,rdim,cdim,-37);
     PrintCenter(ri,ci,rdim,cdim,ss);
     PrintBox(ri,ci+cdim,rdim,cdim,-37);
     PrintCenter(ri,ci+cdim,rdim,cdim,se);
     ri=ri+rdim;
     }
    ri=2;
    gotoRowCol(1,88+26);
    cout<<"Ladders!";
    for(int s=0;s<NOL;s++)
    {
     int ss=Ladders[s][0],se=Ladders[s][1];
     PrintBox(ri,ci+25,rdim,cdim,-37);
     PrintCenter(ri,ci+25,rdim,cdim,ss);
     PrintBox(ri,ci+cdim+25,rdim,cdim,-37);
     PrintCenter(ri,ci+cdim+25,rdim,cdim,se);
     ri=ri+rdim;

     }

}

void PrintDice(int rdim,int cdim)
{
    gotoRowCol(78,20);
    cout<<"DICE";

    gotoRowCol(75,25);
    PrintBoxForSnakes(75,25,rdim,cdim,-37);
}

int RollDice()
{
    int d,t=0;
    do
    {
        while(!kbhit())
        {
                d=rand()%6+1;
                gotoRowCol(77,28);
                wait(10);
                cout<<d;
            }
            if(d==6)
            {
                t++;
                gotoRowCol(72,18);
                cout<<"YOU GOT SIX! PRESS KEY TO ROLL DICE AGAIN! ";
                getch();
            }
            if(t==3)
            {
                return 0;
            }
            while(kbhit())
            {
                getch();
            }
    }

    while(d==6);

    return (6*t)+d;
}

void ChangePosition(int & Ppos,int Dice)
{
     Ppos=Ppos+Dice;
}

void PrintPlayerPos(int Ppos,int Turn,char S,int rdim,int cdim)
{

    int BN=Ppos;
    BN=101-BN;
    BN=BoxNumberToNumber(BN);
    int sr=((BN-1)/10)*rdim+(rdim/2)+1;
    int sc=((BN-1)%10)*cdim+(cdim/2)+1;

    if(Turn==0)
    {
      gotoRowCol(sr-2,sc-3);
    }
    else if(Turn==1)
    {
     gotoRowCol(sr-2,sc+1);
    }
    else if(Turn==2)
    {
     gotoRowCol(sr+2,sc-3);
    }
    else if(Turn==3)
    {
     gotoRowCol(sr+2,sc+2);
    }
//    gotoRowCol(sr-2,sc-3);
    cout<<S;
}

void InitSymbols(int NOP,char Psym[])
{
    for(int i=0;i<NOP;i++)
    {
        cout<<"Enter Symbols: ";
        cin>>Psym[i];
    }
}

bool CheckForSnakes(int Snakes[][2],int NOS,int & Ppos)
{
    for(int s=0;s<NOS;s++)
    {
        if(Snakes[s][0]==Ppos)
        {
            Ppos=Snakes[s][1];
            return true;
        }
    }
    return false;
}

bool CheckForLadders(int Ladders[][2],int NOL,int & Ppos)
{
    for(int l=0;l<NOL;l++)
    {
        if(Ladders[l][0]==Ppos)
        {
            Ppos=Ladders[l][1];
            return true;
        }
    }
    return false;
}

void TurnChange(int&Turn,int NOP)
{
    Turn=(Turn+1)%NOP;
}



int main()
{
    int NOP;
    cout<<"Enter The number of players: ";
    cin>>NOP;
    char Psymbol[NOP];
    InitSymbols(NOP,Psymbol);
    int Turn=0,Dim,Dice,Rows=100,Cols=100,rdim=Rows/13,cdim=Cols/12;
    int NOS,Winners[NOP],Wi=0;
    ifstream SR("Snakes.txt");
    SR>>NOS;
    int Snakes[NOS][2];
    for(int s=0;s<NOS;s++)
    {
        int ss=0,se=0;
        SR>>ss>>se;
        Snakes[s][0]=ss;
        Snakes[s][1]=se;
    }
    int NOL;
    ifstream LR("Ladders.txt");
    LR>>NOL;
    int Ladders[NOS][2];
    for(int l=0;l<NOL;l++)
    {
     int ls=0,le=0;
     LR>>ls>>le;
     Ladders[l][0]=ls;
     Ladders[l][1]=le;
    }

    int PlayerPos[NOP];
    Init(PlayerPos,NOP,Turn);
    system("cls");
    PrintGrid(rdim,cdim);
    int ri=2,ci=88;
    PrintSnakes(rdim,cdim,Snakes,Ladders,NOL,NOS,ri,ci);
    PrintDice(rdim,cdim);
    gotoRowCol(74,20);
    cout<<"Press Enter to roll the dice: ";
    getch();
    do
    {
    Dice=RollDice();
    int PrevPos=PlayerPos[Turn];
    ChangePosition(PlayerPos[Turn],Dice);
    gotoRowCol(74,20);
    cout<<"Press any key to move your character: ";
    getch();

    PrintPlayerPos(PrevPos,Turn,' ',rdim,cdim);
    PrintPlayerPos(PlayerPos[Turn],Turn,Psymbol[Turn],rdim,cdim);
    if(PlayerPos[Turn]>=90)
    {
        cout<<"";
    }

    if(CheckForSnakes(Snakes,NOS,PlayerPos[Turn])==true)
    {
        gotoRowCol(71,20);
        cout<<"You have bitten by a snake!";
        PrintPlayerPos(PrevPos+Dice,Turn,' ',rdim,cdim);
        PrintPlayerPos(PlayerPos[Turn],Turn,Psymbol[Turn],rdim,cdim);
    }
    if(CheckForLadders(Snakes,NOS,PlayerPos[Turn])==true)
    {
        gotoRowCol(72,20);
        cout<<"You have a Ladder in your way!";
        PrintPlayerPos(PrevPos+Dice,Turn,' ',rdim,cdim);
        PrintPlayerPos(PlayerPos[Turn],Turn,Psymbol[Turn],rdim,cdim);
    }
    if(PlayerPos[Turn]==100)
    {
        Winners[Wi]=Turn;
        Wi++;
        gotoRowCol(52,80);
        cout<<"PLAYER"<<Turn<<"WINS!";
    }
    do
    {
        TurnChange(Turn,NOP);
    }
    while(PlayerPos[Turn]==100);
    getch();
  }
  while(Wi<NOP-1);
    getch();
    system("cls");
    for(int i=0;i<NOP;i++)
    {
        cout<<"Player"<<Winners[0]<<+1<<"Wins "<<i+1<<endl;
    }
    return 0;
}
