#include "def.h"
#include <cstdlib>
#include "im_fun_3.h"
using namespace std;
bool cmp(clause t1,clause t2)
{
    return t1.num < t2.num;
};
bool cmp2(record a,record b)
{
    return a.times > b.times;
}
void putin(char filename[],int flag)
{
    ifstream fp;
    fp.open(filename,ios::in);
    char ss;
    char s[100];
    while(1)
    {
        fp >> ss;
        if(ss == 'p') break;
    }
    fp >> s;
    fp >> num_bool;
    fp >> num_clause;
    cs = (clause *)malloc(sizeof(clause) * (num_clause + 10));
    for(int i = 1; i <= num_clause; i++)
    {
        int temp;
        bool_var last = NULL;
        while(1)
        {     
            fp >> temp;
            if(temp == 0)   break;
            cs[i].num++;
            bool_var temp_var;
            temp_var = (bool_var)malloc(sizeof(Bool_var));
            if(last)    last->next = temp_var;
            temp_var->num = temp;
            temp_var->next = NULL;
            if(!cs[i].head)   cs[i].head = temp_var;
            last = temp_var;
            if(temp < 0)    temp *= -1;
            if(value_var[temp] != 4)
            {
                var[++num_var].num = temp;
                var[num_var].times++;
                pos_var[temp] = num_var;
            }
            else
                var[pos_var[temp]].times++;
            value_var[temp] = 4;
        }
    }
    if(flag)    sort(var+1,var+num_var+1,cmp2);
    fp.close();
};
void sort_var(record tvar[])
{
    for(int i = 1; i <= num_clause; i++)
    {
        bool_var temp;
        temp = cs[i].head;
        while(temp)
        {
            if(value_var[abs(temp->num)] == 4)
            {
                tvar[abs(temp->num)].num = abs(temp->num);
                if(temp->num > 0)   tvar[temp->num].t_time++;
                else
                    tvar[abs(temp->num)].f_time++;
                tvar[abs(temp->num)].times++;
            }
            temp = temp->next;
        }
    }
    sort(tvar + 1,tvar + num_var + 1,cmp2);
    return ;
}
void putout()
{
    for(int i = 1; i <= num_clause; i++)
    {
        cout << i << endl;
        bool_var temp = cs[i].head;
        while(temp)
        {
            cout << temp->num << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}
void putout2()
{
    cout << "putout2:" << endl;
    for(int i = 1; i <= num_bool; i++)
        {
            if(value_var[i] == 1)   cout << i << " ";
            if(value_var[i] == 2)   cout << i * -1 << " ";
            if(value_var[i] == 0 or value_var[i] == 4)  cout << "0" << " ";
        }
        cout << endl;
}

void putout3(int times_marks)
{
    for(int i = 1; i <= times_marks; i++)
    {
        for(int j  = 1; j <= tmarks[i].num; j++)
            cout << tmarks[i].marks[j] << " ";
        cout << endl;
    }
    return ;
}
int check()
{
//    putout2();
    int flag = 1;
    int cnt = 0;
    for(int i = 1; i <= num_clause; i++)
    {
        bool_var temp;
        int sum = 0;
        int temp_sum = 0;
        int temp_sum_2 = 0;
        temp = cs[i].head;
        while(temp)
        {
            sum++;
            if(temp->num > 0 and value_var[temp->num] == 2)  temp_sum++;
            if(temp->num < 0 and value_var[-1 * temp->num] == 1)    temp_sum++;
            if(temp->num > 0 and value_var[temp->num] == 1)  temp_sum_2++;
            if(temp->num < 0 and value_var[-1 * temp->num] == 2)    temp_sum_2++;
            temp = temp->next;
        }
        if(sum == temp_sum) 
            flag = 0;           
        if(temp_sum_2 >= 1)
            cnt++;
    }
    if(flag == 0)   return 0;
    if(cnt != num_clause)   
        return 0;
    return 2;
};

bool Readcnf(char filename[],int flag)
{
    FILE *fp;
    fp = fopen(filename,"r+");
    if(!fp) 
    {
        cout << "文件读入失败" << endl;
        return false;
    }
    cout << "文件读入成功" << endl;
    putin(filename,flag);
    return true;
}

void putcnf(char filename[],int flag,clock_t start,clock_t end)
{
    ofstream op;
    op.open(filename,ios::out);
    if(flag == 2)
    {
        op << "s " << 1 << endl;
        op << "v ";
        for(int i = 1; i <= num_bool; i++)
        {
            if(value_var[i] == 1)   op << i << " ";
            else
                op << -1 * i << " ";
        }
        op << endl;
        double run_time = double(end - start)/CLOCKS_PER_SEC;
        op << "t ";
        op << run_time * 1000;
    }
    else
    {
        op <<"s 0"<< endl;
        double run_time = double(end - start)/CLOCKS_PER_SEC;
        op << "t ";
        op << run_time * 1000;
    }
    op.close();
    return ;
}

void Resetcnf()
{
    memset(var,0,sizeof(var));
    memset(tmarks,0,sizeof(tmarks));
    memset(pos_var,0,sizeof(pos_var));
    memset(value_var,0,sizeof(value_var));
    num_var = 0;
}

void putcnf_2(char filename[],int flag,clock_t start,clock_t end)
{
    ofstream fop;
    fop.open(filename,ios::out);
    if(flag == 1)
    {
        fop<< "s " << 1 << endl;
        fop << "v ";
        for(int i = 1; i <= num; i++)
        {
            if(ans_var[i] == 1)   fop << i << " ";
            else    
                fop << -1 * i << " ";
        }
        fop << endl;
        double run_time = double(end - start)/CLOCKS_PER_SEC;
        fop << "t ";
        fop << run_time * 1000;
    }
    else
    {
        fop <<"s 0"<< endl;
        double run_time = double(end - start)/CLOCKS_PER_SEC;
        fop << "t ";
        fop << run_time * 1000;
    }
    fop.close();
    return ;
}