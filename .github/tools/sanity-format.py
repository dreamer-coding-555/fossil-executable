#!/usr/bin/env python3

import os
import re
import sys
import threading
import json
from queue import Queue

# Define refined patterns to search for common security issues
patterns = {
    'unsafe_functions': re.compile(r'\b(strcpy_s?|strcat_s?|sprintf_s?|gets|scanf_s?|sscanf_s?|vfscanf_s?|vscanf_s?|vsscanf_s?)\b'),
    'buffer_overflow': re.compile(r'\b(memcpy_s?|memmove_s?|memset_s?)\b.*?\[(?!sizeof)'),
    'uninitialized_var': re.compile(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*[^;]*;\s*(if\s*\(\1\s*==\s*[^)]*\)|while\s*\(\1\s*==\s*[^)]*\))'),
    'command_injection': re.compile(r'\b(system|exec|popen)\b|\b(os.system|os.popen|subprocess.call|subprocess.Popen|subprocess.run)\b'),
    'unprotected_format_string': re.compile(r'(?:^|(?<=[^%]))printf\s*\([^"]')
}

class CodeScanner:
    def __init__(self, directory, output_format='text'):
        self.directory = directory
        self.output_format = output_format
        self.summary = {
            'unsafe_functions': 0,
            'buffer_overflow': 0,
            'uninitialized_var': 0,
            'command_injection': 0,
            'unprotected_format_string': 0
        }
        self.issues = []
        self.queue = Queue()
        self.lock = threading.Lock()
    
    def check_file(self, filepath):
        file_issues = []
        try:
            with open(filepath, 'r', errors='ignore') as file:
                content = file.readlines()
                for i, line in enumerate(content):
                    for issue_type, pattern in patterns.items():
                        matches = pattern.findall(line)
                        if matches:
                            with self.lock:
                                self.summary[issue_type] += len(matches)
                            file_issues.append((issue_type, i + 1, line.strip(), matches))
        except Exception as e:
            print(f"Error reading file {filepath}: {e}")
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
                if file.endswith(('.c', '.cpp', '.m', '.mm', '.cu')):
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
        if self.output_format == 'json':
            result = {
                'summary': self.summary,
                'issues': [{
                    'file': filepath,
                    'issues': [{'type': issue[0], 'line': issue[1], 'code': issue[2], 'matches': issue[3]} for issue in issues]
                } for filepath, issues in self.issues]
            }
            print(json.dumps(result, indent=2))
        else:
            for filepath, issues in self.issues:
                print(f"Issues found in {filepath}:")
                for issue_type, line_num, code, matches in issues:
                    print(f"  Line {line_num}: {issue_type} - {code} (matches: {matches})")
            print("\nSummary of issues found:")
            for issue_type, count in self.summary.items():
                print(f"  {issue_type}: {count} occurrences")

def main():
    default_directory = os.path.dirname(os.path.realpath(__file__))
    
    if len(sys.argv) > 1 and sys.argv[1] not in ('--json', '-j'):
        directory = sys.argv[1]
    else:
        directory = default_directory

    output_format = 'json' if any(arg in sys.argv for arg in ('--json', '-j')) else 'text'

    if not os.path.isdir(directory):
        print(f"Error: {directory} is not a valid directory.")
        sys.exit(1)
    
    scanner = CodeScanner(directory, output_format)
    scanner.scan_directory()
    scanner.output_results()

if __name__ == "__main__":
    main()
