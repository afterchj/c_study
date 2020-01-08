+ 查看某个串口的波特率等信息
>stty -F /dev/ttyS0 -a
+ 查看串口设备
>dmesg | grep ttyS*
+ 查看串口名称使用
>ls -l /dev/ttyS*
