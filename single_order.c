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

	MYSQL_RES* b_res;
	MYSQL_ROW b_row;

	MYSQL_RES* c_res;	       
       	MYSQL_ROW c_row;

	MYSQL_RES* d_res;
	MYSQL_ROW d_row;

	int fields,b_f,c_f,d_f;
	
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
	
	//유저정보 저장.
	strcpy(q,"select * from user where id='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	fields=mysql_num_fields(res);

	strcpy(q,"select * from book where num='");
	strcat(q,findEntry("arg1"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	b_res=mysql_store_result(&mysql);
	b_row=mysql_fetch_row(b_res);
	b_f=mysql_num_fields(b_res);
	strcpy(q,"select comp,num,date_format(date,'%y/%m') from card where id='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	c_res=mysql_store_result(&mysql);
	c_f=mysql_num_fields(c_res);
	strcpy(q,"select * from addr where id ='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	d_res=mysql_store_result(&mysql);
	d_f=mysql_num_fields(d_res);



	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function change_input(val){\n");
	c_row=mysql_fetch_row(c_res);
	printf("var cn=document.getElementById(\"cardnum\");\n");
	printf("var cd=document.getElementById(\"carddate\");\n");
	printf("if(val==\"%s:%s\"){\n",c_row[0],c_row[1]);
	printf("cn.value=\"%s\";\n",c_row[1]);
	printf("cd.value=\"%s\";}\n",c_row[2]);
	while((c_row=mysql_fetch_row(c_res)))
	{
		printf("else if(card=\"%s:%s\"){\n",c_row[0],c_row[1]);
		printf("cn.value=\"%s\";\n",c_row[1]);
		printf("cd.value=\"%s\";\n}",c_row[2]);
	}
	printf("else if(card=\"-------\"){\n");
	printf("cn.value=\"NON\";\n");
	printf("cd.value=\"NON\";\n}");
	printf("}\n");
	mysql_free_result(c_res);
	
	d_f=mysql_num_rows(d_res);
	
	printf("function input_addr(val){");
	printf("var zip=document.getElementById(\"zip\");\n");
	printf("var base=document.getElementById(\"base\");\n");
	printf("var detail=document.getElementById(\"detail\");\n");
//	printf("var d%d=\"asdf\";",d_f);
	if(d_f==2)
	{
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
	}
	else if(d_f==1)
	{
		d_row=mysql_fetch_row(d_res);
		printf("if (val==\"%s\"){",d_row[1]);
		printf("zip.value=\"%s\";",d_row[2]);
		printf("base.value=\"%s\";",d_row[3]);
		printf("detail.value=\"%s\";}",d_row[4]);
		printf("else{");
		printf("zip.value=\"\";");
		printf("base.value=\"\";");
		printf("detail.value=\"주소를 등록 해주세요\";}");
	}
	printf("}");

	printf("</script>");
	strcpy(q,"select comp,num,date_format(date,'%y/%m') from card where id='");
	strcat(q,findEntry("arg0"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	c_res=mysql_store_result(&mysql);
	c_f=mysql_num_fields(c_res);
	printf("<h1>상품 주문</h1>");
	printf("<body><table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:left;\"><tbody>");
	printf("<form method=\"post\" action=\"commit_order.cgi\">");
//	printf("<form method=\"post\" action=\"cpa.cgi\">");
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">상품번호</td><td style=\"border-bottom:1px solid black;\">%s</td></tr>",findEntry("arg1"));
	printf("<input type=\"hidden\" name=\"id\" value=\"%s\">",findEntry("arg0"));
	printf("<input type=\"hidden\" name=\"book_num\" value=\"%s\">",findEntry("arg1"));
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">타이틀</td><td style=\"border-bottom:1px solid black;\">%s</td></tr>",b_row[1]);
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">수량</td><td style=\"border-bottom:1px solid black;\">%s</td></tr>",findEntry("arg2"));
	printf("<input type=\"hidden\" name=\"quan\" value=\"%s\">",findEntry("arg2"));
	int total=atoi(b_row[3]) * atoi(findEntry("arg2"));
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">총액</td><td style=\"border-bottom:1px solid black;\">%d</td></tr>",total);
	printf("<input type=\"hidden\" name=\"total\" value=\"%d\">",total);
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">결제 카드</td><td style=\"border-bottom:1px solid black;\">");
	printf("<select name=\"card\" onchange=\"change_input(this.value)\">");
	printf("<option value=\"NON\" selected>-------</option>");
	while((c_row=mysql_fetch_row(c_res)))
	{
		printf("<option value=\"%s:%s\">%s</option>",c_row[0],c_row[1],c_row[0]);
	}
	printf("</select></td></tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">카드번호</td>");
	printf("<td style=\"border-bottom:1px solid black;\"><input type=\"text\" size=\"16\" id=\"cardnum\"  name=\"cardnum\" value=\"카드번호\">  <input type=\"text\" size=\"2\" id=\"carddate\" value=\"유효기간\"></td></tr>");

	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">배송지</td><td style=\"border-bottom:1px solid black;\"><input type=\"radio\" name=\"chk\" value=\"자택\" checked onclick=\"input_addr(this.value)\">자택");
	printf("<input type=\"radio\" name=\"chk\" value=\"회사\" onclick=\"input_addr(this.value)\">회사</td></tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">우편번호</td><td style=\"border-bottom:1px solid black;\"><input type=\"text\" size=\"10\"id=\"zip\" value=\"배송지를\"></td></tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">기본주소</td><td style=\"border-bottom:1px solid black;\"><input type=\"text\" size=\"20\"id=\"base\" value=\"선택해주세요.\"></td></tr>");
	printf("<tr><td style=\"border-bottom:1px solid black;border-right:3px solid black;\">상세주소</td><td style=\"border-bottom:1px solid black;\"><input type=\"text\" size=\"30\"id=\"detail\" value=\"\"></td></tr>");
	printf("<tr><td></td><td><input type=\"submit\" value=\"주문하기\">\t<input type=\"button\" value=\"취소\" onclick=\"window.close();\"></td></tr>");
	printf("</form>");
	printf("</tbody></table>");
	printf("</head></html>");
}
