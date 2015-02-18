
#include<stdio.h>
#include<stdlib.h>
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
char insert()
{
    int i;printf("insert function\n");
    temp3=(struct line*)malloc(sizeof(struct line));  
    temp2=(struct word*)malloc(sizeof(struct word));
    temp3->ulink=temp3->dlink=0;//initializing pointers to 0
    temp3->rlink=temp2;
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
        if(first==0)
            first->dlink=temp3;
    }
 
      rear=temp2;
    for(;;)
    {
        scanf("%s",rear->info2);
        ch=getchar();
        if(ch=='\n')
        {   printf("newline\n");
            return ch;
        }
        else if(ch=='\t')
        {
            printf("semi colon");
            return ch;
        }
        else if(ch==' ')
        {   printf("space\n");
            temp2=(struct word*)malloc(sizeof(struct word));
           
            temp2->left=rear;
            rear->right=temp2;
            rear=temp2;
            continue;
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
            temp2=temp3->rlink;
            while(temp2!=0)
            {
                printf("%s ",temp2->info2);
                temp2=temp2->right;
            }
            printf("\n");
        }
        temp3=temp3->dlink;
      
    }
}
int main()
{
    int choice;
    do
    {
        printf("enter 1 to write 2 to read 3 to exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1 :while(1)
                    {
                        ch=insert();
                        if(ch=='\t')
                            break;
                    }
            case 2 :display();
                    break;
        }
    }while(choice!=3);
}

