
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define _max_n 30
#define _max_m 40
#define maxn 20
#define maxm 40

//Group
int ME_HEAD = 2 ;
int ME_BODY = 1 ;
int Enemy_Body =  111110;
int Enemy_Head =  222220;


int CurDirection = 0;

int map[_max_n][_max_m];
int DirX[4] = {0,-1,0,1};
int DirY[4] = {-1,0,1,0};
int HeadX = -1;
int HeadY = -1;

//判断是否开启尖刺
int isSpineOn = 0;

//敌人阵营数量
int EnemyGroupNum = 0;

//const int Alert_range ;

void encodeMap(){
    
    for(int i = 0;i<maxn;i++)
        for(int j = 0 ;j<maxm;j++){
            if(map[i][j] == 2017202034){
                map[i][j] = ME_BODY;
            }
            else if(map[i][j] >= 70340 && map[i][j] <=70343){
                CurDirection = map[i][j] - 70340;
                map[i][j] = ME_HEAD;
                HeadX = i;
                HeadY = j;
               
            }
            else if(map[i][j] <= 0 ){
                //Nothing happen
            }
            else if(map[i][j] >= 2000000000){
                map[i][j] = Enemy_Body;
            }
            else {
                EnemyGroupNum++;
                int Enemy_head_dir;
                Enemy_head_dir = map[i][j]%10;
                map[i][j] = Enemy_Head+Enemy_head_dir;

            }
            
        }
    //判断尖刺状态
    for(int i = 0;i<maxn;i++)
        for(int j = 0 ;j<maxm;j++){
            if( isEnemyHead(map[i][j])){
                int Enemy_head_dir;
                Enemy_head_dir = map[i][j]%10;
                if((map[i+DirX[Enemy_head_dir]][j+DirY[Enemy_head_dir]] == ME_BODY)||(map[i+DirX[Enemy_head_dir]][j+DirY[Enemy_head_dir]] == ME_HEAD))
                    isSpineOn = 1;

        }
        }


}
int isAtWall(int x,int y){
    return (x == 0 || x == maxn-1||y ==0 || y ==maxm -1);
}


int isEnemyHead(int x){
    return (x>=Enemy_Head)&&(x<=Enemy_Head+3);
}


//判断到某一点之间有没有障碍物
int judgeToPoint(int xx,int yy){
    return 1;
}

//判断能否前往墙壁
int dirToWall(){
    int flag = 1;
    //int k[4];
    //for(int i = 0 ; i<4;i++)k[i]=-1;
    if(((CurDirection+2)%4) != 0){
        flag = 1;
        for(int y = 0 ; y < HeadY ; y++){
            if(map[HeadX][y]>0 && map[HeadX][y]!=ME_BODY){
                flag = 0;
            }
        }
        if(flag == 1) return 0;
    }
    if(((CurDirection+2)%4) != 1){
        flag = 1;
        for(int x = 0 ; x < HeadX ; x++){
            if(map[x][HeadY]>0 && map[x][HeadY]!=ME_BODY){
                flag = 0;
            }
        }
        if(flag == 1) return 1;
    }
    
    if(((CurDirection+2)%4) != 2){
        flag = 1;
        for(int y = maxm ; y > HeadY ; y--){
            if(map[HeadX][y]>0 && map[HeadX][y]!=ME_BODY){
                flag = 0;
            }
        }
        if(flag == 1 ) return 2;
    }
    
    if(((CurDirection+2)%4) != 3){
        flag = 1;
        for(int x = maxn ; x > HeadX ; x--){
            if(map[x][HeadY]>0 && map[x][HeadY]!=ME_BODY){
                flag = 0;
            }
        }
        if(flag == 1) return 3;
    }
    
    return -1;
    
}

//TODO : 报警函数


int isAvaluble(int x,int y){
    //return (x>-1 && x < maxn && y>-1 && y<maxm && !(isEnemyHead(x,y)) && (map[x][y]!=Enemy_Body) ) ;
    return 1;
}


//检测大乱斗是否结束 返回1/0 敌人数量在5之下认为乱斗结束。
int isSmashOver(){
    if(EnemyGroupNum < 5)
    return 1 ;
    else return 0 ;
}



