#include<fstream.h> 
#include<conio.h>
#include<string.h>	//including header files #include<stdio.h>
#include<stdlib.h> 
#include<graphics.h> 
#include<dos.h>

class Game
{
    public: 
        void welcome_screen();	//function prototypes 
        void main_menu();
        void report_menu(); 
        void user_menu(); 
        void instructions(); 
        void play_game(); 
        void highscore(); 
        void exit_screen();
        int check(char[][15],int);
}

class UserScore	//class `UserScore' for user's info.
{
    int score,no_of_words; 
    float performance;
    char name[40];	        //private data members 
    struct date dt_of_play;

    public:

    void indata(int s,int n)	//to input data of user
    { 
        cout<<"Enter Name of User: "; 
        gets(name);	                //name
        score=s;	                //score
        no_of_words=n;	            //no. of words 
        performance=((s*100.0)/n);	//perform
        getdate(&dt_of_play);	    //date
    }
 
    void outdata(int x,int y)	//to display data of user
    {
        gotoxy(x,y); 
        cout<<"Name: "<<name; 
        y++;

        gotoxy(x,y);
        cout<<"Score: "<<score<<" / "<<no_of_words; 
        y++;

        gotoxy(x,y);
        cout<<"Performance: "<<performance<<" %"; 
        y++;

        gotoxy(x,y);
        printf("Date: %d/ %d/ %d", dt_of_play.da_day, dt_of_play.da_mon, dt_of_play.da_year);
    }

    float get_performance()	//to get performance % for sorting
    {
        return performance;
    }

    void write_to_bfile(UserScore &us) //write into the binary file
    {
        fstream f("Spellathon.dat",ios::binary|ios::app);

        if(f.good())	//returns non-zero value if no error has occurred
        { 
            f.write((char*)&us,sizeof(us)); 
        }

        else	//if(f.good()==0)
        { 
            cout<<"An ERROR has occurred ";
        }

        f.close();
    }

};	//end of class `UserScore’
 
void Game::welcome_screen()	//welcome screen
{
    cleardevice();
    setcolor(BLUE);	//set text color as blue 
    setlinestyle(0,0,3);
    rectangle(5,5,635,475);	//border

    setbkcolor(WHITE);	//white background 
    settextstyle(1,0,4);

    outtextxy(90,125," COMPUTER SCIENCE PROJECT"); 
    outtextxy(105,185," SPELLATHON : WORD GAME");
    
    char ch;

    settextstyle(1,0,3);
    outtextxy(150,310," Press `Y' for Main Menu... "); 
    ch=getch();	//choice from user

    if(ch=='y' || ch=='Y')
    { 
        main_menu(); 
    }

    else
    { 
        welcome_screen(); 
    }

}


void Game::main_menu()	//main menu of the game
{
    int choice; 
    
    cleardevice();
    setbkcolor(LIGHTRED);	//background and text color 
    setcolor(WHITE);
 
    setlinestyle(0,0,3);
    rectangle(5,5,635,475);	//border

    settextstyle(1,0,4);
    outtextxy(200,7," **MAIN MENU** ");

    setlinestyle(1,0,3); 
    line(220,50,450,50);

    settextstyle(1,0,2);

    outtextxy(50,60," Press 1 for User menu "); 
    outtextxy(50,90," Press 2 for Report "); 
    outtextxy(50,120," Press 3 to Exit ");

    line(100,160,550,160);

    char ch;

    outtextxy(50,169," Enter your choice: ");
    ch=getch();	//choice from user 
    
    choice=ch-48;
    gotoxy(32,15);

    if(choice==1)
    { user_menu(); }

    else if(choice==2)
    { report_menu(); }

    else if(choice==3)
    { exit_screen(); }

    else
    { main_menu(); }

}
 

