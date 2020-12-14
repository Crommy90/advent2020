#include <stdio.h>
#include <stdbool.h>


struct LetterHit
{
	bool m_values[26];
};

void reset_letter( struct LetterHit* letters )
{
	for( int i = 0; i < 26; ++i )
	{
		letters->m_values[i] = false;
	}
}

int get_letter_hit_count( struct LetterHit* letters )
{
	int count = 0;
	for( int i = 0; i < 26; ++i )
	{
		if( letters->m_values[i] )
		{
			++count;
		}
	}
	return count;
}

void process_file( const char* file_name )
{
	FILE* file_ptr = fopen( file_name, "r" );
	if( !file_ptr )
	{
		return;
	}
	char buf[1000];
	struct LetterHit letters;
	reset_letter( &letters );
	int count = 0;
	while( fgets(buf, 1000, file_ptr) != NULL )
	{
		if( buf[0]== '\n' )
		{
			count += get_letter_hit_count( &letters );
			reset_letter( &letters );
			continue;
		}
		int index = 0;
		while( isalpha( buf[index] ) )
		{
			// We're storing ASCII, a is 97
			int as_ascii = (int) buf[index];
			as_ascii -= 97;
			letters.m_values[as_ascii] = true;
			++index;
		}
	}
	count += get_letter_hit_count( &letters );
	printf( "The total sum is %d\n", count );
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