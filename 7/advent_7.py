import os
import string

def run_program( file_name : str ):
    p_file = open( file_name , 'r')
    lines = p_file.readlines()
    bag_dictionary = {}
    for line in lines:
        split_line = line.split()
        bag = split_line[0] + split_line[1]
        if "contain no other bags" in line:
            bag_dictionary[bag] = {}
        else:
            other_bags = split_line[4:]
            other_bag_dict = {}
            for i in range(0, len(other_bags), 4 ):
                bag_num = int(other_bags[i])
                bag_name = other_bags[i+1] + other_bags[i+2]
                other_bag_dict[bag_name] = bag_num
            bag_dictionary[bag] = other_bag_dict
    print( bag_dictionary )

    list_to_check = ["shinygold"]
    successful_bags = set()
    while len( list_to_check ) != 0:
        for bag in bag_dictionary:
            if list_to_check[0] in bag_dictionary[bag] and list_to_check[0] != bag:
                print( list_to_check[0] + " found in " + bag )
                list_to_check.append( bag )
                successful_bags = successful_bags.union( { bag } )
        list_to_check = list_to_check[1:]
    print( str( successful_bags ))
    print( "Number bags: " + str(len( successful_bags)))
             

print( "Running Example Data")
run_program( "./data/sample.txt")

print( "Running Actual Data")
run_program( "./data/actual.txt")