#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//functions to generate bills

struct items {
    char item[20];
    float price;
    int quantity;
};

struct orders {
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};


void generateBillHeader(char name[50] , char date[30]) {
          printf("\n\n");
          printf("\t      THE BIGG CHILL CAFE");
          printf("\n\t     _________________________");
          printf("\nDate:%s" , date);
          printf("\nInvoice to : %s" , name);
          printf("\n");
          printf("-----------------------------------------------\n");
          printf("Items\t\t");
          printf("Quantity\t\t");
          printf("TOTAL\t\t");
          printf("\n-----------------------------------------------");
          printf("\n\n");
}

void generateBillBody(char item[20] , int quantity , float price) {
    printf("%s\t\t" , item);
    printf("%d\t\t" , quantity);
    printf("%.2f\t\t" , quantity * price);
    printf("\n");
}


void generateBillFooter(float total) {
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total-dis;
    float cgst=0.09 * netTotal , grandTotal = netTotal + 2 * cgst;
    printf("---------------------------------------------\n");
    printf("sub total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f" , "%" , dis);
    printf("\n\t\t\t-------------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%" , cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%" , cgst);
    printf("\n----------------------------------------------");
    printf("\nGrand Total\t\t\t%2.f",grandTotal);
    printf("\n----------------------------------------------\n");
}

int main() {
    
    //dashboard
    
    int opt , n ;
    float total;
    struct orders ord;
    struct orders order;
    char saveBill = 'y' , contflag = 'y';
    char name[50];
    FILE *fp;

    while(contflag == 'y') {
        system("clear");
        float total = 0;
        int invoiceFound = 0;
    printf("\t=========== THE BIGG CHILL CAFE=============");
    printf("\n\nplease select your prefered option");
    printf("\n1.Generate Invoice");
    printf("\n2.show all invioces");
    printf("\n3.Search invoices");
    printf("\n4.Exit");
    printf("\n\nyour choice:\t");
    scanf("%d" , &opt);
    fgetc(stdin);
    switch(opt) {
        case 1:
        system("clear");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,50 , stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        strcpy(ord.date , __DATE__);
        printf("\nplease enter the number of  items\t");
        scanf("%d" , &n);
        ord.numOfItems = n;

        for (int i =0; i< n ;i++) {
            fgetc(stdin);
            printf("\n\n");
            printf("please enter the item %d:" , i + 1);
            fgets(ord.itm[i].item , 20 , stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("please enter the quantity:\t");
            scanf("%d" , &ord.itm[i].quantity);
            printf("please enter the unit price:\t");
            scanf("%f" , &ord.itm[i].price);
            total += ord.itm[i].quantity * ord.itm[i].price;
        }

        generateBillHeader(ord.customer , ord.date);
        for(int i=0 ; i<ord.numOfItems;i++){
        generateBillBody(ord.itm[i].item , ord.itm[i].quantity,ord.itm[i].price);

        }
        generateBillFooter(total);

        printf("do you want to save th invoice[y/n]\t");
        scanf("%s" , &saveBill);

        if(saveBill =='y') {
            fp = fopen("bill.dat" , "a+");
            fwrite(&ord,sizeof(struct orders) , 1, fp);
            if(fwrite != 0) 
            printf("\nsuccessfully saved");
            else
            printf("\nError saving");
            fclose(fp);
        }
        break;

        case 2:
        system("clear");
        fp = fopen("bill.dat" , "r");
        printf("\n *****Your Previous Invoices*****\n");
        while(fread(&order , sizeof(struct orders) , 1 , fp)) {
            float tot = 0;
            generateBillHeader(order.customer , order.date);
            for (int i =0 ; i<order.numOfItems ; i++) {
                generateBillBody(order.itm[i].item , order.itm[i].quantity , order.itm[i].price);
                tot+=order.itm[i].quantity * order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("\nenter the name od the customer\t");
        //fgetc(stdin);
        fgets(name , 50 , stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("bill.dat" , "r");
        printf("\n *****Invoices of %s*****\n" , name);
        while(fread(&order , sizeof(struct orders) , 1 , fp)) {
            float tot = 0;
            if(!strcmp(order.customer , name)) {
              generateBillHeader(order.customer , order.date);
            for (int i =0 ; i<order.numOfItems ; i++) {
                generateBillBody(order.itm[i].item , order.itm[i].quantity , order.itm[i].price);
                tot+=order.itm[i].quantity * order.itm[i].price;
            }
            
            generateBillFooter(tot);
            invoiceFound = 1;
        }
        }
    if (!invoiceFound) {
        printf("sorry , the invoice for the %s does not exist" , name);
    }
        fclose(fp);
        break;

        case 4:
        printf("\n\t\t THANKYOU FOR VISITING");
        exit(0);
        break;

        default:
        printf("sorry , invalid option");
        break;
    }
    printf("\ndo you want to perform another operation?\t");
    scanf("%s" , &contflag);
    printf("\n\t\t THANKYOU FOR VISITING");
    }
        printf("\n\n");

    return 0;

    }

    

