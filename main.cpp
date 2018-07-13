
#include "snake.h"
#include <QDebug>
#include "stdio.h"
#include "stdlib.h"
#include "time.h"


int main(int argc, char *argv[])
{
    Snake snake = Snake();

    for(int counter = 0;counter<3;counter++)
    {
        cout<<"ADD NODE?"<<endl;
        qDebug()<<"cout<<ADD NODE?<<endl;";

        //cin>>x>>y;

        srand((unsigned)time(NULL));

        int ran = (int)random()%4;

        //snake.addNode((*(snake.Body.end()-1))->getTransferedX()+dirX[ran],(*(snake.Body.end()-1))->getTransferedY()+dirY[ran]);
        snake.addNode((*(snake.Body.end()-1))->getTransferedX(),(*(snake.Body.end()-1))->getTransferedY()-1);
        qDebug()<<snake.Body.size();

        int map[MAX_M][MAX_N];
        for(int i = 0 ; i<MAX_M ; i++)
                for(int j = 0 ; j<MAX_N ; j++)
                    map[i][j] = WHITE;
        snake.move();
        snake.print(map);
        cout<<"================="<<endl;
        for(int i = 0 ; i<MAX_N ; i++){

                for(int j = 0 ; j<MAX_M ; j++)
                {
                    switch (map[j][i]) {
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
