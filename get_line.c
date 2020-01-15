#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
   
int main() 
{ 
    char* buf = "HTTP/1.1 200 \nServer: nginx/1.8.0\nDate: Mon, 13 Jan 2020 02:35:48 GMT\nContent-Type: application/json;charset=UTF-8\nTransfer-Encoding: chunked\n112\n[{\"is_master\":false,\"mesh_id\":\"46431234\",\"mname\":\"\",\"is_control\":true,\"host_id\":\"7669522f\"},{\"is_master\":false,\"mesh_id\":\"49661234\",\"mname\":\"\",\"is_control\":true,\"host_id\":\"8f6b1c50\"},{\"is_master\":false,\"mesh_id\":\"43761234\",\"mname\":\"\",\"is_control\":true,\"host_id\":\"eebc08a7\"}]";
    char * p =strchr(buf,'[');
    char * s1="hello";
    char s2[] = {"hello"};
    char s3[] = "hello";
    int len1 = strlen(s1)+1; 
    int len2 = sizeof(s2) / sizeof(char); 
    int len3 = sizeof(s3) / sizeof(char); 

    printf("%d\t%d\t%d",len1,len2,len3);
    // printf("%s\n\n",p);
} 