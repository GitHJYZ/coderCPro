#ifndef __LINK_H__
#define __LINK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "QQ_server.h"


typedef struct news_list
{		
		
		unsigned long int num;
		char name[64];
		int new_fd;
		struct news_list *next;
}LIST;

extern void up_link(LIST *head, char *msg, unsigned long int num);
extern LIST *insert_link(LIST *head,LIST temp);
extern LIST *delete_link(LIST *head,char *name);
LIST *search_ip(LIST *head,unsigned long int num);
extern void print_link(LIST *head);
extern void close_serve(LIST *head);
extern void check_member(LIST *head,char *msg,unsigned long int snum,unsigned long int dnum);
extern void check_all_member(LIST *head,unsigned long int snum);

#endif