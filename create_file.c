#include<stdio.h>
int main(int argc,char *argv[])
{
    int i;
    FILE *fp;
    int c;
    fp=fopen(argv[1],"w+");
    if(fp==NULL)
    {
        printf("could not open file");
        return 0;
        
    }
    while((c=fgetc(fp))!=EOF)
      putchar(c);
    fclose(fp);
    return 0;
}    
