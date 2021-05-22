#include <stdio.h>
#define im_len (25) /*Width and Height of Image*/
int which_color(int x, int y); 
void bucket_fill(int color,int x, int y, int initial_color);
int image[im_len][im_len];
int copy_image[im_len][im_len];
int change_image[im_len][im_len];
int main()
{
    
    int color,initial_color,changed_cells=0,fill_control=0;
    int x,y,i,j,initial_x=0,initial_y=0; 
    int value;
    char operation;

    int copy1_x,copy1_y,copy2_x,copy2_y,paste1_x,paste1_y,paste2_x,paste2_y,loop1,loop2,temp;

    /*Generates the 25x25 list of coordinates*/
    for(x=0;x<im_len;x++)
    {
        for(y=0;y<im_len;y++)
        {
            scanf(" %d",&value); /*Input of the cells*/
            image[x][y] = value;
        }
    }

    
    scanf(" %c",&operation); /*gets the operation code*/
    switch(operation)
    {
        case 'F': /*Fill Operation*/
        {
            fill_control = 1;
            scanf(" %d %d",&x,&y);
            color = which_color(x,y);
            
            if (color == -1)
            {
                color = image[x][y];
            }

            scanf(" %d %d",&initial_x,&initial_y);
            initial_color = image[initial_x][initial_y];
            if(initial_color != color)
            {
                bucket_fill(color,initial_x,initial_y,initial_color);
            }
            
            break;
        }
        case 'P':
        {
            scanf(" %d %d %d %d",&copy1_x,&copy1_y,&copy2_x,&copy2_y); /*copy area*/
            scanf(" %d %d %d %d",&paste1_x,&paste1_y,&paste2_x,&paste2_y); /*paste area*/
            
            for(i=0;i<im_len;i++)
            {
                for(j=0;j<im_len;j++)
                {
                    change_image[i][j] = image[i][j];
                }
            }

            if(copy1_x > copy2_x)
            {
                temp = copy1_x;
                copy1_x = copy2_x;
                copy2_x = temp; 
            }
            if(copy1_y > copy2_y)
            {
                temp = copy1_y;
                copy1_y = copy2_y;
                copy2_y = temp; 
            }

            if(paste1_x>paste2_x)
            {
                temp = paste1_x;
                paste1_x = paste2_x;
                paste2_x = temp;
            }
            if(paste1_y>paste2_y)
            {
                temp = paste1_y;
                paste1_y = paste2_y;
                paste2_y = temp;
            }
            
            for(loop1=copy1_x,i=paste1_x ; loop1<copy2_x+1 ; loop1++,i++)
            {
                for(loop2=copy1_y,j=paste1_y ; loop2<copy2_y+1 ; loop2++,j++)
                { 
                    image[i][j] = image[loop1][loop2]; /*Pastes the copy area*/
                }
            }
            break;
        }
        case 'R':
        {
            char direction;
            int degree,rotate_count,length;
            int copy_x1,copy_y1,copy_x2,copy_y2;
            int paste_x1,paste_y1,paste_x2,paste_y2;
            int loop1,loop2,loop3,loop4;
            scanf(" %c %d",&direction,&degree); /*direction and degree*/
            scanf(" %d %d %d %d",&copy_x1,&copy_y1,&copy_x2,&copy_y2); /*copy area*/
            scanf(" %d %d %d %d",&paste_x1,&paste_y1,&paste_x2,&paste_y2);/*paste area*/
            length = copy_x2 - copy_x1 + 1;
            
            for(i=0;i<im_len;i++)
            {
                for(j=0;j<im_len;j++)
                {
                    change_image[i][j] = image[i][j];
                }
            }
            
            if(degree == 0)
            {
                degree = 360;
            }
            else if(direction != 'R')
            {
                degree = 360-degree;
            }
            rotate_count = degree/90;
            
            while(rotate_count) /*rotates 90 degree to the right in every loop*/
            {
                
                for(loop1=copy_x1,loop3=0 ; loop1<copy_x2+1 ; loop1++,loop3++)
                {
                    for(loop2=copy_y1,loop4=0 ; loop2<copy_y2+1 ; loop2++,loop4++)
                    {
                        copy_image[loop3][loop4] = image[loop1][loop2];
                    }
                }
            
                for(loop1=0,loop3=paste_x1;loop1<length;loop1++,loop3++)
                {
                    for(loop2=length-1,loop4=paste_y1;loop2>-1;loop2--,loop4++)
                    {
                        image[loop3][loop4] = copy_image[loop2][loop1];
                    }
                }
                copy_x1 = paste_x1;
                copy_x2 = paste_x2;
                copy_y1 = paste_y1;
                copy_y2 = paste_y2;
                rotate_count--;
            }
            break;
        }
        default:
        {
            break;
        }
    }

    /*Output 1*/
    for(i=0;i<im_len;i++)
    {
        for(j=0;j<im_len;j++)
        {
            printf("%d ",image[i][j]);
        }
        printf("\n");
    }
    /*Output 2*/
    if(!fill_control)
    {
        for(i=0;i<im_len;i++)
        {
            for(j=0;j<im_len;j++)
            {
                if(change_image[i][j] != image[i][j])
                {
                    changed_cells += 1;
                }
            }
        }
        printf("%d\n",changed_cells);
    }
    return 0;
}


int which_color(int x, int y)
{
    if(x<0 && y<0) {return 0;}
    else if(x<0 && (0<=y && y<im_len) ) {return 1;}
    else if(x<0 && y>=im_len) {return 2;}
    else if((0<=x && x<im_len) && y>=im_len) {return 3;}
    else if(x>=im_len && y>=im_len) {return 4;}
    else if(x>=im_len && (0<=y && y<im_len)) {return 5;}
    else if(x>=im_len && y<0) {return 6;}
    else if((0<=x && x<im_len) && y<0) {return 7;}
    else {return -1;}  
}

void bucket_fill(int color,int x,int y,int initial_color)
{
    if (x>im_len-1|| x<0 || y>im_len-1 || y<0)
    {
        return;
    }
    else if (image[x][y] == initial_color)
    {
        image[x][y] = color;
        bucket_fill(color,x+1,y,initial_color);
        bucket_fill(color,x,y+1,initial_color);
        bucket_fill(color,x+1,y+1,initial_color);
        bucket_fill(color,x-1,y,initial_color);
        bucket_fill(color,x,y-1,initial_color);
        bucket_fill(color,x-1,y-1,initial_color);
        bucket_fill(color,x+1,y-1,initial_color);
        bucket_fill(color,x-1,y+1,initial_color);
        
    }
}

