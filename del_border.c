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
	strcpy(q,"delete from corder where order_num='");
	        strcat(q,findEntry("order_num"));
		        strcat(q,"'");
	mysql_query(&mysql,q);
	strcpy(q,"delete from border where num='");
	strcat(q,findEntry("order_num"));
	strcat(q,"'");

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("</script>");
	if( mysql_query(&mysql,q))
	{
		printf("<p1>%s</p1>",mysql_error(&mysql));
	}
	else
	printf("<h1>내역 삭제 완료<br></h1>");	
	printf("<input type=\"button\" value=\"닫기\" onclick=\"winclo();\">");
	printf("</head></html>");
}
