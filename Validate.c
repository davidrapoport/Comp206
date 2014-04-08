#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
	char *inputLength = getenv("CONTENT_LENGTH");
	char *inputType = getenv("REQUEST_METHOD");
	if(strcmp(inputType, "POST")){
		return 1;
	}
	char *input;

	scanf("%[^/n]",input);
	printf("%s %s %s",input, inputType, inputLength);


}

