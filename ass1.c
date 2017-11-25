//-----------------------------------------------------------------------------
// ass1.c
//
// Dreiecksüberprüfungen
//
// Group: 3 study assistant Hancianu Michael
//
// Authors: Rijad Kovacevic 01231648
//          Dzenis Kajtazovic 01231661
//
// Latest Changes: 02.11.2017 (by Dzenis Kajtazovic)
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

typedef struct _Triangle_
{
	float a_;
	float b_;
	float c_;
} Triangle;

Triangle* angle;
Triangle trg;

// forward declarations
void swap(float *number_1, float *number_2);
void bubbleSort(float number_1, float number_2, float number_3, int index);
void triangleType(float number_1, float number_2, float number_3);
void checkTriangle(float number_1, float number_2, float number_3, int index);
float isItFloat(char *userInput);
int isItDigit(char* userInput);

//-----------------------------------------------------------------------------
///
/// The main program.
///
/// In combination with for and while loops, functions isItDigit and isItFloat
/// will take care of right input. BubbleSort function should sort numbers
/// and last checkTriangle func will check if it's triangle and triangle type
///
/// @angle initializing the pointer
/// @param userInput[UCHAR_MAX] used instead of hardcore value or
///  defining value, since we want 255 characters for our char array
/// @param num_of_triangles used to store number of triangles on stack.
///
/// @return always zero
//
int main()
{
	angle = &trg;
	char userInput[UCHAR_MAX];
	int loop = 0;
	int num_of_triangles = isItDigit(userInput);

	for(int i = 0; i < num_of_triangles; i++)
	{
		while(loop == 0)
		{
			printf("Please enter the first number of the triplet: ");
			angle[i].a_ = isItFloat(userInput);
			if(angle[i].a_ != 0)
			{
				break;
			}
		}

		while(loop == 0)
		{
			printf("Please enter the second number of the triplet: ");
			angle[i].b_ = isItFloat(userInput);
			if(angle[i].b_ != 0)
			{
				break;
			}
		}

		while(loop == 0)
		{
			printf("Please enter the third number of the triplet: ");
			angle[i].c_ = isItFloat(userInput);
			if(angle[i].c_ != 0)
			{
				break;
			}
		}
	}

	for(int index = 0; index < num_of_triangles; index++)
	{
		bubbleSort(angle[index].a_, angle[index].b_, angle[index].c_, index);
	}

	for (int index = 0; index < num_of_triangles; index++)
	{
		checkTriangle(angle[index].a_, angle[index].b_, angle[index].c_, index);
	}

	return 0;
}

//-----------------------------------------------------------------------------
///
/// Swap numbers
///
/// @param *number_1 Pointer to first number
/// @param *number_2 Pointer to second number
///
/// @void No return value
//
void swap(float *number_1, float *number_2)
{
    float temp = *number_1;
    *number_1 = *number_2;
    *number_2 = temp;
}

//-----------------------------------------------------------------------------
///
/// Algorithm for sorting the values
///
/// @param number_1 1st side of triangle
/// @param number_2 2nd side of triangle
/// @param number_3 3rd side of triangle
/// @param index Number of triangle
///
/// @void No return value
//
void bubbleSort(float number_1, float number_2, float number_3, int index)
{
	int i, j;
	float array[] = {number_1, number_2, number_3};
	int num_of_sides = (int)(sizeof(array) / sizeof(array[0]));
	for (i = 0; i < num_of_sides; i++)
	{
		for ( j = 0; j < (num_of_sides - i - j); j++)
		{
			if (array[j] > array[j+1])
				swap(&array[j], &array[j+1]);
		}
	}
	angle[index].a_ = array[0];
	angle[index].b_ = array[1];
	angle[index].c_ = array[2];
}

//-----------------------------------------------------------------------------
///
/// Function to decide type of a triangle
///
/// @param number_1 1st side of triangle
/// @param number_2 2nd side of triangle
/// @param number_3 3rd side of triangle
///
/// @void No return value
//
void triangleType(float number_1, float number_2, float number_3)
{
	if ((number_1 == number_2) && (number_2 == number_3))
	{
		printf("%2s%s", "", "It is an equilateral triangle.\n");
	}
	if ((number_1 == number_2) || (number_2 == number_3) ||
	    (number_1 == number_3))
	{
		printf("%2s%s", "", "It is an isosceles triangle.\n");
	}
	else
	{
		printf("%2s%s", "", "It is a right triangle.\n");
	}
}

//-----------------------------------------------------------------------------
///
/// Function to check if it is a triangle
///
/// @param number_1 1st side of triangle
/// @param number_2 2nd side of triangle
/// @param number_3 3rd side of triangle
/// @param index Number of the triangle
///
/// @void No return value
//
void checkTriangle(float number_1, float number_2, float number_3, int index)
{
	if ((number_1 + number_2 > number_3) && (number_1 + number_3 > number_2) &&
      (number_2 + number_3 > number_1))
	{
		printf("Triplet %d (a=%f, b=%f, c=%f) is a triangle.\n", index + 1,
           number_1, number_2, number_3);
		triangleType(number_1, number_2, number_3);
		return;
	}
	printf("Triplet %d (a=%f, b=%f, c=%f) is NO triangle.\n", index + 1,
	       number_1, number_2, number_3);
}

//-----------------------------------------------------------------------------
///
/// Function to check if a inserted value is float
///
/// @param userInput What user inputs
///
/// @return If wrong input, return 0,
///         else cast char* pointer to float (atof)
//
float isItFloat(char *userInput)
{
	int dot = 0;
	if(fgets(userInput, UCHAR_MAX, stdin) == NULL)
	{
		exit(0);
	}

	for (int i = 0; i < (strlen(userInput) - 1); i++)
	{
		if ((userInput[0] == '0') && (isdigit(userInput[1])))
		{
			printf("[ERR] Invalid number for the triplet.\n");
			return 0;
		}
		if (!isdigit(userInput[i]))
		{
			if (userInput[0] == '.')
			{
				printf("[ERR] Invalid number for the triplet.\n");
				return 0;
			}
			if (userInput[i] == '.')
			{
				dot++;
			}
			else
			{
				printf("[ERR] Invalid number for the triplet.\n");
				return 0;
			}
		}

		if (dot > 1)
		{
			printf("[ERR] Invalid number for the triplet.\n");
			return 0;
		}
		if ((atof(userInput) <= 0.0) || (atof(userInput) > FLT_MAX))
		{
			printf("[ERR] Invalid number for the triplet.\n");
			return 0;
		}
	}
	return atof(userInput);
}

//-----------------------------------------------------------------------------
///
/// Function to check if a inserted value is integer
/// memset used to clear the array, since we used recursion
///
/// @param userInput What user inputs
///
/// @return If input is wrong, call the function itself(recursion),
///         else return num_of_triangles;
//
int isItDigit(char* userInput)
{
	printf("Please enter the number of triangles to check: ");
	if(fgets(userInput, UCHAR_MAX, stdin) == NULL)
	{
		exit(0);
	}

	for (int i = 0; i < (strlen(userInput) - 1); i++)
	{
		if (!isdigit(userInput[i]) || (userInput[0] == '0'))
		{
			printf("[ERR] Invalid number of triangles.\n");
			memset(&userInput[0], 0, strlen(userInput));
			isItDigit(userInput);
		}
	}

	if ((atoi(userInput) < 1) || (atoi(userInput) > UCHAR_MAX))
	{
		printf("[ERR] Invalid number of triangles.\n");
		memset(&userInput[0], 0, strlen(userInput));
		isItDigit(userInput);
	}
  return atoi(userInput);
}
