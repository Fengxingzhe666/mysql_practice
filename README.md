# MySQL基础使用自我练习  
在电脑上安装MySQL：https://blog.csdn.net/2402_85428625/article/details/146364846  
一个下载地址：https://dev.mysql.com/downloads/file/?id=478034  
变量种类，基础命令教程：https://blog.csdn.net/qq_55797703/article/details/140394423  
```
C:\Users\dell>mysql -uroot -p
Enter password: ******
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 9
Server version: 5.6.29-log MySQL Community Server (GPL)

Copyright (c) 2000, 2016, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> create database zzk;
Query OK, 1 row affected (0.00 sec)

mysql> use zzk;
Database changed

# 新建一个表，表名是student_info
mysql> create table student_info(
    -> stu_id INT primary key auto_increment,
    -> stu_name VARCHAR(20) not null,
    -> gender binary(1) not null default 1,
    -> age INT not null,
    -> stu_birthday DATE not null
    -> );
Query OK, 0 rows affected (0.01 sec)
```

## 常用的必须掌握的命令
```
# 增
insert into 表名 values (字段1值,...,字段n值),...,(字段1值,...,字段n值);
# 改
update 表名 字段1=值1,...,字段n=值n where 条件表达式;
# 删
delete from 表名 where 条件表达式;
# 查
select 字段1,...,字段n from 表名 where 条件表达式; # 查找符合条件的数据的某个字段
select * from 表名 where 条件表达式; # 查找符合条件的数据的所有字段
```

## C++与MySQL的互动  
我使用的编译器是Visual Studio 2022，首先需要将安装好的MySQL添加到项目地址中：  
右键项目->属性->C/C++->附加包含目录->（输入自己的MySQL安装目录的include文件夹，默认是：C:\Program Files\MySQL\MySQL Server 5.6\include）  
右键项目->属性->链接器->常规->附加库目录->（输入自己的MySQL安装目录的lib文件夹，默认是：C:\Program Files\MySQL\MySQL Server 5.6\lib）  

注意一个雷点，我在 Visual Studio 2022 实际使用时在#include<mysql.h>之前必须包含#include<WinSock.h>或#include<WinSock2.h>，否则会报错SOCKET未定义。  

首先先写好自己的mysql配置  
```c++
#include <iostream>
#include <WinSock2.h>//必须加在mysql.h前面
#include <mysql.h>

const char* host = "127.0.0.1";  //默认本机ip地址
const char* user = "root";       //默认用户为root
const char* pw = "123456";       //数据库密码，按照自己创建的写
const char* databse_name = "zzk";//数据库名称，按照自己创建的写
const int port = 3306;           //默认端口号为3306
```
接下来在main()函数中调用函数mysql_real_connect()连接到数据库：(这个函数返回布尔值表示是否连接成功，用于判断是否连接成功)  
```c++
int main()
{
    //初始化数据库
    MYSQL* con = mysql_init(NULL);
    //连接
    if (!mysql_real_connect(con, host, user, pw, databse_name, port, NULL, 0)) {
	    fprintf_s(stderr, "Failed to connect to database. Error: %s\n", mysql_error(con));
	    return -1;
    }
    std::cout << "Connected to MySQL." << std::endl;
    //设置连接的默认字符是 utf8，原始默认是 latin1，不使用可能会导致插入的中文是乱码
    mysql_set_character_set(con, "utf-8");
    //......
}
```
接下来，直接用mysql_query()函数通过命令行的字符串操作MySQL，这个函数如果执行失败会返回1，例如这里查找表student_info中的所有行：  
```c++
int main(){
    //......
    std::string order = "select * from student_info;";
    if(mysql_query(con, order.c_str())){
	    //如果执行失败就打印
	    fprintf_s(stderr, "Error: %s\n", mysql_error(con));
	    return -1;
    }
    //......
}
```
怎么把查询出来的结果显示或者赋值给需要的变量是需要自己去定义的，这里以一种控制台显示输出方式为例子：  
```c++
int main()
{
    //......
    //保存查询结果
    MYSQL_RES* res = mysql_store_result(con);
    my_ulonglong row = mysql_num_rows(res);
    unsigned int column = mysql_num_fields(res);
    for (int i = 0; i < row; i++){
	    MYSQL_ROW line = mysql_fetch_row(res);  //MYSQL_ROW的变量类型其实是char**
	    for (int j = 0; j < column; j++){
		    std::cout << line[j] << " ";
	    }
	std::cout << std::endl;
    }
    //关闭连接
    mysql_close(con);
    return 0;
}
```
