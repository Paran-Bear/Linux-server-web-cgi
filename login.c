#include<stdio.h>
#include"/usr/include/mysql/mysql.h"
#include<errno.h>
#include"cgipost.h"
#include<string.h>
#include<stdlib.h>
void main(){
	

	
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	int fields;
	
	mysql_init(&mysql);//객체 초기화
	
	
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");//한글 사용
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><body>");	
	getPostData();	
	if(!mysql_real_connect(&mysql,NULL,"shop","shop1","shopdb",3306,(char *)NULL,0))
	{
		
		printf("DB연결 실패 ");
		
		
	}
	else
	{               
		//printf("DB로그인 성공<BR> ");
	}
	if(mysql_query(&mysql,"use shopdb"))
	{
		printf("db 연결 쿼리 실패");              
		}
	else
	{
//		printf("use test_db 쿼리문 성공<BR>");
	}
	char *s1="select id,pwd from user";//쿼리문 기초
//	char *s2=malloc(sizeof(char)*99);//최종 쿼리문
	if(mysql_query(&mysql,s1))//쿼리2
	{
		printf("%s",mysql_error(&mysql));
		
		
	}
	else
	{
		//printf("성공<BR>");//쿼리성공
	}
	res=mysql_store_result(&mysql);//쿼리 결과 저장.
	int err_code=0;
	fields=mysql_num_fields(res);//쿼리결과의 개수
	while((row=mysql_fetch_row(res)))//쿼리 결과 탐색.
	{
//		printf("%s, %s",row[0],row[1]);
//		printf("%s, %s",findEntry("id"),findEntry("pwd"));
		if(strcmp(row[0],findEntry("id"))==0){
			
			if(strcmp(row[1],findEntry("pwd"))==0)
				err_code=0;
			else{
				err_code=2;
				break;
			}
			}
		else
			err_code=1;
	}
	if(err_code==1)
	{	
		printf("<h1>ID가 존재하지 않습니다.<br>에러코드%d<h1>",err_code);
	}
	else if(err_code==2)
	{
		printf("<h1>비밀번호가 일치하지 않습니다.<br>에러코드%d<h1>",err_code);
	}
	else if(err_code==0)
	{
		printf("<h1>로그인 성공<br></h1><h1>환영합니다.</h1>");
	}
	else
		printf("<h1>알수없는 에러</h1>");

	
	

	
	
	mysql_free_result(res);//쿼리 결과 해제.
	mysql_close(&mysql);//쿼리 해제.
	printf("</body></html>");//html끝.
}

