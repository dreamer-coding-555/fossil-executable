import os
import argparse

class FileGenerator:
    def __init__(self, directory, file_pair_name):
        self.directory = directory
        self.file_pair_name = file_pair_name

        # Create code and test directories if they don't exist
        if not os.path.exists("code"):
            os.makedirs("code")
        if not os.path.exists("test"):
            os.makedirs("test")

        # Common comment for files
        self.comment = """
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
"""

    def generate_file_pairs(self):
        if self.directory == "code":
            self.generate_code_files()
        elif self.directory == "test":
            self.generate_test_files()

    def generate_code_files(self):
        with open(f"code/{self.file_pair_name}.c", "w") as source_file:
            source_file.write(self.comment)
            source_file.write(self.generate_source_file_content())

        with open(f"code/{self.file_pair_name}.h", "w") as header_file:
            header_file.write(self.comment)
            header_file.write(self.generate_file_content("header"))

        print(f"File pair generated successfully in code directory: {self.file_pair_name}.c, {self.file_pair_name}.h")

    def generate_test_files(self):
        with open(f"test/xtest_{self.file_pair_name}.c", "w") as test_file:
            test_file.write(self.comment)
            test_file.write(self.generate_test_file_content())

        print(f"Test file generated successfully in test directory: xtest_{self.file_pair_name}.c")

    def generate_file_content(self, file_type):
        return f"""{self.comment}

#ifndef {self.file_pair_name.upper()}_{file_type.upper()}
#define {self.file_pair_name.upper()}_{file_type.upper()}

// Your code here

#endif // {self.file_pair_name.upper()}_{file_type.upper()}
"""

    def generate_source_file_content(self):
        return f"""{self.comment}

#include "{self.file_pair_name}.h"

// Your source code here
"""

    def generate_test_file_content(self):
        return f"""{self.comment}

#include "{self.file_pair_name}.h"
#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassume.h> // extra asserts

// Your test code here
"""


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate C code and test file pairs.')
    parser.add_argument('directory', choices=['code', 'test'], help='Directory to generate files (code or test)')
    parser.add_argument('--name', required=True, help='Name of the file pair')

    args = parser.parse_args()
    
    generator = FileGenerator(args.directory, args.name)
    generator.generate_file_pairs()
