#include "basic_fun.h"
using namespace std;
int make_marks(int ii,int symbol,int times_marks)
{
    int flag = 1;
    int sum_mark = 0;
    int mark = 0;
    if(ii != 0)
    {
        mark = ii * symbol;
        tmarks[times_marks].marks[++tmarks[times_marks].num] = mark;
        ans_sum++;
    }
    int check_flag = 0;
    while(flag == 1)
    {
        if(check_flag)  break;
        flag = 0;
        if(mark != 0)
        {
            flag = 1;
            for(int i = 1; i <= num_clause; i++)
            {
                bool_var temp = cs[i].head;
                while(temp and temp->num != mark * -1)   
                    temp = temp->next;
                if(temp)    
                    cs[i].num--;
                temp = cs[i].head;
                   cs[i].isright++;                 
            }
            mark = 0;
            continue;
        }
        for(int i = 1; i <= num_clause; i++)
        {
            if(cs[i].num == 0)
            {
                check_flag = 1;
                break;
            }
            if(cs[i].num == 1)
            {
                bool_var temp = cs[i].head;
                while(temp and value_var[abs(temp->num)] != 4)   temp = temp->next;
                if(temp) 
                {  
                    mark = temp->num;
                    if(mark > 0)    value_var[mark] = 1;
                    else 
                        value_var[mark * -1] = 2;
                    mark = temp->num;
                    tmarks[times_marks].marks[++tmarks[times_marks].num] = mark;
                    ans_sum++;
                    flag = 1;
                    break;
                }
                else   continue;
            }
        }
    }    
    return check_flag;
}
void back_marks(int times_marks)
{
    int sum_mark = tmarks[times_marks].num;
    for(int i = 1; i <= sum_mark; i++)
        {
            int temp_mark = tmarks[times_marks].marks[i];
            for(int j = 1; j <= num_clause; j++)
            {
                bool_var temp;
                temp = cs[j].head;
                while(temp)
                {
                    if(temp->num == -1 * tmarks[times_marks].marks[i])
                    {
                        cs[j].num++;
                        break;
                    }    
                    temp = temp->next;
                }
            }
            value_var[abs(tmarks[times_marks].marks[i])] = 4;
            ans_sum--;
        }
    tmarks[times_marks].num = 0;
    return ;
}
int dpll(int ii,int symbol,int level)
{
    int mark = 0;
    int check_flag = 0;
    check_flag = make_marks(ii,symbol,level);
    if(check_flag)
    {
        back_marks(level);
        return 0;
    }
    for(int si = 1; si <= num_bool; si++)
    {
        int i = var[si].num;    
        if(value_var[i] == 4)
        {
            value_var[i] = 1;
            int temp_flag = dpll(i,1,level + 1);
            if(temp_flag == 2)
                return 2;
            else
            {                   
                value_var[i] = 2;
                temp_flag = dpll(i,-1,level + 1);
                if(temp_flag == 0)  
                {
                    back_marks(level);
                    return 0;
                }
                if(temp_flag == 2)  return 2;
            }
        }
    }
    int temp_check = check();
    if(temp_check == 1) return 1;
    else if (temp_check == 2)   return 2;
    else
    {
        back_marks(level);
        return 0;
    }  
    return 0;
};
