#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string.h>
using namespace std;

int num_bool;
int num_clause;
int value_var[300000];
int iftrue;
int ans_sum;
int num_var;
int pos_var[300000];
int value_clause_num[300];
int type_of_clauses;
int choices = 0;
typedef struct Bool_var
{
    int num;
    bool value = false;
    Bool_var* next = NULL;
}*bool_var;

struct clause
{
    int num;
    bool_var head = NULL;
    int isright = 0;
}*cs;

struct record
{
    int num = 0;
    int times = 0;
    int t_time = 0;
    int f_time = 0;
}var[300000];

struct T_marks
{
    int num = 0;
    int marks[2000];
}tmarks[20000];