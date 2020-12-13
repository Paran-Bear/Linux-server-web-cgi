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
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");

	//비밀번호 변경
	strcpy(q,"update user set pwd='");
	strcat(q,findEntry("pwd"));
	strcat(q,"' where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	if(mysql_query(&mysql,q))
	{
		printf("<p1>error : %s</p1",mysql_error(&mysql));
	}
	
	//이름변경
	strcpy(q,"update user set name='");
	strcat(q,findEntry("name"));
	strcat(q,"' where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
if(mysql_query(&mysql,q))
	        {
			                printf("<p1>error : %s</p1",mysql_error(&mysql));
					        }
	//배송지 변경-자택
	strcpy(q,"update addr set zip='");
	strcat(q,findEntry("zip자택"));
	strcat(q,"',base='");
	strcat(q,findEntry("base자택"));
	strcat(q,"',detail='");
	strcat(q,findEntry("detail자택"));
	strcat(q,"' where chk='자택' and id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	if(mysql_query(&mysql,q))
		        {
				                printf("<p1>error : %s</p1",mysql_error(&mysql));
						        }
	//배송지 변경-회사
	strcpy(q,"update addr set zip='");     
     	strcat(q,findEntry("zip회사"));
	strcat(q,"',base='");
	strcat(q,findEntry("base회사"));
	strcat(q,"',detail='");
	strcat(q,findEntry("detail회사"));
	strcat(q,"' where chk='회사' and id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	if(mysql_query(&mysql,q))
		        {
				                printf("<p1>error : %s</p1",mysql_error(&mysql));
						        }
	printf("<h1>완료되었습니다</h1>");
	printf("<input type=\"button\" value=\"확인\" onclick=\"window.close();\">");
	mysql_close(&mysql);
	free(q);
	printf("<html><head>");
	printf("</head></html>");
}
