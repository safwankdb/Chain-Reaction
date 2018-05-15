#include <bits/stdc++.h>
using namespace std;
struct point
{
    int val=0;
    int max;
};
point** gridmaker()
{
    point** ans=0;
    ans = new point*[9];
    
    for(int i=0;i<9;i++)
    { 
        ans[i]= new point[6];
         for(int j=0;j<6;j++)
         {
             if((i==8||i==0)&&(j==5||j==0))
             {
                 ans[i][j].max=2;
             }
             else if(i>0&&i<8&&j>0&&j<5)
             {
                 ans[i][j].max=4;
             }
             else ans[i][j].max=3;
         }
     }    
     return ans;
}
int** abovemax(point** grid)
{
   int** ans;
   ans =new int*[9];
   for(int i=0;i<9;i++)
   {
       ans[i]=new int[6];
       for(int j=0;j<6;j++)
       {
           if(abs(grid[i][j].val)>=grid[i][j].max)
           {
               ans[i][j]=1;
           }
           else ans[i][j]=0;
       }
   }
   return ans;
}
void updateOnce(point** &grid, int x,int y,int sign)
{
    grid[x][y].val-= grid[x][y].max*sign;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<6;j++)
        {
            if((i==x+1||i==x-1)&&(j==y)||(i==x)&&(j==y+1||j==y-1))
            {
                grid[i][j].val= sign*(abs(grid[i][j].val)+1);
            }
        }
    }
    
}
void update(point** &grid,int** listnum,int sign)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<6;j++)
        {
           if(listnum[i][j]==1)
               updateOnce(grid,i,j,sign);
        }
    }
}
bool checklegal(point** grid,int x,int y,int sign)
{   
    bool legal=1;
    if(grid[x][y].val*sign<0)
        return 0;
    if(x>=0&&x<=8&&y>=0&&y<=5)
      {
          return 1;
      }
     
    return 0;    
}
bool notnull(int** list)
{
    bool b=0;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(list[i][j])
            {
                b=1;
                break;
            }
        }
    }
    return b;
}
bool checkWin(point** myGrid,int count)
{
    if(count<2)
        return false;
    bool flag1=1,flag2=1;
    for(int i=0;i<9;i++)
        for(int j=0;j<6;j++)
        {
            if(myGrid[i][j].val>0)
                flag1=false;
            else if(myGrid[i][j].val<0)
                flag2=false;
        }
    return flag1+flag2;
}
int main()
{
    point** myGrid= gridmaker();
    
    
    int sign=1;
    int x,y;
    cin>>x;
    int count=0;
    cin>>y; 
    while(!checkWin(myGrid,count))
    {
        if(checklegal(myGrid,x,y,sign))
        {
            count++;
            myGrid[x][y].val+= sign;
            int** list = abovemax(myGrid);
            
            while(notnull(list))
            {
                update(myGrid,list,sign);
                list=abovemax(myGrid);
            }
            sign = -1*sign;
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<6;j++)
                {
                cout<<myGrid[i][j].val<<" ";
                }
                cout<<endl;
            }
            cout<<endl<<endl;
        }
        else cout<<"Illegal Move"<<endl<<endl<<endl;
        cin>>x;
        if(x==-1) break;
        cin>>y;
    }
    return 0;
}
