
#include "snake.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    Snake snake = Snake();

    for(int counter = 0;counter<5;counter++)
    {
        cout<<"ADD NODE?"<<endl;
        int x,y;
        cin>>x>>y;
        snake.addNode(x,y);

        int map[MAX_M][MAX_N];
        for(int i = 0 ; i<MAX_M ; i++)
                for(int j = 0 ; j<MAX_N ; j++)
                    map[i][j] = WHITE;
        snake.move();
        snake.print(map);
        cout<<"================="<<endl;
        for(int i = 0 ; i<MAX_M ; i++){

                for(int j = 0 ; j<MAX_N ; j++)
                {
                    switch (map[i][j]) {
                    case WHITE:
                        cout<<"  ";
                        break;
                    case BLACK:
                        cout<<"A ";
                        break;
                    case RED:
                        cout<<"B ";
                        break;
                    default:
                        break;
                    }
                }
                cout<<endl;
        }
        cout<<"==================="<<endl;



    }


}
