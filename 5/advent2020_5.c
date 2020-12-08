#include <stdio.h>
#include <stdbool.h>


struct SeatInfo
{
	int m_row;
	int m_column;
};

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/**
 * Processes a file into an array
 * @param file_name the name of the file to process
 */ 
void process_file( const char* file_name )
{
	FILE* file_ptr = fopen( file_name, "r" );
	if( !file_ptr )
	{
		return;
	}
	char buf[1000];
	int highest_score = 0;
	int seat_count = 0;
	int sorted_seats[867];
	while( fgets(buf, 1000, file_ptr) != NULL )
	{
		if( buf[0]== '\n' )
		{
			continue;
		}
		buf[strcspn(buf, "\n")] = 0;
		struct SeatInfo seat_info;
		int upper = 127;
		int lower = 0;
		for( int row_index = 0; row_index < 6; ++row_index )
		{
			if( buf[row_index] == 'F' )
			{
				upper = lower + ((upper - lower )/ 2);
			}
			else
			{
				lower = lower + ((upper-lower + 1)/2);
			}
		}
		seat_info.m_row = buf[6] == 'F' ? lower : upper;
		upper = 7;
		lower = 0;
		for( int col_index = 7; col_index < 9; ++col_index )
		{
			if( buf[col_index] == 'L' )
			{
				upper = lower + ((upper - lower )/ 2);
			}
			else
			{
				lower = lower + ((upper-lower + 1)/2);
			}
		}
		seat_info.m_column = buf[9] == 'L' ? lower : upper;;
		const int score = (seat_info.m_row * 8) + seat_info.m_column;
		if( score > highest_score )
		{
			highest_score = score;
		}
		printf( "%s, row %d, column %d, seat ID %d\n", buf, seat_info.m_row, seat_info.m_column, score );
		sorted_seats[seat_count] = score;
		++seat_count;
	}
	printf( "The highest score is %d\n", highest_score );
	qsort( sorted_seats, 867, sizeof( int ), cmpfunc );
	for( int i = 0; i < 866; ++i )
	{
		if( sorted_seats[i + 1] != sorted_seats[i] + 1 )
		{
			printf( "Missing seat %d\n", sorted_seats[i] + 1 );
		}
	}
	printf( "Seat count %d\n", seat_count);
	fclose( file_ptr );	
}

void run_program( const char* file_name )
{
	process_file( file_name );
}



int main()
{
	printf( "Solving Example problem\n" );
	run_program( "data/sample.txt" );
	printf("\n");
	
	printf( "Solving Actual problem\n" );
	run_program( "data/actual.txt" );
	printf("\n");
		
	return 0;
}