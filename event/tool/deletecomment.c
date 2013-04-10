#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isComment(char *buf)
{
	if(buf==NULL)return 0;
	if(*buf=='#')return 1;
	return 0;
}
int isAllSpace(char *buf)
{
	int i=0,len=0;
	if(buf==NULL)return 0;
	len=strlen(buf);
	for(i=0;i<len;i++)if(buf[i]<=0 || buf[i]>' ')return 0;
	return 1;
}

int topIs(char*p,char* str){
	char tmp[256];
	strncpy(tmp,str,256);
	strncat(tmp," ",1);
	if(strstr(p,tmp)==p)return 1;
	return 0;
}

int main(int argc,char* argv[])
{
	FILE *fi=NULL,*fo=NULL;
	char buf[1024];
	int ret=1;
	char* p;
	int fs=0;
	int ftype=0;
	int lftype=0;
	
	if(argc<3){
		printf("Error: deletecomment infile outfile\n");
		goto end;
	}
	fi=fopen(argv[1],"rt");
	fo=fopen(argv[2],"wt");
	if(fi==NULL){
		printf("Error: input file cannot open\n");
		goto end;
	}
	if(fo==NULL){
		printf("Error: input file cannot open\n");
		goto end;
	}
	while(fgets(buf,sizeof(buf),fi)!=NULL){
		if(isComment(buf))continue;
		if(isAllSpace(buf))continue;
		p=buf;
		while(*p==' '){
			fputs("   ",fo);
			*p++;
		}
		if( topIs(p,"public") ){
			ftype=1;
		}else if(topIs(p,"private")){
			ftype=2;
		}else if(topIs(p,"static")){
			ftype=3;
		}else if(topIs(p,"import")){
			ftype=4;
		}else {
			ftype=0;
		}
		
		fs=0;
		if(ftype==0)lftype=0;
		if(ftype){
			if(ftype!=lftype){
				fs=1;
				lftype=ftype;
			}
		}
		if(fs){
				fputs("\n",fo);
		}
		fputs(buf,fo);
	}
	fputs("\n\n",fo);
	ret=0;
end:
	if(fi)fclose(fi);
	if(fo)fclose(fo);
	return ret;
}


