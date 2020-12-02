#include <stdio.h>

/**
 * Processes a file and returns the list of integers within it
 * @param file_name the name of the file to process
 * @param num_lines the number of lines counted
 * @return pointer to the integer data
 */ 
int* process_file_into_int_array( char* file_name, int* num_lines )
{
	FILE* file_ptr = fopen( file_name, "r" );
	if( !file_ptr )
	{
		return NULL;
	}
	
	int* text_data = (int*) malloc( sizeof( int ) * 1 );

	*num_lines = 0;
	char buf[1000];
	while( fgets(buf, 1000, file_ptr) != NULL )
	{
		*num_lines = *num_lines + 1;
		if( *num_lines > 1 )
		{
			text_data = (int*) realloc(text_data, sizeof( int ) * (*num_lines ));
		}
		text_data[(*num_lines) - 1] = atoi(buf);
	}
	
	fclose( file_ptr );	
	return text_data;
}

/**
 * Processes a file and prints the two numbers which add up to 2020
 * @param file_name the name of the file to process
 */ 
void solve_2020_problem( char* file_name )
{
	int num_lines = 0;
	int* data = process_file_into_int_array( file_name, &num_lines );
	for( int i = 0; i < num_lines; ++i )
	{
		for( int j = i + 1; j < num_lines; ++j )
		{
			if( ( data[i] + data[j] ) == 2020 )
			{
				printf( "Solution is %d and %d, which make %d\n", data[i], data[j], data[i]*data[j] );
			}
		}
	}
	free(data);
}

int main()
{
	printf( "Solving Example problem\n" );
	solve_2020_problem( "data/sample.txt" );
	
	printf( "Solving Actual problem\n" );
	solve_2020_problem( "data/actual.txt" );
	return 0;
}