import os
import argparse

def generate_file_pairs(directory, file_pair_name):
    # Create code directory if it doesn't exist
    if not os.path.exists("code"):
        os.makedirs("code")
        
    # Create test directory if it doesn't exist
    if not os.path.exists("test"):
        os.makedirs("test")
    
    if directory == "code":
        # Create C source and header files in code directory
        with open(f"code/{file_pair_name}.c", "w") as source_file:
            source_file.write(generate_source_file_content(file_pair_name))

        with open(f"code/{file_pair_name}.h", "w") as header_file:
            header_file.write(generate_file_content(file_pair_name, "header"))

        print(f"File pair generated successfully in code directory: {file_pair_name}.c, {file_pair_name}.h")

    elif directory == "test":
        # Create test files in test directory
        with open(f"test/xtest_{file_pair_name}.c", "w") as test_file:
            test_file.write(generate_test_file_content(file_pair_name))

        print(f"Test file generated successfully in test directory: xtest_{file_pair_name}.c")

def generate_file_content(file_name, file_type):
    return f"""
/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/

#ifndef {file_name.upper()}_{file_type.upper()}
#define {file_name.upper()}_{file_type.upper()}

// Your code here

#endif // {file_name.upper()}_{file_type.upper()}
"""

def generate_source_file_content(file_name):
    return f"""
/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/

#include "{file_name}.h"

// Your source code here
"""

def generate_test_file_content(file_name):
    return f"""
/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/

#include "{file_name}.h"
#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassume.h> // extra asserts

// Your test code here
"""

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate C code and test file pairs.')
    parser.add_argument('directory', choices=['code', 'test'], help='Directory to generate files (code or test)')
    parser.add_argument('--name', required=True, help='Name of the file pair')

    args = parser.parse_args()
    generate_file_pairs(args.directory, args.name)
