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

	char *q=malloc(sizeof(char)*999);
	strcpy(q,"insert into putbasket(basket_num,book_num,quantity) values('");
	strcat(q,findEntry("basketnum"));
	strcat(q,"','");
	strcat(q,findEntry("book_num"));
	strcat(q,"','");
	strcat(q,findEntry("quantity"));
	strcat(q,"')");
	mysql_query(&mysql,q);

	printf("<script language=\"javascript\">");
	        printf("function move_page(){");
		        printf("f.submit();");
			        printf("}</script>");

	printf("<body onload=\"move_page();\">");
	printf("<form name=\"f\" id=\"f\" method=\"post\" action=\"basket.cgi\">");
	printf("<input type=\"hidden\" name=\"basketnum\" value=\"%s\">",findEntry("basketnum"));
	printf("</form>");
	printf("</body>");
	printf("</head></html>");
	free(q);
}
