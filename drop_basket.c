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
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"JavaScript\">");
	printf("function mv(){");
//	printf("window.history.back();");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("</script>");
	
		
		
	char *q=malloc(sizeof(char)*999);
	strcpy(q,"delete from putbasket where basket_num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"' and book_num='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	printf("<body onload=\"mv();\"></body>");
	printf("<form name=\"f\" id=\"f\" method=\"post\" action=\"basket.cgi\">");
	printf("<input type=\"hidden\" name=\"basketnum\" value=\"%s\">",findEntry("id"));
	printf("%s %s<br>",entries[0].name,entries[0].val);
	printf("%s %s",entries[1].name,entries[1].val);
	printf("</head></html>");
}
