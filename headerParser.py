import os
import json
import pprint
from Parser import *
from regex_patterns import *

class HeaderParser:
    def __init__(self, path, filename): 
        self.path = path
        self.filename = filename
        self.headers = list()
        # self.functionTree = dict()
        # self.formalFuncID = list()
        # self.funcTransformerMap = dict()
        # self.directory_name = ""
    
    headerExtract = Parser.file_read()
    # def extract_headers(path):
    #     with open(file_path, 'r') as file:
    #         content = file.read()
    #         matches = re.findall('#include\s+<([^>]+)>', content)  # Match lines starting with #include <header>
    #         for match in matches:
    #             self.headers.append(match)
        
    #     return self.headers

def main():
    obj = HeaderParser('/home/klee/klee_src/examples/SSEL', 'test_pattern.cpp')
    # obj.extract_headers()
    # headers = extract_headers(file_path)
    # for header in headers:
    #     print(header)
   


if __name__ == '__main__':
    main()