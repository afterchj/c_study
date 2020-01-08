#include <stdio.h>
#include <sqlite3.h>

//select callback function
int select_callback(void * data, int col_count, char ** col_values, char ** col_Name);

int main(int argc, char * argv[])
{
    const char * sSQL1 = "create table users(id int(11) PRIMARY KEY,name varchar(32),age int, birthday datetime);";
    char * pErrMsg = 0;
    int result = 0;
    // connect database
    sqlite3 * db = 0;
    int ret = sqlite3_open("./test.db", &db);
    if( ret != SQLITE_OK ) {
        fprintf(stderr, "can't open database: %s", sqlite3_errmsg(db));
        return(1);
    }
    printf("connected succesfully!\n");

    // execute create table SQL
    sqlite3_exec( db, sSQL1, 0, 0, &pErrMsg );
    if( ret != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", pErrMsg);
        sqlite3_free(pErrMsg);
    }

    //execute delete SQL
    result = sqlite3_exec( db, "delete from users;", 0, 0, &pErrMsg);
    if(result == SQLITE_OK){
        printf("delete successful.\n");
    }
    // execute insert SQL
    result = sqlite3_exec( db, "insert into users values(1,'张三',23,'1996-3-21'),(2,'李四',25,'1995-2-16'),(3,'admin',27,'1993-7-23'),(4,'after',26,'2019-12-16');", 0, 0, &pErrMsg);
    if(result == SQLITE_OK){
        printf("insert successfuly.\n");
    }
    // result = sqlite3_exec( db, "insert into users values(4,'after',26,'2019-12-16');", 0, 0, &pErrMsg);

    result = sqlite3_exec( db, "update users set birthday = '1994-04-29' where id =4;", 0, 0, &pErrMsg);
    if(result == SQLITE_OK){
        printf("update successfully.\n");
    }
    // execute select
    printf("select all data\n");
    sqlite3_exec( db, "select * from users;", select_callback, 0, &pErrMsg);

    // close data
    sqlite3_close(db);
    db = 0;
    printf("data close successfully!\n");
    getchar();
    return 0;
}

int select_callback(void * data, int col_count, char ** col_values, char ** col_Name)
{
    //foreach row data
    int i;
    for( i=0; i < col_count; i++){
        printf( "%s = %s\n", col_Name[i], col_values[i] == 0 ? "NULL" : col_values[i] );
    }
    return 0;
}