void report_menu()	//function to display game report
{
    cleardevice();

    setlinestyle(0,0,3);
    rectangle(5,5,635,475);	//border

    setbkcolor(LIGHTBLUE);	//background and text color 
    setcolor(WHITE);

    settextstyle(1,0,5); 
    outtextxy(135,40,"**REPORT MENU**");

    setlinestyle(1,0,3); 
    line(140,95,500,95);

    UserScore us, us_high, us_low;	//objects of class `UserScore' 
    fstream f("Spellathon.dat",ios::in|ios::binary);

    if(f.good())	//returns non-zero value if no error has occurred
    {
        f.read((char*)&us,sizeof(us));	//read from binary file 
        
        float sum=0.0,avg,l,s,t;
        float t1=us.get_performance(),
        l=t1; 
        s=t1;

        while(!f.eof())
        {
            t=us.get_performance();
            sum+=us.get_performance(); //sum to calculate avg. performance 
            
            if(t>=l)
            { 
                l=t;
                us_high=us;	//to get highest performance %
            }
 
            if(t<=s)
            { 
                s=t;
                us_low=us;	//to get lowest performance %
            }

            f.read((char*)&us,sizeof(us));

        }
        
        f.seekg(0,ios::end);	//seeking cursor to the end 
        
        long int m=f.tellg();
        int k=m/sizeof(us);	//to get no. of records in the file

        //details 
        gotoxy(20,8);        
        cout<<"Number of players who played Spellathon: "<<k;

        gotoxy(35,10); 
        cout<<"Highest score: "; 
        us_high.outdata(28,11);

        gotoxy(35,17); 
        cout<<"Lowest score: "; 
        us_low.outdata(28,18);

        gotoxy(20,23); 
        avg=(sum)/k;
        cout<<"Average Performance of players : "<<avg<<" %";

    }

    else	//if(f.good()==0)
    { 
        cout<<"An ERROR has occured in opening the file"; 
    } 
    
    char ch;
    
    gotoxy(28,25);
    cout<<"Back to MAIN MENU ?(Y/N): ";
    ch=getch();	//choice from user f.close();
 
    if(ch=='y' || ch=='Y')
    { main_menu(); }

    else
    { report_menu(); }

}


void Game::user_menu()	//function to display user-related menu
{	
    cleardevice();

    int choice; 
    char ch;

    setbkcolor(LIGHTRED);	//background and text color 
    setcolor(WHITE);

    setlinestyle(0,0,3);
    rectangle(5,5,635,475);	//border 
    
    settextstyle(1,0,4);
    outtextxy(200,7," **USER MENU** ");

    setlinestyle(1,0,3); 
    line(200,50,450,50);

    settextstyle(1,0,2);
    outtextxy(50,60," Press 1 for Instructions "); 
    outtextxy(50,90," Press 2 to Play "); 
    outtextxy(50,120," Press 3 to Display Highest Score"); 
    outtextxy(50,150," Press 4 to go back to MAIN MENU");

    line(100,185,550,185);

    outtextxy(50,190," Enter your choice:"); 
    gotoxy(38,26);
 
    ch=getch();	//choice from user 
    
    choice=ch-48;
    
    if(choice==1)
    { instructions(); }

    else if(choice==2)
    { play_game(); }

    else if(choice==3)
    { highscore(); }

    else if(choice==4)
    { main_menu(); }

    else
    { user_menu(); }

}

void Game::instructions()	//function to display the instructions
{
    cleardevice();

    setlinestyle(0,0,3);
    rectangle(5,5,635,475);	//border

    setbkcolor(LIGHTBLUE);	//background and text color 
    setcolor(WHITE);

    settextstyle(1,0,4); 
    outtextxy(185,9,"**INSTRUCTIONS**");

    setlinestyle(1,0,3); 
    line(200,50,450,50);

    settextstyle(1,0,1);

    //to open text file `Instruct.txt'
    ifstream f("C:\\TURBOC3\\Projects\\prj\\Instruct.txt"); char word[70],ch;
 
    int x=18,y=70;

    while(!f.eof())
    {
        f.getline(word,70,'\n');	//reading string from file 
        outtextxy(x,y,word);
        y=y+20;
    }

    f.close();

    ch=getch();	//choice from user 
    
    if(ch=='y' || ch=='Y')
    { user_menu(); }

    else
    { instructions(); }

}


int Game::check(char A[][15],int pos)
{		//function to check repetition of the word 
    
    int i,count;

    for(i=0;i<=(pos-1);i++)
    { 
        count=0;

        if(strcmpi(A[i],A[pos])==0)
        { 
            count++; 
            break;
        }
    }

    if(count)
    { return 1; }	//if word is repeated

    else
    { return -1; }	//if word is not repeated
}
 
