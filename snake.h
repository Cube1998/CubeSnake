#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include "snakenode.h"
#include <QDebug>
using namespace std;

class Snake
{
public:
    Snake(int Dir = UP);


    void print(int map[MAX_M][MAX_N]);

    //身体移动
    void move();

    //Added Node
    void addNode(int xx,int yy){
         snake_node* tmp = new snake_node(xx,yy,Body_Color,(*(Body.end()-1)));
         this->Body.push_back(tmp);
         qDebug()<<*tmp;
         qDebug()<<"Added";
    }

    //转换方向
    void changeDir(int TurnTo){this->Direction = (Direction + TurnTo)%4;}



    //蛇身队列
    vector<snake_node* > Body ;




private:

    //蛇身颜色
    int Body_Color = RED;
    //蛇头移动方向
    int Direction;





};

Snake::Snake(int Dir)
{
    srand((unsigned)time(NULL));
    snake_node* head = new snake_node(rand()%MAX_M,rand()%MAX_N,BLACK,NULL);
    this->Body.push_back(head);
    this->Body_Color = RED;
    this->Direction = Dir;
}

void Snake::move(){

    vector<snake_node*>::iterator it = Body.begin();

    it++;
    for(;it!=Body.end();it++)
    {
        (*it)->setXYasNode(*((*it)->getLastNode()));

    }
    Body[0]->moveDir(Direction);

}
void Snake::print(int map[MAX_M][MAX_N]){
    vector<snake_node*>::iterator it = Body.begin();
    map[(*it)->getTransferedX()][(*it)->getTransferedY()] = (*it)->getColorGroup();
    it++;


    for(;it!=Body.end();it++)
    {
        map[(*it)->getTransferedX()][(*it)->getTransferedY()] = (*it)->getColorGroup();

    }
}


#endif // SNAKE_H
