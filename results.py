#!/bin/python3

import argparse
import os
import sys
from pathlib import Path
import re
import json

LOGS_DIR            = "logs"
TESTS_DIR           = "tests"

LOGS_FILE_PATTERN   = "llc" 
TESTS_FILE_PATTERNS = ["test", "snoop"]

METRICS_REGEXES     = {"Total Memory Accesses": r"([0-9]+)",
                       "Reads": r"([0-9]+)",
                       "Writes": r"([0-9]+)",
                       "HITs": r"([0-9]+)",
                       "MISSes": r"([0-9]+)",
                       "Hit Ratio": r"([0-9]+\.[0-9]+)",
                       "Miss Ratio": r"([0-9]+\.[0-9]+)"}

def find_file_paths():
    _logs_paths = []
    _tests_paths = []

    # Traverse through files and directories in logs/ one iteration
    for root, dirs, files in os.walk(LOGS_DIR):
        for _file in files:
            # Check IF file pattern is in file string
            if LOGS_FILE_PATTERN in _file.lower():
                path = os.path.join(LOGS_DIR, _file)     # join path with file
                _logs_paths.append(path)                # append it to list
        break

    # Traverse through files and directories in tests/ one iteration
    for root, dirs, files in os.walk(TESTS_DIR):
        for _file in files:
            # Traverse through patterns
            for pattern in TESTS_FILE_PATTERNS:
                # Check IF file pattern is in file string
                if pattern in _file.lower():
                    path = os.path.join(TESTS_DIR, _file)     # join path with file
                    _tests_paths.append(path)                # append it to list
        break

    return _logs_paths, _tests_paths

def search_metric_results(log_file_path):
    metric_results = {}

    # Read log file as text file
    with open(log_file_path, "rt") as f:
        content = f.read()

        # Traverse through metric regexes
        for metric, regex in METRICS_REGEXES.items():
            metric_results[metric] = None               # set to None by default
            match = re.search(rf'{metric}\s=\s{regex}', content) # capture match
            metric_results[metric] = match.group(1)              # store capture group

    # Update dictionary with log file name with out file path and extension
    metric_results.update({"log":f'{os.path.splitext(os.path.basename(log_file_path))[0]}'})

    return metric_results

def search_all_results(log_files_paths, test_files_paths):
    results = {"results": []}
    matches = []

    # Update dictionary with list of logs and tests files
    results.update({"logs": [os.path.splitext(os.path.basename(log_file_path))[0] for log_file_path in log_files_paths]})
    results.update({"tests": [os.path.splitext(os.path.basename(test_file_path))[0] for test_file_path in test_files_paths]})

    # Find the matching pairs stored as tuple
    matches = [(log_file_path, os.path.splitext(os.path.basename(test_file_path))[0]) \
                for log_file_path in log_files_paths for test_file_path in test_files_paths \
                if os.path.splitext(os.path.basename(test_file_path))[0] in log_file_path]

    # Traverse matches
    for pair in matches:
        # Append to list of 'results' key with test file as key and dictionary
        # of metric results as the value
        results["results"].append({pair[1]: search_metric_results(pair[0])})

    return results

def write_to_json(data_dict, dir_path, file_name="results"):
    
    # Write json file as text file
    with open(os.path.join(dir_path, f"{file_name}.json"), "wt") as f:
        json.dump(data_dict, f, indent=4)   # indent by 4 to represent data clearly

    return

def main(args):
    cwd = os.getcwd()

    target_dir = Path(args.t)   # create a path using the t argument in parser
    
    # Check IF directory doesn't exist
    if not target_dir.exists():
        os.mkdir(os.path.join(cwd, target_dir))    # create target directory
    
    # retrieve lists of paths
    logs_paths, tests_paths = find_file_paths()

    # find the data from both lists of paths
    results = search_all_results(logs_paths, tests_paths)

    # create json file in target directory
    write_to_json(results, target_dir) 
 
    return

if __name__ == "__main__":

    parser = argparse.ArgumentParser(prog='', description='Parses           \
            results from each log file with respect to their test files and \
            produces a json file')

    parser.add_argument('-t', metavar='dir', type=str, nargs='?',           \
            const='results', default='test_results', help='A directory name \
            that exists or to be created where the json file produced will  \
            reside')

    # Check IF no argument passed
    if len(sys.argv) == 1:
        parser.print_help(sys.stderr)
        sys.exit(1)

    main(parser.parse_args())
