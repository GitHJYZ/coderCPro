#include "link.h"


LIST *insert_link(LIST *head,LIST temp)
{
	LIST *pi ;
	pi = (LIST *)malloc(sizeof(LIST));
	*pi = temp;
	pi ->next = NULL;
	
	if(NULL == head)
	{
		head = pi;
	}
	else
	{
		LIST *pf=NULL,*pb = NULL;
		pf = pb = head;
		while((pb->num < pi->num) && (NULL != pb->next))
		{
			pf = pb;   //是不是保存了已经比较过的节点
			pb = pb->next;//指向下一个将要比较的节点
		}
		
		if(pb->num >= pi->num)
		{
			
			if(pb == head)
			{
				pi->next = head;
				head = pi;
			}
			else
			{
				pf->next = pi;
				pi->next = pb;
			}
		}
		else
		{
			pb->next = pi;
		}
	}
		return head;
}

LIST *delete_link(LIST *head,char *name)
{
	if(NULL == head)
	{
		printf("link not exist\n");
	}
	else 
	{	
		LIST *pf = NULL, *pb = NULL;
		pf = pb = head;
		while((0 != strcmp(pb->name,name)) && (NULL != pb->next))
		{
			pf = pb;
			pb = pb->next;
		}
		
		if(0 == strcmp(pb->name,name))
		{
			if(pb == head)
			{
				head = pb->next;
			}
			else
			{
				pf->next = pb->next;	
			}	
				free(pb);
				printf("delete is sucessful!\n");
		}
		else
		{
			printf("not found name\n");
		}
	}
	
	return head;
}

void print_link(LIST *head)
{
	if(NULL == head)
	{
		printf("link not exist\n");
	}
	else
	{
		LIST *pb = head;
		while(NULL != pb)
		{
			printf("%lu %s %d\n",pb->num,pb->name,pb->new_fd);
			pb = pb->next;
		}
	}
	
	return;
}
void check_all_member(LIST *head,unsigned long int snum)
{
	if(NULL == head)
	{
		printf("link not exist\n");
	}
	else{
		LIST *pb = head;
		LIST *pq = head;
		char msg[128]="";
		while(NULL != pb)
		{
			while(NULL != pq){
				if (snum == pq->num){
					sprintf(msg, "%s:%s","exist",pb->name);
					sleep(1);
					send(pq->new_fd, msg, strlen(msg),0);
					bzero(msg,sizeof(msg));
					break;	
				}
				pq = pq->next;
			}
			pb = pb->next;
		}
	}
	return;
}

void check_member(LIST *head,char *msg,unsigned long int snum,unsigned long int dnum)
{
	if(NULL == head)
	{
		printf("link not exist\n");
	}
	else
	{
		LIST *pb = head;
		LIST *pq = head;
		char msg1[128]="";
		while(NULL != pb)
		{
			if (dnum != pb->num)
			{
				pb = pb->next;
			}
			else{
				while(NULL != pq){
					if (snum == pq->num){
						sprintf(msg1, "%s:%s","exist",msg);
						send(pq->new_fd, msg1, strlen(msg1),0);
						return;	
					}
					pq = pq->next;
				}
			}
		}
		while(NULL != pq){
			if (snum == pq->num){
				sprintf(msg1, "%s:%s","not_exist",msg);
				send(pq->new_fd, msg1, strlen(msg1),0);
				return;	
			}
			pq = pq->next;
		}
	}
	return;
}


void up_link(LIST *head, char *msg,unsigned long int num)
{
	
	if(NULL == head)
	{
		printf("link not exist\n");
	}
	else
	{
		LIST *pb = head;
		while(NULL != pb)
		{
			if (num != pb->num)
			{
				send(pb->new_fd, msg, strlen(msg),0);
				pb = pb->next;
			}
			else{
				pb = pb->next;
			}
		}
	}
	
	return;
}

LIST *search_ip(LIST *head,unsigned long int num)
{

	if(NULL == head)
	{
		printf("link not exist\n");
	}
	else
	{
		LIST *pb = head;
		while((pb->num != num) && (NULL != pb->next))
		{
			pb = pb->next;
		}
		
		if(pb->num == num)
		{
			return pb;
		}
		else 
		{
			printf("not found\n");
		}
	}
	
		return NULL;
}


void close_serve(LIST *head)
{
	if(NULL == head)
	{
		printf("link not exist\n");
	}
	else
	{
		LIST *pb = NULL, *pi = NULL;
		pb = pi = head;
		while(NULL != pb)
		{
			printf("pb->new_fd = %d\n", pb->new_fd);
			close(pb->new_fd);
			pi = pb;	
			pb = pb->next;
			printf("close success\n");
			free(pi);
		}
	}
	
	return;
}