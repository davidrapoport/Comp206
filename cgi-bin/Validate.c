#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *SSV = "members.ssv";
int contains(char *user, char *passwd);
int main(){
	char *inputLength = getenv("CONTENT_LENGTH");
	char *inputType = getenv("REQUEST_METHOD");
	if(strcmp(inputType, "POST")){ //If the request is a post
		return 1;
	}
	printf("%s%c%c\n", "Content-Type: text/html; charset= iso-8859-1",13,10);
	char user[1000];
	char passwd[64];
	char c = getchar();
	int inputStart=0;
	int username=1;
	int i=0;
	//parses the input string places username and passwd in their appropriate char[]
	while(c != '\n' && c != '\r' && c!=' ' && c!=0 && c!=-1){
		
		if(c =='='){ //user data has begun 
			inputStart= 1;
		}
		else if( c=='&'){ //user data is finished
			user[i]=0;
			inputStart=0;
			username =0;
			i=0;
		}
		else if(inputStart){ //if current char is part of the data that the user input
			if(username){
				user[i]=c;
				i++;
			} else {
				passwd[i]=c;
				i++;
			}
		}
		c=getchar();
		
	}
	passwd[i]=0;
	if(contains(strdup(user),strdup(passwd))){ //if the SSV contains this username passwd combo
		char *html = "<!DOCTYPE html>\n<html>\n<head><title>Survey-Login</title><head>\n<body bgcolor=\"#cbcbcb\" >\n<body background=\"../UI_Elements/bgg.jpg\">\n<img src=\"../UI_Elements/bar.png\" style=\"position: absolute; top: 0; left: 0;width:100%;height:9px;\" /><br><br>\n<center><img src=\"../UI_Elements/Title.png\" align=\"middle\" /><center/>\n<p>\n <div id=\"content\" align=\"justify\" style=\"height:270px;width:400px;float:middle;\">\n<h3 align=\"center\"> You have succesfully logged in</h3>\n<div align=\"center\"> <ul><li><a href=\"http://cs.mcgill.ca/~kqaise/206/welcome.html\"> Home </a> </li> <li> <a href=\"http://cs.mcgill.ca/~bnirau/take.html\">Take a survey </a> </li><li><a href=\"http://cs.mcgill.ca/~bnirau/create.html\">Make a survey</a></li></ul></div>\n</div> \n<img src=\"../UI_Elements/Duck.png\" /><br><br>\n<br><br>\n<footer>\n<div id=\"content\" style=\"height:110px;width:100%;float:middle;background-color:#454545;\">\n<br>\n<font face=\"verdana\" color=\"white\" >Copyright 2014<br> Kayhan Qaiser <br> David Rappoport <br> Bimochan Niraula <br><br> Contact: <a href=\"mailto:bill@yolo.com\" style=\"text-decoration:none\" style=\"color:rgb(0,0,0)\"><font color=\"ffffff\">bill@yolo.com</a>\n</font> \n</div>\n</footer> </body>\n</html>";
		printf("%s",html);
	}
	else{
	char *html ="<!DOCTYPE html>\n<html>\n<head><title>Survey-Login</title><head>\n<body bgcolor=\"#cbcbcb\" >\n<body background=\"../UI_Elements/bgg.jpg\">\n<img src=\"../UI_Elements/bar.png\" style=\"position: absolute; top: 0; left: 0;width:100%;height:9px;\" /><br><br>\n<center><img src=\"../UI_Elements/Title.png\" align=\"middle\" /><center/>\n<p>\n <div id=\"content\" align=\"justify\" style=\"height:270px;width:400px;float:middle;\">\n<h3 align=\"center\"> Username/Password is incorrect. Please try again or register</h3>\n<div align=\"center\"> <ul><li><a href=\"http://cs.mcgill.ca/~kqaise/206/welcome.html\"> Home </a> </li> <li> <a href=\"http://cs.mcgill.ca/~drapop/login.html\">Login </a> </li><li><a href=\"http://cs.mcgill.ca/~drapop/register.html\">Register</a></li></ul></div>\n</div> \n<img src=\"../UI_Elements/Duck.png\" /><br><br>\n<br><br>\n<footer>\n<div id=\"content\" style=\"height:110px;width:100%;float:middle;background-color:#454545;\">\n<br>\n<font face=\"verdana\" color=\"white\" >Copyright 2014<br> Kayhan Qaiser <br> David Rappoport <br> Bimochan Niraula <br><br> Contact: <a href=\"mailto:bill@yolo.com\" style=\"text-decoration:none\" style=\"color:rgb(0,0,0)\"><font color=\"ffffff\">bill@yolo.com</a>\n</font> \n</div>\n</footer> </body>\n</html>";
		printf("%s",html);
	}
	return 0;
}

int contains(char *user, char *passwd){
	FILE *ssv = fopen(SSV,"r");
	if(ssv == NULL){printf("File not found");}
	char  input[256];
	int i;
	for(i=0;i<256;i++){ //clears input[]
		input[i]=0;
	}
	int userMatch =0;
	while(fscanf(ssv, "%s", input) != EOF) {
    	if(userMatch){ //if the user matched we check the passwd
    		return !strcmp(input,passwd);
    	}
    	userMatch= !strcmp(input,user); //compares the current word to the given username
    	for(i=0;i<256;i++){
			input[i]=0;
		}
	}
	return 0; //no match
	
}

