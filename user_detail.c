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
	printf("Content-type: text/html\n\n");
	printf("<meta charset=\"utf-8\">");
	
	printf("<html><head>");
	printf("<script language=\"javascript\">");
	printf("function winclo(){");
	printf("window.close();");
	printf("opener.location.reload();}");

	printf("function add_card(id)\n{");
	printf("var mpg=document.userf;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='inst_card.cgi';\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.submit();\n}\n");

	printf("function del_card(id,num)\n{");
	printf("var mpg=document.userf;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='rm_card.cgi';\n");
	printf("mpg.id.value=id;\n");
	printf("mpg.num.value=num;");
	printf("mpg.submit();\n}\n");

	printf("function del_account(id,pwd)\n{");
	printf("var mpg=document.userf;\n");
	printf("window.open('','popupView','width=600,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='commit_del_account.cgi';\n");
/*	printf("mpg.pwd.value=pwd;");
	printf("mpg.inputpwd.value=pwd;");
	printf("mpg.inputid.value=id;");*/
	printf("mpg.submit();\n}\n");


	printf("function edit_user_info(id,pwd,name,chk1,zip1,base1,detail1,chk2,zip2,base2,detail2)\n{");	  
  	printf("var mpg=document.userf;\n");
	printf("window.open('','popupView','width=1000,height=500');\n");
	printf("mpg.target='popupView';\n");
	printf("mpg.action='edit_user_info.cgi';\n");
