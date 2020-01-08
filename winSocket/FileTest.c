#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2


void test_fgets()
{
    FILE *fp;
    char ch;
    int a='a';
    printf("ch=%d and ch is %c\n",a,a);
    char str[N+1];
    if( (fp=fopen("d:\\demo.txt","rt")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
   
    while(fgets(str, N, fp) != NULL){
        printf("%s", str);
    }
    fclose(fp);
}

void test_fputs()
{
    FILE *fp;
    char str[102] = {0}, strTemp[100];
    if( (fp=fopen("D:\\demo.txt", "at+")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    while(fgets(str, N, fp) != NULL){
        printf("%s", str);
    }
    printf("Input a string:\n");
    gets(strTemp);
    printf("strTemp=%s\n",strTemp);
    strcat(str, "\n");
    strcat(str, strTemp);
    printf("str=%s\n",str);
    fputs(str, fp);
    fclose(fp);
}

void fread_fwrite()
    {
        struct stu{
        char name[10]; //姓名
        int num;  //学号
        int age;  //年龄
        float score;  //成绩
    }boya[2], boyb[2], *pa, *pb;

    FILE *fp;
    int i;
    pa = boya;
    pb = boyb;
    if( (fp=fopen("d:\\demo.txt", "wb+")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    //从键盘输入数据
    printf("Input data:\n");
    for(i=0; i<N; i++,pa++){
        scanf("%s %d %d %f",pa->name, &pa->num,&pa->age, &pa->score);
    }
    //将数组 boya 的数据写入文件
    fwrite(boya, sizeof(struct stu), N, fp);
    //将文件指针重置到文件开头
    rewind(fp);
    //从文件读取数据并保存到数据 boyb
    fread(boyb, sizeof(struct stu), N, fp);
    //输出数组 boyb 中的数据
    for(i=0; i<N; i++,pb++){
        printf("%s  %d  %d  %f\n", pb->name, pb->num, pb->age, pb->score);
    }
    fclose(fp);
}
int main() {
    // test_fgets();
    // test_fputs();
    fread_fwrite();
    return 0;
}