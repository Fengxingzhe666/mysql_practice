#include <iostream>
#include <winsock.h>//�������mysql.hǰ��
#include <mysql.h>

const char* host = "127.0.0.1";
const char* user = "root";
const char* pw = "123456";
const char* databse_name = "zzk";
const int port = 3306;

int main()
{
	//��ʼ�����ݿ�
	MYSQL* con = mysql_init(NULL);
	//����
	if (!mysql_real_connect(con, host, user, pw, databse_name, port, NULL, 0)) {
		fprintf_s(stderr, "Failed to connect to database. Error: %s\n", mysql_error(con));
		return -1;
	}
	std::cout << "Connected to MySQL." << std::endl;
	//�������ӵ�Ĭ���ַ��� utf8��ԭʼĬ���� latin1����ʹ�ÿ��ܻᵼ�²��������������
	mysql_set_character_set(con, "utf-8");

	std::string order = "select * from student_info;";
	if(mysql_query(con, order.c_str())){
		//���ִ��ʧ�ܾʹ�ӡ
		fprintf_s(stderr, "Error: %s\n", mysql_error(con));
		return -1;
	}
	//�����ѯ���
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
	//�ر�����
	mysql_close(con);
	return 0;
}