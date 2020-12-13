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
/*	strcpy(q,"update addr set zip='");
	strcat(q,findEntry("zip자택"));
	strcat(q,"',base='");
	strcat(q,findEntry("base자택"));
	strcat(q,"',detail='");
	strcat(q,findEntry("detail자택"));
	strcat(q,"' where id='");
	strcat(q,findEntry("id"));
	strcat(q,"' and chk='자택'");
	mysql_query(&mysql,q);
	strcpy(q,"update addr set zip='");
	strcat(q,findEntry("zip회사"));
	strcat(q,"',base='");
	strcat(q,findEntry("base회사"));
	strcat(q,"',detail='");
	strcat(q,findEntry("detail회사"));
	strcat(q,"' where id='");
	strcat(q,findEntry("id"));
	strcat(q,"' and chk='회사");
	mysql_query(&mysql,q);*/

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	strcpy(q,"update addr set zip='");
	strcat(q,findEntry("zip자택"));
	strcat(q,"',base='");
	strcat(q,findEntry("base자택"));
	strcat(q,"',detail='");
	strcat(q,findEntry("detail자택"));
	strcat(q,"' where id='");
	strcat(q,findEntry("id"));
	strcat(q,"' and chk='자택'");
	if(mysql_query(&mysql,q))
	{
		printf("<h1>자택 수정 X</h1>");
		printf("<p1>%s</p1",mysql_error(&mysql));
	}
	strcpy(q,"update addr set zip='");
	strcat(q,findEntry("zip회사"));
	strcat(q,"',base='");
	strcat(q,findEntry("base회사"));
	strcat(q,"',detail='");
	strcat(q,findEntry("detail회사"));
	strcat(q,"' where id='");
	strcat(q,findEntry("id"));
	strcat(q,"' and chk='회사'");
	if(mysql_query(&mysql,q))
	{
		printf("<h1>회사 수정 X</h1>");
		printf("<p1>%s</p1",mysql_error(&mysql));
	}

	



	printf("<h1>적용되었습니다.</h1>");
	printf("<input type=\"button\" value=\"닫기\" onclick=\"window.close();\">");
	printf("</head></html>");
}
