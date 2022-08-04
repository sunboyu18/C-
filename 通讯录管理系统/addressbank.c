#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*----------------------
	@author：孙博宇 
------------------------------------------------------------------------------------------
！暂时没有实现删除和修改txt文本中的内容（不会），现在可以将创建信息和插入信息写入txt文本。
！本来想把写入文本函数进行封装直接调用，不知道为什么运行会内存泄露。所以没用注释掉了。    
！必须要先创建通讯录链表才能进行插入数据。												  
！   fp=fopen("1.txt","a") || 1.txt是保存的通讯录文件，a是从下一行开始打印到txt。		
------------------------------------------------------------------------------------------
*/ 

typedef struct{//structure for the address book
 char num[5];
 char name[9];
 char sex[9];
 char phone[30];
 char QQ[20];
/*如果需要添加通讯录的信息，直接在结构体中添加并增加一个链表结点即可*/ 
}DataType;
typedef struct node{
 DataType data;
 struct node*next;
} ListNode, *LinkList;

LinkList head;
ListNode *p;// 

int menu_select();
LinkList CreateList(void);
void InsertNode(LinkList head,ListNode *p);
ListNode *ListFind(LinkList head);
void DelNode(LinkList head);
void printList(LinkList head);
void ChangeNode(LinkList head);

