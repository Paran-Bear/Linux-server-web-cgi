#include<stdio.h>
#include"/usr/include/mysql/mysql.h"
#include<errno.h>
#include"cgipost.h"
#include<string.h>
#include<stdlib.h>
void main(){
	
	getPostData();
	
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	int fields;
	
	mysql_init(&mysql);//객체 초기화
	
	
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");//한글 사용*/
	if(!mysql_real_connect(&mysql,NULL,"shop","shop1","shopdb",3306,(char *)NULL,0))
	{
		
		printf("DB연결 실패 ");
		
	}
	else
		
		
		if(mysql_query(&mysql,"use shopdb"))
		{
			printf("use test_db 쿼리문은 실패");
		}
	char *q=malloc(sizeof(char)*999);
	strcpy(q,"insert into card(id,num,date,comp) values('");
	
	strcat(q,findEntry("id"));
	strcat(q,"','");
	strcat(q,findEntry("cn0"));
	strcat(q,"-");
	strcat(q,findEntry("cn1"));
	strcat(q,"-");
	strcat(q,findEntry("cn2"));
	strcat(q,"-");
	strcat(q,findEntry("cn3"));
	strcat(q,"','");
	strcat(q,findEntry("date"));
	strcat(q,"-01','");
	strcat(q,findEntry("comp"));
	strcat(q,"')");
	int err=0;
	mysql_query(&mysql,q);

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	if(err==0)
	{
		printf("<h1>카드 등록 완료</h1>");
		printf("<input type=\"button\" value=\"닫기\" onclick=\"window.close();\">");
	}
	else
	{
		printf("<h1>카드 등록 실패<h1>");
		printf("<input type=\"button\" value=\"닫기\" onclick=\"window.history.back();\">");
	}
	printf("</head></html>");
}
