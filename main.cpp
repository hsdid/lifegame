#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

using namespace std;
using namespace sf;


#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>


//if( i<=30 || ( i>=571 && i<=600))

int checkneighbors(int i, int grid[])
{
    int sum_neighbors = 0;
    int tab [8] = {i-31, i-30, i-29
                    ,i-1,        i+1,
                    i+29, i+30, i+31};
    for(int i=0 ;i<8; i++)
    {
        if( grid[tab[i]] == 1 )
        sum_neighbors += 1;
    }

    return sum_neighbors;
}



int main()
{


     bool isPlaying = true;
    const int CELL_SIZE = 30;
    const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
    const int GRID_WIDTH = 30;
    const int GRID_HEIGHT = 20;
    const int FIELD = GRID_WIDTH * GRID_HEIGHT;
    /// its a our board where cells will live
    int grid[FIELD]={};
    int second_grid[FIELD];

    srand(time(NULL));
    ///nadawanie wartosci calls
    for(int i =0; i<FIELD; i++)
    {
        grid[i] = (double(rand())/RAND_MAX < 0.1) ? 1:0;

    }

    /// Rendering window which has
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT + 50 ),"Game of Life");
   ///main loop
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {

            switch(event.type)
            {

            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space)
                    isPlaying = !isPlaying;

            case sf::Event::MouseButtonPressed:
                if (!isPlaying && event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = double(event.mouseButton.x)/CELL_SIZE;
                    int y = double(event.mouseButton.y)/CELL_SIZE;
                    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
                        grid[x + y * GRID_WIDTH] = !grid[x + y * GRID_WIDTH];
                }
                break;
            }
        }

        ///display grid and prepare grid Next
        window.clear(sf::Color::White);
        for(int x=0; x<GRID_WIDTH; x++)
        {
            for(int y=0; y<GRID_HEIGHT; y++)
            {
                ///draw cell
                sf::RectangleShape cell;
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                cell.setSize(CELL_VECTOR);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color(153, 153, 153));


                if(grid[x + y * GRID_WIDTH] == 1)
                    cell.setFillColor(sf::Color::Green);
                else
                    cell.setFillColor(sf::Color::White);
                window.draw(cell);


            }
        }
        if(isPlaying)
       {
            for(int i=0; i<(GRID_HEIGHT*GRID_WIDTH); i++)
            {
                second_grid[i] = grid[i];

                /*
                    /// if only one grid
                     if(grid[i] == 1 && (checkneighbors(i,grid)) < 2 ||(checkneighbors(i,grid)) > 3 )
                        grid[i] = 0;
                    else if( checkneighbors(i,grid) == 3)
                        grid[i] = 1;
                */

                if(grid[i] == 1 && (checkneighbors(i,grid)) < 2 ||(checkneighbors(i,grid)) > 3 )
                    second_grid[i] = 0;
                else if( checkneighbors(i,grid) == 3)
                    second_grid[i] = 1;

            }

            for(int i=0; i<FIELD; i++)
            {
                grid[i] = second_grid[i];
            }
        }

        window.display();
        sf::sleep(sf::milliseconds(500));
    }

}
