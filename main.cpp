#include "im_fun_2.h"
#include "Sudoku.h"
using namespace std;
int sudoku[10][10];
int sudoku2[10][10];
int main()
{
    int op = 1;
    char ss[300];
    while(op)
    {
        printf("      Menu                                       \n");
	    printf("-------------------------------------------------\n");
	    printf("    	  1. Solvecnf       2.Verify \n");
        printf("          3. Createsudoku   4.Play\n");
	    printf("    	  0. Exit\n");
	    printf("-------------------------------------------------\n");
	    printf("    请选择你的操作[0~24]:");
        cin >> op;
        switch(op)
        {
            case 0:
                return 0;
            case 1:
            {
                cout << "请输入你要选择的算法" << endl;
                cout << "1 标记 2 标记 + 排序 3 链表 + 双子句" << endl;
                int temp_flag = 0;
                cin >> temp_flag;
                if(temp_flag == 1)
                {
                    cout << "请输入你要测试的算例文件名:" << endl;
                    Resetcnf();
                    cin >> ss;
                    if(!Readcnf(ss,0))  break;;
                    cout << "";
                    clock_t start;
                    clock_t end;
                    cout << "读取的文字数为：" << num_bool << "   " << "子句数为： " << num_clause << endl;
                    start = clock();  
                    cout << "开始运算" << endl;
                    dpll(0,0,1);
                    end = clock();
                    cout << "运算完成" << endl;
                    cout << "运算时间:" << endl << double(end - start)/CLOCKS_PER_SEC * 1000 <<"ms"<< endl;
                    cout << "请输入你要保存的结果的文件名" << endl;
                    cin >> ss;
                    putcnf(ss,check(),start,end);
                    cout << "保存完成" << endl;
                    free(cs);
                }
                if(temp_flag == 2)
                {
                    cout << "请输入你要测试的算例文件名:" << endl;
                    Resetcnf();
                    cin >> ss;
                    if(!Readcnf(ss,1))  break;
                    clock_t start;
                    clock_t end;
                    cout << "读取的文字数为：" << num_bool << "   " << "子句数为： " << num_clause << endl;
                    start = clock();  
                    cout << "开始运算" << endl;
                    dpll(0,0,1);
                    end = clock();
                    cout << "运算完成" << endl;
                    cout << "运算时间:" << endl << double(end - start)/CLOCKS_PER_SEC << endl;
                    cout << "请输入你要保存的结果的文件名" << endl;
                    cin >> ss;
                    putcnf(ss,check(),start,end);
                    cout << "保存完成" << endl;
                    free(cs);
                }   
                if(temp_flag == 3)
                {
                    cout << "请输入你要测试的算例文件名:" << endl;
                    Resetcnf();
                    cin >> ss;
                    if(scancnf(ss)) cout << "文件读取成功" << endl;
                    else
                    {
                        cout << "文件读取失败" << endl;
                        break;
                    }
                    Hnode *root;
                    cnf_to_lb(&root);
                    clock_t start;
                    clock_t end;
                    cout << "开始运算" << endl;
                    start = clock();
                    int tf = zdpll(root,4);
                    end = clock();
                    cout << "运算完成" << endl;
                    cout << "运算时间:" << endl << double(end - start)/CLOCKS_PER_SEC << endl;
                    cout << "请输入你要保存的结果的文件名" << endl;
                    cin >> ss;
                    putcnf_2(ss,tf,start,end);
                    cout << "保存完成" << endl;
                } 
                break;
            }
            case 2:
            {
                getchar();
                cout << "检测程序终端命令" << endl;
                char temp_ss[300];
                cin.getline(temp_ss,300);
                system(temp_ss);
                break;
            }
            case 3:
            {
                cout << "现在将创造一个双数独" << endl;
                memset(sudoku,0,sizeof(sudoku));
                memset(sudoku2,0,sizeof(sudoku2));
                create_dosudoku(sudoku,sudoku2);
                cout << "这是完整的数独" << endl;
                print_dosudoku(sudoku,sudoku2);
                cout << "现在将随机挖空" << endl;
                dig_sudoku(sudoku);dig_sudoku(sudoku2);
                cout << "这是处理后的数独" << endl;
                print_dosudoku(sudoku,sudoku2);
                cout << "请输入你要储存的文件的名字" << endl;
                cin >> ss;
                translate_sudoku(ss,sudoku,sudoku2);
                cout << "储存完成" << endl;
                break;
            }
            case 4:
            {
                cout << "开始玩游戏咯！！" << endl;
                system("./Test_pac/untitled.sh");
                break;
            }
        }
    }
    return 0;
}