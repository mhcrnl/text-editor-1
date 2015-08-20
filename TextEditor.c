/*
    implemented backspace for multiple lines
    
*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#include <termios.h>
#include <unistd.h>
char ch;
/*
3ple linked list definition
ulink and dlink points to upper and lower lines
rlink points to first word in a line
last points to last nod first points to first node
*/
struct line                                 
{
    struct line *ulink,*dlink,*rlink;  
}*last=0,*temp3=0,*first;
/*
double linked list definition
left and right points to left and right words
*/
struct word
{
    char info2[20];
    struct word *left,*right;
}*rear=0,*temp2;
char insert();
int backspace();
void traverse(int d);
char readd(FILE *fp);
void display();
void search();
void save(FILE *fp,char filename[15]);

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
/*
inserts words,lines etc to the data stucture
most important funtion after main
most editing done in this funtion
*/
char insert()
{
    /*
        flag is used to indicate if word has crossed max array size
        row and column used in search (ctrl-f) funtion
    */
    int i,flag=0;
    int row=0,col=0;
    temp3=(struct line*)malloc(sizeof(struct line));  
    temp2=(struct word*)malloc(sizeof(struct word));
    temp3->ulink=temp3->dlink=0;//initializing pointers to 0
    temp3->rlink=(struct line *)temp2;
    temp2->left=(struct word *)temp3;
    temp2->right=0;
    rear=temp2;
    if(last==0)//last=0 for a blank file
    {
        last=temp3;
        first=temp3;
    }//if file is not blank add new lines after last line of existing file
    else
    {
        temp3->ulink=last;
        last->dlink=temp3;
        last=temp3;
        if(first->dlink==0)
            first->dlink=temp3;
    } 
    /*
    this for loop checks each character typed and performs actions accordingly
    */
    for(i=0;;i++)
    {
        ch=getch();//to accept a chracter

        if(ch=='\n'||ch==7)//7 is ctrl+g
        {   if(ch=='\n')
            {
                putchar(ch);
            }
            return ch;
        }
        if(ch==6)//ctrl+f
            search();
        if(ch==127||ch==07)//backspace
        {   
            col--;
            if(col<0)
            {   col=0;
                temp3=temp3->ulink;
                if(temp3->rlink!=0)
                {
                    temp2=(struct word *)temp3->rlink;
                    col+=strlen(temp2->info2);
                    while(temp2->right!=0)
                    {  
                        temp2=temp2->right;
                        col+=strlen(temp2->info2);                        
                    }
                }
            
            }
            backspace();
            i=strlen(temp2->info2)-1;
            continue;
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
            temp2->info2[i]=ch;
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
            temp2->info2[i]=ch;
        }
    }      
}
int backspace()
{
    int l;
    l=strlen(temp2->info2);
    if(l>0)     
        temp2->info2[l-1]='\0';
    else if(strlen(temp2->info2)==0)
    {   
        temp2=temp2->left;
        l=strlen(temp2->info2);
        temp2->info2[l-1]='\0';
        if(strlen(temp2->info2)==0)
            temp2=temp2->left;  
    }
    return l-1;
  
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
/*
used to read a file and put it into the data structure
*/   
char readd(FILE *fp)
{
    int i,flag=0;
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
/*
    used to display the data structure

*/
void display()
{

    temp3=first;
    while(temp3!=last->dlink)
    {   
        if(temp3->rlink!=0)
        {
            temp2=(struct word *)temp3->rlink;
            while(temp2!=0)
            {  
                printf("%s",temp2->info2);
                temp2=temp2->right;
            }
            if(temp3!=last)
                printf("\n");
        }
        temp3=temp3->dlink;   
    }
}
/*
used to save the file ctrl-g
*/
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
            if(temp3!=last)
                fputc('\n',fp);
        }
        temp3=temp3->dlink;   
    }
    printf("\n\tsaved\n");
    fclose(fp);
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
        if(temp3->rlink!=0)
        {   
            temp2=(struct word *)temp3->rlink;
            while(temp2!=0)
            {   
                for(i=0;temp2->info2[i+m-1]!='\0';i++)
                {     
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

/*
main with arguments
argc=number of arguments
argv=array of arguments 
*/
int main(int argc,char *argv[])
{
    char filename[15];//holds name of the filename
    FILE *fp;
    system("clear");
    if(argc<2)
    {
        printf("no filename\n");
        exit(0);
    }
    strcpy(filename,argv[1]);        
    printf("\t\t\tpress ctrl+b to quit edit, ctrl+g to save and exit\n");
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
            if(last->rlink==0)
            {
               last=last->ulink;
            }
            else if(last->rlink!=0)
            {   
                temp2=(struct word *)last->rlink;
                if(!strlen(temp2->info2))
                {
                    last=last->ulink;
                }
            }
            
            display(); 
            printf("\n");             
            while(1)
            {
                ch=insert();        //fc
                if(ch==7)
                {   
                    if(last->rlink==0)
                        last=last->ulink;
                    save(fp,filename);
                    exit(0);
                }
            }
            break;
         }
     }        
}
