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
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");//한글 사용
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><body>");	
	if(!mysql_real_connect(&mysql,NULL,"shop","shop1","shopdb",3306,(char *)NULL,0))
	{
		
		printf("DB연결 실패 ");
		
	}
	else
	{               
//		printf("DB연결성공<BR> ");
	}
	if(mysql_query(&mysql,"use shopdb"))
	{
		printf("use test_db 쿼리문은 실패");              
	}
	else
	{
//		printf("use test_db 쿼리문 성공<BR>");
	}
	
	char *s=malloc(sizeof(char)*999);
	strcpy(s,"select * from book where num ='");
	strcat(s,entries[0].val);
	strcat(s,"'");
	if(mysql_query(&mysql,s))
	{printf("조회 불가: %s",s);}
	else{
		res=mysql_store_result(&mysql);
		row=mysql_fetch_row(res);
		printf("<form method='post' action='../cgi-bin/edit_book.cgi'><table><tbody><tr><td>상품번호</td><td><input type=\"text\" name=\"num\" value=\"%s\" size=\"20\" maxlength=\"10\" required></td>		</tr>		<tr>		<td>상품이름</td>		<td><input type=\"text\" name=\"title\" value=\"%s\"  size=\"30\" maxlength=\"30\"required></td>		</tr>		<tr>		<td>재고</td>		<td><input type=\"number\" name=\"stock\" value=\"%s\"  min=\"0\" max=\"99999999\"required></td>		</tr>		<tr>		<td>판매가</td>		<td><input type=\"number\" name=\"price\" value=\"%s\"  min=\"0\" max=\"99999999\"required></td>		</tr>		</tbody>		</table>		<input type=\"submit\" value=\"수 정\">		</form>",row[0],row[1],row[2],row[3]);		}
	
//	if(mysql_query(&mysql,s2))
//		printf("등록실패");
//	else
//		printf("<h1>상품 등록 완료</h1>");
//	res=mysql_store_result(&mysql);//쿼리 결과 저장.
//	fields=mysql_num_fields(res);//쿼리결과의 개수
//	while((row=mysql_fetch_row(res)))//쿼리 결과 탐색.
//	{
//		for(int i=0;i<fields;++i)
//			printf("%s ",row[i]);
//		printf("<br>");
//	}
//	mysql_free_result(res);//쿼리 결과 해제.
	mysql_close(&mysql);//쿼리 해제.
	printf("</body></html>");//html끝.
}

