#include <bits/stdc++.h>
using namespace std;
void print_sudoku(int sudoku[][10]);
bool copy_sudo(int sudoku[][10],int sudoku2[][10])
{
    for(int i = 7; i <= 9; i++)
        for(int j = 7; j <= 9; j++)
            sudoku2[i - 6][j - 6] = sudoku[i][j];
    return true;
}
int pos_g(int x)
{
    if(x >= 1 and x <= 3)   return 1;
    if(x >= 4 and x <= 6)   return 4;
    if(x >= 7 and x <= 9)   return 7;
    return 0;
}
bool check_pos(int x,int y,int v,int sudoku[][10])
{
    if(sudoku[y][x] != 0)   return false;
    for(int i = 1; i <= 9; i++)
        if(sudoku[y][i] == v)   return false;
    for(int j = 1; j <= 9; j++)
        if(sudoku[j][x] == v)   return false;
    int ii = pos_g(y);
    int jj = pos_g(x);
    for(int i = ii; i <= ii + 2; i++)
        for(int j = jj; j <= jj + 2; j++)
            if(sudoku[i][j] == v)   return false;
    sudoku[y][x] = v;
    return true;
}

void rand_array(int* a)
{
    int k;
    for(int i = 1; i <= 9; i++)
        a[i] = i;
    for(int i = 1; i <= 9; i++)
    {
        k = rand() % 9 + 1;
        swap(a[i],a[k]);
    }
}

bool create_sudoku(int y,int v,int sudoku[][10])
{
    int a[10];
    rand_array(a);
    for(int i = 1; i <= 9; i++)
    {
        int x = a[i];
        if(check_pos(x,y,v,sudoku) == true)
        {
            if(y == 9)
            {
                if(v == 9 or create_sudoku(1, v + 1, sudoku))
                    return true;
            }
            else
            {
                if(create_sudoku(y + 1,v,sudoku))   
                    return true;
            }
            sudoku[y][x] = 0;
        }
    }
    return false;
}

bool create_sudoku_2(int y,int v,int sudoku[][10])
{
    int a[10];
    rand_array(a);
    for(int i = 1; i <= 9; i++)
    {
        int x = a[i];
        int temp_flag = 0;
        if(y <= 3 and x <= 3 and sudoku[y][x] == v)   temp_flag = 1;
        if(check_pos(x,y,v,sudoku) == true or temp_flag)
        {
            if(y == 9)
            {
                if(v == 9 or create_sudoku_2(1, v + 1, sudoku))
                    return true;
            }
            else
            {
                if(create_sudoku_2(y + 1,v,sudoku))   
                    return true;
            }
            if(!temp_flag)  sudoku[y][x] = 0;
        }
    }
    return false;
}
void print_sudoku(int sudoku[][10])
{
    for(int i = 1; i <= 9; i++)
    {
        for(int j = 1; j <= 9; j++)
            cout << sudoku[i][j] << " ";
        cout << endl;
    }
}

void print_dosudoku(int sudoku[][10],int sudoku2[][10])
{
    for(int i = 1; i <= 15; i++)
    {
        
        for(int j = 1; j <= 15; j++)
        {
            if(i <= 6 and j >= 10)  cout << "  ";
            else
                if(i >= 10 and j <= 6)  cout << "  ";
                else
                    if(i <= 9 and j <= 9)   cout << sudoku[i][j] << " ";
                    else
                        cout << sudoku2[i - 6][j - 6] << " ";
            
        }
        cout << endl;
    }
}

void create_dosudoku(int sudoku[][10],int sudoku2[][10])
{
    while(!create_sudoku(1,1,sudoku))   memset(sudoku,0,sizeof(int) * 100);
    bool flag = true;
    copy_sudo(sudoku,sudoku2);
    while(!create_sudoku_2(1,1,sudoku2))    memset(sudoku,0,sizeof(int) * 100);
    return ;
}

void dig_sudoku(int sudoku[][10])
{
    int sum = 0;
    while(sum <= 45)
    {
        int temp_x = rand() % 9 + 1;
        int temp_y = rand() % 9 + 1;
        if(sudoku[temp_x][temp_y] != 0)
        {
            sum++;
            sudoku[temp_x][temp_y] = 0;
        }
    }
}

