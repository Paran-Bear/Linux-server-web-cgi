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
	strcpy(q,"select * from basket where id='");
	strcat(q,findEntry("id"));
	strcat(q,"' and date='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	strcpy(q,"delete from basket where id='");
	strcat(q,findEntry("id"));
	strcat(q,"' and date='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);

	strcpy(q,"delete from putbasket where basket_num='");
	strcat(q,row[0]);
	strcat(q,"'");
	mysql_query(&mysql,q);

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("</script>");
	printf("<body onload=\"winclo();\"></body>");
	printf("</head></html>");
}
