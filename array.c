#include <stdio.h>
#include <string.h>

struct employee{
    char name[20];
    char job[20];
    int age;
};

void showStruct(void)
{
    struct employee engineer={
        "after",
        "java开发",
        25
    };
    printf("engineer=%p,name=%s,job=%s,age=%d\n",&engineer,engineer.name,engineer.job,engineer.age);
    struct employee user;
    strcpy(user.name,"hongjian");
    strcpy(user.job,"全栈工程师");
    user.age=25;

    struct employee *emps[2]={&engineer,&user};
    struct employee users[2]={engineer,user};
    
    printf("user=%p,name=%s,job=%s,age=%d\n",&user,user.name,user.job,user.age);
    for(size_t i = 0; i < 2; i++)
    {
        printf("postion[%d]=%p,name=%s,job=%s,age=%d\n",i,emps[i],emps[i]->name,emps[i]->job,emps[i]->age);
    }
    for(size_t j = 0; j < 2; j++)
    {
        printf("j=%d: name=%s,job=%s,age=%d\n",j,users[j].name,users[j].job,users[j].age);
    }
    
}
void show_p(void)
{
    int    a = 10,   *pa = &a, *paa = &a;
    double b = 99.9, *pb = &b;
    char   c = '@',  *pc = &c;
    printf("&a=%p, &b=%p, &c=%p\n", &a, &b, &c);
    printf("pa=%p, pb=%p, pc=%p\n", pa, pb, pc);
    pa++; pb++; pc++;
    printf("pa=%p, pb=%p, pc=%p\n", pa, pb, pc);
    pa -= 2; pb -= 2; pc -= 2;
    printf("pa=%p, pb=%p, pc=%p\n", pa, pb, pc);
    if(pa == paa){
        printf("%d\n", *paa);
    }else{
        printf("%d\n", *pa);
    }
}

void show_arry(void)
{
    char str[]={"hello"};
    int iarr[3]={1,2,3};
    char carr[3]={'A','B','C'};
    size_t size=sizeof(iarr) /sizeof(iarr[0]);
    size_t size2=sizeof(str) /sizeof(str[0]);

    int i=0;
    for(; i < size; i++)
    {
       printf("%d   %c\n",iarr[i],carr[i]);
    }
    if (str[size2-1]=='\0') {
        printf("str = %d, size = %d\n",str[size2-1],size2);
    }
}

void show_demo(void)
{
    int iarr[4]={2,4,6,8};
    int a=1,b=2,c=3;
    int * p=iarr;
    for(size_t i = 0; i < 4; i++)
    {
        printf("%p, %d\n", p+i,*(p+i));
    }
    
}

void show_str(void)
{
    char str[] = "http://c.biancheng.net";
    int len = sizeof(str)/sizeof(char), i;
    printf("str=%s,len=%d\n", str,len);
    for(i=0; i<len; i++){
        if(str[i]=='\0'){
            printf("\nstr[%d] = %d\n", i,str[i]);
        }
        printf("%c", str[i]);
    }
    printf("EOF=%d\n",EOF);
}
void showTowLevelPoint()
{
    int a =100;
    int *p1 = &a;
    int **p2 = &p1;
    int ***p3 = &p2;
    printf("%d, %d, %d, %d\n", a, *p1, **p2, ***p3);
    printf("p1 = %p &p2 = %p, p3 = %p\n", p1,&p2, p3);
    printf("&p1 = %p, p2 = %p, *p3 = %p\n", &p1, p2, *p3);
    printf(" &a = %p, p1 = %p, *p2 = %p, **p3 = %p\n", &a, p1, *p2, **p3);
}
int main(void)
{
    // show_p();
    // show_demo();
    // show_str();
    // showTowLevelPoint();
    showStruct();
    // getchar();
    return 0;
}