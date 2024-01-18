//============================================================================
// Name        : Mohammad Attique .cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<fstream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include<ctime>
using namespace std;




/* FOR NO USE TILL NOW
//for file handle
string highscore[10];
string text;
int COUNTER234=0;
*/



//variables
string cur_dir="left";
int movement=10; //red car
int movement2=20; //yellow car
int coordinatex=800;
int coordinatey=800;
string name;


//auto car
int temp[5]={10,10,10,10,10};
bool switch_up=false;
bool switch_up2=false;
bool switch_up3=false;
bool switch_up4=false;
bool switch_up5=false;
int mov_temp[5]={2,2,2,10,2};


//pick
bool pick=false;
bool drop=false;

bool pick1=false;
bool drop1=false;

bool pick2=false;
bool drop2=false;

bool pick3=false;
bool drop3=false;

//highscore
int score=0;
int mtime=0;


//string temp;
bool flag = true;
int width = 1020;
int  height = 840; // i have set my window size to be 800 x 60
int r,g,b,x;

//menu
bool game=false;
bool Red=false;
bool Yellow=false;



/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * 
 */
void SetCanvasSize(int width, int height) // function to set canvas size
 {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


int xI = 10,yI = 770;

void drawCar()  //function for drawing car
{
	//range bound`
	if (yI < 0)
	{
		yI += 10;
	}
	if(yI>800)
	{
		yI-=10;
	}
	//red car
	if(Red==true)
	{
	DrawSquare(xI, yI, 30, colors[MAROON]);
	DrawCircle(xI+25,yI,5,colors[BLACK]);
	DrawCircle(xI+5,yI,5,colors[BLACK]);
	}
	//yellow car
	else if(Yellow==true)
	{
		DrawSquare(xI, yI, 30, colors[YELLOW]);
		DrawCircle(xI+5,yI,5,colors[BLACK]);
		DrawCircle(xI+25,yI,5,colors[BLACK]);
	}
	glutPostRedisplay();
}



//CALCULATING SCORE by detecting color and subtracting score
int Total_score()
{			//time in ms

			mtime+=1;

			//passenger scoree
			if(r==-91 && g==42 && b==42)
			{
				
				
				score-=5;	
				
			}		
			
			//red taxi
				if(Red==true)
				{
					//obstacle
					if((r==107 && g==-114 && b==35) || (r==-96 && g==82 && b==45))//green triangle AND BROWN SQUARE
					{
						score-=2;	
						cout << "score" << score;
					}	
						//other taxis
						if(r==-46 && g==105 && b==30) //Sienna square
						{
							score-=3;	
							cout << "score" << score;
						}
				}
			
			//yelllow taxxi
			if(Yellow==true)
			{	//obstacle
					if((r==107 && g==-114 && b==35) || (r==-96 && g==82 && b==45)) //green triangle
					{
						score-=4;	
						cout << "score" << score;
					}	
					
					//taxis 
					
						if(r==-46 && g==105 && b==30) //Sienna square
						{
							score-=2;	
							cout << "score" << score;
						}	
			}	
			/*  done in key 	
			//destination score
			if(r==34 && g==-117 && b==34) //Green circle
			{
					score+=10;	
			cout << "score" << score;
			}	
			*/
			
				
			Num2Str(score);
			Num2Str(mtime);
			return score;
}






void menu()   //creating menu and then calling tit to display function
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	
	if(game==false)
		{
				glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
						0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
				glClear (GL_COLOR_BUFFER_BIT); //Update the colors

				DrawSquare( 500, 400, 100, colors[RED]);
				DrawSquare( 300, 400, 100, colors[YELLOW]);
				DrawString( 300, 600, "press 1 for Red taxi and 2 for Yellow Taxi" , colors[WHITE]);
				DrawString( 400, 800, "RUSH HOUR " , colors[WHITE]);
				DrawString( 400, 800, name , colors[WHITE]);



				glutSwapBuffers(); // do not modify this line..

		}
}


