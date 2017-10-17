#include "myString.h"
#ifndef NULL
#define NULL 0
#endif // NULL

/*code*/
/*function definations*/
/*code end*/
unsigned int myStrlen(const char s[]);
unsigned int myStrlen(const char s[]) {
	int i=0;
	while(s[i]!='\0') {
		i++;
	}
	return i;
} 

char * myStrcat(char destination[], const char source[]);
char * myStrcat(char destination[], const char source[]) {
	int i=0;
	while(destination[i]!='\0') {
		i++;
	}
	int j,k;
	for(k=0;source[k]!='\0';k++) {
		destination[i+k]=source[k];
	}
	destination[i+k]='\0';
	return destination;
}

char * myStrcpy(char destination[], const char source[]);
char * myStrcpy(char destination[], const char source[]) {
	int i=0,k=0;
	int j;
	while(source[i]!='\0') {
		i++;
	}
	while(destination[k]!='\0') {
		k++;
	}
	for(j=0;j<i;j++) {
		destination[j]=source[j];
	}
	if(k>i) {
		for(j=i;j<k;j++) {
			destination[j]='\0';
		}
	}  else{
		for(j=i;destination[j]!='\0';j++){
			destination[j]='\0';
		}
	}
	return destination;
}

int myStrcmp(const char str1[], const char str2[]);
int myStrcmp(const char str1[], const char str2[]) {
	int i=0,k=0;
	int j;
	while(str1[i]!='\0') {
		i++;
	}
	while(str2[k]!='\0') {
		k++;
	}
	if(i>k) i=i;
	else i=k;
	for(j=0;j<i;j++) {
		if(str1[j]<str2[j]||str1[j]=='\0') {
			k=-1;
			break;
		} else if(str2[j]<str1[j]||str2[j]=='\0') {
			k=1;
			break;
		} else {
			k=0;
		}
	}
	return k;
} 

int MyStrfind(const char str1[], const char str2[]);
int MyStrfind(const char str1[], const char str2[]) {
	int i=0,k=0,d=0;
	int j=-1,l,a,b,c;
	while(str1[i]!='\0') {
		i++;
	}
	while(str2[k]!='\0') {
		k++;
	}
	if(i>=k) {
		for(l=0;l<i;l++) {
			if(str1[l]==str2[0]) {
				for(a=l;a<l+k;a++) {
					if(str1[a]==str2[a-l]) {
						d++;
					}
				}
				if(d==k) {
					j=l-1;
					break;
				}
			} else d=0;
		}
	}
	return j;
}

void LeftRotateString(char *buff, int n);
void LeftRotateString(char *buff, int n) {
	char a[1000];
	char*left=buff;
	char*Left;
	int i,j;
	buff+=n;
	for(i=0;*buff!='\0';i++) {
		a[i]=*buff;
		buff+=1;
	}
	for(j=i;j<i+n;j++) {
		a[j]=*left;
		left+=1;
	}
	Left=a;	
	printf("%s",Left);
}

int myParseInt(const char str[]);
int myParseInt(const char str[]) {
	int i=0;
	long long k=0;
	int j,l;
	int a[1000]={0};
	while(str[i]!='\0') {
		i++;
	}
	if(i!=0) {
		if(str[0]=='+'||str[0]=='-') {
			for(j=1;j<i;j++) {
				if(str[j]-'0'<=9&&str[j]-'0'>=0) {
					k=k*10+str[j]-'0';
				} else {
					break;
				}
			}
		} else if(str[0]-'0'<=9&&str[0]-'0'>=0) {
			for(j=0;j<i;j++) {
				if(str[j]-'0'<=9&&str[j]-'0'>=0) {
					k=k*10+str[j]-'0';
				} else {
					break;
				}
			}
		} 
	}
	if(str[0]=='+'||k==0||str[0]-'0'<=9&&str[0]-'0'>=0) {
		if(k>2147483647) {
			return 2147483647;
		} else {
			return k;
		}
	} else if (str[0]=='-') {
		if(k>2147483648) {
			return -2147483648;
		} else {
			return -k;
		}
	} 
}

int myStrcontain(const char str1[], const char str2[]);
int myStrcontain(const char str1[], const char str2[]) {
	int i=0,k=0,d=0;
	int j,l;
	while(str1[i]!='\0') {
		i++;
	}
	while(str2[k]!='\0') {
		k++;
	}
	if(i<k) {
		return d;
	} else {
		for(j=0;j<k;j++) {
			for(l=0;l<i;l++) {
				if(str2[j]==str1[l]) {
					d++;
					break;
				}
			}
		}
		if(d==k) {
			return 1;
		} else {
		    return 0;
		}
	}
}






