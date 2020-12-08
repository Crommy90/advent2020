import os


def validate_data( p_in : dict ): 
    if "byr" not in p_in:
        return False
        
    if "iyr" not in p_in:
        return False
        
    if "eyr" not in p_in:
        return False
        
    if "hgt" not in p_in:
        return False
        
    if "hcl" not in p_in:
        return False
        
    if "ecl" not in p_in:
        return False
        
    if "pid" not in p_in:
        return False
    return True

def run_program( file_name : str ):
    p_file = open( file_name , 'r')
    lines = p_file.readlines()
    currentEntry = {}
    allEntries = []
    for line in lines:
        if line == "\n":
            allEntries.append( currentEntry )
            currentEntry = {}
        else:
            split_line = line.split()
            for entry in split_line:
                currentEntry[entry.split(":")[0]] = entry.split(":")[1]

    valid_entries = 0
    invalid_entries = 0
    for entry in allEntries:
        if( validate_data( entry ) ):
            valid_entries = valid_entries + 1
        else:
            invalid_entries = invalid_entries + 1
    print( "Valid entries " + str(valid_entries) + ", Invalid entries " + str(invalid_entries) )


print( "Running Example Data")
run_program( "./data/sample.txt")

print( "Running Actual Data")
run_program( "./data/actual.txt")