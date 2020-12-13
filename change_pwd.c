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
		
	printf("<body><form method=\"post\" action=\"commit_pwd.cgi\">");
	printf("<table><tbody>");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));
	printf("<tr>");
	printf("<td>");
	printf("현재 비밀번호  </td>");
	printf("<td>");
	printf("<input type=\"password\" name=\"pwd\" maxlength=\"30\"></td>");
	printf("<tr><td>");
	printf("변경할 비밀번호</td>");
	printf("<td>");
	printf("<input type=\"password\" name=\"new_pwd\" maxlength=\"30\"></td>");	
	printf("</form><tr><td><input type=\"submit\" value=\"변경\"></td></tr></tbody></table>");

	printf("</head></html>");
}
