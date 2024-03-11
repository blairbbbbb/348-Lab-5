#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Array of month names
char *months[] = {"January", "February", "March", "April", "May", "June", 
                  "July", "August", "September", "October", "November", "December"};

//Function to read data from given file and store it in sales_data.
void read_sales_data(char *file_name, float *sales_data) {
    FILE *file = fopen(file_name, "r"); // Open the file.
    if (file == NULL) {
        printf("Error opening file.\n"); 
        exit(1);
    }
    char line[100]; 
    int i = 0; //Index to keep track of the current position in sales_data array.
    while (fgets(line, sizeof(line), file)) { //Read each line and convert string to fload and store in sales_data.
        sales_data[i] = atof(line);
        i++;
    }
    fclose(file); 
}

//Function to print a sales report showing sales for each month 
void sales_report(float *monthly_sales) {
    printf("\nMonthly sales report for 2022:\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < 12; i++) { //Loop through all months and print months and sales. 
        printf("%s\t\t$%.2f\n", months[i], monthly_sales[i]);
    }
}

//Function to generate a summary of the min, max, and average sales.
void sales_summary(float *monthly_sales) {
    float min_sale = monthly_sales[0];
    float max_sale = monthly_sales[0];
    float total_sales = 0;
    int min_month = 0;
    int max_month = 0;

    for (int i = 0; i < 12; i++) { //Loop through all the months and calculate min, max, and total sales. 
        if (monthly_sales[i] < min_sale){
            min_sale = monthly_sales[i];
            min_month = i;
        }
        if (monthly_sales[i] > max_sale){
            max_sale = monthly_sales[i];
            max_month = i;
        }
        total_sales += monthly_sales[i];
    }

    printf("\nSales summary:\n"); 
    printf("Minimum sales: $%.2f (%s)\n", min_sale, months[min_month]); //Print the min sales.
    printf("Maximum sales: $%.2f (%s)\n", max_sale, months[max_month]); //Print the max sales.
    printf("Average sales: $%.2f\n", total_sales / 12); //Print the average sales.
}

//Function to calculate and print the six-month moving average sales. 
void six_month_moving_average(float *monthly_sales) {
    printf("\nSix-Month Moving Average Report:\n");
    for (int i = 0; i < 7; i++) { //Loop through the first six months. 
        float sum = 0;
        for (int j = i; j < i + 6; j++) { //Sum sales for the next six months.
            sum += monthly_sales[j];
        }
        printf("%s \t- %s \t$%.2f\n", months[i], months[i + 5], sum / 6);
    }
}

//Function to generate and print a sales report sorted from highest to lowest. 
void sales_report_sorted(float *monthly_sales) {
    printf("\nSales Report (Highest to Lowest):\n");
    float temp_sales[12];
    memcpy(temp_sales, monthly_sales, sizeof(temp_sales)); //Copy sales data to temp array.
    int sorted_indices[12];
    for (int i = 0; i < 12; i++) {
        sorted_indices[i] = i;
    }

    //Sort sales in descending order.
    for (int i = 0; i < 12; i++) {
        for (int j = i + 1; j < 12; j++) {
            if (temp_sales[i] < temp_sales[j]) {
                float temp = temp_sales[i];
                temp_sales[i] = temp_sales[j];
                temp_sales[j] = temp;
                int temp_index = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp_index;
            }
        }
    }

    printf("Month\t\tSales\n");
    for (int i = 0; i < 12; i++) {
        printf("%s\t\t$%.2f\n", months[sorted_indices[i]], temp_sales[i]);
    }
}

int main() {
    float monthly_sales[12];
    char file_name[100];
    printf("Enter the name of the file: ");
    scanf("%s", file_name);
    read_sales_data(file_name, monthly_sales);
    sales_report(monthly_sales);
    sales_summary(monthly_sales);
    six_month_moving_average(monthly_sales);
    sales_report_sorted(monthly_sales);
    return 0;
}