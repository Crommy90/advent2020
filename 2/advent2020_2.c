#include <stdio.h>
#include <stdbool.h>

/**
 * Holds the password and the rule to evaluate it against
 */ 
struct PasswordData
{
	int min_num;
	int max_num;
	char letter;
	char password[1000];
};

/**
 * Returns the password data from a string
 * @param line line to parse
 * @return password data
 */ 
struct PasswordData get_password_data_for_string( const char* line )
{
	struct PasswordData pdata;
	int index = 0;
	while( isdigit( line[index] ) )
	{
		++index;
	}
	pdata.min_num = atoi( line );
	while( !isdigit( line[index] ) )
	{
		++index;
	}
	int start_index = index;
	pdata.max_num = atoi( line + start_index );
	++index;
	while( isdigit( line[index] ) )
	{
		++index;
	}
	++index;
	pdata.letter = line[index];
	int copy_index = 0;
	index += 2;
	while( line[index] != '\n'
			&& line[index] != '\0' )
	{
		pdata.password[copy_index] = line[index];
		++index;
		++copy_index;
	}
	pdata.password[copy_index] = '\0';
	return pdata;
}

/**
 * Tests whether a password passes the old password system
 * @param data the password to test
 * @return if the password passes the test
 */ 
bool test_old_password_system( const struct PasswordData* data )
{
	int char_count = 0;
	int index = 0;
	//printf( "Letter %c, min %d, max %d, pwd %s\n", data.letter, data.min_num, data.min_num, data.password );
	while( data->password[index] != '\0' )
	{
		if( data->password[index] == data->letter )
		{
			++char_count;
			if( char_count > data->max_num )
			{
				return false;
			}
		}
		++index;
	}
	if( char_count < data->min_num )
	{
		return false;
	}
	return true;
}
	


/**
 * Processes a file and prints the number of valid passwords
 * @param file_name the name of the file to process
 */ 
void solve_problem( char* file_name, bool test_frequency )
{
	FILE* file_ptr = fopen( file_name, "r" );
	if( !file_ptr )
	{
		return;
	}
	
	int valid_count = 0;
	int invalid_count = 0;
	
	char buf[1000];
	while( fgets(buf, 1000, file_ptr) != NULL )
	{
		struct PasswordData data = get_password_data_for_string( buf );
		bool valid = true;
		if( test_frequency )
		{
			valid = test_old_password_system( &data );
		}
		if( valid )
		{
			++valid_count;
			//printf( "%s is valid\n", data.password );
		}
		else
		{
			++invalid_count;
			//printf( "%s is invalid\n", data.password );
		}
	}
	printf( "Valid: %d | Invalid: %d\n", valid_count, invalid_count);
	fclose( file_ptr );	
}

int main()
{
	printf( "Solving Example problem\n" );
	solve_problem( "data/sample.txt", true );
	printf("\n");
	
	printf( "Solving Actual problem\n" );
	solve_problem( "data/actual.txt", true );
	printf("\n");

	return 0;
}