int main(void){
  for(; ;){
  switch(menu_select()){
  case 1:
    printf("**********************\n");
    printf("* 通 讯 录 链 表 建 立 *\n");
    printf("***********************\n");
    head=CreateList();
    break;
  case 2:
    printf("*********************\n");
    printf("通 讯 录 信 息 的 插 入 *\n");
    printf("*********************\n");
    printf("请输入编号，姓名，性别，电话和QQ \n");
    printf("**********************************\n");
    p=(ListNode*)malloc(sizeof(ListNode));
    scanf("%s%s%s%s%s",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
    // Save_txt();//调用函数
      FILE *fp;
    fp=fopen("1.txt","a");
    fprintf(fp,"\n编号：%s\t姓名：%s\t性别：%s\t电话：%s\tQQ：%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
    fclose(fp);//关闭流
    InsertNode(head,p);
    break;
  case 3:
    printf("***********************\n");
    printf("通 讯 录 的 查 询 *\n");
    p=ListFind(head);
    if(p!=NULL){
     printf("编号 姓名 性别 电话 QQ \n");
     printf("-------------------------- \n");
     printf("%s%s%s%s%s",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
}    else
     printf("没查到要查询的通讯者！\n");
     break;
   case 4:
    printf("***********************\n");
    printf("* 通 讯 者 信 息 的 修 改 *\n");
    printf("**********************\n");
    ChangeNode(head);
    break;
   case 5:
    printf("************************\n");
    printf("通 讯 录 的 信 息 删 除 *\n");
    printf("*************************\n");
    DelNode(head);
    break;
   case 6:
    printf("************************\n");
    printf("通 讯 录 链 表 的 输 出 *\n");
    printf("*************************\n");
    printList(head);
    break;
   case 0:
    printf("\t 再 见！\n");
    return 0;
 }
 }

}
int menu_select(){
 int sn;
 printf(" 通讯录管理系统\n");
 printf("========================\n");
 printf(" 1. 通讯录链表的建立\n");
 printf(" 2. 通讯录信息的插入\n");
 printf(" 3. 通讯录信息的查询\n");
 printf(" 4. 通讯录信息的修改\n");
 printf(" 5. 通讯录信息的删除\n");
 printf(" 6. 通讯录信息的输出\n");
 printf(" 0. 退出管理系统\n");
 printf(" 请 选 择 0—6：");
 for(; ;){
  scanf("%d",&sn);
  if(sn<0 || sn>6)
   printf("\n\t输入错误，重选0-6：");
  else
   break;
}
 return sn;


}
LinkList CreateList(void){
 LinkList head=(ListNode *)malloc(sizeof(ListNode));
 ListNode *p,*rear;
 char flag='y';
 rear=head;
 while(flag=='y'){
  p=(ListNode *)malloc(sizeof(ListNode));
  printf("请顺序输入编号，姓名，性别，电话和QQ\n");
  printf("--------------------------------------\n");
  scanf("%s%s%s%s%s",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
  FILE *fp;
  fp=fopen("1.txt","a");
  fprintf(fp,"\n编号：%s\t姓名：%s\t性别：%s\t电话：%s\tQQ：%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
  fclose(fp);//关闭流
  // Save_txt();
  rear->next=p;
  rear=p;
  printf("继续输入吗？ （y/n）:");
  getchar();
  scanf("%c",&flag);
}

 rear->next=NULL;
 return head;

} 
void InsertNode(LinkList head,ListNode *p){
 ListNode *p1,*p2;
 p1=head;
 p2=p1->next;
 while(p2!=NULL && strcmp(p2->data.num,p->data.num)<0)//比较编号
 {
  p1=p2;//指针后移
  p2=p2->next;// 指针后移
 }

 p1->next=p;//插入
 p->next=p2;

} 
ListNode *ListFind(LinkList head){
 ListNode *p; 
 char num[5];
 char name[9]; 
 int xz=0;
 printf("===========\n");
 printf("1. 按编号查询 \n");
 printf("2. 按姓名查询 \n");
 printf("===========\n");
 printf(" 请选择：");
 p=head->next;
 scanf("%d",&xz);
 if(xz==1){
  printf("请输入要查询者的编号:");
  scanf("%s",num);
  while(p && strcmp(p->data.num,num)<0)
   p=p->next;
  if(p==NULL||strcmp(p->data.num,num)>0)//如果没找到
   p=NULL;

}
 else
  if(xz==2) {
   printf("请输入要查询者的姓名：");
   scanf("%s",name);
   while(p && strcmp(p->data.name,name)!=0)
    p=p->next;    
 }

 return p;
}
void DelNode(LinkList head){
 char jx;
 ListNode *p,*q;
 p=ListFind(head);
 if(p==NULL){
  printf("没有查到要删除的通讯者!\n");
  return;

 }
 printf("真的要删除该节点吗?(y/n):");
 getchar();
 scanf("%c",&jx);
 if(jx=='y'||jx=='Y'){
  q=head;
  while(q!=NULL && q->next!=p)
   q=q->next;
  q->next=p->next;
  free(p);
  printf("通讯录已经删除!\n");
 }
}
void printList(LinkList head){
 ListNode *p;
 p=head->next;
 printf("编号 姓名 性别 电话 QQ\n");
 printf("---------------------------------------------------------------------------\n");
 while(p!=NULL)
 {
  printf("编号：%s\t姓名：%s\t性别：%s\t电话：%s\tQQ：%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
  printf("--------------------------------------------------------------------------\n");
  p=p->next;
 }
} 
// void Save_txt(){//写入文本文件函数进行封装
//   FILE *fp;
//   fp=fopen("1.txt","a");
//   fprintf(fp,"\n编号：%s\t姓名：%s\t性别：%s\t电话：%s\tQQ：%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
//   fclose(fp);//关闭流
// }
void ChangeNode(LinkList head){
 ListNode *p;
 p=ListFind(head);
 if(p!=NULL){
  printf("编号 姓名 性别 电话 QQ\n");
  printf("--------------------------------------------------------------------------\n");
  scanf("编号：%s\t姓名：%s\t性别：%s\t电话：%s\tQQ：%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
  printf("--------------------------------------------------------------------------\n");
  printf("输入该通讯录者正确的联系电话 QQ：\n中间用空格号分隔\n");
  scanf("%s%s",p->data.phone,p->data.QQ);

}
 else
  printf("没查到要查询的通讯录者！\n");
}
