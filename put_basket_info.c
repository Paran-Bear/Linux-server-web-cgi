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
	if(mysql_query(&mysql,"use shopdb"))
		{
			printf("use test_db 쿼리문은 실패");
		}

	char *q=malloc(sizeof(char)*999);
	strcpy(q,"select * from book where num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int rows=mysql_num_rows(res);
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<h1>장바구니 추가</h1>");	
	printf("<script language=\"JavaScript\">");
	printf("function closeWin(t){");
	printf("setTimeout(\"window.close();\",t);}");
	printf("function create_bask(id){");
	printf("var create = document.create_basket;");
	printf("var url='create_basket.cgi';");
	printf("window.open('','popupView','width=300,height=300');");
	printf("create.action=url;");
	printf("create.target='popupView';");
	printf("create.id.value=id;");
	printf("create.submit();window.location.reload();}");


	printf("</script>");
	printf("<body>");
	row=mysql_fetch_row(res);
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\">\n<tbody>");
//	mysql_query(&mysql,q);
//	res=mysql_store_result(&mysql);
//	row=mysql_fetch_row(res);
	printf("<form method=\"post\" action=\"put_basket.cgi\">");
	printf("<tr><td style=\"border-bottom:1px solid black; border-right:1px solid black;padding-right:40;padding-left:10;\">상품번호</td>");
	printf("<input type=\"hidden\" name=\"book_num\" value=\"%s\">",row[0]);
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:10;\">%s</td>",row[0]);
	printf("</tr><tr>");
	printf("<td style=\"border-bottom:1px solid black; border-right:1px solid black;padding-right:40;padding-left:10;\">타이틀</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:10;\">%s</td>",row[1]);
	printf("</tr><tr>");
	printf("<td style=\"border-bottom:1px solid black; border-right:1px solid black;padding-right:40;padding-left:10;\">수량</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:10;\">%s</td>",findEntry("quantity0"));
	printf("<input type=\"hidden\" name=\"quantity\" value=\"%s\">",findEntry("quantity0"));
	strcpy(q,"select price*");
	strcat(q,findEntry("quantity0"));
	strcat(q," from book where num='");
	strcat(q,row[0]);
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	printf("</tr><tr>");
	printf("<td style=\"border-bottom:1px solid black; border-right:1px solid black;padding-right:40;padding-left:10;\">가격</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:10;\">%s 원</td>",row[0]);

	printf("<tr><td style=\"border-bottom:1px solid black; border-right:1px solid black;padding-right:40;padding-left:10;\">장바구니 선택</td>");
	printf("<td style=\"border-bottom:1px solid black;padding-right:40;padding-left:10;\">");
	printf("<select name=\"basketnum\">");
	printf("<option value=\"Non\">--------</option>");
	mysql_free_result(res);
	strcpy(q,"select * from basket where id ='");
	strcat(q,findEntry("arg1"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int cnt=1;
	while((row=mysql_fetch_row(res)))
	{
		printf("<option value=\"%s\">%s</option>",row[0],row[1]);
	}
	printf("</option></td>");
	printf("<tr><td><input type=\"submit\" value=\"장바구니에 담기\"></td></form>");
	printf("<td>");
	printf("<form name=\"create_basket\" id=\"create_basket\" method=\"post\" action=\"create_basket.cgi\">");
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("arg1"));
	printf("<input type=\"submit\" value=\"장바구니 생성\"></td>");



	printf("</tr></tbody></table></body></head></html>");

	printf("</body></head></html>");
	free(q);
	mysql_free_result(res);
	mysql_free_result(row);
}

