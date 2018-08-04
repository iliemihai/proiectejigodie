#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <time.h>
#include "SDL.h"
#include <deque>


using namespace std;


char tab[23][10];
deque<pair<int,int> >  sarpe;
bool stare;

void sleep( time_t delay )
{
		time_t timer0, timer1;
		time( &timer0 );
	do {
		time( &timer1 );
	}while (( timer1 - timer0 ) < delay );
}

void tabel(deque<pair<int,int> > &sarpe,int &x,int &y)
{

	int i=0,j=0;
	for(i=1;i<22;i++)	
		for( j=1;j<9;j++)
			tab[i][j] = ' ';
	for(i=0;i<23;i++)
		 {
		 	tab[i][0] = '*';
		 	tab[i][9] ='*';
		 }
	for( j=0;j<10;j++)
		{
			tab[0][j] = '*';
			tab[22][j] = '*';
		}
		
	for(int i=0;i<sarpe.size();i++)
		tab[sarpe[i].first][sarpe[i].second]='0';
		
		tab[x][y]='M';
	

	for(i=0;i<23;i++)
		{for(j=0;j<10;j++)
		cout<<tab[i][j];
		cout<<endl;}
		 
	 	
} 


int mergiSus(int &c,int &d,deque<pair<int,int> > &sarpe,bool &stare,int &x,int &y)
{
	
		c--;
		if(tab[c][d] == 'M') 
	{
		
			srand(time(NULL));
			x=rand()%22;
			y=rand()%9;
			if(tab[x][y]=='*' || tab[x][y]=='0') {
				x=rand()%22;
				y=rand()%9;
			}
		tab[x][y]='M';
			sarpe.push_back(make_pair(c,d));
			
	}
	else if(tab[c][d] == '*' || tab[c][d] == '0' )
		stare=false;
	else
	{
		sarpe.push_back(make_pair(c,d));
		sarpe.pop_front(); 
		

	}	
		tabel(sarpe,x,y); 

}

int mergiJos(int &c,int &d,deque<pair<int,int> > &sarpe,bool &stare,int &x,int &y)
{

	 
		c++;
		if(tab[c][d] == 'M') 
	{	
		
			srand(time(NULL));
			x=rand()%22;
			y=rand()%9;
			if(tab[x][y]=='*' || tab[x][y]=='0') {
				x=rand()%22;
				y=rand()%9;
			}
		tab[x][y]='M';
			sarpe.push_back(make_pair(c,d));
		 
	}
	else if(tab[c][d] == '*' || tab[c][d] == '0' )
		stare=false;
	else
	{
		sarpe.push_back(make_pair(c,d));
		sarpe.pop_front(); 
		
	}	
		tabel(sarpe,x,y);  
}

int mergiStanga(int &c,int &d,deque<pair<int,int> > &sarpe,bool &stare,int &x,int &y)
{ 
	 
	d--;
		if(tab[c][d] == 'M') 
	{
		
			srand(time(NULL));
			x=rand()%22;
			y=rand()%9;
			if(tab[x][y]=='*' || tab[x][y]=='0') {
				x=rand()%22;
				y=rand()%9;
			}
		tab[x][y]='M';
			sarpe.push_back(make_pair(c,d));
		 	
	}
	else if(tab[c][d] == '*' || tab[c][d] == '0' )
		stare=false;
	else
	{
		sarpe.push_back(make_pair(c,d));
		sarpe.pop_front();  
			
	}	
		tabel(sarpe,x,y);
	}

int mergiDreapta(int &c,int &d,deque<pair<int,int> > &sarpe,bool &stare,int &x,int &y)
{
	 
	d++;
		if(tab[c][d] == 'M') 
	{
		
			srand(time(NULL));
			x=rand()%22;
			y=rand()%9;
			if(tab[x][y]=='*' || tab[x][y]=='0') {
				x=rand()%22;
				y=rand()%9;
			}
		tab[x][y]='M';
			sarpe.push_back(make_pair(c,d));
		 
	}
	else if(tab[c][d] == '*' || tab[c][d] == '0' )
		stare=false;
	else
	{
		sarpe.push_back(make_pair(c,d));
		sarpe.pop_front();  
		 

			
	}	
		tabel(sarpe,x,y); 
}

void mancare(char  tab[23][10]) {
	int  x,y;
	srand(time(NULL));
		x=rand()%22;
		y=rand()%9;
	tab[x][y]='M';
} 

int main() {
	int  c=4;
	int  d=5;
	int  x=7;
	int  y=7;
	int key;
	stare=true;
	sarpe.push_back(make_pair(c,d));
	 
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Surface* screen = SDL_SetVideoMode( 640, 320, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption( "Cu sarpele", 0 );


	SDL_Event event;
	bool gameRunning = true;
	tabel(sarpe,x,y);
	  
    while(gameRunning) 
    {

     	while ( SDL_PollEvent(&event) ) {
     	
  			if (event.type == SDL_KEYDOWN)
			{
 				 	system("clear");
				
  	 			SDLKey key = event.key.keysym.sym;
				if(key == SDLK_ESCAPE || stare ==false)	
	    		gameRunning = false;   
   	 			if (key == SDLK_LEFT)
	     			
  	    			mergiStanga(c,d,sarpe,stare,x,y);
	 				
  	  			if (key == SDLK_RIGHT)
	     
 	     			mergiDreapta(c,d,sarpe,stare,x,y);
	 				
 	   			if (key == SDLK_UP)
	     	
 	     			mergiSus(c,d,sarpe,stare,x,y);
	 
	    		if (key == SDLK_DOWN)
	     
  	    			mergiJos(c,d,sarpe,stare,x,y);
 				   
			} 	 
    	}
	}
	cout<<"GAME OVER LOSER!"<<endl;   
}
