#ifndef SNAKENODE_H
#define SNAKENODE_H
//C++ STL
#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>


//QtLibrary
#include <QPoint>
//Color
#define BLACK 0
#define WHITE 1
#define RED   2
#define YELLOW 3
#define GREEN 4

//Map
#define MAX_M 30
#define MAX_N 40

//DIRECTION
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

//Turn Dir Command
#define AntiClockOrder 1
#define ClockOrder -1


//define Grids' data
#define GRIDS_WIDTH 30
#define GRIDS_HEIGHT 30

static const int dirX[4] = {0,-1,0,1};
static const int dirY[4] = {-1,0,1,0};

using namespace std;


class snake_node : public QPoint{
public:
    //snake_node(){this->next = NULL; this->Color_Group = Black }
    snake_node(int x = -1,int y =-1,int Color_Group = BLACK,snake_node* lastNode = NULL){
        this->Color_Group = Color_Group;
        this->last = lastNode;

        this->transferedX = x;
        this->transferedY = y;
        this->setX(x*GRIDS_WIDTH);
        this->setY(y*GRIDS_HEIGHT);

    }

    //内联函数
    //Color 操作
    int getColorGroup(){return Color_Group;}
    void setColorGroup(int Color){this->Color_Group = Color;}

    //下一个节点
    snake_node* getLastNode(){return this->last;}
    void setNextNode(snake_node* last){this->last = last;}

    //更改坐标
    void setTransferedX(int x){this->setX(x*GRIDS_WIDTH);this->transferedX = x;}
    void setTransferedY(int y){this->setY(y*GRIDS_HEIGHT);this->transferedY = y;}
    void updateXY(){
        this->setX(transferedX*GRIDS_WIDTH);
        this->setY(transferedY*GRIDS_HEIGHT);
    }
    //根据一个snake_node更改坐标
    void setXYasNode(snake_node& t){
        this->setTransferedX(t.getTransferedX());
        this->setTransferedY(t.getTransferedY());
        this->updateXY();
    }

    //获取坐标
    int getTransferedX(){return this->transferedX;}
    int getTransferedY(){return this->transferedY;}

    //坐标上下左右移动
    void moveDir(int Dir){
        this->transferedX += dirX[Dir];
        this->transferedY += dirY[Dir];
        this->updateXY();

    }

private:
    //下一节点
    snake_node* last = NULL;
    //颜色组别
    int Color_Group = BLACK;
    //转换后的坐标
    int transferedX;
    int transferedY;

};

#endif // SNAKENODE_H