//	printf("mpg.id.value=id;\n");
//	printf("mpg.pwd.value=pwd;");
//	printf("mpg.name.value=name;");
	printf("mpg.submit();\n}\n");



	strcpy(q,"select num,date_format(date,'%y/%m'),comp from card where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	int rows;
	rows=mysql_num_rows(res);
	if(rows!=0)     
	{
		row=mysql_fetch_row(res);
	printf("function change_input(val){");
	
	printf("var cn=document.getElementById(\"card_num\");");
	printf("var cd=document.getElementById(\"card_date\");");
	printf("if(val==\"0\"){");
	printf("cn.value=\"%s\";",row[0]);
	printf("cd.value=\"%s\";}",row[1]);
	int t=1;
	while((row=mysql_fetch_row(res)))
	{
		printf("else if(val=\"%d\"){",t++);
		printf("cn.value=\"%s\";",row[0]);
		printf("cd.value=\"%s\";}",row[1]);
	}
	printf("}");
	}
	printf("</script>");
	
	printf("<body>");
	printf("<table style=\"border-collapse:collapse;width=60%;height=100px;margin:auto;text-align:left;\"><tbody>");
	printf("<form method=\"post\" name=\"userf\" id=\"userf\" action=\"edit_user_info.cgi\">");
	printf("<input type=\"hidden\" name=\"inputid\" value=\"%s\">",findEntry("id"));
	printf("<input type=\"hidden\" name=\"num\" value=\"\">");
//기본정보 
	strcpy(q,"select * from user where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	row=mysql_fetch_row(res);
	printf("<tr>");
	printf("<td style=\"border-bottom:1px solid black;border-right:3px solid black;text-align:center\">이름</td> ");
	printf("<td style=\"border-bottom:1px solid black;\">");
	printf("<input type=\"text\" maxlength=\"30\" name=\"name\" value=\"%s\"></td>",row[2]);
//	printf("<td style=\"border-bottom:1px solid black;\"></td>");
	printf("</tr>");
	printf("<tr>");
	printf("<td style=\"border-bottom:1px solid black;border-right:3px solid black;text-align:center\">ID</td> ");
	printf("<td style=\"border-bottom:1px solid black;\">");
	printf("<input type=\"text\" maxlength=\"30\" name=\"id\" value=\"%s\"></td>",row[0]);
//	printf("<td style=\"border-bottom:1px solid black;\">");
	printf("</tr>");
	printf("<tr>");
	printf("<td style=\"border-bottom:3px solid black;border-right:3px solid black;text-align:center\">PASSWORD</td> ");
	printf("<td style=\"border-bottom:3px solid black;\">");
	printf("<input type=\"text\" maxlength=\"30\" name=\"pwd\" value=\"%s\"></td>",row[1]);
	printf("<input type=\"hidden\" name=\"inputpwd\" value=\"%s\">",row[1]);
//	printf("<td style=\"border-bottom:3px solid black;\">");
	printf("</tr>");

//카드정보
	strcpy(q,"select comp from card where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	rows=mysql_num_rows(res);
	printf("<tr>");
	printf("<td style=\"border-bottojklhm:1px solid black;border-right:3px solid black;text-align:center\">");
	printf("등록 카드</td>");

	printf("<td style=\"border-bottom:1px solid black;borde2r-right:3px solid black;\">");
	printf("<select name=\"comp\" onchange=\"change_input(this.value)\">");
	printf("<option selected>카드선택</option>");
	int idx=0;	
	if(rows!=0)
	{
	while((row=mysql_fetch_row(res)))
	{
		printf("<option value=\"%d\">%s</option>",idx++,row[0]);
	
	}
	}
	printf("<input type=\"button\" value=\"카드 등록\" onclick=\"add_card('%s')\">",findEntry("id"));
//	printf("");
//rintf("<td style=\"border-bottom:1px solid black;border12-right:3px solid black;t1ext-align:center\">");
	printf("<input type=\"button\" value=\"카드 삭제\" onclick=\"del_card('%s',card_num.value)\">",findEntry("id"));
	printf("</td>");
	printf("<tr>");
	printf("<td  style=\"border-bottom:3px solid black;border-right:3px solid black;text-align:center\"></td>");
	printf("<td  style=\"border-bottom:3px solid black;bord123er-right:3px solid black2;t2ext-align:c2enter\">");
	printf("<input type=\"text\" maxlength=\"19\" id=\"card_num\" name=\"card_num\" value=\"\">");
	printf("<input type=\"text\" size=\"3\" maxlength=\"5\" id=\"card_date\" name=\"card_date\" value=\"\">");
	printf("</td>");
	
	
	
	
//배송지 정보
	strcpy(q,"select chk,zip,base,detail from addr where id='");
	strcat(q,findEntry("id"));
	strcat(q,"'");
	mysql_query(&mysql,q);
	res=mysql_store_result(&mysql);
	idx=1;
	while((row=mysql_fetch_row(res)))
	{
		printf("<tr>");
		printf("<td style=\"border-bo32ttom:1px solid black;border-right:3px solid black;text-align:center\"></td>");
		printf("<td>");
		printf("<input type=\"text\" name=\"zip%s\" value=\"%s\"></td>",row[0],row[1]);
		printf("</tr>");

		printf("<tr>"); 
		printf("<td style=\"border-right:3px solid black;paddin-right:10px;\">주소지 : %s</td>",row[0]);
	    	printf("<input type=\"hidden\" name=\"chk%d\" value=\"%s\">",idx++,row[0]);	
		printf("<td style=\"bor123der-bottom:1px solid black;\">"); 
		printf("<input type=\"text\" name=\"base%s\" value=\"%s\"></td>",row[0],row[2]);
		printf("</tr>");

		printf("<tr>"); 
		printf("<td  style=\"border-bottom:3px solid black;border-right:3px solid black;text-align:center\"></td>");    
		printf("<td style=\"border-bottom:3px solid black;\">"); 
		printf("<input type=\"text\" name=\"detail%s\" value=\"%s\"></td>",row[0],row[3]);
		printf("</tr>");
	}
	printf("<tr>");
	printf("<td>");
	printf("</form>");
	printf("<input type=\"button\" value=\"수정\" onclick=\"edit_user_info();\"></td>");
	printf("<td>");
	printf("<input type=\"button\" value=\"계정삭제\" onclick=\"del_account();\"></td>");
	printf("<td>");
	printf("<input type=\"button\" value=\"확인\" onclick=\"winclo();\">");
	printf("</td></tr></tbody></table>");
	free(q);
	mysql_free_result(res);
	mysql_close(&mysql);

	printf("</head></html>");
}
