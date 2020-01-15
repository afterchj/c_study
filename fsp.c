#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 2
void f_std(void);
void f_file(void);

struct stu{
    char name[10];
    int num;
    int age;
    float score;
} boya[N], boyb[N], *pa, *pb;


void f_getc()
{
    FILE *fp;
    char ch;
   
    //如果文件不存在，给出提示并退出
    if( (fp=fopen("D:\\demo.txt","rt")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    //每次读取一个字节，直到读取完毕
    while( (ch=fgetc(fp)) != EOF ){
        putchar(ch);
    }
    putchar('\n');  //输出换行符
    fclose(fp);
}

void f_putc()
{
     FILE *fp;
    char ch;
    //判断文件是否成功打开
    if( (fp=fopen("D:\\demo.txt","a+")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    printf("Input a string:\n");
    //每次从键盘读取一个字符并写入文件
    while ( (ch=getchar()) != '\n' ){
        fputc(ch,fp);
    }
    fclose(fp);
}

void fget_s()
{
    FILE *fp;
    char s[128];
   
    //如果文件不存在，给出提示并退出
    if( (fp=fopen("D:\\demo.txt","rt")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    //每次读取一个字节，直到读取完毕
    while( fgets(s,127,fp)!=NULL ){
       printf("read line:%s\n",s);
    }
    fclose(fp);
}

void fput_s()
{
    FILE *fp;
    char str[102] = {0}, strTemp[100];
    if( (fp=fopen("D:\\demo.txt", "at+")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    printf("Input a string:");
    gets(strTemp);
    strcat(str, "\n");
    strcat(str, strTemp);
    fputs(str, fp);
    fclose(fp);
}

void test_binary()
{
     //从键盘输入的数据放入a，从文件读取的数据放入b
    int a[5], b[5];
    int i, size = sizeof(int);
    FILE *fp;
    if( (fp=fopen("D:\\bin.txt", "rb+")) == NULL ){  //以二进制方式打开
        puts("Fail to open file!");
        exit(0);
    }
  
    //从键盘输入数据 并保存到数组a
    for(i=0; i<5; i++){
        scanf("%d", &a[i]);
    }
    //将数组a的内容写入到文件
    fwrite(a, size, 5, fp);
    //将文件中的位置指针重新定位到文件开头
    rewind(fp);
    //从文件读取内容并保存到数组b
    fread(b, size, 5, fp);
    //在屏幕上显示数组b的内容
    for(i=0; i<5; i++){
        printf("%d ", b[i]);
    }
    printf("\n");
    fclose(fp);
}

int main(){
    // f_std();
    // f_file();
    // f_putc();
    // f_getc();
    // fput_s();
    fget_s();
    // test_binary();
    return 0;
}

void f_file(void)
{
     FILE *fp;
    int i;
    pa=boya;
    pb=boyb;
    if( (fp=fopen("D:\\demo.txt","wt+")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }

    //从键盘读入数据，保存到boya
    printf("Input data:\n");
    for(i=0; i<N; i++,pa++){
        scanf("%s %d %d %f", pa->name, &pa->num, &pa->age, &pa->score);   
    }
    pa = boya;
    //将boya中的数据写入到文件
    for(i=0; i<N; i++,pa++){
        fprintf(fp,"%s %d %d %f\n", pa->name, pa->num, pa->age, pa->score);   
    }
    //重置文件指针
    rewind(fp);
    //从文件中读取数据，保存到boyb
    for(i=0; i<N; i++,pb++){
        fscanf(fp, "%s %d %d %f\n", pb->name, &pb->num, &pb->age, &pb->score);
    }
    pb=boyb;
    //将boyb中的数据输出到显示器
    for(i=0; i<N; i++,pb++){
        printf("%s  %d  %d  %f\n", pb->name, pb->num, pb->age, pb->score);
    }

    fclose(fp);
}

void f_std()
{
    int a, b, sum;
    fprintf(stdout, "Input two numbers: ");
    fscanf(stdin, "%d %d", &a, &b);
    sum = a + b;
    fprintf(stdout, "sum=%d\n", sum);
}