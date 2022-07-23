#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define length_id 10
#define length_array 30
#define SUCCESS 0

const int length_product = 20;

#include "smalls_function.h" // include my library

/*
	Define 2 types using struct
*/
	typedef struct products {
		int id;
		char description[length_array];
	} product;

	typedef struct recipes {
		int ** products;
		int size_products;
		char description[length_array];
	} recipe;

// End Define struct


/* 
	Prototype from function 
*/
	product* initialize_products(product* array, const unsigned int length);
	void print_all_product(const product* ingredients, const unsigned int length);
	recipe* register_recipes(product* ingredients, recipe* recipes, const unsigned int total);
	void show_all_recipes(const product* ingredient, const recipe* recipes, const unsigned int length);
	void Search_recipe(const recipe* recipes, const product* ingredients, const unsigned int length);
// End prototype


int main(int argc, char* argv) {
	product * twenty_products = (product*)malloc(sizeof(product) * length_product);
	twenty_products = initialize_products(twenty_products, length_product);
	recipe* recipes = malloc(sizeof(recipe) * 1);
	char* name;
	int total = 0;
	bool openSecund = false;
	do {
		printf("\n%30s\n","_________________________");
		printf("%26s\n","1) See all products");
		printf("%30s\n","2) Register new recipes");
		if (openSecund) {
			printf("%25s\n", "3) See all recipes");
			printf("%24s\n", "4) Search recipes");
		}
		printf("%30s\n","_________________________");
		name = readstring(30, "\nOpen your option:");
		if (isnumber(name[0])) {
			int option = (int)name[0] - 48;
			switch (option) {
				case  1: {
					print_all_product(twenty_products, length_product);
					break;
				} case  2: {
					system("cls");
					total = readInt("amount of revenue: ");
					recipes = (recipe*)malloc(sizeof(recipe) * total);
					recipes = register_recipes(twenty_products, recipes, total);
					openSecund = true;
					break;
				}case  3: {
					if (openSecund) { show_all_recipes(twenty_products, recipes, total); }
					break;
				} case 4: {
					if (openSecund) { Search_recipe(recipes, twenty_products, total); }
					break;
				}default: {
					printf("%s", "Option invalid[1, 2]\n");
					break;
				}
			}
		}
	} while (isequals(name, "Exit"));

	return SUCCESS;
}

product* initialize_products(product * array, const unsigned int length) {

	const char * ingredients[20] = {
							
							        "Ovos"      ,       "Tomate"       , "PCT Farinha de trigo" , "Fatias de queijo" ,
							"Fatias de presunto", "Colheres de azeite" ,        "Manteiga"      ,      "acucar"      , 
							    "PQt Fermento"  ,      "Azeitona"      ,         "Cebola"       ,      "Frango"      , 
								"catupiry"      ,      "ervilha"       ,    "Fatias calabresa"  ,      "chocolate"   , 
							"colheres orégano"  ,      "parmessao"     ,   "PCT Molho de tomate",      "Pimentao"

								};
	for (int index = 0; index < length; index++) {
		(*(array + index)).id = index + 1;
		strcpy((*(array + index)).description, ingredients[index]);
	}
	return array;
}

void print_all_product(const product* ingredients, const unsigned int length) {
	system("cls"); // clear screen
	printf("\n\n%20s\n", "ALL PRODUCTS");
	for (int index = 0; index < length; index++) {
		printf("%5d %5s\n", (*(ingredients + index)).id, (*(ingredients + index)).description);
	}
	printf("\n");
}


// read identify from ingredient
int id_ingredient (int number) {
	int id;
	do {
		printf("\n[%d] ", number);
		id = readInt("Input the identify the ingredients: ");
	} while (id < 1 || id > 20);
	return (id - 1);
}

recipe * register_recipes(product * ingredients, recipe * recipes, const unsigned int total) {
	int registered_ingredients = 0, id;
	for (int counter_recipe = 0; counter_recipe < total; counter_recipe++) {
		printf("\n[%d] ", counter_recipe + 1);
		strcpy((*(recipes + counter_recipe)).description, readstring(length_array, "Input the name recipe (you don't can input the name with space): "));
		int quantity_ingredients = readInt("\nTotal ingrediente this revenue: ");
		(*(recipes + counter_recipe)).products = (int**)malloc(sizeof(int**) * quantity_ingredients);
	
		// separate memory total from of ingredients
		for (int index = 0; index < quantity_ingredients; index++) {
			(*(recipes + counter_recipe)).products[index] = (int*)malloc(sizeof(int) * 2);
		}
	
		// fill camps from ingredient
		for (int index = 0; index < quantity_ingredients; index++) {
			(*(recipes + counter_recipe)).products[index][0] = id_ingredient(index + 1);
			(*(recipes + counter_recipe)).products[index][1] = readInt("How much of this product? ");
		}
		(*(recipes + counter_recipe)).size_products = quantity_ingredients;
	}
	return recipes;
}

void show_all_recipes(const product * ingredient, const recipe * recipes, const unsigned int length) {
	system("cls");
	for (int index = 0; index < length; index++) {
		printf("%30s", "----------------------");
		printf("\n%15dº recipes\n", index + 1);
		int length_product = (*(recipes + index)).size_products;
		printf("%30s %s\n %30s", "Description: ", (*(recipes + index)).description, "Ingredients: \n");
		for (int products = 0; products < length_product; products++) {
			int value = (recipes + index)->products[products][0];
			printf("%24d %s\n", (recipes + index)->products[products][1], ingredient[value].description);
			}
		printf("%30s\n", "----------------------");
	}
}

void Search_recipe(const recipe* recipes, const product* ingredients, const unsigned int length) {
	system("cls");
	char* name = readstring(30,"\nInput the name recipe (you don't can input the name with space): ");
	int index = 0;
	bool meet = false;
	while (index < length && !meet){
		if (strcmp((*(recipes + index)).description, name) == 0) {
			meet = true;
			int size_ingredients = (*(recipes + index)).size_products;
			printf("%30s\n %20s %s:\n", "----------------------\n", "recipe", name);
			for (int products = 0; products < size_ingredients; products++) {
				int value = (recipes + index)->products[products][0];
				printf("%20d %s\n", (recipes + index)->products[products][1], ingredients[value].description);
			}
			printf("%30s", "----------------------");
		}
		index++;
	}
	if (!meet) { printf("Sorry. I don't meet this recipe :( [%s]", name); }
}