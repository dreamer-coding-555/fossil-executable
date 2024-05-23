#!/usr/bin/env python3

import os
import sys
import re
from queue import Queue
import threading

# Configuration for format checks
config = {
    'indentation': 4,  # Number of spaces for indentation
    'max_line_length': 80,  # Maximum allowed line length
}

# Define patterns for format checks
patterns = {
    'trailing_whitespace': re.compile(r'[ \t]+$'),
    'multiple_blank_lines': re.compile(r'\n{3,}'),
    'missing_newline_at_eof': re.compile(r'[^\n]\Z'),
}

class FormatChecker:
    def __init__(self, directory):
        self.directory = directory
        self.queue = Queue()
        self.lock = threading.Lock()
        self.issues = []
        self.file_extensions = ['.c', '.cpp', '.h', '.hpp', '.m', '.mm', '.cu']  # File extensions to check

    def check_file(self, filepath):
        file_issues = []
        with open(filepath, 'r', errors='ignore') as file:
            lines = file.readlines()

            # Check for trailing whitespace
            for i, line in enumerate(lines):
                if patterns['trailing_whitespace'].search(line):
                    file_issues.append((i + 1, 'Trailing whitespace'))

            # Check for indentation
            for i, line in enumerate(lines):
                stripped_line = line.lstrip()
                if stripped_line and len(line) - len(stripped_line) % config['indentation'] != 0:
                    file_issues.append((i + 1, 'Incorrect indentation'))

            # Check for line length
            for i, line in enumerate(lines):
                if len(line) > config['max_line_length']:
                    file_issues.append((i + 1, f'Line exceeds {config["max_line_length"]} characters'))

            # Check for multiple blank lines
            content = ''.join(lines)
            if patterns['multiple_blank_lines'].search(content):
                file_issues.append((None, 'Multiple consecutive blank lines'))

            # Check for missing newline at EOF
            if not content.endswith('\n'):
                file_issues.append((len(lines), 'Missing newline at end of file'))

        return file_issues

    def worker(self):
        while True:
            filepath = self.queue.get()
            if filepath is None:
                break
            issues = self.check_file(filepath)
            if issues:
                with self.lock:
                    self.issues.append((filepath, issues))
            self.queue.task_done()

    def scan_directory(self):
        for root, _, files in os.walk(self.directory):
            for file in files:
                if any(file.endswith(ext) for ext in self.file_extensions):
                    self.queue.put(os.path.join(root, file))

        threads = []
        for _ in range(min(8, os.cpu_count())):  # Limit to a maximum of 8 threads
            t = threading.Thread(target=self.worker)
            t.start()
            threads.append(t)

        self.queue.join()

        for _ in range(min(8, os.cpu_count())):
            self.queue.put(None)
        for t in threads:
            t.join()

    def output_results(self):
        if not self.issues:
            print("No formatting issues found.")
        else:
            for filepath, issues in self.issues:
                print(f"Issues found in {filepath}:")
                for line_num, issue in issues:
                    if line_num:
                        print(f"  Line {line_num}: {issue}")
                    else:
                        print(f"  {issue}")
            print("\nSummary of files checked:", len(self.issues))

def main():
    if len(sys.argv) < 2:
        directory = os.getcwd()
    else:
        directory = sys.argv[1]

    if not os.path.isdir(directory):
        print(f"Error: {directory} is not a valid directory.")
        sys.exit(1)

    checker = FormatChecker(directory)
    checker.scan_directory()
    checker.output_results()

if __name__ == "__main__":
    main()