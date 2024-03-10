#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//need a make file
char *months[] = {"January", "February", "March", "April", "May", "June", 
                  "July", "August", "September", "October", "November", "December"};

void read_sales_data(char *file_name, float *sales_data) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    char line[100];
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        sales_data[i] = atof(line);
        i++;
    }
    fclose(file);
}

void generate_sales_report(float *monthly_sales) {
    printf("Monthly sales report for 2022:\n");
    printf("Month\tSales\n");
    for (int i = 0; i < 12; i++) {
        printf("%s\t\t$%.2f\n", months[i], monthly_sales[i]);
    }
}

void generate_sales_summary(float *monthly_sales) {
    float min_sale = monthly_sales[0];
    float max_sale = monthly_sales[0];
    float total_sales = 0;

    for (int i = 0; i < 12; i++) {
        if (monthly_sales[i] < min_sale)
            min_sale = monthly_sales[i];
        if (monthly_sales[i] > max_sale)
            max_sale = monthly_sales[i];
        total_sales += monthly_sales[i];
    }

    printf("\nSales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", min_sale, months[0]);
    printf("Maximum sales: $%.2f (%s)\n", max_sale, months[0]);
    printf("Average sales: $%.2f\n", total_sales / 12);
}

void generate_six_month_moving_average(float *monthly_sales) {
    printf("\nSix-Month Moving Average Report:\n");
    for (int i = 0; i < 7; i++) {
        float sum = 0;
        for (int j = i; j < i + 6; j++) {
            sum += monthly_sales[j];
        }
        printf("%s \t- %s \t$%.2f\n", months[i], months[i + 6], sum / 6);
    }
}

void generate_sales_report_sorted(float *monthly_sales) {
    printf("\nSales Report (Highest to Lowest):\n");
    float temp_sales[12];
    memcpy(temp_sales, monthly_sales, sizeof(temp_sales));
    int sorted_indices[12];
    for (int i = 0; i < 12; i++) {
        sorted_indices[i] = i;
    }

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
    generate_sales_report(monthly_sales);
    generate_sales_summary(monthly_sales);
    generate_six_month_moving_average(monthly_sales);
    generate_sales_report_sorted(monthly_sales);
    //return 0;
}