/*accepts character on kewstroke
    good
*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include"conio.h"
char ch;
struct line
{
    struct line *ulink,*dlink,*rlink;
}*last=0,*temp3=0,*first;
struct word
{
    char info2[20];
    struct word *left,*right;
}*rear=0,*temp2;
char insert();
void traverse(int d);
char readd(FILE *fp);
void display();
void search();
void save(FILE *fp,char filename[15]);


char insert()
{
    int i,flag=0;//c is for different cases of last character
    int row=0,col=0;
    char l;
    temp3=(struct line*)malloc(sizeof(struct line));  
    temp2=(struct word*)malloc(sizeof(struct word));
    temp3->ulink=temp3->dlink=0;//initializing pointers to 0
    temp3->rlink=(struct line *)temp2;
    temp2->left=(struct word *)temp3;
    temp2->right=0;
    rear=temp2;
    if(last==0)
    {
        last=temp3;
        first=temp3;
    }
    else
    {
        temp3->ulink=last;
        last->dlink=temp3;
        last=temp3;
        if(first->dlink==0)
            first->dlink=temp3;
    } 
    for(i=0;;i++)
    {
        ch=getch();
        if(ch=='\n'||ch==2||ch==7)//2 is ctrl b 7 is ctrl+g
        {   if(ch=='\n')
            {
                putchar(ch);
                row++;
                col=0;
            }
            return ch;
        }
        if(ch==6)//ctrl+f
            search();
         if(ch==127||ch==07)//backspace
        {
            l=strlen(rear->info2);
                printf("%c",rear->info2[l-1]);
                rear->info2[l-1]='\0';
        }             

        if(ch!=' '&&flag==1)//1st character after space
        {
            temp2=(struct word*)malloc(sizeof(struct word));
            temp2->left=rear;
            rear->right=temp2;
            rear=temp2;
            i=0;       
            flag=0;     
        }
        if(ch==' ')
        {
            putchar(ch);
            if(i==19)//end of array size
            {
                flag=0;//to start new array
                i=0;
            }
            if(flag==0)
            {            
                flag=1;
                temp2=(struct word*)malloc(sizeof(struct word));
                temp2->left=rear;
                rear->right=temp2;
                rear=temp2;
                i=0;
            }
            col++;
            rear->info2[i]=ch;
        }
       
        else if(ch=='\033')//escape
        {
            getch();
            switch(getch())
            {
                
                case 'A' :traverse(1);
                        break;
                case 'B' :traverse(2);
                        break;
                case 'C' :traverse(3);
                      break;
                case 'D' :traverse(4);
                      break;       
            }    
        }
        



        else//if ch is a character  
        {
            if(i==19)
            {
                temp2=(struct word*)malloc(sizeof(struct word));
                temp2->left=rear;
                rear->right=temp2;
                rear=temp2;
                i=0;
             }
            col++;
            putchar(ch);
            rear->info2[i]=ch;
        }
    }      
}
void traverse(int d)
{
    int l;
    switch(d)
    {
         case 1 :printf("up arrow\n");       
                      break;
         case 2 :printf("down arrow\n");
                      break;
         case 3 :printf("right arrow\n");              
                      break;
         case 4 :printf("left arrow\n");
                // temp3=temp3->ulink;
                //rear=(struct word *)temp3->rlink;
                l=strlen(rear->info2);
                      
                printf("%c",rear->info2[l-1]);
                rear->info2[l-1]='\0';
                      break;      
     }    
}


    
char readd(FILE *fp)
{
    int i,flag=0;//c is for different cases of last character
    temp3=(struct line*)malloc(sizeof(struct line));  
    temp2=(struct word*)malloc(sizeof(struct word));
    temp3->ulink=temp3->dlink=0;//initializing pointers to 0
    temp3->rlink=(struct line *)temp2;
    temp2->left=(struct word *)temp3;
    temp2->right=0;
    rear=temp2;
    if(last==0)
    {
        last=temp3;
        first=temp3;
    }
    else
    {
        temp3->ulink=last;
        last->dlink=temp3;
        last=temp3;
        if(first->dlink==0)
            first->dlink=temp3;
    }
    for(i=0;;i++)
    {
        ch=fgetc(fp);
        if(ch=='\n'||ch==EOF)//2 is ctrl b
            return ch;
        if(ch!=' '&&flag==1)//1st character after space
        {
            temp2=(struct word*)malloc(sizeof(struct word));
            temp2->left=rear;
            rear->right=temp2;
            rear=temp2;
            i=0;       
            flag=0;     
        }
        if(ch==' ')
        {
            if(i==19)//end of array size
            {
                flag=0;//to start new array
                i=0;
            }
            if(flag==0)
            {            
                flag=1;
                temp2=(struct word*)malloc(sizeof(struct word));
                temp2->left=rear;
                rear->right=temp2;
                rear=temp2;
                i=0;
            }
            rear->info2[i]=ch;
        }
        else//if ch is a character
        {
            if(i==19)
            {
                temp2=(struct word*)malloc(sizeof(struct word));
                temp2->left=rear;
                rear->right=temp2;
                rear=temp2;
                i=0;
             }
            rear->info2[i]=ch;
        }
    }      
}
void display()
{
    temp3=first;
    while(temp3!=0)
    {   
        if(temp3->rlink!=0)
        {
            temp2=(struct word *)temp3->rlink;
            while(temp2!=0)
            {   
                printf("%s",temp2->info2);
                temp2=temp2->right;
            }
                printf("\n");
        }
        temp3=temp3->dlink;   
    }
}
void search()
{
    char se[20],r=0,c=0,flag=0,i,j,m;
    printf("enter element to search\n");
    scanf("%s",se);
    temp3=first;
    m=strlen(se);
    while(temp3!=0)
    {
        r++;
        c=0;
      //  printf("\t\t\ta\n");
        if(temp3->rlink!=0)
        {   
           // printf("\t\t\tb\n");
            temp2=(struct word *)temp3->rlink;
            while(temp2!=0)
            {   

               // printf("\t\t\tc\n");
                for(i=0;temp2->info2[i+m-1]!='\0';i++)
                {     //  printf("\t\t\td\n");
                        j=0;
                        while(j<m&&(temp2->info2[i+j]==se[j]))
                            j++;
                        if(j==m)
                        {
                            printf("element found in line %d, column %d\n",r,c);
                            flag=1;
                        }
                }    
                 c+=strlen(temp2->info2);  
                temp2=temp2->right;  
               
            }
        }
        temp3=temp3->dlink;   
        
    }
    if(flag==0)
        printf("not found");
}




void save(FILE *fp,char filename[15])
{
    fp=fopen(filename,"w");
    temp3=first;
    while(temp3!=0)
    {   
        if(temp3->rlink!=0)
        {
            temp2=(struct word *)temp3->rlink;
            while(temp2!=0)
            {   
                fputs(temp2->info2,fp);
                temp2=temp2->right;
            }
            fputc('\n',fp);
        }
        temp3=temp3->dlink;   
    }
    printf("\n\tsaved\n");
    fclose(fp);
}
int main(int argc,char *argv[])
{
    int choice=5;
    char filename[15];
    FILE *fp;
    if(argc<2)
    {
        printf("no filename\n");
        exit(0);
    }
    strcpy(filename,argv[1]);        
    //printf("\npress\nctrl+e to edit \n9 to exit");
        //scanf("%c",&choice);
       // printf("choice is%d\n",choice);
    switch(choice)
    {
        case 5:    //ctrl+e
                printf("\t\t\tpress ctrl+b to quit edit, ctrl+g to save\n");
                fp=fopen(argv[1],"r+");
                if(fp==NULL)
                {
                    printf("no file");
                    exit(0);
                }
                while(1)
                {   
                    ch=readd(fp);
                    if(ch==EOF)
                    {
                        display();              //fc
                        while(1)
                        {
                            ch=insert();        //fc
                            if(ch==2)
                                break;
                            if(ch==7)
                                save(fp,filename);
                        }
                        break;
                     }
                 }  
                 break;
    }  
}
