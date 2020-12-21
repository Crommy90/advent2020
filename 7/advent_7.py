import os
import string


def get_bag_dictionary( file_name : str) :
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
    #print( bag_dictionary )
    return bag_dictionary

def run_part_1( file_name : str ):
    bag_dictionary = get_bag_dictionary( file_name )
    list_to_check = ["shinygold"]
    successful_bags = set()
    while len( list_to_check ) != 0:
        for bag in bag_dictionary:
            if list_to_check[0] in bag_dictionary[bag] and list_to_check[0] != bag:
                #print( list_to_check[0] + " found in " + bag )
                list_to_check.append( bag )
                successful_bags = successful_bags.union( { bag } )
        list_to_check = list_to_check[1:]
    #print( str( successful_bags ))
    print( "Number bags: " + str(len( successful_bags)))

def get_num_bags( bag : str, bag_dict : dict, mul : int ):
    num_bags = mul # this is self
    for sub_bag in bag_dict[bag]:
        num_bags += mul * get_num_bags( sub_bag, bag_dict, bag_dict[bag][sub_bag] )
    #print( str( num_bags) + " bags in bag " + bag )
    return num_bags

def run_part_2( file_name : str ):
    bag_dictionary = get_bag_dictionary( file_name )
    num_bags = get_num_bags( "shinygold", bag_dictionary, 1 ) - 1 #Minus 1 as it will include self
    print( "Number bags: " + str( num_bags) )
             

print( "Running Example Data")
run_part_1( "./data/sample.txt")

print( "Running Actual Data")
run_part_1( "./data/actual.txt")

print( "Running Example Data")
run_part_2( "./data/sample.txt")

print( "Running Actual Data")
run_part_2( "./data/actual.txt")