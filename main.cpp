#include <iostream>
#include <winsock.h>//必须加在mysql.h前面
#include <mysql.h>

const char* host = "127.0.0.1";
const char* user = "root";
const char* pw = "123456";
const char* databse_name = "zzk";
const int port = 3306;

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

	std::string order = "select * from student_info;";
	if(mysql_query(con, order.c_str())){
		//如果执行失败就打印
		fprintf_s(stderr, "Error: %s\n", mysql_error(con));
		return -1;
	}
	//保存查询结果
	MYSQL_RES* res = mysql_store_result(con);
	my_ulonglong row = mysql_num_rows(res);
	unsigned int column = mysql_num_fields(res);
	for (int i = 0; i < row; i++){
		MYSQL_ROW line = mysql_fetch_row(res);
		for (int j = 0; j < column; j++){
			std::cout << line[j] << " ";
		}
		std::cout << std::endl;
	}
	//关闭连接
	mysql_close(con);
	return 0;
}