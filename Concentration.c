#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
int x, y;
int stop=0;
int score=0;
int match=0;
int finish=0;
char *cnames[10]={
    "metal", "water", "earth","fire","wood",
    "tower", "chariot","emperor","fool","world"
    
};

struct card{
    int matched;
    int num;
    int assigned;
    int paired;
    char *ptr;
};

struct card* Cards;


int assign(){   //assign each of the 20 cards a text
   
    
    for(int i=0;i<20;i++){         //assign 1 card at a time
        srand(time(0));
        int cr=(rand()%10); //choose random card type
        int nr;
        int a=0;
        
        for(int j=0;j<20;j++){ //count number of occurrences
            if(Cards[j].ptr==cnames[cr]){
                    a++;
            }

        }

        
        
        while(a==2){
            while(nr==cr){  //choose a text different than the last
                srand(time(0));
                nr=(rand()%10);
            }
            a=0;
            for(int j=0;j<20;j++){
                if(Cards[j].ptr==cnames[nr]){
                    a++;
                }

            }

            
        }
        if(a<2){
            struct card o={ 
                 0,
                 i+1,
                 1,
                 1,
                cnames[cr]
            };
            Cards[i]=o; //add the new card to the array of structs

        }
            





        /*

        for(int h=0;h<20;h++){  //look through the array for a matching text card
                                //if matched add the card and make them both paired
            if(Cards[j].ptr==cnames[cr]){
                if(Cards[j].paired==0){
                    Cards[j].paired=1;
                    struct card o={
                        0,
                        i+1,
                        1,
                        1,
                        cnames[cr]
                    };

                    Cards[i]=o; //add the new card to the array of structs
                }
            }
        }
        */


        
        
            
           

            
       
       

    }
    

}

int initialization(){
    printf("Setting up game");
    printf("\n");

    //Cards= (struct card *)malloc(sizeof(struct card)*20);
    Cards= malloc(sizeof(struct card)*20);
}

int teardown(){
    printf("Destroying game");
    printf("\n");
    free(Cards);

}

int acceptInput(){
    x=-1;
    y=-1;

    
        printf("Enter 1st number from 1 to 20 \n");
        scanf("%d",&x);
        if(x==0){
            stop=1;
            return 1;
        }
        if(x<1||x>20){ //test if out of range and get another if it is
                while (x<1||x>20)
                {
                    printf("Enter 1st number within 1 to 20 \n");
                    scanf("%d",&x);
                    if(x==0){
                        stop=1;
                        return 1;
                    }
                
                }


        }
        


        while(Cards[x-1].matched==1){
            printf("Already chosen. Choose another.  \n");
            scanf("%d",&x);
            if(x==0){
                stop=1;
                return 1;
            }
            if(x<1||x>20){  //test if out of range and get another if it is
                 while (x<1||x>20)
                 {
                    printf("Enter within 1 to 20 \n");
                    scanf("%d",&x);             
                    if(x==0){
                        stop=1;
                        return 1;
                    }
                    
                 }    

            }
            
            

        }
    

    printf("Enter 2nd number from 1 to 20 \n");
    scanf("%d",&y);
    if(y==0){
        stop=1;
        return 1;
    }
    if(y<1||y>20){
        while(y<1||y>20){ //test if out of range and get another if it is
            printf("Enter 2nd number within 1 to 20 \n");
            scanf("%d",&y);
                if(y==0){
                    stop=1;
                    return 1;
                } 

            

            
        }



    }
    
    while(y==x){
        printf("No repeat number \n");
        printf("Enter 2nd number \n");
        scanf("%d",&y);
         if(y==0){
            stop=1;
            return 1;
         } 
         while(y<1||y>20){ //test if out of range and get another if it is
            printf("Enter 2nd number within 1 to 20 \n");
            scanf("%d",&y);
                if(y==0){
                    stop=1;
                    return 1;
                } 

        }
         
    }
    while(Cards[y-1].matched==1){ 
            printf("Already chosen. Choose another.  \n");
            scanf("%d",&x);
            if(x==0){
                stop=1;
                return 1;
            }
            while(y<1||y>20){ //test if out of range and get another if it is
                printf("Enter 2nd number within 1 to 20 \n");
                scanf("%d",&y);
                    if(y==0){
                        stop=1;
                        return 1;
                    } 
            
             }
            while(y==x){
                printf("No repeat number \n");
                printf("Enter 2nd number \n");
                scanf("%d",&y);
                if(y==0){
                    stop=1;
                    return 1;
                }
                while(y<1||y>20){ //test if out of range and get another if it is
                    printf("Enter 2nd number within 1 to 20 \n");
                    scanf("%d",&y);
                        if(y==0){
                            stop=1;
                            return 1;
                        } 
                
                }

            }

    }
        
         
 
}

int display(){
    if(finish==1){
        printf("Game over \n");
        printf("Play again? (0 for yes 1 for no)\n");
        scanf("%d",&stop);

        if(stop==0){
            
            initialization();
            assign();
            finish=0;
        }


    }



    if(match==1){
        printf("Match");
        printf("\n");


        match=0;
    }
    else if(match==0){
        printf("No match");
        printf("\n");
        printf("First Card: %d \n", x);
        int c;
        
        
        c=0;
        while(*(Cards[x-1].ptr+c)!='\0'){

            printf("%c", *(Cards[x-1].ptr+c));
            c++;
        }
        printf("\n");
        printf("Second Card: %d \n", y);
        c=0;

        while(*(Cards[y-1].ptr+c)!='\0'){

            printf("%c", *(Cards[y-1].ptr+c)); //segment faults on the prints
            c++;
        }
        printf("\n");

    }
    

} 


int update(){
  
   if(Cards[x-1].ptr==Cards[y-1].ptr){
    
   
        Cards[x-1].matched=1;
        Cards[y-1].matched=1;
        match=1;
        int m=0;
        for(int i=0;i<20;i++){
            if(Cards[i].matched==1){
                m++;
            }
        }
        if(m==20){
            finish=1;
        }


    }


}

int main(){
    srand(time(0));
    initialization();
    assign();
    while(stop==0){
        
        acceptInput();
        if(stop==1){
            break;
        }
        update();
        display();


    }

    teardown();
    



}
