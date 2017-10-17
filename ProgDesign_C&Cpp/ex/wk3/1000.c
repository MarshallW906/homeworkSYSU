#include <stdio.h>
#include <string.h>

#define MaxLength 8
char num[MaxLength+1],numA[MaxLength/2+1],numB[MaxLength/2+1];

void outp(char a[]);
void prtNum(char c);
void prtChar(int ch, char cc);

int main()
{
	scanf("%s",num);
	int length=strlen(num),i;
	if ( length > 4 ){
		for(i=0; i<length-4; i++) numA[i]=num[i]; numA[i]='\0';
		for(i=length-4; i<length; i++) numB[i-length+4]=num[i]; numB[i-length+4]='\0';
		outp(numA);
		printf("wan ");
		if(numB[0]!='0')
			outp(numB);	
	}else{
		outp(num);
	}
	printf("\b\n");
	return 0;
}

void outp(char a[]){
	int sublength=strlen(a),j,k,flag=0;
	for(j=0;j<sublength; ++j){
		if(!((a[j]=='0')&(j>=1)&(a[j-1]=='0'))) {
		prtNum(a[j]);
		prtChar(sublength-j,a[j]);
	}
	/*k=j;
	while((a[k+1]!='\0')&&(a[k+1]=='0'))k++;
	if (k==4) return;*/
	for(k=j;k<sublength;k++){
		if((a[k+1]!='\0')&&(a[k+1]=='0')) continue;
		flag=1;
	}
	if (flag) return;
	}
}

void prtNum(char c){
	switch(c){
		case '0':{printf("ling ");break;}
		case '1':{printf("yi ");break;}
		case '2':{printf("er ");break;}
		case '3':{printf("san ");break;}
		case '4':{printf("si ");break;}
		case '5':{printf("wu ");break;}
		case '6':{printf("liu ");break;}
		case '7':{printf("qi ");break;}
		case '8':{printf("ba ");break;}
		case '9':{printf("jiu ");break;}
	}
}

void prtChar(int ch,char cc){
	if (cc!='0')
		switch(ch){
		case 1:{return;}
		case 2:{printf("shi ");break;}
		case 3:{printf("bai ");break;}
		case 4:{printf("qian ");break;}
	}
}