void translate_sudoku(char filename[],int sudoku[][10],int sudoku2[][10])
{
    ofstream fp;
    fp.open(filename,ios::out);
    fp << "p cnf 2000 ";
    int temp_su = 24138;
    for(int i = 1; i <= 9; i++)
    {
        for(int j = 1; j <= 9; j++)
        {
            if(sudoku[i][j] != 0)   temp_su++;
            if(sudoku2[i][j] != 0)  temp_su++;   
        }
    }
    fp << temp_su << endl;
    //输出单字句语句
    for(int i = 1; i <= 9; i++)
    {
        for(int j = 1; j <= 9; j++)
        {
            if(sudoku[i][j] != 0)
                fp << i * 100 + j * 10 + sudoku[i][j] << " " << 0 << endl;
            if(sudoku2[i][j] != 0)
                fp << 1000 + i * 100 + j * 10 + sudoku2[i][j] << " " << 0 << endl;
        }
    }
    //输出宫格部分
    for(int i = 1; i <= 9; i++)
    {
        for(int j = 1; j <= 9; j++)
        {
            for(int k = 1; k <= 9; k++) fp << i * 100 + j * 10 + k << " ";
            fp << 0 << endl;
            for(int k = 1; k <= 8; k++)
                for(int kk = k + 1; kk <= 9; kk++)
                    fp << -1 * (i * 100 + j * 10 + k) << " " << -(i * 100 + j * 10 + kk) << " " << 0 << endl;
            for(int k = 1; k <= 9; k++) fp << 1000 + i * 100 + j * 10 + k << " ";
            fp << 0 << endl;
            for(int k = 1; k <= 8; k++)
                for(int kk = k + 1; kk <= 9; kk++)
                    fp << -1 * (1000 + i * 100 + j * 10 + k) << " " << -(1000 + i * 100 + j * 10 + kk) << " " << 0 << endl;
        }
    }
    //输出行部分
    for(int i=1;i<=9;i++)  //第i行
    {
        for(int j=1;j<=9;j++) //第j个数字
        {
            for(int k=1;k<=9;k++)   //第几列
                fp << i*100+k*10+j << " ";
            fp << 0 <<endl;
        }
        for(int j=1;j<=9;j++)      //不同时为j
        {
            for(int k=1;k<=8;k++)
            {
                for(int kk=k+1;kk<=9;kk++)
                fp << -(i*100+k*10+j) << " " << -(i*100+kk*10+j) << " " << 0 << endl;
            }
        }
        for(int j=1;j<=9;j++) //数字
        {
            for(int k=1;k<=9;k++)   //列数
            {
                fp << 1000+i*100+k*10+j << " ";
            }
            fp << 0 <<endl;
        }
        for(int j=1;j<=9;j++)      //不同时为j
        {
            for(int k=1;k<=8;k++)
            {
                for(int kk=k+1;kk<=9;kk++)
                fp << -(1000+i*100+k*10+j) << " " << -(1000+i*100+kk*10+j) << " " << 0 << endl;
            }
        }
    }
    //输出列部分
    for(int i=1;i<=9;i++)  //第i列
    {
        for(int j=1;j<=9;j++) //数字
        {
            for(int k=1;k<=9;k++)   //行数
            {
                fp << k*100+i*10+j << " ";
            }
            fp << 0 <<endl;
        }
        for(int j=1;j<=9;j++)      //不同时为j
        {
            for(int k=1;k<=8;k++)
            {
                for(int kk=k+1;kk<=9;kk++)
                fp << -(k*100+i*10+j) << " " << -(kk*100+i*10+j) << " " << 0 << endl;
            }
        }
        for(int j=1;j<=9;j++) //数字
        {
            for(int k=1;k<=9;k++)   //行数
            {
                fp << 1000+k*100+i*10+j << " ";
            }
            fp << 0 <<endl;
        }
        for(int j=1;j<=9;j++)      //不同时为j
        {
            for(int k=1;k<=8;k++)
            {
                for(int kk=k+1;kk<=9;kk++)
                fp << -(1000+k*100+i*10+j) << " " << -(1000+kk*100+i*10+j) << " " << 0 << endl;
            }
        }
    }
    //单元格部分
    for(int i=1;i<=7;i+=3)         //第i个九宫格的第一行
    {
        for(int j=1;j<=7;j+=3)    //第j个九宫格的第一列
        {
            for(int k=1;k<=9;k++)  //k是数
            {
                for(int ii=i;ii<=i+2;ii++)
                {
                    for(int jj=j;jj<=j+2;jj++)
                    {
                        fp << ii*100+jj*10+k << " ";
                    }
                }
                fp << 0 << endl;
            }
            for(int n=1;n<=9;n++)       //数      
            {
                for(int jj=j;jj<=j+2;jj++)    //去分析每一列的第一个的比较状况
                {
                    fp << -(i*100+j*10+n) << " " << -(i*100+j*10+n+100) << " " << 0 << endl;
                    fp << -(i*100+j*10+n) << " " << -(i*100+j*10+n+200) << " " << 0 << endl;
                    for(int k=jj+1;k<=j+2;k++)
                    {
                        fp << -i << j << n << " " << -i << k << n << " " << 0 << endl;
                        fp << -i << j << n << " " << -(i+1) << k << n << " " << 0 << endl;
                        fp << -i << j << n << " " << -(i+2) << k << n << " " << 0 << endl;
                    }
                }
                for(int jj=j;jj<=j+2;jj++)    //去分析每一列的第二个的比较状况
                {
                    fp << -(i+1) << j << n << " " << -(i+2) << j << n << " " << 0 << endl;
                    for(int k=jj+1;k<=j+2;k++)
                    {
                        fp << -(i+1) << j << n << " " << -i << k << n << " " << 0 << endl;
                        fp << -(i+1) << j << n << " " << -(i+1) << k << n << " " << 0 << endl;
                        fp << -(i+1) << j << n << " " << -(i+2) << k << n << " " << 0 << endl;
                    }
                }
                for(int jj=j;jj<=j+2;jj++)    //去分析每一列的第三个的比较状况
                {
                    for(int k=jj+1;k<=j+2;k++)
                    {
                        fp << -(i+2) << j << n << " " << -i << k << n << " " << 0 << endl;
                        fp << -(i+2) << j << n << " " << -(i+1) << k << n << " " << 0 << endl;
                        fp << -(i+2) << j << n << " " << -(i+2) << k << n << " " << 0 << endl;
                    }
                }
            }
            for(int k=1;k<=9;k++)  //k是数
            {
                for(int ii=i;ii<=i+2;ii++)
                {
                    for(int jj=j;jj<=j+2;jj++)
                    {
                        fp << 1000+ii*100+jj*10+k << " ";
                    }
                }
                fp << 0 << endl;
            }
            for(int n=1;n<=9;n++)       //数      
            {
                for(int jj=j;jj<=j+2;jj++)    //去分析每一列的第一个的比较状况
                {
                    fp << -1 << i << j << n << " " << -1 << i+1 << j << n << " " << 0 << endl;
                    fp << -1 << i << j << n << " " << -1 << i+2 << j << n << " " << 0 << endl;
                    for(int k=jj+1;k<=j+2;k++)
                    {
                        fp << -1 << i << j << n << " " << -1 << i << k << n << " " << 0 << endl;
                        fp << -1 << i << j << n << " " << -1 << i+1 << k << n << " " << 0 << endl;
                        fp << -1 << i << j << n << " " << -1 << i+2 << k << n << " " << 0 << endl;
                    }
                }
                for(int jj=j;jj<=j+2;jj++)    //去分析每一列的第二个的比较状况
                {
                    fp << -1 << i+1 << j << n << " " << -1 << i+2 << j << n << " " << 0 << endl;
                    for(int k=jj+1;k<=j+2;k++)
                    {
                        fp << -1 << i+1 << j << n << " " << -1 << i << k << n << " " << 0 << endl;
                        fp << -1 << i+1 << j << n << " " << -1 << i+1 << k << n << " " << 0 << endl;
                        fp << -1 << i+1 << j << n << " " << -1 << i+2 << k << n << " " << 0 << endl;
                    }
                }
                for(int jj=j;jj<=j+2;jj++)    //去分析每一列的第三个的比较状况
                {
                    for(int k=jj+1;k<=j+2;k++)
                    {
                        fp << -1 << i+2 << j << n << " " << -1 << i << k << n << " " << 0 << endl;
                        fp << -1 << i+2 << j << n << " " << -1 << i+1 << k << n << " " << 0 << endl;
                        fp << -1 << i+2 << j << n << " " << -1 << i+2 << k << n << " " << 0 << endl;
                    }
                }
            }
        }
    }
    //关联部分
    for(int i=7;i<=9;i++)
    {
        for(int j=7;j<=9;j++)        
        {
            for(int k=1;k<=9;k++)
            {
                fp << -(i*100+j*10+k) << " " << 1000+(i-6)*100+(j-6)*10+k << " " << 0 << endl;
                fp << i*100+j*10+k << " " << -(1000+(i-6)*100+(j-6)*10+k) << " " << 0 << endl;
            }
        }
    }
    fp << 0 << endl;
    fp.close();
    return ;
}


