import os
import string

eye_colour_entries = {
    "amb",
    "blu",
    "brn",
    "gry",
    "grn",
    "hzl",
    "oth"
}

def check_number( value, min, max, length ):
    if len( value ) != length or not value.isdigit():
        return False
    num = int( value )
    return num >= min and num <= max

def validate_height( value ):
    if value.endswith("cm"):
        return check_number( value[0:-2], 150, 193, 3 )
    elif value.endswith("in"):
        return check_number( value[0:-2], 59, 76, 2 )
    return False

def validate_hair_colour( value ):
    return len( value ) == 7 and value[0] == '#' and all( c in string.hexdigits for c in value[1:] )

def validate_eye_colour( value ):
    if( len(value ) != 3):
        return False
    return value in eye_colour_entries

def print_rejected( p_in : dict, reason : str ):
    print( "Rejected due to " + reason )
    print( p_in )


def validate_data( p_in : dict ): 
    if "byr" not in p_in:
        return False
    else:
        if not check_number( p_in.get( "byr" ), 1920, 2002, 4 ):
            print_rejected( p_in, "byr")
            return False

    if "iyr" not in p_in:
        return False
    else:
        if not check_number( p_in.get( "iyr" ), 2010, 2020, 4 ):
            print_rejected( p_in, "iyr")
            return False

    if "eyr" not in p_in:
        return False
    else:
        if not check_number( p_in.get( "eyr" ), 2020, 2030, 4 ):
            print_rejected( p_in, "eyr")
            return False
        
    if "hgt" not in p_in:
        return False
    else:
        if not validate_height( p_in.get( "hgt" ) ):
            print_rejected( p_in, "hgt")
            return False
        
    if "hcl" not in p_in:
        return False
    else:
        if not validate_hair_colour( p_in.get("hcl")):
            print_rejected( p_in, "hcl")
            return False
        
    if "ecl" not in p_in:
        return False
    else:
        if not validate_eye_colour( p_in.get( "ecl")):
            print_rejected( p_in, "ecl")
            return False
        
    if "pid" not in p_in:
        return False        
    else:
        if not check_number( p_in.get( "pid" ), 0, 999999999, 9 ):
            print_rejected( p_in, "pid")
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
    if currentEntry:
        allEntries.append( currentEntry )

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