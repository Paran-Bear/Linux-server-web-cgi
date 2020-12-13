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
	
	printf("<p1>계정 탈퇴를 위해 아이디와 비밀번호를 입력해주세요.</p1>");
	printf("<table><tbody>");
	printf("<form method=\"post\" action=\"commit_del_account.cgi\">");
	printf("<tr><td>ID</td><td><input type=\"text\" name=\"inputid\" size=20 maxlength=30 required></td></tr>");
	printf("<tr><td>PASSWORD</td><td><input type=\"text\" name=\"inputpwd\" size=20 maxlength=30 required></td></tr>");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));
	printf("<input type=\"hidden\" name=\"pwd\" value=\"%s\">",findEntry("pwd"));
	
	printf("<tr><td><input type=\"submit\" value=\"계정탈퇴\"></td>");
	printf("</form>");
	printf("<td><input type=\"button\" value=\"취소\" onclick=\"window.close();\"></td></tr>");
	printf("</tbody></table>");	
	printf("</head></html>");
}
