#include <stdio.h>
#include <stdbool.h>

/**
 * Gets the index within an array given a row and column
 * @param row
 * @param column
 * @param row_length
 * @return the index within the array
 */ 
int get_cell_index( int row, int column, int row_length )
{
	return row + (column*row_length);
}

/**
 * Processes a file into an array
 * @param file_name the name of the file to process
 * @param array the array to populate
 * @param row_length the row length dictated by the file
 * @param column_length the column length dictated by the file
 */ 
void process_file_into_array( const char* file_name, bool** array, int* row_length, int* column_length )
{
	FILE* file_ptr = fopen( file_name, "r" );
	if( !file_ptr )
	{
		return;
	}
	char buf[1000];
	int column_index = 0;
	*row_length = 0;
	while( fgets(buf, 1000, file_ptr) != NULL )
	{
		if( column_index == 0 )
		{
			int test_char = 0;
			while( buf[test_char] == '.' || buf[test_char] == '#' )
			{
				++test_char;
			}
			*row_length = test_char;
		}
		int realloc_size = ( *row_length ) * (column_index+1);
		*array = (bool*) realloc(*array, sizeof( bool ) * realloc_size);		
		for( int i = 0; i < *row_length; ++i )
		{
			const bool value = buf[i] == '.';
			(*array)[get_cell_index(i, column_index, *row_length )] = value;
		}
		++column_index;
		
	}
	*column_length = column_index;	
	fclose( file_ptr );	
}

unsigned long long run_program( const char* file_name, const int x_step, const int y_step )
{
	bool* array = NULL;
	int row_length = 0;
	int column_length = 0;
	process_file_into_array( file_name, &array, &row_length, &column_length );
	int x_loc = 0;
	int y_loc = 0;
	int tree_count = 0;
	while( true )
	{
		x_loc = (x_loc + x_step) % row_length;
		y_loc = y_loc + y_step;
		if( y_loc >= column_length )
		{
			break;
		}
		else if( !array[get_cell_index( x_loc, y_loc, row_length )] )
		{
			++tree_count;
		}
	}
	printf( "You have encountered %d trees\n", tree_count );
	free( array );
	return (unsigned long long)tree_count;
}

void run_part2_program( const char* file_name ) 
{
	unsigned long long tree_count = run_program( file_name, 1, 1 );
	tree_count *= run_program( file_name, 3, 1 );
	tree_count *= run_program( file_name, 5, 1 );
	tree_count *= run_program( file_name, 7, 1 );
	tree_count *= run_program( file_name, 1, 2 );
	printf( "Tree multiplication answer is: %llu\n", tree_count );
}

int main()
{
	printf( "Solving Example problem\n" );
	run_program( "data/sample.txt", 3, 1 );
	printf("\n");
	
	printf( "Solving Actual problem\n" );
	run_program("data/actual.txt", 3, 1);
	printf("\n");
	
	printf("---Part Two---\n");
	
	printf( "Solving Example problem\n" );
	run_part2_program( "data/sample.txt" );
	printf("\n");
	
	printf( "Solving Actual problem\n" );
	run_part2_program( "data/actual.txt" );
	printf("\n");
	
	return 0;
}