void Game::play_game()	//function to play the game
{

    cleardevice();

    setbkcolor(LIGHTBLUE);	//to set background color 
    setlinestyle(0,0,3);
    rectangle(5,5,635,475);	//border 
    
    outtextxy(225,7," **PLAY GAME** ");
    
    randomize();	//randomize function 
    char string[5];

    //path of the question and answer files
    char questionfile[60]="C:\\TURBOC3\\Projects\\prj\\q"; 
    char answerfile[60]="C:\\TURBOC3\\Projects\\prj\\ans";

    int t=(random(11)+1);   //random values between 1 and 11

    itoa(t,string,10);

    strcat(questionfile,string); 
    strcat(questionfile,".txt");

    strcat(answerfile,string); 
    strcat(answerfile,".txt");

    ifstream fquestion(questionfile);	//opening question file 
    
    char ch,letter[2];
    int row=1, x=470,y,c=1,n;

    fquestion.get(ch);	//to read character
 
    while(!fquestion.eof())
    {		//to display the letters of the puzzle 
        letter[0]=ch;
        letter[1]='\0';

        if(row==1 && c<=2)
        { 
            y=60;
            outtextxy(x,y,letter); 
            x=x+50;
            c++;

            if(c==3)
            { 
                row++;	//to come to next row 
                x=446;
            }
        }

        else if(row==2 && c<=5)
        {
            y=105;

            outtextxy(x,y,letter); 
            
            x=x+48;
            c++;

            if(c==6)
            { 
                row++;
                x=470;	//to come to next row
            }

        }

        else if(row==3 && c<=7)
        {
            y=145;
            
            outtextxy(x,y,letter);
 
            x=x+50; 
            c++;

            if(c==8)	//to read a number which tells
            { fquestion>>n; }	//how many words can be formed
        }

        fquestion.get(ch);
    }

    fquestion.close();

    //to draw hexagons and lines 
    int poly[13];
    setcolor(YELLOW); //for the yellow lines

    poly[0] = 500;
    poly[1] = 30;

    poly[2] = 570;
    poly[3] = 80;

    poly[4] = 570;
    poly[5] = 150;

    poly[6] = 500;
    poly[7] = 200;

    poly[8] = 430;
    poly[9] = 150;

    poly[10] = 430;
    poly[11] = 80;
    
    //drawpoly doesn't close automatically ,so we close it 
    poly[12] = poly[0];
    poly[13] = poly[1];
 
    drawpoly(7, poly);	//to draw bigger hexagon

    line(500,90,500,30);
    line(522,105,570,80);	//lines to connect 2 hexagons 
    line(522,125,570,150);
    line(500,140,500,200); 
    line(478,125,430,150); 
    line(478,105,430,80);

    poly[0] = 500;
    poly[1] = 90;

    poly[2] = 522;
    poly[3] = 105;

    poly[4] = 522;
    poly[5] = 125;

    poly[6] = 500;
    poly[7] = 140;

    poly[8] = 478;
    poly[9] = 125;

    poly[10] = 478;
    poly[11] = 105;

    //drawpoly doesn't close automatically ,so we close it 
    poly[12]=poly[0];
    poly[13] = poly[1];

    drawpoly(7, poly);	//to draw smaller hexagon 
    
    gotoxy(5,3);
    cout<<"Maximum number of words that can be formed: "<<n;

    char A[25][15] , B[10];
    //declaring character and other variables
    int score=0,y_cord=4,life=3;
 
    gotoxy(5,y_cord); 
    cout<<"Enter words: ";
    y_cord++; 
    
    gotoxy(50,15);
    cout<<" LIFELINES remaining= 3";

    for(int i=0; i<=(n-1) ;i++)
    {
        l: gotoxy(5,y_cord); 
        cout<<"Word "<<i+1<<": ";
        gets(A[i]);	//taking word from the user
        
        int repeat=check(A,i);	//to check for repetition 
        
        if(repeat==-1)	//if word is not repeated
        {
            int right=0;
            ifstream fanswer(answerfile); 
            
            while(!fanswer.eof())
            {		//to read answers from file 
                fanswer.getline(B,15,'\n');

                if(strcmpi(B,A[i])==0)
                { 
                    right++;	//if answer is correct 
                    score++;
                }

            }

        fanswer.close();

        if(right==1)	//if answer is correct
        {
            gotoxy(25,y_cord); 
            cout<<"Correct";
        }
 
        if(right==0 && life>0)	//if answer is incorrect
        { 
            if(life!=1)
            {
                gotoxy(25,y_cord); 
                cout<<"Incorrect, Enter again";
            }

            if(life==1)
            {
                gotoxy(25,y_cord); 
                cout<<"Incorrect";
            }

            gotoxy(50,15);
            cout<<" LIFELINES remaining= "<<life-1;

            life--; 
            y_cord++;

            if(life==1)
            {
                gotoxy(50,16);
                cout<<"This is your LAST LIFELINE";
            }

            if(life==0)	//when no LIFELINE is left
            {
                y_cord++; 
                gotoxy(20,y_cord); 
                cout<<"GAME OVER";

                gotoxy(50,16);
                cout<<"	GAME OVER	";

                break;
            }

            goto l;
        }

        }
 
        else	//if word is repeated
        {
            gotoxy(25,y_cord); 
            cout<<"Word already entered!"; 
            y_cord++;
            goto l;
        }

        y_cord+=1;

    }	//end of 'for' loop

    UserScore us; 
    gotoxy(5,23);

    us.indata(score,n);		//to input details from the user 
    us.write_to_bfile(us);	//to write into the binary file 
    
    rectangle(400,300,620,400);
    gotoxy(58,20);
    cout<<" SCORE CARD ";

    us.outdata(55,22);	//to display details of the user 
    gotoxy(5,25);
    cout<<"Back to USER MENU ?(Y/N): "; 
    ch=getch();	//choice from user

    if(ch=='y' || ch=='Y')
    { user_menu(); }

}


