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
	strcpy(q,"select num,date,status,card_num,date_format(card_date,'%y-%m'),card_comp,addr_zip,addr_base,addr_detail from border where num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);

	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<body>");
	printf("<h1>주문 상세 내역</h1>");

	printf("<table><tobdy>");
	printf("<tr><td>주문번호</td><td>%s</td></tr>",row[0]);
	printf("<tr><td>주문날자</td><td>%s</td><td>주문 상태</td><td>%s</td></tr>",row[1],row[2]);
	printf("<tr><td>결제카드정보</td></tr>");
	printf("<tr><td>카드번호</td><td>%s %s</td><td>유효기간</td><td>%s</td></tr>",row[5],row[3],row[4]);
	printf("<tr><td>배송지</td></tr>");
	printf("<tr><td>우편번호</td><td>%s</td></tr><tr><td>기본주소</td><td>%s</td></tr><tr><td>상세주소</td><td>%s</td></tr>",row[6],row[7],row[8]);
	printf("<table><tbody>");
	printf("<table><tbody>");

	strcpy(q,"select num,title,quantity, (book.price*corder.quantity) from book,corder where corder.order_num='");
	strcat(q,findEntry("arg0"));
       	strcat(q,"' and corder.book_num=book.num;");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	printf("<tr><td>주문도서<td></tr>");
	int idx=0;
	while((	row=mysql_fetch_row(res))){
	
		printf("<tr>");
		printf("<td>%d</td>",++idx);
		for(int i=0; i<4;i++)
		{
			printf("<td>%s</td>",row[i]);
		}
		printf("</tr>");
	}
	strcpy(q,"select sum(corder.quantity),sum(book.price*corder.quantity) from corder,book where order_num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"' and corder.book_num=book.num;");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	printf("<tr><td>total</td><td></td><td></td><td>%s</td><td>%s</td></tr>",row[0],row[1]);
	printf("</tbody></table>");
	printf("</body><input type=\"button\" value=\"닫기\" onclick=\"window.close();\">");


	printf("</head></html>");
}
