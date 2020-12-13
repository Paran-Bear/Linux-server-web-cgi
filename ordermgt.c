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
	MYSQL_RES* tres;
	MYSQL_ROW trow;

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
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("</script>");
	char *q=malloc(sizeof(char)*999);

	if(strcmp(findEntry("code"),"1")==0)
	{
		printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:left;\"><tbody>");
		//상세페이지
		strcpy(q,"select num,id,date,status,card_num,date_format(card_date,'%y/%m'),card_comp,addr_zip,addr_base,addr_detail from border where num='");
		strcat(q,findEntry("order_num"));
		strcat(q,"'");
		mysql_query(&mysql,q);
		res=mysql_store_result(&mysql);
		int rows=mysql_num_fields(res);
		int tq=0;
		int tp=0;
		char *arr[]={"주문번호","주문자","주문일자","주문상태","카드번호","유효기간","카드사","우편번호","기본주소","상세주소"};
		while((row=mysql_fetch_row(res)))
		{
			strcpy(q,"select corder.book_num,book.title,corder.quantity,corder.quantity*book.price from corder,book where corder.book_num=book.num and order_num='");
			strcat(q,findEntry("order_num"));
			strcat(q,"'");
			mysql_query(&mysql,q);
			tres=mysql_store_result(&mysql);
			for(int i=0;i<rows;i++)
			{
				printf("<tr>");
				printf("<td style=\"border-right:3px solid black; border-bottom:1px solid black;\">%s</td>",arr[i]);
				printf("<td style=\"border-bottom:1px solid black;\">%s</td>",row[i]);
				printf("<td style=\"border-bottom:1px solid black;\"></td>");
				printf("<td style=\"border-bottom:1px solid black;\"></td>");

				printf("</tr>");
			}
//			printf("<td style=\"border-bottom:1px solid black;\"></td>");

		}
//		printf("</tbody></table>");
//		printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:center;\"><tbody>");
		printf("<tr><td style=\"border-bottom:3px solid black;\">주문한도서</td>");
		printf("<td style=\"border-bottom:3px solid black;\"></td>");
		printf("<td style=\"border-bottom:3px solid black;\"></td>");
		printf("<td style=\"border-bottom:3px solid black;\"></td></tr>");

		rows=mysql_num_fields(tres);
		while((trow=mysql_fetch_row(tres)))
			{
				printf("<tr>");
				for(int i=0;i<rows;i++){
					printf("<td style=\"border-bottom:1px solid black; text-align:center;\">");
					printf("%s",trow[i]);
					printf("</td>");
				}
				printf("</tr>");
				tq+=atoi(trow[2]);
				tp+=atoi(trow[3]);
			}
			printf("<tr>");
			printf("<td style=\"text-align:center;\">total</td>");
			printf("<td></td>");//제목 빈칸
			printf("<td style=\"text-align:center;\">%d</td>",tq);
			printf("<td style=\"text-align:center;\">%d</td>",tp);
			printf("</tr>");
		
		printf("<tr><td></td>");

		printf("<td style=\"text-align:center;\"><input type=\"button\" value=\"확인\" onclick=\"winclo();\"></td>");
		printf("</tr>");
		printf("</tbody></table>");
		free(q);
		mysql_free_result(res);
		mysql_close(&mysql);

	}
	


	
	if(strcmp(findEntry("code"),"2")==0)
	{
		//발송으로 바꾸기
		strcpy(q,"update border set status='발송' where num='");
		strcat(q,findEntry("order_num"));
		strcat(q,"'");
		if(mysql_query(&mysql,q))
		{
			printf("<p1>error : %s</p1>",mysql_error(&mysql));
		}
		else
		{
			printf("<h1>상품을 발송 하였습니다</h1>");
		}
		printf("<input style=\"text-align:center;\" type=\"button\" value=\"확인\" onclick=\"winclo();\">");
		free(q);
		mysql_close(&mysql);


		
	}
	if(strcmp(findEntry("code"),"3")==0)
	{
		//주문 취소
		strcpy(q,"update border set status='취소' where num='");
		strcat(q,findEntry("order_num"));
		strcat(q,"'");
		if(mysql_query(&mysql,q))
		{
			 printf("<p1>error : %s</p1>",mysql_error(&mysql));
		}
		strcpy(q,"select * from corder where order_num='");
		strcat(q,findEntry("order_num"));
		strcat(q,"'");
		mysql_query(&mysql,q);
		res=mysql_store_result(&mysql);
		while((row=mysql_fetch_row(res)))
		{
			strcpy(q,"update book set stock=stock+");
			strcat(q,row[2]);
			strcat(q," where num='");
			strcat(q,row[1]);
			strcat(q,"'");
			mysql_query(&mysql,q);
		}
		printf("<h1>주문을 취소하였습니다</h1>");
		printf("<input style=\"text-align:center;\" type=\"button\" value=\"확인\" onclick=\"winclo();\">");
		free(q);
		mysql_free_result(res);
		mysql_close(&mysql);


	}
	
	printf("</head></html>");
}