//苟避决策
int Solve(){
    
    
    //未达到墙
    if(!isAtWall(HeadX,HeadY)){
        int x_next = HeadX + DirX[CurDirection];
        int y_next = HeadY + DirY[CurDirection];
        int ToWall = dirToWall();
        if(ToWall != -1 && isAvaluble(HeadX + DirX[ToWall],HeadY + DirY[ToWall]))return ToWall;
        else if(!isAvaluble(x_next,y_next)){
            int tmp_x = HeadX + DirX[(CurDirection+1)%4];
            int tmp_y = HeadY + DirY[(CurDirection+1)%4];
            if(isAvaluble(tmp_x,tmp_y))
                return (CurDirection+1)%4;
            else return (CurDirection-1)%4;

        }

        else {
            srand((unsigned)time(NULL));
            return (CurDirection+(random()%2))%4;  //这里就是听天由命了！
        }
    }
    else if (isAtWall(HeadX,HeadY)){
        int x_next = HeadX + DirX[CurDirection];
        int y_next = HeadY + DirY[CurDirection];
        if(isAvaluble(x_next,y_next))return CurDirection;
        else if(HeadX == 0 && HeadY == 0){
            if(CurDirection == 0)return 3;
            if(CurDirection == 1)return 2;
        }
        else if(HeadX == maxn-1 && HeadY == 0){
            if(CurDirection == 3)return 2;
            if(CurDirection == 0)return 1;
        }
        else if(HeadX == maxn-1 && HeadY == maxm -1){
            if(CurDirection == 2)return 1;
            if(CurDirection == 3)return 0;
        }
        else if(HeadX == 0 && HeadY == maxm -1){
            if(CurDirection == 1)return 0;
            if(CurDirection == 2)return 3;
        }
        else {
            int tmp_x = HeadX + DirX[(CurDirection+1)%4];
            int tmp_y = HeadY + DirY[(CurDirection+1)%4];
            if(isAvaluble(tmp_x,tmp_y))
                return (CurDirection+1)%4;
            else return (CurDirection-1)%4;
        }
        
    }
    return 0;
}

//坐收渔利决策

int smashOverSOlve(){
    int x_next = HeadX + DirX[CurDirection];
    int y_next = HeadY + DirY[CurDirection];
    if(isAvaluble(x_next,y_next) && map[x_next,y_next] < 0&& map[x_next,y_next] > -6)return CurDirection;
    int LeftValue = 0;
    int RightValue = 0;
    if(CurDirection == 0){
        for(int i = HeadX - 2;i<=HeadX-1;i++){
            if(i<0||i>=maxn)continue;
            for(int j = HeadY - 2;j<=HeadY+2;j++){
                if((j<0||j>=maxm)||map[i][j]==ME_BODY)continue;
                RightValue -=map[i][j];

            }
        }
        for(int i = HeadX + 1;i<=HeadX+2;i++){
            if(i<0||i>=maxn)continue;
            for(int j = HeadY - 2;j<=HeadY + 2;j++){
                if((j<0||j>=maxm)||map[i][j]==ME_BODY)continue;
                LeftValue -=map[i][j];

            }
        }
        }
    else if(CurDirection == 1){
    for(int i = HeadX - 2;i<=HeadX+2;i++){
        if(i<0||i>=maxn)continue;
        for(int j = HeadY+ 1;j<=HeadY+2;j++){
            if((j<0||j>=maxm)||map[i][j]==ME_BODY)continue;
            RightValue -=map[i][j];

        }
    }
    for(int i = HeadX - 2;i<=HeadX+2;i++){
        if(i<0||i>=maxn)continue;
        for(int j = HeadY - 1;j>=HeadY - 2;j--){
            if((j<0||j>=maxm)||map[i][j]==ME_BODY)continue;
            LeftValue -=map[i][j];

        }
    }
    }
    else if(CurDirection == 2){
    for(int i = HeadX + 1;i<=HeadX+2;i++){
        if(i<0||i>=maxn)continue;
        for(int j = HeadY - 2;j<=HeadY+2;j++){
            if((j<0||j>=maxm)||map[i][j]==ME_BODY)continue;
            RightValue -=map[i][j];

        }
    }
    for(int i = HeadX - 1;i>=HeadX-2;i--){
        if(i<0||i>=maxn)continue;
        for(int j = HeadY - 2;j<=HeadY + 2;j++){
            if((j<0||j>=maxm)||map[i][j]==ME_BODY)continue;
            LeftValue -=map[i][j];

        }
    }
    }
    else if(CurDirection == 3){
    for(int i = HeadX - 2;i<=HeadX+2;i++){
        if(i<0||i>=maxn)continue;
        for(int j = HeadY - 2;j<=HeadY-1;j++){
            if((j<0||j>=maxm)||map[i][j]==ME_BODY)continue;
            RightValue -=map[i][j];

        }
    }
    for(int i = HeadX - 5;i<=HeadX+5;i++){
        if(i<0||i>=maxn)continue;
        for(int j = HeadY + 5 ;j>=HeadY + 1;j--){
            if((j<0||j>=maxm)||map[i][j]==ME_BODY)continue;
             LeftValue -=map[i][j];

        }
    }
    }

    //srand((unsigned)time(NULL));
    if(LeftValue == RightValue) return (CurDirection);
    else if( LeftValue>RightValue) return (CurDirection-1)%4 ;
    else return (CurDirection+1)%4;

}



//输入地图
void get_map(){
    
    for(int i = 0 ; i<_max_n ; i++)
        for(int j = 0 ; j<_max_m ; j++)
            scanf("%d", &map[i][j]);
    
    
}


