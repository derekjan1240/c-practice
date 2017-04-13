#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;
void bg(void);
void reset(void);
void ending(int score);
void gotoxy(int xpos, int ypos)
{
COORD scrn;
HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
scrn.X = xpos; scrn.Y = ypos;
SetConsoleCursorPosition(hOuput,scrn);
}


int main()
{
  bool again=true;

do{
    srand(time(NULL));
    int x,y,candy_x,candy_y,speed,lastdir=1,body=1,score=0,walktime=0; //snake,candy
    int snaketailx[100000]={};  //之後要改vetor !!
    int snaketaily[100000]={};

    bool play,eat,up,down,left,right;
    char changedir,nu=32;    //ascii:null
    char speedchose;

    right=true; //start
    play=true;
    eat=false;
    x=25,y=10; //出發位置

    candy_x=rand()%49+1;
    candy_y=rand()%19+1;

    bg();  //(x:0-50 y:0-20)

    gotoxy(15,8);
    cout<<"Welcome Snake GAME !!! ";
    gotoxy(13,10);
    cout<<"A.Easy   B.Hard   C.Crazy ";

    bool qq=true;

    do{
    speedchose=getch();

    if(speedchose=='a'||speedchose=='A')
    {speed=150;
    speedchose='e';
     qq=false;}
    else if(speedchose=='b'||speedchose=='B')
    {speed=100;
     speedchose='h';
     qq=false;}
    else if(speedchose=='c'||speedchose=='C')
    {speed=50;
     speedchose='c';
     qq=false;}
    }while(qq);

    reset();

    while(play)
    {
        gotoxy(0,21);
        //cout<<"candy_x ="<<candy_x;
        //cout<<"  candy_y ="<<candy_y<<endl;
        cout<<"Your Score= "<<score<<endl;

        snaketailx[walktime]=x;
        snaketaily[walktime]=y;

       if(!kbhit())
       {
         walktime++;

         if(right==true)
         {x++;}
         else if(up==true)
         {y--;}
         else if(left==true)
         {x--;}
         else if(down==true)
         {y++;}

         gotoxy(x,y);
         cout<<"o";

         if(walktime>=body)
         {
           gotoxy(snaketailx[walktime-body],snaketaily[walktime-body]);
           cout<<nu;
         }


         Sleep(speed);//速度控制
       }

       else
      {
       changedir = getch();  //輸入方向

       if((changedir=='d'||changedir=='D') && lastdir!=3 )
       {
           lastdir=1;//原本方向 1:d 2:w 3:a 4:s
           right=true,left=false,up=false,down=false;
       }

       else if((changedir=='w'||changedir=='W')&& lastdir!=4)
       {
           lastdir=2;
           up=true,right=false,left=false,down=false;
       }

       else if((changedir=='a'||changedir=='A')&& lastdir!=1)
       {
           left=true,right=false,up=false,down=false;
           lastdir=3;
       }

       else if((changedir=='s'||changedir=='S') && lastdir!=2)
       {
           down=true,right=false,left=false,up=false;
           lastdir=4;
       }

       }

       //candy -------------------------------------

        if(eat)
       {candy_x=rand()%49+1;
        candy_y=rand()%19+1;
        eat=false;}

        gotoxy(candy_x,candy_y);
        cout<<"@";

        if(candy_x == x && candy_y== y)  //eat=true
        {
            eat=true;
            body++;

            if(speedchose=='c')  //50
            {
                if(speed<30)
                {score+=20;}
                else
                {score+=8;}

            }
            else if(speedchose=='h') //100
            {
                if(speed<30)
                {score+=20;}
                else if(speed<80)
                {speed=50,score+=5;}
                else
                {score+=3;}
            }
            else if(speedchose=='e') //150
            {

                if(speed<30)
                {score+=20;}
                else if(speed<80)
                {speed=50,score+=5;}
                else if(speed<100)
                {score+=3;}
                else
                {score++;}
            }

            speed--;
            if(speed<10)
            {speed=10;}

            gotoxy(x,y);
            cout<<"o";
        }

    //die---------------------------------------------
       if(x>=50||x<=0||y>=20||y<=0)   //wall die
       {play=false;}

       int j;//clear xy

       for(j=(walktime-1);j>(walktime-body);j--) //body die
       {
          if(x==snaketailx[j] && y==snaketaily[j])
          {play=false;}
       }
    //---------------------------------------------
    }

    ending(score);

    char playagain;  //play again?
    bool dodo=false;

    do{
    playagain = getch();

    if(playagain=='y'||playagain=='Y')
    {
        again=true;
        dodo=false;
    }
    else if(playagain=='n'||playagain=='N')
    {
        again=false;
        dodo=false;
        system("CLS");
    }
    else
    {dodo=true;}
    }while(dodo);

    reset();
}while(again);

    return 0;
}

void bg()
{
    int i,j;

    for(i=0;i<51;i++)
    {gotoxy(i,0);
     cout<<"*";
     gotoxy(i,20);
     cout<<"*";}

    for(j=0;j<21;j++)
      {gotoxy(0,j);
       cout<<"*"<<endl;
       gotoxy(51,j);
       cout<<"*"<<endl;}
}

void ending(int score)
{
    int i,j;

    for(i=1;i<51;i++)       //reset display
    {
        for(j=1;j<20;j++)
        {
            gotoxy(i,j);
            cout<<" ";
        }
    }


    for(i=1;i<9;i++)
    {
       if(i>1)
       {
         gotoxy(20,i-1);
         cout<<"           ";
       }
        gotoxy(20,i);
        cout<<"GAME OVER!!";
        Sleep(180);
    }

    gotoxy(15,10);
    cout<<"Your Final Score: "<<score;
    gotoxy(15,12);
    cout<<"Play again?   <Y/N>";

}

void reset()
{
    int j,i;

    for(i=1;i<51;i++)       //reset display
    {
        for(j=1;j<20;j++)
        {
            gotoxy(i,j);
            cout<<" ";
        }
    }
}
