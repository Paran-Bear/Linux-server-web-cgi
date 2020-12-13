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
//	MYSQL_RES* tmp;
//	MYSQL_ROW tmp;
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("function go_login(){");
	printf("window.close();");
	printf("opener.window.location.href='/login.html';}");

	printf("</script>");



	if(strcmp(findEntry("id"),findEntry("inputid"))==0)
	{
		if(strcmp(findEntry("pwd"),findEntry("inputpwd"))==0)
		{
			
			strcpy(q,"delete from addr where id='");
			strcat(q,findEntry("id"));
			strcat(q,"'");
			mysql_query(&mysql,q);

			strcpy(q,"delete from au_in where id='");
			strcat(q,findEntry("id"));
			strcat(q,"'");
			mysql_query(&mysql,q);

			strcpy(q,"delete from putbasket where basket_num in (select num from basket where id='");
			strcat(q,findEntry("id"));
			strcat(q,"')");
			mysql_query(&mysql,q);

			strcpy(q,"delete from basket where id='");
			strcat(q,findEntry("id"));
			strcat(q,"'");
			mysql_query(&mysql,q);

			strcpy(q,"delete from card where id='");
			strcat(q,findEntry("id"));
			strcat(q,"'");
			mysql_query(&mysql,q);

			strcpy(q,"select book_num, quantity from corder where order_num in (select num from border where status='신청' and id='");
			strcat(q,findEntry("id"));
			strcat(q,"')");
			mysql_query(&mysql,q);
			res=mysql_store_result(&mysql);
			while((row=mysql_fetch_row(res)))
			{

				strcpy(q,"update book set stock=stock+");
				strcat(q,row[1]);
				strcat(q," where num='");
				strcat(q,row[0]);
				strcat(q,"'");
				mysql_query(&mysql,q);
			}
			strcpy(q,"delete from corder where order_num in (select num from border where status='신청' and id='");
			strcat(q,findEntry("id"));                                                                      
			strcat(q,"')");                                                                                         
			mysql_query(&mysql,q);

			strcpy(q,"delete from border where status='신청' and id='");   
   			strcat(q,findEntry("id"));   
			strcat(q,"'");                  
			mysql_query(&mysql,q);

			strcpy(q,"update border set status='판매완료' where status='발송' and id='"); 
			strcat(q,findEntry("id"));   
			strcat(q,"'"); 
			mysql_query(&mysql,q);

			strcpy(q,"update border set id='삭제된계정' where id='");  
  			strcat(q,findEntry("id"));   
			strcat(q,"'");                                          
			mysql_query(&mysql,q);

			strcpy(q,"delete from user where id='");                                    
			strcat(q,findEntry("id"));                                              
			strcat(q,"'");                                                                                                                  
    			mysql_query(&mysql,q);
			printf("<h1>삭제가 완료되었습니다.</h1>");
			printf("<input type=\"button\" value=\"확인\" onclick=\"go_login();\">");
			mysql_free_result(res);

		}
		else
		{
			printf("<p1>입력 정보가 일치하지 않습니다<br></p1>");
			printf("<input type=\"button\" value=\"확인\" onclick=\"window.close();\">");
		}
	}
	else{
		printf("<p1>입력 정보가 일치하지 않습니다<br></p1>");
		printf("<input type=\"button\" value=\"확인\" onclick=\"window.close();\">");
	}

	printf("</head></html>");
	free(q);
}
