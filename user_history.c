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

	MYSQL_RES* cres;
	MYSQL_ROW crow;

	MYSQL_RES* bres;
	MYSQL_ROW brow;
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
printf("<script language=\"javascript\">");
	printf("function myorder(ord,id)\n{\n");
	printf("var mpg=document.my_order;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='detail_order.cgi';\n");
	printf("mpg.arg0.value=ord;\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");
printf("</script>");
	printf("<body>");
	strcpy(q,"select * from border where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	strcat(q," order by status asc;");
	
	int idxb=1;
	mysql_query(&mysql,q);
	
	
	
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);
	int rows=mysql_num_rows(res);
	
	char *color=malloc(sizeof(char)*99);
	printf("<form method=\"post\" action=\"\" name=\"my_order\" id=\"my_order\">");
	printf("<input type=\"hidden\" name=\"id\" value=\"\">");
	printf("<input type=\"hidden\" name=\"arg0\" value=\"\">");
	printf("</form>");
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\"><tbody>");
	if(rows!=0){
		while((row=mysql_fetch_row(res)))
		{
			
			if(strcmp(row[3],"신청")==0){
				strcpy(color,"bgcolor=\"#A9F5D0\"");}
			if(strcmp(row[3],"발송")==0){
				strcpy(color,"bgcolor=\"#F3E2A9\"");}
			if(strcmp(row[3],"판매완료")==0){
				strcpy(color,"bgcolor=\"#A9D0F5\"");}
			if(strcmp(row[3],"취소")==0){
				strcpy(color,"bgcolor=\"#FA5858\"");
			}
			
			printf("<tr %s>",color);
			printf("<td style=\"border-bottom:3px solid black;\">%d</td><td style=\"border-bottom:3px solid black\";>주문번호:%s</td><td style=\"border-bottom:3px solid black\";>상태:%s</td><td style=\"border-bottom:3px solid black;\"><input type=\"button\" value=\"주문상세\" onclick=\"myorder('%s','null');\"></td>",idxb++,row[0],row[3],row[0]);
			if(strcmp(row[3],"발2송")==0)
			{
				//printf("<td style=\"border-bottom:3px solid black;\"><input type=\"button\" value=\"수취확인\" onclick=\"get_book('%s','null');\" ></td>",row[0]);
			}
			else if(strcmp(row[3],"2신청")==0)
			{
				//printf("<td style=\"border-bottom:3px solid black;\"><input type=\"button\" value=\"주문취소\" onclick=\"order_cancle('%s','null');\" ></td>",row[0]);		
			}
			else
				printf("<td style=\"border-bottom:3px solid black;\"></td>");
			printf("</tr>");
			
			strcpy(q,"select book_num,book.title,quantity,(quantity*book.price) from book,corder where order_num='");
			strcat(q,row[0]);
			strcat(q,"' and book_num=book.num");
			mysql_query(&mysql,q);
			cres=mysql_store_result(&mysql);
			int idx=0;
			while((crow=mysql_fetch_row(cres)))
			{
				printf("<tr bgcolor=\"#E6E6E6\">");
				printf("<td style=\"border-bottom:1px solid black;\">%d</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td>",++idx,crow[0],crow[1],crow[2],crow[3]);
				printf("</tr>");
			}
			strcpy(q,"select sum(corder.quantity),sum(book.price*corder.quantity) from corder,book where order_num='");
			strcat(q,row[0]);
			strcat(q,"' and corder.book_num=book.num;");
			mysql_query(&mysql,q);
			bres=mysql_store_result(&mysql);
			brow=mysql_fetch_row(bres);
			printf("<tr bgcolor=\"#BDBDBD\"><td style=\"border-bottom:1px solid black;\">total</td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\">%s</td><td style=\"border-bottom:1px solid black;\">%s</td></tr>",brow[0],brow[1]);
			printf("<tr><td><br></td></tr>");
			
		}
	}
		else
			printf("<h1>판매이력이 존재하지 않습니다.</h1>");	
	printf("</tbody></table>");
	printf("<input type=\"button\" value=\"확인\" onclick=\"window.close();\">");
	printf("</head></html>");
}

