/************************************************************************* 
    > File Name:DButil.c  
    > Author:  after
    > Mail:  766256898@qq.com
    > Created Time: 2019-12-16 13:32:30 
 ************************************************************************/  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <WinSock2.h>
#include <mysql.h>
  
int main()  
{  
    int ret = 0;  
  
    MYSQL mysql;  
    MYSQL * connect = NULL;  
    connect = mysql_init(&mysql);  
    if(connect == NULL){  
        ret = mysql_errno(&mysql);  
        printf("mysql_init error, %s\n", mysql_error(&mysql));  
        return ret;  
    }  
    printf("mysql_init ok...\n");  
  
  
    // connect = mysql_real_connect(connect, "127.0.0.1", "root", "root", "test", 0, NULL, 0);  
    connect = mysql_real_connect(connect, "119.3.49.192", "root", "1Believe#", "test", 0, NULL, 0);  
    if(connect == NULL){  
        ret = mysql_errno(&mysql);  
        printf("mysql_real_connect error, err is: %s\n", mysql_error(&mysql));  
        return ret;  
    }  
    if (!mysql_set_character_set(&mysql, "gbk"))
	{
		printf("New client character set: %s\n",
		mysql_character_set_name(&mysql));
	}
    printf("mysql_real_connect ok...\n");  
	// execute the insert query
	char * query = "insert into users(id, name,add_time) values(2, '张三','2019/12/16')";
	// execute the update query
	query = "update users set id='1000004' where name = '李四'";
	ret = mysql_real_query(&mysql,query,(unsigned int) strlen(query));
	if (ret) {
		printf("Error making query: %s\n",mysql_error(&mysql));
	}
	else 
		printf("[%s] made...\n", query);

	// execute the select query
    query = "select * from users order by id";  
    ret = mysql_query(connect, query);  
    if(ret != 0){  
        printf("mysql_query error\n");  
        return ret;  
    }  
  
    MYSQL_RES *result = mysql_use_result(&mysql);  
    if(result == NULL){  
        printf("mysql_use_result error\n");  
        return -1;  
    }  
      
    int field_num = mysql_field_count(&mysql);  
    //琛ㄥご  
    MYSQL_FIELD * fields = mysql_fetch_fields(result);  
    int i = 0;  
  
    printf("------------------------------------------\n");  
    for(i= 0; i < field_num; i++){  
        printf("%s \t", fields[i].name);   
    }  
    printf("\n------------------------------------------\n");  
  
  
    //琛ㄥ唴瀹?  
    MYSQL_ROW row = NULL;  
    while(row = mysql_fetch_row(result)){  
        for(i= 0; i < field_num; i++){  
            printf("%s \t", row[i]);   
        }  
        printf("\n");  
    }  
  
    mysql_free_result(result);//释放内存
    mysql_close(connect);  
  
    printf("mysql_close...\n");  
  
  	getchar();
    return ret;  
}  