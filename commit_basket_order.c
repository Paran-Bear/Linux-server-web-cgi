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
	char *order_num=malloc(sizeof(char)*999);
	int ck=0;

	printf("Content-type: text/html\n\n");
	
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");
	printf("</script>");

	//재고검사.
	for(int i=0;i<atoi(findEntry("bt"));i++)
	{       
		if((i%2)==0)
		{
			strcpy(q,"select stock from book where num='");
			strcat(q,entries[i].val);
			strcat(q,"'");
			mysql_query(&mysql,q);
			res=mysql_store_result(&mysql);
			row=mysql_fetch_row(res);
			if(atoi(entries[i+1].val)>atoi(row[0])){
				ck++;
				printf("<p1>%s의 재고가 부족합니다<br></p1>",entries[i].val);
			}
		}
	}








	if(ck==0){
	//주문번호 생성
	strcpy(q,"insert into au_in(id) values('");
	strcat(q,findEntry("id"));
	strcat(q,"')");
	mysql_query(&mysql,q);

	strcpy(q,"select concat(date_format(now(),'%Y%m\%d'),LPAD(max(num),3,'0')) from au_in where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	//printf("%s<br>",q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	strcpy(order_num,row[0]);
	
	//결제 카드 정보
	MYSQL_RES* cres;
	MYSQL_ROW crow;
	strcpy(q,"select * from card where id='");
	strcat(q,findEntry("id"));
	strcat(q,"' and num='");
	strcat(q,findEntry("cardnum"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	cres=mysql_store_result(&mysql);
	crow=mysql_fetch_row(cres);


	//배송지 정보
	MYSQL_RES* dres;
	MYSQL_ROW drow;
	strcpy(q,"select * from addr where id='");
	strcat(q,findEntry("id"));
	strcat(q,"' and chk='");
	strcat(q,findEntry("chk"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	dres=mysql_store_result(&mysql);
	drow=mysql_fetch_row(dres);

	//주문 등록
	strcpy(q,"insert into border(num,total,status,card_num,card_date,card_comp,addr_zip,addr_base,addr_detail,id) values ('");
	strcat(q,order_num);
	strcat(q,"','");	
	strcat(q,findEntry("tp"));
	strcat(q,"','");
	strcat(q,"신청");
	strcat(q,"','");
	strcat(q,crow[1]);
	strcat(q,"','");
	strcat(q,crow[2]);
	strcat(q,"','");
	strcat(q,crow[3]);
	strcat(q,"','");
	strcat(q,drow[2]);
	strcat(q,"','");
	strcat(q,drow[3]);
	strcat(q,"','");
	strcat(q,drow[4]);
	strcat(q,"','");
	strcat(q,findEntry("id"));
	strcat(q,"')");
	mysql_query(&mysql,q);
	/*
	strcpy(q,"select date from au_in where num=(select max(num) from au_in where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	*/


	//주문선택 등록
	for(int i=0;i<atoi(findEntry("bt"));i++)
	{	
		if((i%2)==0)
		{
			
			strcpy(q,"insert into corder(order_num,book_num,quantity) values('");
			strcat(q,order_num);
			strcat(q,"','");
			strcat(q,entries[i].val);
			strcat(q,"','");
			strcat(q,entries[i+1].val);
			strcat(q,"')");
			mysql_query(&mysql,q);
			strcpy(q,"update book set stock=(stock-");
			strcat(q,entries[i+1].val);
			strcat(q,") where num='");
			strcat(q,entries[i].val);
			strcat(q,"'");
			mysql_query(&mysql,q);
		}
	}


	



	
	
	printf("<h1>주문이 완료 되었습니다.</h1>");
	printf("<body>주문 완료<br>주문번호 : %s",order_num);}
	else
	{
		printf("<p1>주문 실패</p1>");
	}
	printf("<br><input type=\"button\" value=\"닫기\" onclick=\"winclo();\">");
	printf("</head></html>");
	free(q);
	mysql_free_result(res);
	mysql_close(&mysql);
}
