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
	strcpy(q,"select pwd from user where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");

	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("</script>");

	if(strcmp(findEntry("pwd"),row[0])==0)
	{
		strcpy(q,"update user set pwd='");
		strcat(q,findEntry("new_pwd"));
		strcat(q,"' where id='");
		strcat(q,findEntry("id"));
		strcat(q,"'");
		if(mysql_query(&mysql,q))
		{
			printf("<p1>err:%s</p1>",mysql_error(&mysql));
		}
		else printf("<h1>변경되었습니다.</h1>");
	}
	else
	{
		printf("<p1>기존 비밀번호가 일치하지 않습니다.</p1>");
	}
	printf("<br><input type=\"button\" value=\"확인\" onclick=\"winclo();\">");
	free(q);
	mysql_free_result(res);	


	printf("</head></html>");
}
