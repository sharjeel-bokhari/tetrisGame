#include<iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include<SFML/Graphics.hpp>
#include<cstring>
using namespace sf;
using namespace std;
using namespace this_thread;    
using namespace chrono_literals;
using chrono::system_clock;


#define MAX_NUMBER_OF_ITEMS 2

//---------- Menu Class Starting ----------

class Menu
{
public:
	Menu(float width, float height);

	void draw( RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem(){
        return Index;
    }

private:
	int Index;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
	Text controls;
	Texture disp;

};
Menu::Menu(float width, float height)
{
	disp.loadFromFile("images/MenuPage.jpeg");	
	if (!font.loadFromFile("hehe.TTF"))
	{
		cout << "ERROR!" << endl;
	}

	controls.setFont(font);
	controls.setFillColor(Color::White);
	controls.setCharacterSize(23);
	controls.setString("\t\t\t\tKEYS\nRotate: Up Arrow Key\nMove Left: Left Arrow Key\nMove Right: Right Arrow Key\nMove Down: Down Arrow Key");
	controls.setPosition(Vector2f(width / 16, (height / (MAX_NUMBER_OF_ITEMS + 1) * 1.35)));

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(width / 1.25, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Exit");
	menu[1].setPosition(Vector2f(width / 1.25, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	Index = 0;
}

void Menu::draw( RenderWindow &window1)
{
	Sprite men(disp);
	window1.draw(men);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window1.draw(menu[i]);
	}
	window1.draw(controls);
}

void Menu::MoveUp()
{
	if (Index - 1 >= 0)
	{
		menu[Index].setFillColor(Color::White);
		Index--;
		menu[Index].setFillColor(Color::Red);
	}
}

void Menu::MoveDown()
{
	if (Index + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[Index].setFillColor(Color::White);
		Index++;
		menu[Index].setFillColor(Color::Red);
	}
}
struct coordinates{
  int x; 
  int y;
  };
coordinates a[4]={{1,0},{1,1},{1,2},{1,3}} , a2[4];

coordinates shapes[7][4]=
{
 {{1,0},{1,1},{1,2},{1,3}},// I
 {{0,1},{1,1},{1,2},{2,2}},
 {{0,1},{1,1},{2,1},{1,2}},
 {{0,0},{1,0},{1,1},{1,2}},
 {{0,1},{1,1},{0,2},{1,2}},
 {{0,2},{1,1},{1,2},{2,1}},
 {{1,0},{1,1},{1,2},{2,0}} // z
};

const int Len = 20;
const int wid = 10;

int field[Len][wid]={0};

bool cfalling()
{
  for(int i=0; i<4 ; i++)
  {
    if(a[i].x < 0 || a[i].x >=wid || a[i].y >= Len)
      return 0;
    if(field[a[i].y][a[i].x] != 0)
      return 0;
  }
 return 1;
}
//---------End----------
bool end()
{
  bool flag = false;
  for(int i=0; i < wid ;i++)
  {   
    if(field[0][i] != 0){
      flag = true;
    }
  }
  return flag;
}


int main()
{
//----------------
    Clock clock;
    int color=1;
    Texture tex,tex1;
    tex1.loadFromFile("images/backdrop1.png");
    tex.loadFromFile("images/tiles.png");
    int dx = 0, score = 0;
    bool rotate =false;
    float timer = 0 , delay = 0.5;
    Sprite s(tex), back(tex1);
	Text scores;
	Font scrFnt;

//--------------
	RenderWindow window1(VideoMode(600, 400), "Start Up Page!");

	Menu m(window1.getSize().x, window1.getSize().y);

	while (window1.isOpen())
	{

		Event event;

		while (window1.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					m.MoveUp();
					break;

				case Keyboard::Down:
					m.MoveDown();
					break;

				case Keyboard::Return:

					switch (m.GetPressedItem())
					{
					case 0:
							
                            window1.clear();
                            srand(time(0));
                            
                            while(window1.isOpen())
                            {

                                float t=clock.getElapsedTime().asSeconds();
                                clock.restart();
                                timer += t;

                                Event e;
                                while(window1.pollEvent(e))
                                {
									if(e.type == Event::Closed){
										window1.close();
									}
									
									if(e.type == Event:: KeyPressed){
										if(e.key.code == Keyboard::Up){
											rotate=true;
										}
										else if(e.key.code == Keyboard::Left){
											dx=-1;
										}
										else if(e.key.code == Keyboard::Right){
											dx=1;
										}
									}
                                }

                                if(Keyboard::isKeyPressed(Keyboard::Down)){
									delay=0.1;
								}

                                //----------MOVE------------
                                int i = 0;
								while(i < 4){
									a2[i] = a[i];
									a[i].x += dx;
									i++;
                                }
                                if(!cfalling())
                                {
									int i = 0;
									while(i < 4){
										a[i] = a2[i];
										i++;
									}
                                }
                                //------------rotaion---------
                                if(rotate)
                                {
									coordinates point = a[1];
									for(int i = 0; i < 4; i++){

										int x = a[i].y - point.y;
										int y = a[i].x - point.x;
										a[i].x = point.x - x;
										a[i].y = point.y + y;
									}
									if(!cfalling()){
										
										for(int i = 0; i < 4; i++){
											a[i] = a2[i];
										}
									}
                                }
                                //-----------Down------------
                                if(timer > delay){

									for(int i=0; i<4 ; i++ ){

										a2[i] = a[i];
										a[i].y += 1;
									}
									if(!cfalling()){
										for(int i = 0; i < 4; i++){
											field[a2[i].y][a2[i].x] = color;
										}
										color = 1 + rand() % 7;
										int n = rand() % 7;
										for(int i = 0; i < 4; i++){
											a[i].x = shapes[n][i].x;
											a[i].y = shapes[n][i].y;
										}
                                	}
                                	timer = 0;
                                }
                                //---------erasing line----------
                                int max = Len - 1;
                                int line;
								for(int rows = Len - 1; rows > 0; rows--){
									line = 0;
									for(int col = 0; col < wid; col++){
										if(field[rows][col] != 0){
											line++;
										}
										field[max][col] = field[rows][col];
									}
										if(line < wid){
											max--;
										}
										else{
											score += 10;										
										}
                                }

                                //--------------Ending------------
                                if(!cfalling() || end()){
                                    sleep_for(1s);
                                    sleep_until(system_clock::now());									
									window1.close();
                                }

                                //--------------Building---------

                                window1.clear(Color::Black);
                                window1.draw(back);
                                for(int i = 0; i < Len; i++){
									for(int j = 0; j < wid; j++){
										if(field[i][j] == 0) continue;
										s.setTextureRect(IntRect(field[i][j]*18,0,18,18));//color
										s.setPosition(j*18,i*18);
										s.move(24,24);
										window1.draw(s);
									}
								}

                                dx = 0;
								rotate = false;
								delay = 0.5;

                                for(int i=0;i<4;i++){
                                    s.setTextureRect(IntRect(color*18,0,18,18));//color
                                    s.setPosition(a[i].x*18,a[i].y*18);
                                    s.move(24,24);
                                    window1.draw(s);
                                }
                                window1.display();
                            }
						break;
					case 1:
						window1.close();
						break;
					}
					break;
				}

				break;
			case Event::Closed:
				window1.close();

				break;
			}
		}

		window1.clear();
		m.draw(window1);
		window1.display();
	}

	RenderWindow window2(VideoMode(300,200),"Game Over!");
		while (window2.isOpen())
    	{
        	Event GmOr;
			while (window2.pollEvent(GmOr))
			{
				if (GmOr.type == Event::Closed)
					window2.close();
			}
			
			Text txt;
			Font fnt;
			if(!fnt.loadFromFile("hehe.TTF")){
				cout << "Game over Font not Loading!" << endl;
			}
			string scr = to_string(score);
			txt.setFont(fnt);
			txt.setFillColor(Color::Red);
			txt.setCharacterSize(30);
			txt.setString("GAME OVER!\nScore:\t" + scr);
			txt.setPosition(Vector2f(50, 70));
			window2.clear();
			window2.draw(txt);
			window2.display();
			
			sleep_for(3s);
			sleep_until(system_clock::now());
			window2.close();
		}
	return 0;
}