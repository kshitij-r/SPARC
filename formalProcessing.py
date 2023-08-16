import os
import json
import shutil
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
        workingPath = os.path.join(self.path, "formalSynthesisHarness.cpp")
        filePath = os.path.join(self.directory_name, "klee_sim.cpp")
        shutil.copy(filePath, workingPath)
        # with open(workingPath, "w") as testFile:
        #     with open (filePath, "r") as file:
        #         f_contents = file.read()
        #         matches = re.findall(whilepattern, f_contents, re.DOTALL)
        #         # print(matches)
        #         for condition, body in matches:
        #             if(condition != "!scheduler_queue.empty()"):
        #                 loopcondition = condition.strip()
        #                 loopbody = body.strip()
        #                 print(loopcondition, loopbody)
        #                 whiletoif = "           if(" + loopcondition + "){\n" + loopbody + "\n          }\n           else {}\n"
        #                 re.sub(whilepattern, whiletoif, f_contents, 1, flags=re.DOTALL)
        #                 print(f_contents)
                # testFile.write(f_contents)

def main():
    obj = endPointProcessing('/home/klee/klee_src/examples/v0.1release', 'test_pattern.cpp')
    obj.processFormalTestHarness()

if __name__ == '__main__':
    main()