#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <string.h>

#define _WIN32_WINNT 0x0500

#include <windows.h>

/*
Name : The Maze Game
Author : iRewiewer
Version : 1.0
*/

using namespace std;

int maze[1000][1000];

int character = 227;

char tiles[]={0,178,177,176};

char v[]={0,178,177,227,176};

ifstream fi("lab.yml");

// ----------------[ VV CORE GAME VV ]---------------- \\

void switcher(int &a, int &b);

void menu();
void game();
void win();
void options();
void char_select();
void theme();
void music();

int main()
{

    system("title The Maze");

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    MoveWindow(console, r.left, r.top, 818, 600, TRUE);

    system("color 4f");

    menu();
}

void switcher(int &a, int &b)
{
    int tmp;

    tmp = a;
    a = b;
    b = tmp;
}

void win()
{
    system("cls");

    cout << endl << endl << endl << endl << endl << endl;

    cout<<"              o----------------------------------------o"<< endl;
    cout<<"              |                                        |"<< endl;
    cout<<"              |            CONGRATULATIONS!            |"<< endl;
    cout<<"              |                                        |"<< endl;
    cout<<"              |      ==  YOU'VE BEAT 'THE MAZE' ==     |"<< endl;
    cout<<"              |                                        |"<< endl;
    cout<<"              |               /\\    /\\                 |"<< endl;
    cout<<"              |                   >                    |"<< endl;
    cout<<"              |                 ____                   |"<< endl;
    cout<<"              o----------------------------------------o"<< endl;
    cout<< endl <<"                     PRESS ENTER TO CONTINUE";

    int action = getch();

    end1:
    if(getch() == 13) //13 - enter
    {
        system("cls");

        cout << endl << endl << endl << endl << endl << endl;

        cout<<"              o----------------------------------------o"<< endl;
        cout<<"              |                                        |"<< endl;
        cout<<"              |            CONGRATULATIONS!            |"<< endl;
        cout<<"              |                                        |"<< endl;
        cout<<"              |    ==  DO YOU WANT TO PLAY AGAIN? ==   |"<< endl;
        cout<<"              |                                        |"<< endl;
        cout<<"              |    PRESS 'Y' FOR YES AND 'N' FOR NO    |"<< endl;
        cout<<"              |                                        |"<< endl;
        cout<<"              |               [ Y / N ]                |"<< endl;
        cout<<"              o----------------------------------------o"<< endl;

        end2:

        char response = getch();

        if(response == 'y' || response == 'Y') //positive response -> restart game
        {
            system("title exit");
            system("start MazeGame.exe");
            system("taskkill /f /fi \"WINDOWTITLE eq exit\"");
        }
        else
            if(response == 'n' || response == 'N') //negative response -> quit game
            {
                system("title exit");
                system("taskkill /f /fi \"WINDOWTITLE eq exit\"");
            }
            else
                goto end2;
    }
    else
        goto end1;
}

void game() //everything about the maze
{
    int n, m;

    fi >> n >> m;

    v[3] = character;

	struct pos
	{
		int x;
		int y;
	};

	pos current, end;

    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++)
        {
            fi >> maze[i][j]; //read maze

            if(maze[i][j] == 3) //3 - start position in text file
            {
                current.y = i;
                current.x = j;
            }

            if(maze[i][j] == 4) //4 - end position in text file
            {
                end.y = i;
                end.x = j;
            }
        }

    cout << endl << endl << endl << endl << endl << endl;

    for(int i = 1 ; i <= n ; i++)
    {
        cout << "                    ";
        for(int j = 1 ; j <= m ; j++)
            cout << char(v[ maze[i][j] ]);
        cout << endl;
    }

/*

π - 227 - Player ;
░ - 176 - S,E ;
▒ - 177 - Path ;
▓ - 178 - Wall ;

*/

    int tmp;

    while(current.y != end.y || current.x != end.x) //if the player is not at the end
    {
        char action = getch();

        if(action == 'w' && maze[current.y - 1][current.x] == 0) //if the player is pressing w and there's an empty space above
        {
            switcher(maze[current.y][current.x], maze[current.y - 1][current.x]);
            current.y--;
            Beep(500,150);
        }

        if(action == 's' && maze[current.y + 1][current.x] == 0)//if the player is pressing s and there's an empty space below
        {
            switcher(maze[current.y][current.x], maze[current.y + 1][current.x]);
            current.y++;
            Beep(500,150);
        }

        if(action == 'a' && maze[current.y][current.x - 1] == 0)//if the player is pressing a and there's an empty space to the left
        {
            switcher(maze[current.y][current.x], maze[current.y][current.x-1]);
            current.x--;
            Beep(500,150);
        }

        if(action == 'd' && maze[current.y][current.x + 1] == 0)//if the player is pressing d and there's an empty space to the right
        {
            switcher(maze[current.y][current.x], maze[current.y][current.x+1]);
            current.x++;
            Beep(500,150);
        }

        if(maze[current.y - 1][current.x] == 4 || maze[current.y + 1][current.x] == 4 || maze[current.y][current.x - 1] == 4 || maze[current.y][current.x + 1] == 4) //if the player is on the end tile
            break;
        else
            system("cls");

        cout<< endl << endl << endl << endl << endl << endl;

        for(int i = 1 ; i <= n ; i++)
        {
            cout << "                    ";
            for(int j = 1 ; j <= m ;j++)
                cout << char(v[ maze[i][j] ]);
            cout << endl;
        }
    }

    win();
}

