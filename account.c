#include<stdio.h>
#include"/usr/include/mysql/mysql.h"
#include<errno.h>
#include"cgipost.h"
#include<string.h>
#include<stdlib.h>

int main()
{
	int fields;
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	getPostData();
//	printf("%s님 환영합니다.",findEntry("username"));
	
	for(int i = 0;i < entry_count;i++)

	{
	
		printf(" %d) [%s] = [%s]<br>\n",i, entries[i].name, entries[i].val);
       	}

	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	mysql_init(&mysql);//객체 초기화
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");//한글 사용
	
	if(!mysql_real_connect(&mysql,NULL,"test","123qwe","test_db",3306,(char *)NULL,0))
	{
		printf("Content-type: text/html\n\n");
		printf("<meta charset=\"utf-8\">");
		printf("<html><body>");
		printf("DB연결은실패 ");
		printf("</body></html>");
	}
	else
	{
		printf("Content-type: text/html\n\n");
		printf("<meta charset=\"utf-8\">");
		printf("<html><body>");
		printf("DB연결성공<BR> ");		
	}
	if(mysql_query(&mysql,"use test_db"))
	{
		printf("use test_db 쿼리문은 실패");
		printf("</body></html>");
		
	}
	else
	{
		printf("use test_db 쿼리문 성공<BR>");
		;
	}
	char *s1="insert into user_data (name,id,pwd) values(";
	char *s2=malloc(sizeof(char)*999);
	strcpy(s2,s1);
	for(int i=0;i<entry_count;i++)
	{
		strcat(s2,"'");
		strcat(s2,entries[i].val);
		strcat(s2,"'");
		if(i!=entry_count-1)
			strcat(s2,",");
	
	}
	strcat(s2,")");
	printf("%s",s2);
	if(mysql_query(&mysql,s2))
	{
		printf("insert 쿼리문은 실패<BR>%s<BR>",s2);
		
		printf("%s",mysql_error(&mysql));
	}
	else
	{
		printf("성공<BR>");
	}



	
	if(mysql_query(&mysql,"select * from user_data"))
	{
		printf("insert 쿼리문은 실패<BR>%s<BR>",s2);
		printf("%s",mysql_error(&mysql));
		
		
	}
	else
	{
		printf("성공<BR>");
	}
	
	
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	while((row=mysql_fetch_row(res)))
	{
		for(int i=0;i<fields;++i)
			printf("%s ",row[i]);
		printf("<br>");
	}
	mysql_free_result(res);
	mysql_close(&mysql);
free(s2);	
	printf("</body></html>");
	return 0;
}

