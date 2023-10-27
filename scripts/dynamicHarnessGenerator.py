import os
import json
import shutil
import pprint
from atomic_parser import *
from regex_patterns import *
from datetime import datetime

class DynamicParser:
    def __init__(self, rundir, curdir, filename): 
        self.rundir = rundir
        self.curdir = curdir
        self.filename = filename
        self.mutexDict = dict()
        self.mutexList = list()
        self.agentList = list()

    def file_read(self):
        if (not self.filename.endswith('.cpp')) and (not self.filename.endswith('.cc')):
            print('Only files ending in .cpp or .cc should be given')
            exit(0)
        try:
            with open(os.path.join(self.rundir, self.filename), 'r') as file:
                f_contents = file.read()
        except FileNotFoundError:
            print(self.path, self.filename)
            print('File not found')
            return None
        except AttributeError:
            print('There is only commented code')
        else:
            return f_contents
    
    # def get_current_time_and_date(self):
    #     current_time = datetime.now().strftime("%H:%M:%S")
    #     current_date = datetime.now().strftime("%Y-%m-%d")
    #     return current_date, current_time
    
    # def createWorkdir(self):
    #     """
    #     This creates a new directory with the name (currentDate:::currentTime) and all files are dumped in this directory
    #     """
    #     currentDate, currentTime = self.get_current_time_and_date()
    #     self.directory_name = "Dynamic:::" + currentDate + ":::" + currentTime
    #     os.makedirs(self.directory_name, exist_ok=True)
    #     print("[LOG] Dynamic Working directory --> ",self.directory_name)
    
    def parseFile(self):
        # self.createWorkdir()
        atomicParser = Parser(self.rundir, self.curdir, self.filename)
        atomicParser.module_extractor()
        atomicParser.displayFunctionTree()
        for key in atomicParser.functionTree:
            mutexName = key + "_lock"
            self.mutexDict[key] = mutexName
            self.mutexList.append(mutexName)
            self.agentList.append(key)
        dynamicTestFile = "dynamicSynthesis.cpp"
        file_path = os.path.join(self.rundir, dynamicTestFile)
        with open(file_path, "w") as resultFile:
            with open(self.filename) as file:
                f_contents = file.readlines()
                i = 0
                for line in f_contents:
                    if "../../../../headers/SPARC_HEADER.h" in line:
                        # Mutex instantiation for all agents in the specification
                        for item in self.mutexList:
                            line = line + "mutex " + item + ';' + '\n'
                    for index, value in enumerate(self.agentList):
                        value = value + "(){"
                        if value in line:
                            currentPointer = index
                    if "//atomic_init" in line:
                        line = '\n'  + "    "  + self.mutexList[currentPointer] + ".lock();" + '\n'
                    if "//atomic_end" in line:
                        line = "    "  + self.mutexList[currentPointer] + ".unlock();" + '\n'
                        
                    # replace wait contruct with while statement in the source file
                    if(re.search(wait_pat, line)):
                        line = "    " + atomicParser.flattenedWhileStatement[i] + '\n'
                        i = i + 1
                    
                    # drop //-- decoration and synthesize assertions in the source file 
                    if(re.search(dropslash_assertion, line)):
                        line = re.sub(dropslash_assertion, "", line)
                    
                    # drop // decoration from history and prophecy variables
                    if(re.search(dropslash, line)):
                        line = re.sub(dropslash, "__", line)
                    
                    # write updated lines to a new dynamic synthesis file
                    resultFile.write(line)
                    
                    # resultFile.close()
                    
                    
            
    
# def main():
#     obj = DynamicParser('/home/klee/klee_src/examples/v0.1release', 'test_pattern.cpp')
#     obj.parseFile()
   
# if __name__ == '__main__':
#     main()