void Game::highscore()	//function to display the highest score
{
    cleardevice();

    setlinestyle(0,0,3); 
    rectangle(5,5,635,475);	//border
 
    setbkcolor(LIGHTBLUE);	//background and text color 
    setcolor(WHITE);

    settextstyle(1,0,5); 
    outtextxy(135,50,"**HIGHEST SCORE**");

    setlinestyle(1,0,3); 
    line(140,110,500,110);

    UserScore us,us_high;	//declaring objects fstream f("Spellathon.dat",ios::in|ios::binary);
    
    if(f.good())
    {
        f.read((char*)&us,sizeof(us));	//to read from binary file

        while(!f.eof())
        {
            float temp=us.get_performance();

            if(temp>0.0)	//to get highest performance %
            { us_high=us; } 
            
            f.read((char*)&us,sizeof(us));
        }

        gotoxy(22,12);
        cout<<"Details of the player with HIGHEST SCORE";

        us_high.outdata(30,15);	//to display details of high-scorer
    }

    else	//if(f.good()==0)
    { 
        cout<<"An ERROR has occurred in opening the file";
    } 
    
    f.close();

    char ch;
 
    gotoxy(27,25);

    cout<<"Back to USER MENU ?(Y/N): ";
    ch=getch();	//choice from user

    if(ch=='y' || ch=='Y')
    { user_menu(); }

    else
    { highscore(); }

}

void Game::exit_screen()	//exit message
{
    cleardevice();

    setcolor(BLUE);	//set text color as blue 
    setlinestyle(0,0,3);

    rectangle(5,5,635,475);	//border 
    setbkcolor(WHITE);
    settextstyle(1,0,4);

    outtextxy(200,125," THANK YOU !! "); 
    outtextxy(100,185," FOR PLAYING SPELLATHON .");

    char ch;

    settextstyle(1,0,3);
    outtextxy(200,310," Press `E' to EXIT... ");
    
    ch=getch();	//to exit from the game 
    
    if(ch=='e' || ch=='E')
    { exit(0); }

    else
    { exit_screen(); }

}
 
void graph_check()
{
    // initialize graphics and local variables
    int gdriver = DETECT, gmode,errorcode;

    
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

    // read result of initialization 
    errorcode = graphresult();

    if(errorcode != grOk)   // an error occurred
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode)); 
        printf("Press any key to halt:");
        getch();
        
        // terminate with an error code 
        exit(1);
    }
}


void main()
{
    clrscr();

    Game g;

    graph_check();	//to check graphics

    g.welcome_screen();	//welcome message

    g.main_menu();	//main menu
    
    getch();
    
    closegraph();
}
 
