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

	MYSQL_RES* c_res;
	MYSQL_ROW c_row;

	MYSQL_RES* d_res;
	MYSQL_ROW d_row;
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

	//상품 목록 작성
	strcpy(q,"select putbasket.book_num,book.title,book.price,sum(putbasket.quantity), sum(putbasket.quantity)*book.price from putbasket,book where putbasket.basket_num='");
	strcat(q,findEntry("arg0"));
	strcat(q,"' and putbasket.book_num=book.num group by book_num");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	//카드정보 불러오기
	strcpy(q,"select comp,num,date_format(date,'%y/%m') from card where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	c_res=mysql_store_result(&mysql);
	//배송지 정보 불러오기
	strcpy(q,"select * from addr where id ='");
	strcat(q,findEntry("id"));
	strcat(q,"' order by chk asc");
	mysql_query(&mysql,q);
	d_res=mysql_store_result(&mysql);


	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");

	printf("<script language=\"javascript\">");
	printf("function change_input(val){");
	c_row=mysql_fetch_row(c_res);
	printf("var cn=document.getElementById(\"cardnum\");");
	printf("var cd=document.getElementById(\"carddate\");");
	printf("if(val==\"%s:%s\"){",c_row[0],c_row[1]);
	printf("cn.value=\"%s\";",c_row[1]);
	printf("cd.value=\"%s\";}",c_row[2]);
	while((c_row=mysql_fetch_row(c_res)))
	{
		printf("else if(card=\"%s:%s\"){",c_row[0],c_row[1]);
		printf("cn.value=\"%s\";",c_row[1]);
		printf("cd.value=\"%s\";}",c_row[2]);
	}
	printf("}");

	printf("function input_addr(val){");
	printf("var zip=document.getElementById(\"zip\");");
	printf("var base=document.getElementById(\"base\");");
	printf("var detail=document.getElementById(\"detail\");");
	printf("if (val==\"자택\"){");
	d_row=mysql_fetch_row(d_res);
	printf("zip.value=\"%s\";",d_row[2]);
	printf("base.value=\"%s\";",d_row[3]);
	printf("detail.value=\"%s\";}",d_row[4]);
	printf("else if (val==\"회사\"){");
	d_row=mysql_fetch_row(d_res);
	printf("zip.value=\"%s\";",d_row[2]);
	printf("base.value=\"%s\";",d_row[3]);
	printf("detail.value=\"%s\";}",d_row[4]);
	printf("}");



	printf("</script>");
	mysql_free_result(c_res);




	printf("</head>");
	printf("<body>");
	printf("<form method=\"post\" action=\"commit_basket_order.cgi\">");
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:left;\"><tbody>");
	printf("<tr><td></td><td style=\"text-align:center;\"><h1>상품 주문</h1></td>");
	//상품 목록 작성
	int rows=mysql_num_fields(res);
	fields=mysql_num_rows(res);
	int tq=0;
	int tp=0;
	int idx=0;
	//상품 정보 
	for(int j=0;j<fields;j++)
	{	
		row=mysql_fetch_row(res);
		printf("<tr>");
		for(int i=0;i<rows;i++)
		{
			printf("<td style=\"text-align:center;border-bottom:1px solid black;\">%s</td>",row[i]);
		}
		printf("<input type=\"hidden\" name=\"bn%d\" value=\"%s\">",idx,row[0]);
		printf("<input type=\"hidden\" name=\"bq%d\" value=\"%s\">",idx++,row[3]);

		printf("</tr>");
		tq+=atoi(row[3]);
		tp+=atoi(row[4]);
	}
	printf("<tr><td style=\"border-bottom:1px solid black;text-align:center;border-top:3px solid black;\">Total</td><td style=\"border-bottom:1px solid black;border-top:3px solid black;text-align:center;\"></td><td style=\"border-bottom:1px solid black;text-align:center;border-top:3px solid black;\"></td><td style=\"border-bottom:1px solid black;text-align:center;border-top:3px solid black;\">%d개</td><td style=\"border-bottom:1px solid black;text-align:center;border-top:3px solid black;\">%d원</td>",tq,tp);
	printf("<input type=\"hidden\" name=\"tp\" value=\"%d\">",tp);
	printf("<input type=\"hidden\" name=\"bt\" value=\"%d\">",fields*2);
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("id"));

	//결제 카드 입력
	
	
	printf("<tr><td style=\"border-bottom:1px solid black;\">결제 카드</td><td style=\"border-bottom:1px solid black;\">");
	printf("<select id=\"card\" onchange=\"change_input(this.value)\">");
	printf("<option selected>-------</option>");
	strcpy(q,"select comp,num from card where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	c_res=mysql_store_result(&mysql);

	while((c_row=mysql_fetch_row(c_res)))
	{
		printf("<option value=\"%s:%s\">%s</option>",c_row[0],c_row[1],c_row[0]);
	}
	printf("</select></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td></tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;\">카드번호</td>");
	printf("<td style=\"border-bottom:1px solid black;\"><input type=\"text\" size=\"16\" name=\"cardnum\" id=\"cardnum\" value=\"카드번호\">  <input type=\"text\" size=\"2\" name=\"carddate\" id=\"carddate\" value=\"유효기간\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td></tr>");


	//배송지 입력
	//
	//
	printf("<tr><td style=\"border-bottom:1px solid black;\">배송지</td><td style=\"border-bottom:1px solid black;\"><input type=\"radio\" name=\"chk\" value=\"자택\" onclick=\"input_addr(this.value)\">자택");
	printf("<input type=\"radio\" name=\"chk\" value=\"회사\" onclick=\"input_addr(this.value)\">회사</td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td> </tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;\">우편번호</td><td style=\"border-bottom:1px solid black;\"><input type=\"text\" name=\"zip\"size=\"10\"id=\"zip\" value=\"\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td></tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;\">기본주소</td><td style=\"border-bottom:1px solid black;\"><input type=\"text\"name=\"base\" size=\"20\"id=\"base\" value=\"\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td></tr>");
	printf("<tr><td  style=\"border-bottom:1px solid black;\">상세주소</td><td style=\"border-bottom:1px solid black;\"><input type=\"text\"name=\"detail\" size=\"30\"id=\"detail\" value=\"\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td><td style=\"border-bottom:1px solid black;\"></td></tr>");
	printf("</form><tr><td></td><td> <input type=\"submit\" value=\"주문\"></td>");
	printf("</tbody></tabel></body>");
	printf("</html>");
	free(q);
	mysql_free_result(res);
	mysql_free_result(c_res);mysql_free_result(d_res);
//	mysql_free_result(row);
}
