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
    def __init__(self, filename, queueSize, z3): 
        # self.path = path
        self.filename = filename
        self.directory_name = ""
        self.output_dir = ""
        self.curdir = ""
        self.currundir = ""
        self.whileMap = dict()
        self.queueSize = queueSize
        self.z3 = z3
    
    def get_current_time_and_date(self):
        current_time = datetime.now().strftime("%H:%M:%S")
        current_date = datetime.now().strftime("%Y-%m-%d")
        return current_date, current_time
       
    def create_rundir(self):
        self.get_current_time_and_date()
        self.curdir = os.path.abspath(os.path.curdir)
        currentDate, currentTime = self.get_current_time_and_date()
        self.directory_name = "rundir-f:::" + currentDate + ":::" + currentTime
        os.makedirs(self.directory_name, exist_ok=True)
        self.currundir = self.curdir + '/'+ self.directory_name
        self.output_dir = self.currundir + '/output'
        os.makedirs(self.output_dir, exist_ok=True)
        return self.curdir, self.currundir
    
    def generateMakefile(self):
        makefile = "Makefile"
        makefilePath = os.path.join(self.output_dir, makefile)
        with open(makefilePath, "w") as makefilehandle:
            makefilehandle.write("# Formal synthesis of generated specification\n")
            makefilehandle.write("formalvalidation: clean klee_sim.cpp\n")
            if self.z3:
                makefilehandle.write('\t' + "clang -I ~/klee/include -emit-llvm -c -g klee_sim.cpp && klee -solver-backend=z3 --warnings-only-to-file klee_sim.bc\n")
            else:
                makefilehandle.write('\t' + "clang -I ~/klee/include -emit-llvm -c -g klee_sim.cpp && klee --warnings-only-to-file klee_sim.bc\n")
            makefilehandle.write("clean:\n")
            makefilehandle.write('\t' + "rm -f *.bc")
    
    def processFormalTestHarness(self):
        curdir, currundir = self.create_rundir()
        # print("[SPARC]: ", currundir, self.filename)
        formalTest = queueGenerator(self.curdir, self.currundir, self.filename, self.queueSize)
        formalTest.entityTemplateGenerator()
        self.generateMakefile()
        # self.directory_name = formalTest.directory_name
        # workingPath = os.path.join(self.path, "formalSynthesisHarness.cpp")
        # filePath = os.path.join(self.directory_name, "klee_sim.cpp")
        # shutil.copy(filePath, workingPath)


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

# def main():
#     # obj = endPointProcessing('/Users/pathfinder/Work/Projects/SPARC/klee/examples/SPARC', 'test_pattern.cpp')
#     obj = endPointProcessing('spec4agent.cpp')
#     obj.create_rundir()
#     obj.processFormalTestHarness()

# if __name__ == '__main__':
#     main()