void menu() //menu screen no exter
{
    string response;
    char action;
    int mode = 0;

    while(true)
    {
        if(mode == 0)
        {
            system("cls");

            cout<< endl << endl << endl << endl << endl << endl;
            cout<<"              o----------------------------------------o"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              |          WELCOME TO THE MAZE           |"<< endl;
            cout<<"              |                   BY iRewiewer         |"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              |              >> PLAY <<                |"<< endl;
            cout<<"              |                OPTIONS                 |"<< endl;
            cout<<"              |                 EXIT                   |"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              o----------------------------------------o"<< endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 2;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                response = "play";
                break;
            }
        }

        if(mode == 1)
        {
            system("cls");

            cout<< endl << endl << endl << endl << endl << endl;
            cout<<"              o----------------------------------------o"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              |          WELCOME TO THE MAZE           |"<< endl;
            cout<<"              |                   BY iRewiewer         |"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              |                 PLAY                   |"<< endl;
            cout<<"              |             >> OPTIONS <<              |"<< endl;
            cout<<"              |                 EXIT                   |"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              o----------------------------------------o"<< endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 0;

            if(action == 's' || action == 'S' || action == 80)
                mode = 2;

            if(action == 13)
            {
                response = "options";
                break;
            }
        }

        if(mode == 2)
        {
            system("cls");

            cout<< endl << endl << endl << endl << endl << endl;
            cout<<"              o----------------------------------------o"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              |          WELCOME TO THE MAZE           |"<< endl;
            cout<<"              |                   BY iRewiewer         |"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              |                 PLAY                   |"<< endl;
            cout<<"              |                OPTIONS                 |"<< endl;
            cout<<"              |              >> EXIT <<                |"<< endl;
            cout<<"              |                                        |"<< endl;
            cout<<"              o----------------------------------------o"<< endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 1;

            if(action == 's' || action == 'S' || action == 80)
                mode = 0;

            if(action == 13)
            {
                response = "exit";
                break;
            }
        }
    }

    system("cls");

    if(response == "play")
        game();

    if(response == "options")
        options();

    if(response == "exit")
    {
        system("title exit");
        system("taskkill /f /fi \"WINDOWTITLE eq exit\"");
    }
}

void options()
{
    string response;
    char action;
    int mode = 0;

    while(true)
    {
        if(mode == 0)
        {
            system("cls");

            cout<<endl<<endl<<endl<<endl<<endl<<endl;
            cout<<"              o----------------------------------------o"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |              GAME OPTIONS              |"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |         >> SELECT CHARACTER <<         |"<<endl;
            cout<<"              |              SELECT THEME              |"<<endl;
            cout<<"              |              SELECT MUSIC              |"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |                  BACK                  |"<<endl;
            cout<<"              o----------------------------------------o"<<endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 3;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                response = "character";
                break;
            }
        }

        if(mode == 1)
        {
            system("cls");

            cout<<endl<<endl<<endl<<endl<<endl<<endl;
            cout<<"              o----------------------------------------o"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |              GAME OPTIONS              |"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |            SELECT CHARACTER            |"<<endl;
            cout<<"              |           >> SELECT THEME <<           |"<<endl;
            cout<<"              |              SELECT MUSIC              |"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |                  BACK                  |"<<endl;
            cout<<"              o----------------------------------------o"<<endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 0;

            if(action == 's' || action == 'S' || action == 80)
                mode = 2;

            if(action == 13)
            {
                response = "theme";
                break;
            }
        }

        if(mode == 2)
        {
            system("cls");

            cout<<endl<<endl<<endl<<endl<<endl<<endl;
            cout<<"              o----------------------------------------o"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |              GAME OPTIONS              |"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |            SELECT CHARACTER            |"<<endl;
            cout<<"              |              SELECT THEME              |"<<endl;
            cout<<"              |           >> SELECT MUSIC <<           |"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |                  BACK                  |"<<endl;
            cout<<"              o----------------------------------------o"<<endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 1;

            if(action == 's' || action == 'S' || action == 80)
                mode = 3;

            if(action == 13)
            {
                response = "music";
                break;
            }
        }

        if(mode == 3)
        {
            system("cls");

            cout<<endl<<endl<<endl<<endl<<endl<<endl;
            cout<<"              o----------------------------------------o"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |              GAME OPTIONS              |"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |            SELECT CHARACTER            |"<<endl;
            cout<<"              |              SELECT THEME              |"<<endl;
            cout<<"              |              SELECT MUSIC              |"<<endl;
            cout<<"              |                                        |"<<endl;
            cout<<"              |               >> BACK <<               |"<<endl;
            cout<<"              o----------------------------------------o"<<endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 2;

            if(action == 's' || action == 'S' || action == 80)
                mode = 0;

            if(action == 13)
            {
                response = "back";
                break;
            }
        }
    }

    system("cls");

    if(response == "character")
        char_select();

    if(response == "theme")
        theme();

    if(response == "music")
        music();

    if(response == "back")
    {
        system("title exit");
        system("start LabirynthGame.exe");
        system("taskkill /f /fi \"WINDOWTITLE eq exit\"");
    }
}

