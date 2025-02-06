#include <stdio.h>
#include <stdlib.h>
struct Item
{
    int quantity;
    int unit_price;
};
int main()
{ 
    struct Item paratha;
    struct Item vegetable;
    struct Item mineral_water;
    int number_of_people;
    float total_bill;
    float person_bll;

    // paratha er jonno input
    printf("Enter the quantity of paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Enter the unit price of paratha: ");
    scanf("%d", &paratha.unit_price);

    // vegetable er jonno input
    printf("Enter the quantity of vegetable: ");
    scanf("%d", &vegetable.quantity);
    printf("Enter the unit price of vegetable: ");
    scanf("%d", &vegetable.unit_price);

    // mineral water er jonno input
    printf("Enter the quantity of mineral water: ");
    scanf("%d", &mineral_water.quantity);
    printf("Enter the unit price of mineral water: ");
    scanf("%d", &mineral_water.unit_price);

    // number of people er jonno input
    printf("Enter the number of people: ");
    scanf("%d", &number_of_people);

    // total bill calculation
    total_bill = (paratha.quantity * paratha.unit_price) + (vegetable.quantity * vegetable.unit_price) + (mineral_water.quantity * 20);
    person_bll = total_bill / number_of_people;

    printf("Individual people will pay: %.2f tk \n", person_bll);
}