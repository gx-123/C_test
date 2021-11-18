#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1024

void getInput(struct Person *person);//输入联系人信息
void addPerson(struct Person **head);//添加联系人
void displayContact(struct Person **head);//显示通讯录
void changePerson(struct Person **head);//修改联系人
void findPerson(struct Person **head);//查找联系人
void dellPerson(struct Person **head);//删除联系人
void releasePerson(struct Person **head);//退出程序释放内存
void releasePool(void);

struct Person
{
	char name[32];
	char phone[16];
	struct Person *next;
};

struct Person *pool = NULL;
int count;

void getInput(struct Person *person) 
{
	printf("请输入新的联系人姓名：");
	scanf("%s",person->name);
	printf("请输入联系人电话：");
	scanf("%s",person->phone);
}

void addPerson(struct Person **head) // 1 尾插法
{
	struct Person *person;
	static struct Person *tail;//tail 每次都指向链表最后一个节点（新添加的book）就不用每次都去遍历链表了 
	// 如果内存池为空，则直接从里面获取空间
	if (pool != NULL) 
	{
		person = pool;
		pool = pool->next;
		count--;
	}
	//如果内存池为空则调用malloc函数申请新的内存
	if (pool == NULL)
	{
		person = (struct Person *)malloc(sizeof(struct Person));
		if (person == NULL) 
		{
			printf("内存分配失败！！\n");
			exit(1);
		}
	}
	getInput(person);
	if (*head != NULL) //如果不是空链表
	{
		tail->next = person;
		person->next = NULL;
	}
	else
	{
		*head = person;
		person->next = NULL;
	}
	tail = person;
}

void findPerson(struct Person **head) // 2
{
	struct Person *person;
	char input[32];
	person = *head;
	printf("请输入要查找的联系人（姓名/电话）：");
	scanf("%s",&input);
	while (person != NULL  ) 
	{
		if (!strcmp(person->name,input) || !strcmp(person->phone ,input)) 
		{
			printf("姓名：%s\n", person->name);
			printf("电话：%s\n", person->phone);
		}
		person = person->next;
	}
}
void changePerson(struct Person **head) //3
{
	struct Person *person;
	int ch = 0;
	char input[32];
	person = *head;
	printf("请输入原联系人（姓名/电话）");
	scanf("%s",&input);
	while (person != NULL) 
	{
		if (!strcmp(person->name, input) || !strcmp(person->phone, input))
		{
			printf("请输入新的联系人姓名：");
			scanf("%s", person->name);
			printf("请输入新联系人电话：");
			scanf("%s", person->phone);
		}
		person = person->next;
	}
}

void dellPerson(struct Person **head) 
{
	struct Person *previous;
	struct Person *current;
	struct Person *temp;
	//struct Person *person;

	char input[16];
	printf("请输入要删除的联系人名字：");
	scanf("%s",&input);
	//person = findPerson(head);
		current = *head;
		previous = NULL;
		while (current != NULL)
		{
			if (!strcmp(current->name, input))
			{
				if (previous == NULL)
				{
					*head = current->next;
				}
				else
				{
					previous->next = current->next;
				}
		 }
			previous = current;
			current = current->next;
		}
		//判断内存池是否有空位
		if (count < MAX)
		{
			if (pool != NULL)
			{
				temp = pool;
				pool = current;
				current->next = temp;
			}
			else
			{
				pool = current;
			}
			count++;
		}
		else
		{
			free(current);
		}
	
}

void displayContact(struct Person **head)// 5
{
	int count = 1;
	struct Person *person;
	person = *head;
	while (person != NULL)
	{
		printf("第%d位：\n", count);
		printf("姓名：%s\n", person->name);
		printf("电话：%s\n", person->phone);
		person = person->next;
		count++;
	}
	if ((*head) == NULL)
	{
		printf("暂时还没有联系人呐，先输入吧！！！\n");
	}
}

void releasePerson(struct Person **head)//6
{
	struct Person *temp;
	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}
void releasePool(void) 
{
	struct Person *temp;
	while ( pool != NULL) 
	{
		temp = pool;
		pool = pool->next;
		free(temp);
	}
}
int main() 
{
	int ch;
	struct Person *head;
	printf("选择模式\n1：插入新的联系人\n2：查找已有联系人\n3：更改已有联系人\n4：删除已有联系人\n5：显示当前通讯录\n6：退出程序\n");
	while (1)
	{
		printf("请输入指令编号：");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1: addPerson(&head); break;
		case 2: findPerson(&head);break;
		case 3: changePerson(&head);break;
		case 4: dellPerson(&head);break;
		case 5: displayContact(&head); break;
		case 6: goto END;
		default: break;
		}
	}
END:
	releasePerson(&head);
	releasePool();
}