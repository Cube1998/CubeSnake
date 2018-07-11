#ifndef SNAKE_H
#define SNAKE_H

#include "snakenode.h"


class Snake
{
public:
    Snake(int Dir = UP);


    void print();

    //身体移动
    void move();

    //转换方向
    void changeDir(int TurnTo){this->Direction = (Direction + TurnTo)%4;}






private:
    //蛇身队列
    vector<snake_node*> Body;
    //蛇身颜色
    int Body_Color = RED;
    //蛇头移动方向
    int Direction;





};
/*
Snake::Snake(int Dir )
{
    snake_node* head = new snake_node(5,5,BLACK,NULL);
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
*/


#endif // SNAKE_H
