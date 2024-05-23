#!/usr/bin/env python3

import os
import re
import hashlib
import requests
import subprocess
import sys

def run_meson_subprojects_download():
    """Run the Meson subprojects download command."""
    try:
        subprocess.run(['meson', 'subprojects', 'download'], check=True)
        print("Meson subprojects download completed successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error running meson subprojects download: {e}")
        sys.exit(1)

def read_wrap_file(file_path):
    """Read and parse the wrap file."""
    config = {}
    current_section = None

    try:
        with open(file_path, 'r') as file:
            for line in file:
                line = line.strip()
                if not line or line.startswith('#'):
                    continue  # Skip empty lines and comments
                if line.startswith('[') and line.endswith(']'):
                    current_section = line[1:-1].strip()
                    config[current_section] = {}
                elif '=' in line and current_section:
                    key, value = map(str.strip, line.split('=', 1))
                    config[current_section][key] = value
                else:
                    print(f"Invalid line in wrap file {file_path}: {line}")
    except Exception as e:
        print(f"Error reading wrap file {file_path}: {e}")
        return None

    return config

def validate_url(url):
    """Validate the URL format and check if it's reachable."""
    regex = re.compile(
        r'^(?:http|ftp)s?://'  # http:// or https://
        r'(?:(?:[A-Z0-9](?:[A-Z0-9-]{0,61}[A-Z0-9])?\.)+(?:[A-Z]{2,6}\.?|[A-Z0-9-]{2,}\.?)|'  # domain...
        r'localhost|'  # localhost...
        r'\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}|'  # ...or ipv4
        r'\[?[A-F0-9]*:[A-F0-9:]+\]?)'  # ...or ipv6
        r'(?::\d+)?'  # optional port
        r'(?:/?|[/?]\S+)$', re.IGNORECASE)
    
    if re.match(regex, url) is not None:
        try:
            response = requests.get(url)
            if response.status_code == 200:
                return True
            else:
                print(f"URL {url} is not reachable. Status code: {response.status_code}")
                return False
        except requests.exceptions.RequestException as e:
            print(f"URL {url} is not reachable. Error: {e}")
            return False
    else:
        print(f"Invalid URL format: {url}")
        return False

def validate_hash(file_path, expected_hash, hash_type='sha256'):
    """Validate the hash of the file."""
    hash_func = hashlib.new(hash_type)

    try:
        with open(file_path, 'rb') as f:
            for chunk in iter(lambda: f.read(4096), b""):
                hash_func.update(chunk)
        calculated_hash = hash_func.hexdigest()

        if calculated_hash == expected_hash:
            return True
        else:
            print(f"Hash mismatch for {file_path}. Expected {expected_hash}, got {calculated_hash}")
            return False
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return False
    except Exception as e:
        print(f"Error while hashing {file_path}: {e}")
        return False

def perform_sanity_check(directory):
    """Perform the sanity check on wrap files in the subprojects directory."""
    issues_found = False
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".wrap"):
                wrap_file_path = os.path.join(root, file)
                print(f"Checking wrap file: {wrap_file_path}")
                config = read_wrap_file(wrap_file_path)

                if config is None:
                    issues_found = True
                    continue

                # Check URLs in the [wrap-file] section
                source_url = config.get('wrap-file', {}).get('source_url')
                if source_url and not validate_url(source_url):
                    issues_found = True

                # Check file hashes in the [wrap-file] section
                source_filename = config.get('wrap-file', {}).get('source_filename')
                source_hash = config.get('wrap-file', {}).get('source_hash')
                source_hash_type = config.get('wrap-file', {}).get('source_hash_type', 'sha256')

                if source_filename and source_hash:
                    source_file_path = os.path.join(root, source_filename)
                    if not validate_hash(source_file_path, source_hash, source_hash_type):
                        issues_found = True

    return issues_found

def check_build_files(directory):
    """Ensure only Meson build files are present and no CMake, automake, SCONS, Make, BAZEL files are found."""
    prohibited_files = ['CMakeLists.txt', 'Makefile', 'SConstruct', 'BUILD']
    meson_files = ['meson.build', 'meson_options.txt']

    for root, _, files in os.walk(directory):
        for file in files:
            if file in prohibited_files:
                print(f"Prohibited build file found: {os.path.join(root, file)}")
                return True
            if file in meson_files:
                print(f"Meson build file found: {os.path.join(root, file)}")

    return False

def main():
    subprojects_dir = "subprojects"
    root_dir = os.getcwd()

    # Ensure only Meson build files are present
    if check_build_files(root_dir):
        print("Prohibited build files found.")
        sys.exit(1)

    if not os.path.exists(subprojects_dir):
        print(f"{subprojects_dir} directory does not exist.")
        sys.exit(1)

    run_meson_subprojects_download()

    issues_found = perform_sanity_check(subprojects_dir)
    if issues_found:
        print("Sanity check failed.")
        sys.exit(1)
    else:
        print("Sanity check passed.")
        sys.exit(0)

if __name__ == "__main__":
    main()