import os
import json
import shutil
import pprint
from atomic_parser import *
from regex_patterns import *
from dynamicHarnessGenerator import *
from datetime import datetime

class dynamicEndPointProcessing:
    def __init__(self, path, filename): 
        self.path = path
        self.filename = filename
        self.directory_name = ""
    
    def processDynamicTestHarness(self):
        dynamicTest = DynamicParser(self.path, self.filename)
        dynamicTest.parseFile()
        self.directory_name = dynamicTest.directory_name
        workingPath = os.path.join(self.path, "dynamicSimulation.cpp")
        filePath = os.path.join(self.directory_name, "dynamicSimulation.cpp")
        shutil.copy(filePath, workingPath)

def main():
    obj = dynamicEndPointProcessing('/home/klee/klee_src/examples/v0.1release', 'test_pattern.cpp')
    obj.processDynamicTestHarness()

if __name__ == '__main__':
    main()