void char_select()
{
    string response;
    char action;
    int mode = 0;

    while(true)
    {
        if(mode == 0)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "                 |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 1)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  " << char(174) << " " << char(227) << " " << char(175) << "                 |" << endl;
            cout << "              |                 >> " << char(155) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "                 |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 0;

            if(action == 's' || action == 'S' || action == 80)
                mode = 2;

            if(action == 13)
            {
                character = 255;
                menu();
                break;
            }
        }

        if(mode == 2)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  " << char(174) << " " << char(227) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                 >> " << char(158) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "                 |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 1;

            if(action == 's' || action == 'S' || action == 80)
                mode = 3;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 3)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 2;

            if(action == 's' || action == 'S' || action == 80)
                mode = 4;

            if(action == 13)
            {
                character = 158;
                menu();
                break;
            }
        }

        if(mode == 4)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 3;

            if(action == 's' || action == 'S' || action == 80)
                mode = 5;

            if(action == 13)
            {
                character = 159;
                menu();
                break;
            }
        }

        if(mode == 5)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 4;

            if(action == 's' || action == 'S' || action == 80)
                mode = 6;

            if(action == 13)
            {
                character = 225;
                menu();
                break;
            }
        }

        if(mode == 6)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 5;

            if(action == 's' || action == 'S' || action == 80)
                mode = 7;

            if(action == 13)
            {
                character = 231;
                menu();
                break;
            }
        }

        if(mode == 7)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 6;

            if(action == 's' || action == 'S' || action == 80)
                mode = 8;

            if(action == 13)
            {
                character = 228;
                menu();
                break;
            }
        }

        if(mode == 8)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 7;

            if(action == 's' || action == 'S' || action == 80)
                mode = 9;

            if(action == 13)
            {
                character = 232;
                menu();
                break;
            }
        }

        if(mode == 9)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 8;

            if(action == 's' || action == 'S' || action == 80)
                mode = 10;

            if(action == 13)
            {
                character = 233;
                menu();
                break;
            }
        }

        if(mode == 10)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 9;

            if(action == 's' || action == 'S' || action == 80)
                mode = 11;

            if(action == 13)
            {
                character = 234;
                menu();
                break;
            }
        }

        if(mode == 11)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 10;

            if(action == 's' || action == 'S' || action == 80)
                mode = 12;

            if(action == 13)
            {
                character = 236;
                menu();
                break;
            }
        }

        if(mode == 12)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                  SKINS                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                 >> " << char(227) << " <<                |" << endl;
            cout << "              |                  " << char(174) << " " << char(155) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(158) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(159) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(225) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(231) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(228) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(232) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(233) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(234) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(236) << " " << char(175) << "                 |" << endl;
            cout << "              |                  " << char(174) << " " << char(240) << " " << char(175) << "                 |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               " << char(174) << " BACK " << char(175) << "               |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 11;

            if(action == 's' || action == 'S' || action == 80)
                mode = 0;

            if(action == 13)
            {
                character = 240;
                menu();
                break;
            }
        }
    }
}

void theme()
{
    string response;
    char action;
    int mode = 0;

    while(true)
    {
        if(mode == 0)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |    == Background : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : White " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                system("color 18");
                menu();
                break;
            }
        }

        if(mode == 1)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 2)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 3)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 4)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 5)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 6)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          "" << char(175) << " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 7)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 8)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }

        if(mode == 9)
        {
            system("cls");

            cout << endl << endl;
            cout << "              o----------------------------------------o" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |               THEMES                   |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |       == Bground : Text ==             |" << endl;
            cout << "              |          >> Blue : Gray <<             |" << endl;
            cout << "              |           " << char(174) << " Aqua : Red " << char(175) << "               |" << endl;
            cout << "              |          " << char(174) << " Black : Gray " << char(175) << "              |" << endl;
            cout << "              |          " << char(174) << " Black : Purple " << char(175) << "            |" << endl;
            cout << "              |            " << char(174) << " Red : White " << char(175) << "             |" << endl;
            cout << "              |            " << char(174) << " Red : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " White : Light Red " << char(175) << "         |" << endl;
            cout << "              |          " << char(174) << " Black : Light Green " << char(175) << "       |" << endl;
            cout << "              |         " << char(174) << " Purple : Light Yellow " << char(175) << "      |" << endl;
            cout << "              |                                        |" << endl;
            cout << "              |                " << char(174) << " BACK " << char(175) << "                |" << endl;
            cout << "              o----------------------------------------o" << endl;

            action = getch();

            if(action == 'w' || action == 'W' || action == 72)
                mode = 12;

            if(action == 's' || action == 'S' || action == 80)
                mode = 1;

            if(action == 13)
            {
                character = 227;
                menu();
                break;
            }
        }
    }
}

void music()
{
    cout << "WIP";
}
