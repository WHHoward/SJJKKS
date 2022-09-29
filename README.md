# SJJKKS
linux下实现，可视化已完成
操作手册：
首先确保你在一个Linux系统上运行该SAT求解系统
然后将这个库里的所有文件下下来，尤其是Test_pac文件，里面的文件缺失的话，将无法运行可视化界面
之后 编译 main.cpp  或 直接 运行生成的 main 可执行文件
然后你将看到终端所给你的指示
输入1 将进入 cnf文件求解功能
输入2 将进入 验证程序功能
该部分功能要输入的指令格式如下:
  wine verify.exe xxxx.cnf xxxx.res
或
  wine verify5000.exe xxxx.cnf xxxx.res
注意该验证程序无法验证不满足算例
输入3 将进入 双数独生成功能
输入4 将进入 数独游戏功能

注意所使用的.cnf文件格式应当参考所给的1.cnf文件
格式控制如下:
asdkljh
asdkjd 
asd/
以上都是注释说明行
p cnf a b/这一行要以p cnf 开始 a 为变元的数目 b 为子句的数目
x y z 0//接下来将有 b 行子句 每一个子句都应以0结尾

