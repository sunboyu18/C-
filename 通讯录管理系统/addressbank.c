#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*----------------------
	@author���ﲩ�� 
------------------------------------------------------------------------------------------
����ʱû��ʵ��ɾ�����޸�txt�ı��е����ݣ����ᣩ�����ڿ��Խ�������Ϣ�Ͳ�����Ϣд��txt�ı���
���������д���ı��������з�װֱ�ӵ��ã���֪��Ϊʲô���л��ڴ�й¶������û��ע�͵��ˡ�    
������Ҫ�ȴ���ͨѶ¼������ܽ��в������ݡ�												  
��   fp=fopen("1.txt","a") || 1.txt�Ǳ����ͨѶ¼�ļ���a�Ǵ���һ�п�ʼ��ӡ��txt��		
------------------------------------------------------------------------------------------
*/ 

typedef struct{//structure for the address book
 char num[5];
 char name[9];
 char sex[9];
 char phone[30];
 char QQ[20];
/*�����Ҫ���ͨѶ¼����Ϣ��ֱ���ڽṹ������Ӳ�����һ�������㼴��*/ 
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
    printf("* ͨ Ѷ ¼ �� �� �� �� *\n");
    printf("***********************\n");
    head=CreateList();
    break;
  case 2:
    printf("*********************\n");
    printf("ͨ Ѷ ¼ �� Ϣ �� �� �� *\n");
    printf("*********************\n");
    printf("�������ţ��������Ա𣬵绰��QQ \n");
    printf("**********************************\n");
    p=(ListNode*)malloc(sizeof(ListNode));
    scanf("%s%s%s%s%s",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
    // Save_txt();//���ú���
      FILE *fp;
    fp=fopen("1.txt","a");
    fprintf(fp,"\n��ţ�%s\t������%s\t�Ա�%s\t�绰��%s\tQQ��%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
    fclose(fp);//�ر���
    InsertNode(head,p);
    break;
  case 3:
    printf("***********************\n");
    printf("ͨ Ѷ ¼ �� �� ѯ *\n");
    p=ListFind(head);
    if(p!=NULL){
     printf("��� ���� �Ա� �绰 QQ \n");
     printf("-------------------------- \n");
     printf("%s%s%s%s%s",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
}    else
     printf("û�鵽Ҫ��ѯ��ͨѶ�ߣ�\n");
     break;
   case 4:
    printf("***********************\n");
    printf("* ͨ Ѷ �� �� Ϣ �� �� �� *\n");
    printf("**********************\n");
    ChangeNode(head);
    break;
   case 5:
    printf("************************\n");
    printf("ͨ Ѷ ¼ �� �� Ϣ ɾ �� *\n");
    printf("*************************\n");
    DelNode(head);
    break;
   case 6:
    printf("************************\n");
    printf("ͨ Ѷ ¼ �� �� �� �� �� *\n");
    printf("*************************\n");
    printList(head);
    break;
   case 0:
    printf("\t �� ����\n");
    return 0;
 }
 }

}
int menu_select(){
 int sn;
 printf(" ͨѶ¼����ϵͳ\n");
 printf("========================\n");
 printf(" 1. ͨѶ¼����Ľ���\n");
 printf(" 2. ͨѶ¼��Ϣ�Ĳ���\n");
 printf(" 3. ͨѶ¼��Ϣ�Ĳ�ѯ\n");
 printf(" 4. ͨѶ¼��Ϣ���޸�\n");
 printf(" 5. ͨѶ¼��Ϣ��ɾ��\n");
 printf(" 6. ͨѶ¼��Ϣ�����\n");
 printf(" 0. �˳�����ϵͳ\n");
 printf(" �� ѡ �� 0��6��");
 for(; ;){
  scanf("%d",&sn);
  if(sn<0 || sn>6)
   printf("\n\t���������ѡ0-6��");
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
  printf("��˳�������ţ��������Ա𣬵绰��QQ\n");
  printf("--------------------------------------\n");
  scanf("%s%s%s%s%s",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
  FILE *fp;
  fp=fopen("1.txt","a");
  fprintf(fp,"\n��ţ�%s\t������%s\t�Ա�%s\t�绰��%s\tQQ��%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
  fclose(fp);//�ر���
  // Save_txt();
  rear->next=p;
  rear=p;
  printf("���������� ��y/n��:");
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
 while(p2!=NULL && strcmp(p2->data.num,p->data.num)<0)//�Ƚϱ��
 {
  p1=p2;//ָ�����
  p2=p2->next;// ָ�����
 }

 p1->next=p;//����
 p->next=p2;

} 
ListNode *ListFind(LinkList head){
 ListNode *p; 
 char num[5];
 char name[9]; 
 int xz=0;
 printf("===========\n");
 printf("1. ����Ų�ѯ \n");
 printf("2. ��������ѯ \n");
 printf("===========\n");
 printf(" ��ѡ��");
 p=head->next;
 scanf("%d",&xz);
 if(xz==1){
  printf("������Ҫ��ѯ�ߵı��:");
  scanf("%s",num);
  while(p && strcmp(p->data.num,num)<0)
   p=p->next;
  if(p==NULL||strcmp(p->data.num,num)>0)//���û�ҵ�
   p=NULL;

}
 else
  if(xz==2) {
   printf("������Ҫ��ѯ�ߵ�������");
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
  printf("û�в鵽Ҫɾ����ͨѶ��!\n");
  return;

 }
 printf("���Ҫɾ���ýڵ���?(y/n):");
 getchar();
 scanf("%c",&jx);
 if(jx=='y'||jx=='Y'){
  q=head;
  while(q!=NULL && q->next!=p)
   q=q->next;
  q->next=p->next;
  free(p);
  printf("ͨѶ¼�Ѿ�ɾ��!\n");
 }
}
void printList(LinkList head){
 ListNode *p;
 p=head->next;
 printf("��� ���� �Ա� �绰 QQ\n");
 printf("---------------------------------------------------------------------------\n");
 while(p!=NULL)
 {
  printf("��ţ�%s\t������%s\t�Ա�%s\t�绰��%s\tQQ��%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
  printf("--------------------------------------------------------------------------\n");
  p=p->next;
 }
} 
// void Save_txt(){//д���ı��ļ��������з�װ
//   FILE *fp;
//   fp=fopen("1.txt","a");
//   fprintf(fp,"\n��ţ�%s\t������%s\t�Ա�%s\t�绰��%s\tQQ��%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
//   fclose(fp);//�ر���
// }
void ChangeNode(LinkList head){
 ListNode *p;
 p=ListFind(head);
 if(p!=NULL){
  printf("��� ���� �Ա� �绰 QQ\n");
  printf("--------------------------------------------------------------------------\n");
  scanf("��ţ�%s\t������%s\t�Ա�%s\t�绰��%s\tQQ��%s\n",p->data.num,p->data.name,p->data.sex,p->data.phone,p->data.QQ);
  printf("--------------------------------------------------------------------------\n");
  printf("�����ͨѶ¼����ȷ����ϵ�绰 QQ��\n�м��ÿո�ŷָ�\n");
  scanf("%s%s",p->data.phone,p->data.QQ);

}
 else
  printf("û�鵽Ҫ��ѯ��ͨѶ¼�ߣ�\n");
}
