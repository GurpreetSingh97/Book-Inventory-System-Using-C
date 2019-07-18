// ---------------------------------------
// Name:Gurpreet Singh
// ID:145795167
// Email:gsingh520@myseneca.ca
// ---------------------------------------

#include <stdio.h>

#define MAX_TITLE_SIZE 20

//Type the struct here
struct Book {
	int _isbn;
	float _price;
	int _year;
	int _qty;
	char _title[MAX_TITLE_SIZE];
	
	
};
int select;
//Type the function prototypes here
void menu();
void displayInventory(const char filename[]);
void addBook(const char filename[], struct Book *b2Add);
void checkPrice(const char filename[],const int isbn2find);
int searchInventory(FILE *fp,const int isbn2find);
float calculateCapital(const char filename[]);
int readRecord(FILE *fp, struct Book *b2read);
void flushKeyboard(void);




int main()
{
   //Type your code here:
   struct Book myBook;
   char filename[] = "144_w9_inventory.txt";
   printf("Welcome to the Book Store\n");
   printf("=========================\n");
   
   
   int isbn;
   do{
	menu();
	
	printf("Select: ");
	scanf("%d",&select);
      
	
	switch (select){
		case 1:
			displayInventory(filename);
		break;
			
		case 2:			
			printf("ISBN:");
			scanf("%d",&myBook._isbn);
			flushKeyboard();
			printf("Title:");
			scanf("%[^\n]",myBook._title);
			flushKeyboard();
			printf("Year:");
			scanf("%d",&myBook._year);
			flushKeyboard();
			printf("Price:");
			scanf("%f",&myBook._price);
			flushKeyboard();
			printf("Quantity:");
			scanf("%d",&myBook._qty);
			flushKeyboard();
			addBook(filename,&myBook);
			
		break;
			
		case 3:
			
			printf("Please input the ISBN number of the book:\n\n");
			scanf("%d",&isbn);
			checkPrice(filename,isbn);
		
			
		break;
	
		case 4:
			printf("The total capital is: $%0.2f.\n",  calculateCapital(filename));
		break;
			
		case 0:
			printf("Goodbye!\n");
		break;  
	       
	   }
   }while(select!=0);
   
    return 0;
}

void menu()
{
	printf("Please select from the following options:\n");
	printf("1) Display the inventory.\n");
	printf("2) Add a book to the inventory.\n");
	printf("3) Check price.\n");
	printf("4) Calculate total capital of the store.\n");
	printf("0) Exit.\n\n");

}



void displayInventory(const char filename[])
{
   //Define an object of struct Book
    struct Book book;
    
    FILE *fp= NULL;
    //Open the file, and check for null pointer
    fp = fopen(filename,"r");
    
    if(fp!=NULL){
	  printf("\n\n");
	printf("Inventory\n");
    //If the file is properly opened, display headers, similar to workshop 8
	printf("===================================================\n");
	printf("ISBN      Title               Year Price  Quantity\n");
		printf("---------+-------------------+----+-------+--------\n");
	  
   
     //Use a while loop to call readRecord and display the records.
	       
		while(readRecord(fp,&book)==5){
		
	//display the record
		printf("%-10.0d%-20s%-5d$%-8.2f%-8d\n",book._isbn,book._title,book._year,book._price,book._qty);
	
       
	}
    //Display the footer
		printf("===================================================\n\n");
    
    //Close the file
		fclose(fp);
	
	}
	else{
		printf("Failed to open file\n");
	}
}





void addBook(const char filename[], struct Book *b2Add)
{
    	FILE *fp;
    //Open the file for appending (a+)
    fp = fopen(filename,"a+");
    
    //Type your code here
    	int answer;
		answer = searchInventory(fp,(*b2Add)._isbn);
    	if(answer>0){
    		printf("The book exists in the repository!\n\n");
		}
		else{
			fprintf(fp,"%d;%f;%d;%d;%s\n",(*b2Add)._isbn,(*b2Add)._price,(*b2Add)._year,(*b2Add)._qty,(*b2Add)._title);
			printf("The book is successfully added to the inventory.\n\n");
		}
    
    //Close the file
    fclose(fp);
}

void checkPrice(const char filename[],const int isbn2find)
{
    FILE *fp;
    //Open the file for reading
    fp = fopen(filename,"r");
    //Type your code here
    
	searchInventory(fp,isbn2find);
    
    
    //Close the file
 	fclose(fp);
}

int searchInventory(FILE *fp,const int isbn2find)
{
    //Define an object of struct Book and other necessary variables
    struct Book book;
   
   //If the file ponter is not NULL:
	if(fp!=NULL){
		//as long as the record is not found,
		 //use the function readRecord to read the recods and look for isbn2find
		while(readRecord(fp,&book)==5){
			if(book._isbn == isbn2find){
				if(select ==3){
				printf("Book %d costs $%.2f\n\n",isbn2find,book._price);
			}
				return 1;
			}		
		}
	}
    
        return -1;
}


float calculateCapital(const char filename[])
{
    
    
    //Define an object of struct Book
    struct Book item;
    
    //Define and initialize total_capital
    float total_capital =0;
    
    FILE *fp = NULL;
    //Open the file, and check for null pointer
    fp = fopen(filename,"r");
    if(fp!=NULL){
    //If the file is properly opened, use a while loop to call readRecord
		 while(readRecord(fp,&item)==5){
			total_capital = total_capital + (item._price*item._qty);
	//Accumulate the multiplication of the price of each item to its quantity
	
		}
		
		//Display the footer
//        printf("===================================================\n");
	
    //Close the file
	fclose(fp);
 
    }
	
    
    //return the total_capital
    return total_capital;
    
    
}

int readRecord(FILE *fp, struct Book *b2read)
{
    //Define a variable int rv = 0
    int rv =0;
    
    rv = fscanf(fp,"%d;%f;%d;%d;%[^\n]\n",&(*b2read)._isbn,&(*b2read)._price,&(*b2read)._year,&(*b2read)._qty,(*b2read)._title);
   
    //return rv;
	return rv;

}

void flushKeyboard(void){
	char clearKeyboard;
	do{
		scanf("%c",&clearKeyboard);
	}while(clearKeyboard!='\n');
	
}

