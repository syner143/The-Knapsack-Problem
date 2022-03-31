#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h > 	//for system clear when code re-runs
#include <unistd.h >	//for sleep function to be used
#include <stdlib.h>	//adding librarys to use refrences stored in them

int max(int a, int b)
{
	return a ^ ((a ^ b) &-(a < b));	//finds max value of 2 integers for else if statment earlier in code
}

int Knapsack(int W, int value[], int n, char name[], int User_Weight[], int Gram_Weight[], int User_W)	//prints items in knapsack 
{
	int i, w;
	int K[n + 1][W + 1];	//creates columns and rows for table

	for (i = 0; i <= n; i++)	//repeates process for each input
	{
		for (w = 0; w <= W; w++)
		{
			if (i == 0 || w == 0)
				K[i][w] = 0;	//sets inital weight to 0
			else if (Gram_Weight[i - 1] <= w)
				K[i][w] = max(value[i - 1] + K[i - 1][w - Gram_Weight[i - 1]], K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}

	int result = K[n][W];	//stores outcome of knapsack
	printf("\nThe maximum value you can store in the Knapsack is: %d", result);	//states the max value of the items that fits in the knapsack

	w = W;
	printf("\n\nItems included in the solution:");
	printf("\n\nItem (Entry Number) | Name  |  Value  | Weight(g)");	//headings for table and | creates tables

	for (i = n; i > 0 && result; i--)
	{
		if (result == K[i - 1][w])
			continue;
		else

		{
			printf("\n_________________________________________________");	//making table lines
			printf("\n%d", i);	//prints out item entry number and new line
			printf("                   |\t%c   |", name[i - 1]);	//prints refrence names for each items
			printf("\t%d     |", value[i - 1]);	//make line spacing on c \t gives 3 spacing on results and adds value for item
			//| used to make vertical lines for table
			printf("\t%d", Gram_Weight[i - 1]);	//makes lines spacing 3 and also weight value

			result = result - value[i - 1];	//as weight is used remove value from result 
			w = w - Gram_Weight[i - 1];
		}
	}
}

int main()
{
	int i, W, *ptr, *ptr_value, *ptr_USER, *ptr_GRAM, *ptr_UserW, *ptr_W;
	char *ptr_name, n, cont_prog = 'n';	//sets program to n so loop does not work until y is entered at end of program

	do {
		system("@cls||clear");	//clears user interface
		printf("When using this system remember all numbers enetered must be integers!\n");
		printf("Press Any Key to Continue\n");  
		getchar(); 	//adds delay to outputs so you can read previous line with no distractions

		printf("Enter number of items :\n");	//requests number from user
		scanf("%d", &n);	// stores input as variable n
		ptr = (int*) malloc(n* sizeof(int));

		if (ptr == NULL)
		{
			printf("Error! memory not allocated.");
			return 0;
		}
		free(ptr);
		
		int value[n], User_Weight[n], Gram_Weight[n], NUM, W, User_W;;	//initialises value and weights
		//set array size to n(previous result) so can store to infinity and saves memory
		char name[n];

		printf("\nEnter value and then weight of each item:\n");	// state numbers need to be whole so create loop to correct this and state
		for (i = 0; i < n; ++i)
		{
			printf("Enter a 1 letter refrence for the item - %d\n", i + 1);	//i+1 prints out item number
			scanf("%s", &name[i]);

			ptr_name = (char*) malloc(name[i] *sizeof(char));

			// if memory cannot be allocated
			if (ptr_name == NULL)
			{
				printf("Error! memory not allocated.");
				return 0;
			}

			printf("Enter value for item - %d\n", i + 1);	//loop to make only integer in item as cannot have a value below 0
			scanf("%d", &value[i]);

			ptr_value = (int*) malloc(value[i] *sizeof(int));

			// if memory cannot be allocated
			if (ptr_value == NULL)
			{
				printf("Error! memory not allocated.");
			}

			while (value[i] < 0)
			{
				printf("Invalid value (must be a integer and at least 0)");
				printf("\nEnter new value for item - %d\n", i + 1);
				scanf("%d", &value[i]);
				ptr_value = (int*) malloc(value[i] *sizeof(int));

				// if memory cannot be allocated
				if (ptr_value == NULL)
				{
					printf("Error! memory not allocated.");
					return 0;
				}
				
			}

			printf("SELECT MEASURING MASS FOR ITEM");	//shows all case options as mass must be converted to same units
			printf("\n 1. MILLIGRAM\n");
			printf("\n 2. DECIGRAM\n");
			printf("\n 3. KILOGRAM\n");
			printf("\n 4. GRAMS\n");
			printf("ENTER CHOICE HERE :");
			scanf("%d", &NUM);	//reads case statment choice
			switch (NUM)	//tells user what conversion was chosen
			{
				case 1:
					printf("\n SELETED MILLIGRAMS TO GRAMS\n");
					break;
				case 2:
					printf("\n SELETED DECIGRAMS TO GRAMS\n");
					break;
				case 3:
					printf("\n SELETED KILOGRAMS TO GRAMS\n");
					break;
				case 4:
					printf("\n SELECTED GRAMS TO GRAMS\n");
					break;
				default:
					printf("YOU HAVE ENTERED WRONG CHOICE !!!");	//leaves code in no correct conversion option chosen
					goto QUIT;
			}

			printf("Enter weight for item - %d\n", i + 1);
			scanf("%d", &User_Weight[i]);
			ptr_USER = (int*) malloc(User_Weight[i] *sizeof(int));

			// if memory cannot be allocated
			if (ptr_USER == NULL)
			{
				printf("Error! memory not allocated.");
			}

			while (User_Weight[i] < 0)	//logic as weight cannot be less than 0 so gives chance to change value
			{
				printf("Invalid value (must be a integer and at least 0g)");
				printf("\nEnter new weight for item - %d\n", i + 1);
				scanf("%d", &User_Weight[i]);	//reads new correct value and uses that for answer
				ptr_USER = (int*) malloc(User_Weight[i] *sizeof(int));

				// if memory cannot be allocated
				if (ptr_USER == NULL)
				{
					printf("Error! memory not allocated.");
					return 0;
				}
			
			}

			switch (NUM)	//choses conversion from choice earlier and converts to grams
			{
				case 1:
					Gram_Weight[i] = User_Weight[i] / 1000;	//sets array to be used in calculations
					ptr_GRAM = (int*) malloc(Gram_Weight[i] *sizeof(int));

					// if memory cannot be allocated
					if (ptr_GRAM == NULL)
					{
						printf("Error! memory not allocated.");
						return 0;
					}

					printf("\n %d MILLIGRAMS IS %d GRAMS\n", User_Weight[i], Gram_Weight[i]);	//shows value entered and once converted
					break;

				case 2:
					Gram_Weight[i] = User_Weight[i] / 10;
					ptr_GRAM = (int*) malloc(Gram_Weight[i] *sizeof(int));

					// if memory cannot be allocated
					if (ptr_GRAM == NULL)
					{
						printf("Error! memory not allocated.");
						return 0;
					}

					printf("\n %d DECIGRAMS IS %d GRAMS\n", User_Weight[i], Gram_Weight[i]);
					break;

				case 3:
					Gram_Weight[i] = User_Weight[i] *1000;
					ptr_GRAM = (int*) malloc(Gram_Weight[i] *sizeof(int));

					// if memory cannot be allocated
					if (ptr_GRAM == NULL)
					{
						printf("Error! memory not allocated.");
						return 0;
					}

					printf("\n %d KILOGRAMS IS %d GRAMS\n", User_Weight[i], Gram_Weight[i]);
					break;

				case 4:
					Gram_Weight[i] = User_Weight[i];
					ptr_GRAM = (int*) malloc(Gram_Weight[i] *sizeof(int));

					// if memory cannot be allocated
					if (ptr_GRAM == NULL)
					{
						printf("Error! memory not allocated.");
						return 0;
					}

					printf("\n %d GRAMS IS %d GRAMS\n", User_Weight[i], Gram_Weight[i]);
					break;
			}
		}

		sleep(0.5);
		printf("SELECT MEASURING FOR KNAPSACK MASS");
		printf("\n 1. MILLIGRAM\n");
		printf("\n 2. DECIGRAM\n");
		printf("\n 3. KILOGRAM\n");
		printf("\n 4. GRAMS\n");
		printf("ENTER CHOICE HERE :");
		scanf("%d", &NUM);
		switch (NUM)
		{
			case 1:
				printf("\n SELETED MILLIGRAMS TO GRAMS\n");
				break;
			case 2:
				printf("\n SELETED DECIGRAMS TO GRAMS\n");
				break;
			case 3:
				printf("\n SELETED KILOGRAMS TO GRAMS\n");
				break;
			case 4:
				printf("\n SELETED GRAMS TO GRAMS\n");
				break;
			default:
				printf("YOU HAVE ENTERED WRONG CHOICE !!!");
				goto QUIT;
		}

		printf("Enter size of knapsack (Max capacity):\n");
		scanf("%d", &User_W);
		ptr_UserW = (int*) malloc(User_W* sizeof(int));

		// if memory cannot be allocated
		if (ptr_UserW == NULL)
		{
			printf("Error! memory not allocated.");
			return 0;
		}

		while (W < 0)	//capacity cannot be lower than 0 so prompts user for real input
		{
			printf("Invalid value (must be a integer and at least 0g)");
			printf("\nEnter new Knapsack size - %d\n", i);
			scanf("%d", &User_W);
			
			ptr_UserW = (int*) malloc(User_W* sizeof(int));

			// if memory cannot be allocated
			if (ptr_UserW == NULL)
			{
				printf("Error! memory not allocated.");
				return 0;
			}
			
		}

		switch (NUM)
		{
			case 1:
				W = User_W / 1000;	//converts knapsack capacity to grams
				ptr_W = (int*) malloc(W* sizeof(int));

				// if memory cannot be allocated
				if (ptr_W == NULL)
				{
					printf("Error! memory not allocated.");
					return 0;
				}

				printf("\n %d MILLIGRAMS IS %d GRAMS\n", User_W, W);
				break;
			case 2:
				W = User_W / 10;
				ptr_W = (int*) malloc(W* sizeof(int));

				// if memory cannot be allocated
				if (ptr_W == NULL)
				{
					printf("Error! memory not allocated.");
					return 0;
				}
				
				printf("\n %d DECIGRAMS IS %d GRAMS\n", User_W, W);
				break;
			case 3:
				W = User_W * 1000;
				ptr_W = (int*) malloc(W* sizeof(int));

				// if memory cannot be allocated
				if (ptr_W == NULL)
				{
					printf("Error! memory not allocated.");
					return 0;
				}
				
				printf("\n %d KILOGRAMS IS %d GRAMS\n", User_W, W);
				break;
			case 4:
				W = User_W;
				ptr_W = (int*) malloc(W* sizeof(int));

				// if memory cannot be allocated
				if (ptr_W == NULL)
				{
					printf("Error! memory not allocated.");
					return 0;

				}
				
				printf("\n %d GRAMS IS %d GRAMS\n", User_W, W);
				break;
		}

		Knapsack(W, value, n, name, User_Weight, Gram_Weight, User_W);
		
		free(ptr_W);
		free(ptr_UserW);
		free(ptr_GRAM);
		free(ptr_USER);
		free(ptr_value);
		free(ptr_name);

		sleep(1.5);	//let user read results before offering to start again
		printf("\n\nDo you want to start again? (y/n): ");	//lets user chose if wants to re-run code 
		scanf(" %c", &cont_prog);
	}

	while ((cont_prog == 'y' || cont_prog == 'Y'));	//takes into account case so not case sensitive for re-run question

	QUIT: ;	//entering wrong conversion sends you out of code
	
	return 0;
}
