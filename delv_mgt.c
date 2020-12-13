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
	strcpy(q,"select * from addr where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<table><tbody>");
	printf("<form method=\"post\" action=\"delvmgt.cgi\">");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));
	while((row=mysql_fetch_row(res)))
	{
		printf("<tr><td>%s</td></tr>",row[1]);
		printf("<input type=\"hidden\" name=\"chk\" value=\"%s\">",row[1]);
		printf("<tr><td>우편번호</td><td><input type=\"text\" name=\"zip%s\" value=\"%s\"></td></tr>",row[1],row[2]);
		printf("<tr><td>기본주소</td><td><input type=\"text\" name=\"base%s\" value=\"%s\"></td></tr>",row[1],row[3]);
		printf("<tr><td>상세주소</td><td><input type=\"text\" name=\"detail%s\" value=\"%s\"></td></tr>",row[1],row[4]);
		printf("<tr><td><br></td></tr>");
	}
	printf("<tr><td><br></td></tr>");
	printf("<tr><td></td><td><input type=\"submit\" value=\"적용\"></td></tr>");
	printf("</tbody></table>");
	printf("</form>");

	printf("</head></html>");
}
