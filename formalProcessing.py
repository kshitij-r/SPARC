import os
import json
import pprint
import random
from atomic_parser import *
from formalHarnessGenerator import *
from regex_patterns import *
from datetime import datetime

class endPointProcessing:
    def __init__(self, path, filename): 
        self.path = path
        self.filename = filename
        self.directory_name = ""
        self.whileMap = dict()
    
    def processFormalTestHarness(self):
        formalTest = queueGenerator(self.path, self.filename)
        formalTest.entityTemplateGenerator()
        self.directory_name = formalTest.directory_name
        # test_path = os.path.join(self.path, "formalSynthesisHarness.cpp")
        # file_path = os.path.join(self.directory_name, "klee_sim.cpp")
        # with open(test_path, "w") as testFile:
        #     output_content = []
        #     with open (file_path, "r") as file:
        #         f_contents = file.read()
        #         matches = re.findall(whilepattern, f_contents)
        #         for condition, body in matches:
        #             print("Condition:", condition.strip())
        #             print("Body:", body.strip())
                
        #         f_contents_list = file.readlines()
        #         for line in f_contents_list:
        #             print(line)
        #             # if "while" in line:
        #             #     print("-----------")
                    
                
    
def main():
    obj = endPointProcessing('/home/klee/klee_src/examples/v0.1release', 'test_pattern.cpp')
    obj.processFormalTestHarness()

if __name__ == '__main__':
    main()