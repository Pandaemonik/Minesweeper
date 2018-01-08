#pragma once

#include "Minesweeper.h"

int round(int i_ToBeRounded)
{
	i_ToBeRounded/=SQURE_SIZE;
	i_ToBeRounded*=SQURE_SIZE;
	return i_ToBeRounded;
}

int CellNumber(const int &i_Coord)
{return i_Coord/SQURE_SIZE;}

void recursive_draw(HDC hdc,HINSTANCE hInst, int x,int y)
{
	if(been_here[CellNumber(y)][CellNumber(x)]==true)return ;
	if(safe[CellNumber(y)][CellNumber(x)]==true)return;
	been_here[CellNumber(y)][CellNumber(x)]=true;

	switch (numbers[CellNumber(y)][CellNumber(x)])
	{
	case 1:
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_1)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		return ;
		break;
	case 2:
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_2)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		return ;
		break;
	case 3:
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_3)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		return ;
		break;
	case 4:
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_4)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		return ;
		break;
	case 5 :
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_5)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		return ;
		break;
	case 6:
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_6)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		return ;
		break;
	case 7:
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_7)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		return ;
		break;
	case 8:
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_8)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		return ;
		break;
	default:
		SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_CLICKED)));
		Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
		break;
	}


	if (x!=0)
	{recursive_draw(hdc,hInst,x-SQURE_SIZE,y);}// Goes W

	if (x!=0 && y!=0)
	{recursive_draw(hdc,hInst,x-SQURE_SIZE,y-SQURE_SIZE);}// Goes NW

	if (y!=0)
	{recursive_draw(hdc,hInst,x, y-SQURE_SIZE);}//Goes N

	if (x!=(DEFAULT_X*SQURE_SIZE)-SQURE_SIZE && y!=0)//Goes NE
	{recursive_draw(hdc,hInst,x+SQURE_SIZE,y-SQURE_SIZE);}

	if (x!=(DEFAULT_X*SQURE_SIZE)-SQURE_SIZE)//Goes E
	{recursive_draw(hdc,hInst,x+SQURE_SIZE,y);}

	if (x!=(DEFAULT_X*SQURE_SIZE)-SQURE_SIZE && y!=(DEFAULT_Y*SQURE_SIZE)-SQURE_SIZE)//Goes SE
	{recursive_draw(hdc,hInst,x+SQURE_SIZE,y+SQURE_SIZE);}

	if (y!=(DEFAULT_Y*SQURE_SIZE)-SQURE_SIZE)//Goes S
	{recursive_draw(hdc,hInst,x, y+SQURE_SIZE);}

	if (x!=0 && y!=(DEFAULT_Y*SQURE_SIZE)-SQURE_SIZE)
	{recursive_draw(hdc,hInst,x-SQURE_SIZE,y+SQURE_SIZE);}// Goes SW

	return;
}

void fill_numbers()
{
	for (int y = 0; y < DEFAULT_Y; y++)
	{
		for (int x = 0; x < DEFAULT_X; x++)
		{
			if (bombs[y][x]!=1)
			{
				//Top Left
				if (x==0 && y==0)
				{numbers[y][x]=bombs[y][x+1]+bombs[y+1][x+1]+bombs[y+1][x];}

				//Bottom Left
				else if (x==0 && y==DEFAULT_Y-1)
				{numbers[y][x]=bombs[y-1][x]+bombs[y-1][x+1]+bombs[y][x+1];}

				//Top Right
				else if (x==DEFAULT_X-1 && y==0)
				{numbers[y][x]=bombs[y+1][x]+bombs[y+1][x-1]+bombs[y][x-1];}

				//Bottom Right
				else if (x==DEFAULT_X-1 && y==DEFAULT_Y-1)
				{numbers[y][x]=bombs[y][x-1]+bombs[y-1][x-1]+bombs[y-1][x];}

				//Left Edge
				else if (x==0)
				{numbers[y][x]=bombs[y-1][x] + bombs[y-1][x+1] + bombs[y][x+1] + bombs[y+1][x+1] + bombs[y+1][x];}

				//Right Edge
				else if (x==DEFAULT_X-1)
				{numbers[y][x]=bombs[y+1][x] + bombs[y+1][x-1] + bombs[y][x-1] + bombs[y-1][x-1] + bombs[y-1][x];}

				//Top Edge
				else if (y==0)
				{numbers[y][x]=bombs[y][x+1] + bombs[y+1][x+1] + bombs[y+1][x] + bombs[y+1][x-1] + bombs[y][x-1];}

				//Bottom Edge
				else if (y==DEFAULT_Y-1)
				{numbers[y][x]=bombs[y][x-1] + bombs[y-1][x-1] + bombs[y-1][x] + bombs[y-1][x+1] + bombs[y][x+1];}

				//Centre Case
				else
				{
					numbers[y][x]=
						bombs[y-1][x] + bombs[y-1][x+1] + bombs[y][x+1] + bombs[y+1][x+1] + 
						bombs[y+1][x] + bombs[y+1][x-1] + bombs[y][x-1] + bombs[y-1][x-1];}
			}
			else {Number_of_mines++;}
		}
	}
}

void new_game(HWND hWnd)
{
	if (RedrawWindow(hWnd,NULL,NULL,RDW_ERASE|RDW_INTERNALPAINT!=0)!=0)
	{
		Number_of_mines=0;
		Game_over=false;
		for (int i = 0; i < DEFAULT_Y; i++)
		{
			for (int j = 0; j < DEFAULT_X; j++)
			{
				been_here[i][j]=false;
				safe[i][j]=false;
				numbers[i][j]=0;
			}
		}
		fill_numbers();
	}
	else
	{
		MessageBox(hWnd,"There was an error re-building the window","Error",MB_OK|MB_ICONERROR|MB_DEFBUTTON1);
		DestroyWindow(hWnd);
	}
}