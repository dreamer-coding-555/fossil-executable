#!/usr/bin/env python3

import os
import re
import sys
import threading
import json
import subprocess
from queue import Queue

# Define patterns to search for common security issues
patterns = {
    'unsafe_functions': re.compile(r'\b(strcpy|strcat|sprintf|gets|scanf|sscanf|vfscanf|vscanf|vsscanf)\b'),
    'buffer_overflow': re.compile(r'\b(memcpy|memmove|memset)\b.*?\[(?!sizeof)'),
    'uninitialized_var': re.compile(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*[^;]*;\s*(if\s*\(\1\s*==\s*[^)]*\)|while\s*\(\1\s*==\s*[^)]*\))'),
    'command_injection': re.compile(r'\b(system|exec|popen)\b'),
    'unprotected_format_string': re.compile(r'printf\s*\([^"]')
}

# Define file patterns that are not allowed
disallowed_build_files = [
    re.compile(r'cmake.*', re.IGNORECASE),
    re.compile(r'build.*\.cmake', re.IGNORECASE),
    re.compile(r'CMakeLists\.txt', re.IGNORECASE),
    re.compile(r'.*\.am$', re.IGNORECASE),
    re.compile(r'configure', re.IGNORECASE),
    re.compile(r'configure\.ac', re.IGNORECASE),
    re.compile(r'configure\.in', re.IGNORECASE),
    re.compile(r'makefile', re.IGNORECASE),
    re.compile(r'makefile\..*', re.IGNORECASE),
    re.compile(r'.*\.mk$', re.IGNORECASE),
    re.compile(r'build\.scons', re.IGNORECASE),
    re.compile(r'sconstruct', re.IGNORECASE),
    re.compile(r'sconscript', re.IGNORECASE),
    re.compile(r'build\.bazel', re.IGNORECASE),
    re.compile(r'WORKSPACE', re.IGNORECASE),
]

# Define Meson build files
meson_build_files = [
    'meson.build',
    'meson.options',
    'meson_options.txt'
]

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
                    if 'test/' in filepath and line.strip().startswith('#'):
                        continue  # Skip lines starting with '#' in the 'test/' directory
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

def check_meson_exclusivity(directory):
    """Check for presence of Meson build files and absence of other build system files."""
    meson_files_found = False
    other_build_files_found = False

    for root, _, files in os.walk(directory):
        for file in files:
            if file in meson_build_files:
                meson_files_found = True
            for pattern in disallowed_build_files:
                if pattern.match(file):
                    print(f"Disallowed build file found: {os.path.join(root, file)}")
                    other_build_files_found = True

    if not meson_files_found:
        print("No Meson build files found. Ensure that meson.build, meson.options, or meson_options.txt are present.")
        sys.exit(1)
    
    if other_build_files_found:
        sys.exit(1)

def run_meson_subprojects_download(directory):
    """Run the Meson subprojects download command."""
    try:
        subprocess.run(['meson', 'subprojects', 'download'], check=True, cwd=directory)
        print("Meson subprojects download completed successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error running meson subprojects download: {e}")
        sys.exit(1)

def main():
    if len(sys.argv) < 2:
        directory = os.getcwd()
    else:
        directory = sys.argv[1]

    output_format = 'json' if '--json' in sys.argv else 'text'

    if not os.path.isdir(directory):
        print(f"Error: {directory} is not a valid directory.")
        sys.exit(1)
    
    subprojects_dir = os.path.join(directory, 'subprojects')
    if not os.path.exists(subprojects_dir):
        print(f"{subprojects_dir} directory does not exist.")
        sys.exit(1)

    check_meson_exclusivity(directory)
    run_meson_subprojects_download(directory)

    scanner = CodeScanner(directory, output_format)
    scanner.scan_directory()
    scanner.output_results()

    if any(value > 0 for value in scanner.summary.values()):
        sys.exit(1)
    else:
        sys.exit(0)

if __name__ == "__main__":
    main()
