# 安装sqlite3.h依赖 
1. centerOS: sudo yum install sqlite-devel
2. ubuntuOS: sudo apt-get install libsqlite3-dev  
# 编译命令
gcc .\dbsqlite.c -o db -lsqlite3  
