# MySQL基础使用练习  
在电脑上安装MySQL：https://blog.csdn.net/2402_85428625/article/details/146364846  
一个下载地址：https://dev.mysql.com/downloads/file/?id=478034  
基础命令教程：https://blog.csdn.net/qq_55797703/article/details/140394423  
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