//car movement function
void moveCar()
 {



	if( (xI<1000) && (xI>10) ) {  // canvas width range
	
				// for left movement
				if (cur_dir=="left") {

					//declaring arrays to store color values			
						char pixels[4] = { 0 };
		
					//    x coordinate, ycoordinate, width, height, format,typr, date
    				glReadPixels( xI-10, yI+15, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
    				r= pixels[ 0 ] ;
    				g= pixels[ 1 ] ;
    				b=  pixels[ 2 ] ;
	
	
				//RED   						BLUE   							green
					if ((r==-1 && g==-1 && b==-1) || (r==65 && g==105 && b==-31) || (r==34 && g==-117 && b==34))
						{ 
							if(Red==true)
						{
							xI -= movement; //subtracting x values to move left for red
						}
			
			
						else if(Yellow==true)
						{
							xI -= movement2;     //subtracting x values to move left for yellow
						}
			
		
						cout << "going left"<<endl; 

						}
	
					else	
						{
							cout<<"collision"<<endl;
							cout<<r<<g<<b<<endl;        // for debugging
						}

							//calling function to calculate score
							Total_score();		

							cout << "score" << score; //score on terminal for debug
		
	}



	else if (cur_dir=="right") 
				{
					//declaring arrays to store color values
					char pixels[100] = { 0 };
		
						//    x coordinate, ycoordinate, width, height, format,typr, date
    					glReadPixels( xI+35, yI+10, 4, 4, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
    					r=  pixels[ 0 ] ;
    					g=  pixels[ 1 ] ;
    					b= pixels[ 2 ] ;
		
		
								//RED   						BLUE   							green
							if ((r==-1 && g==-1 && b==-1) ||(r==65 && g==105 && b==-31)|| (r==34 && g==-117 && b==34))
								{					
									if(Red==true)
									{
										xI += movement;
									}
								
									else if(Yellow==true)
									{
									xI += movement2;
									}
			
			
											cout << "going right"<<endl;		

								}
							else	
							{
								cout<<"collision"<<endl;
								cout<<r<<g<<b<<endl;
							}
								//calling function to calculate score
								Total_score();
								cout << "score" << score;
				}




				else if (cur_dir=="up") {
						//declaring arrays to store color values
						char pixels[100] = { 0 };

								//    x coordinate, ycoordinate, width, height, format,typr, date
    							glReadPixels(xI+12, yI+30, 5 ,5, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
    							r= pixels[ 0 ] ;
    							g= pixels[ 1 ] ;
    							b= pixels[ 2 ] ;
												//RED   						BLUE   							green
										if ((r==-1 && g==-1 && b==-1) || (r==65 && g==105 && b==-31) || (r==34 && g==-117 && b==34))
										{
											
											if(Red==true)
												{
													yI += movement;
												}
				
				
										else if(Yellow==true)
										{
										yI += movement2;
										}


							cout << "going up"<<endl;
							}
		
		
		
					else	
					{
						cout<<"collision"<<endl;
						cout<<"r" << r << "g" << g << "b" << b<<endl;
			
					}
						//calling function to calculate score
						Total_score();
						cout << "score" << score;	
										
										}


	else if (cur_dir=="down") {
		char pixels[64] = { 0 };
    	glReadPixels( xI+10 ,yI-8, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
    	r= pixels[ 0 ];
    	g= pixels[ 1 ] ;
    	b= pixels[ 2 ] ;

		if( (r==-1 && g==-1 && b==-1) || (r==65 && g==105 && b==-31) || (r==34 && g==-117 && b==34) )

	
			{
			if(Red==true)
				{
				yI -= movement;
				}
				else if(Yellow==true)
				{
				yI -= movement2;
				}
			

			cout << "going down"<<endl;
			
	
		
				}
		else	
			{
				cout<<"collision"<<endl;
			cout<<r<<g<<b<<endl;
			}
			//calling function to calculate score
		Total_score();
	
		cout << "score" << score;
	
	}
 }
 }



void pessenger()  // function for pessenger spawn and pick and drop
{
	
		//passenger 1
	if (pick==false)	
	{

		DrawCircle(790,750,20,colors[BROWN]);// top right 

		DrawCircle(200,50,20,colors[BROWN]); // bottom left
		DrawCircle(200,400,20,colors[BROWN]); //middle
		DrawCircle(850,20,20,colors[BROWN]);
	}	
	 if (pick==true) 
		{
			// removing coordinate
			//destination
			
			int y=600;
			x=200;
			DrawCircle(x,y,30,colors[GREEN]);// make it random later complete the rest code
			
		}
		// if dropped
		else if(drop==true)
		{	
			
			pick=false;
		}
		
}
		

 

void GameDisplay(){
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	//displaying menu
	if(game==false)
	{
		menu();
	}
	
	
	// game grid 
	else if(game==true)
	{
	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	//grid
	DrawLine( 51 ,  0 ,  51 , 840  , 1 , colors[BLUE] );
	DrawLine( 102 , 0 ,  102 , 840 , 1 , colors[BLUE] );
	DrawLine( 153 , 0 ,  153 , 840 , 1 , colors[BLUE] );
	DrawLine( 204 , 0 ,  204 , 840 , 1 , colors[BLUE] );
	DrawLine( 255 , 0 ,  255 , 840 , 1 , colors[BLUE] );
	DrawLine( 306,  0 ,  306 , 840 , 1 , colors[BLUE] );
	DrawLine( 357,  0 ,  357 , 840 , 1 , colors[BLUE] );	
	DrawLine( 408,  0 ,  408 , 840 , 1 , colors[BLUE] ); 	
	DrawLine( 459,  0 ,  459 , 840 , 1 , colors[BLUE] );	
	DrawLine( 510,  0 ,  510 , 840 , 1 , colors[BLUE] );
	DrawLine( 561 , 0 ,  561 , 840 , 1 , colors[BLUE] );
	DrawLine( 613 , 0 ,  613 , 840 , 1 , colors[BLUE] );
	DrawLine( 664 , 0 ,  664 , 840 , 1 , colors[BLUE] );
	DrawLine( 715 , 0 ,  715 , 840 , 1 , colors[BLUE] );
	DrawLine( 766 , 0 ,  766 , 840 , 1 , colors[BLUE] );
	DrawLine( 817,  0 ,  817 , 840 , 1 , colors[BLUE] );
	DrawLine( 868,  0 ,  868 , 840 , 1 , colors[BLUE] );	
	DrawLine( 919,  0 ,  919 , 840 , 1 , colors[BLUE] ); 	
	DrawLine( 970,  0 ,  970 , 840 , 1 , colors[BLUE] ); 	
	DrawLine( 1021, 0 , 1021 , 840 , 1 , colors[BLUE] ); 
	
	
	//Y AXIS lines
	DrawLine( 0 ,  42 ,  1021 , 42  , 1 , colors[BLUE] );
	DrawLine( 0 ,  84 ,  1021 , 84  , 1 , colors[BLUE] );
	DrawLine( 0 , 126 ,  1021 , 126 , 1 , colors[BLUE] );
	DrawLine( 0 , 168 ,  1021 , 168 , 1 , colors[BLUE] );
	DrawLine( 0 , 210 ,  1021 , 210 , 1 , colors[BLUE] );
	DrawLine( 0 , 252 ,  1021 , 252 , 1 , colors[BLUE] );
	DrawLine( 0 , 294 ,  1021 , 294 , 1 , colors[BLUE] );	
	DrawLine( 0 , 336 ,  1021,  336 , 1 , colors[BLUE] );	
	DrawLine( 0 , 378 ,  1021 , 378 , 1 , colors[BLUE] ); 	
	DrawLine( 0 , 420 ,  1021 , 420 , 1 , colors[BLUE] );	
	DrawLine( 0 , 462 ,  1021 , 462 , 1 , colors[BLUE] );
	DrawLine( 0 , 504 ,  1021 , 504 , 1 , colors[BLUE] );
	DrawLine( 0 , 546 ,  1021 , 546 , 1 , colors[BLUE] );
	DrawLine( 0 , 588 ,  1021 , 588 , 1 , colors[BLUE] );
	DrawLine( 0 , 630 ,  1021 , 630 , 1 , colors[BLUE] );
	DrawLine( 0 , 672 ,  1021 , 672 , 1 , colors[BLUE] );
	DrawLine( 0 , 714 ,  1021 , 714 , 1 , colors[BLUE] );
	DrawLine( 0 , 756 ,  1021 , 756 , 1 , colors[BLUE] ); 	
	DrawLine( 0 , 798 ,  1021 , 798 , 1 , colors[BLUE] ); 
	DrawLine( 0 , 840 ,  1021 , 840 , 1 , colors[BLUE] ); 	

	
	
	//track
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 561 , 714 ,  765 , 714 , 84 , colors[BLACK] );//top right x
	DrawLine(  0  , 714 ,  357 , 714 , 84 , colors[BLACK] );//top left
	DrawLine( 867 , 714 ,  867 , 420 , 102 , colors[BLACK] );//right top
	DrawLine( 663 , 714 ,  664 , 840 , 102 , colors[BLACK] );//top y
	DrawLine( 663 , 504 ,  663 , 42  , 102 , colors[BLACK] );
	DrawLine( 868 , 294 ,  868 , 42  , 102 , colors[BLACK] );//
	DrawLine( 102 , 504 ,  459 , 504 , 84 , colors[BLACK] );	//top middle left
	DrawLine( 102 , 294 ,  459 , 294 , 84, colors[BLACK] ); //middle left



	//taxis auto movement 
	if(switch_up==false) 		//upwards
	{
		DrawSquare(300, temp[0], 40, colors[SIENNA]);
		DrawCircle(335,temp[0],5,colors[BLACK]);
		DrawCircle(305,temp[0],5,colors[BLACK]);		

		if(mov_temp[0]%8==0) 	//speed
			{
				temp[0]+=10; 	//by how much it will move
				
			}
		mov_temp[0]+=1; //incrementing by one 
		if(temp[0]>200)  //upper range
		{ 
			switch_up=true; // to move downward at max height
		}
	}
	
	if(switch_up==true)			//DOWNWARD MOVE
	{
		
		if(mov_temp[0]%8==0)	//speed
			{
				temp[0]-=10;    //by how much it will move
			}
		mov_temp[0]++;			//increment

				//drawing car
		DrawSquare(300, temp[0], 40, colors[SIENNA]); 
		DrawCircle(335,temp[0],5,colors[BLACK]);
		DrawCircle(305,temp[0],5,colors[BLACK]);
		
		
		if(temp[0]==10) //lower range
		{
			switch_up=false;
		}
	}
 
	//taxi 2 auto movement
	if(switch_up2==false)
	{
		DrawSquare(950, temp[1], 40, colors[SIENNA]);
		DrawCircle(985,temp[1],5,colors[BLACK]);
		DrawCircle(955,temp[1],5,colors[BLACK]);

		if(mov_temp[1]%8==0)
			{
				temp[1]+=10;
				
			}
		mov_temp[1]++;
		if(temp[1]>800)
		{ 
			switch_up2=true;
		}
	}
	
	if(switch_up2==true)
	{
		
		if(mov_temp[1]%8==0)
			{
				temp[1]-=10;
			}
		mov_temp[1]++;

		DrawSquare(950, temp[1], 40, colors[SIENNA]);
		DrawCircle(985,temp[1],5,colors[BLACK]);
		DrawCircle(955,temp[1],5,colors[BLACK]);
		if(temp[1]==10)
		{
			switch_up2=false;
		}
	}


	//taxi 3 auto movement
	if(switch_up3==false)
	{
		DrawSquare(50, temp[2], 40, colors[SIENNA]);
		DrawCircle(85,temp[2],5,colors[BLACK]);
		DrawCircle(55,temp[2],5,colors[BLACK]);

		if(mov_temp[2]%8==0)
			{
				temp[2]+=10;
				
			}
		mov_temp[2]++;
		if(temp[2]>615)
		{ 
			switch_up3=true;
		}
	}
	
	if(switch_up3==true)
	{
		
		if(mov_temp[2]%8==0)
			{
				temp[2]-=10;
			}
		mov_temp[2]++;

		DrawSquare(50, temp[2], 40, colors[SIENNA]);
		DrawCircle(85,temp[2],5,colors[BLACK]);
		DrawCircle(50,temp[2],5,colors[BLACK]);
		if(temp[2]==10)
		{
			switch_up3=false;
		}
	}
	

		//taxi 4  auto movement
	if(drop==true)
	{
	if(switch_up4==false)
	{
		DrawSquare(750, temp[3], 40, colors[SIENNA]);
		DrawCircle(785,temp[3],5,colors[BLACK]);
		DrawCircle(755,temp[3],5,colors[BLACK]);

		if(mov_temp[3]%8==0)
			{
				temp[3]+=10;
				
			}
		mov_temp[3]++;
		if(temp[3]>615)
		{ 
			switch_up4=true;
		}
	}
	
	if(switch_up4==true)
	{
		
		if(mov_temp[3]%8==0)
			{
				temp[3]-=10;
			}
		mov_temp[3]++;

		DrawSquare(750, temp[3], 40, colors[SIENNA]);
		DrawCircle(785,temp[3],5,colors[BLACK]);
		DrawCircle(755,temp[3],5,colors[BLACK]);
		if(temp[3]==10)
		{
			switch_up4=false;
		}
	}
	
	}
	


		
			//OBSTACLES
			// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)

			DrawTriangle( 250, 370 , 350, 370 , 300 , 450, colors[DARK_OLIVE_GREEN] );  
			DrawTriangle( 400, 700 , 500, 700 , 450 , 750, colors[DARK_OLIVE_GREEN] ); //top
			DrawTriangle( 450, 100 , 550, 100 , 500 , 150, colors[DARK_OLIVE_GREEN] ); 
			DrawSquare(850, 320, 50,colors[SADDLE_BROWN]);
			DrawSquare(663, 600, 50,colors[SADDLE_BROWN]);
		
		
			//GAMEOVER
				if((score>=100) || (score<=-200) || (mtime==1800))	
					{			
						exit(1);
					}
		
			//DISPLAY SCORE and time
			
			DrawString( 10, 800, "Score = " , colors[BLACK]);
			DrawString( 100, 800, Num2Str(score) , colors[BLACK]);
			DrawString( 720, 800, "M.sec =" , colors[BLACK]);
			DrawString( 800, 800, Num2Str(mtime) , colors[BLACK]);
			drawCar();
			pessenger();

	
	glutSwapBuffers(); // do not modify this line..


	}
}
 
	







/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {


	

		if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
		 {
		// what to do when left key is pressed...
				if (cur_dir!="left")  // condition to stop it from moving faster
				{
					xI -= 10; //movement towards left
				}
		cur_dir="left";    //direction string
		} 
		
		else if (key== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
		{
		
				if (cur_dir!="right")
				{
					xI += 10;  					//movement towards Right
					cur_dir="right";        //direction string
				}

		}


		else if (key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
		{
			if (cur_dir!="up")
				{
				yI += 10;    		//movement towards Up
				}
			cur_dir="up";

		}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) 
	{
				if (cur_dir!="down")
				{
						yI -= 10;           //movement towards down
				}
				cur_dir="down";  //direction string
	}
	
	



	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();


}
/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/)
	 {
		exit(1); // exit the program when escape key is pressed.
	 }

	
	
	
	if (key == 32) //Key for spacebar to pick and drop pessnegers
			{				
				
	//boundrie		s	//p1   											p2												p3															P4			
				if(((xI<=900 && xI>=600) && (yI<=900 && yI>=600)) || ((xI<=400 && xI>=50) && (yI<=200 && yI>00)) || ((xI<=400 && xI>=50) && (yI<=550 && yI>350)) || ((xI<=1100 && xI>=700) && (yI<=200 && yI>00)))
				{
					pick=true;
				}
				else if((r==34 && g==-117 && b==34))
				{
				
				drop=true;
				pick=false;
				movement+=5;
				movement2+=5;
				score+=10;
		//do something if b is pressed
		cout << "b pressed" << endl;
				}
				
			}	 
			
			// if 1 pressed red car display
		if(key=='1')  
		{		
				Red=true;
					game=true;
		}

		// if 2 pressed Yellow car display
		else if(key=='2')
		{		
			Yellow=true;
			game=true;
		}
		
	
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {
		
	// implement your functionality here
	moveCar();
	GameDisplay();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
		
		movement=0;    //movement of red
		movement2 =0; //movement of yellow

	} 
	 if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
			cout<<"Right Button Pressed"<<endl;
		
			movement=10;     //movement of red
			movement2=10;	//movement of yellow
			
		
	}
	glutPostRedisplay();
}



/*
 * Main Canvas drawing function.


/*
 * our gateway main function
*/


int main(int argc, char*argv[]) {

	 


	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Naveed Ahmad"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	//glutDisplayFunc(menu);
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse  

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}

#endif /* RushHour_CPP_ */
