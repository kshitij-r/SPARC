import os
import json
import glob
import pprint
import shutil
from atomic_parser import *
from regex_patterns import *
from dynamicHarnessGenerator import *
from datetime import datetime

class dynamicEndPointProcessing:
    def __init__(self, filename): 
        # self.path = path
        self.filename = filename
        self.directory_name = ""
        self.output_dir = ""
        self.curdir = ""
        self.currundir = ""
    
    def get_current_time_and_date(self):
        current_time = datetime.now().strftime("%H:%M:%S")
        current_date = datetime.now().strftime("%Y-%m-%d")
        return current_date, current_time

    def create_rundir(self):
        self.get_current_time_and_date()
        self.curdir = os.path.abspath(os.path.curdir)
        currentDate, currentTime = self.get_current_time_and_date()
        self.directory_name = "rundir-d:::" + currentDate + ":::" + currentTime
        os.makedirs(self.directory_name, exist_ok=True)
        self.currundir = self.curdir + '/'+ self.directory_name
        self.output_dir = self.currundir + '/output'
        os.makedirs(self.output_dir, exist_ok=True)
        return self.curdir, self.currundir
    
    def processDynamicTestHarness(self):
        curdir, currundir = self.create_rundir()
        print("[SPARC] : Dynamic synthesis directory : ", currundir)
        dynamicTest = DynamicParser(curdir, currundir, self.filename)
        dynamicTest.parseFile()
    
    def generateMakefile(self):
        makefile = "Makefile"
        makefilePath = os.path.join(self.output_dir, makefile)
        with open(makefilePath, "w") as makefilehandle:
            makefilehandle.write("# Dynamic synthesis of generated specification\n")
            makefilehandle.write("test: clean dynamicSynthesis.cpp\n")
            makefilehandle.write('\t' + "g++ -std=c++14 -pthread dynamicSynthesis.cpp -o dynamicSynthesis && ./dynamicSynthesis\n")
            makefilehandle.write("clean:\n")
            makefilehandle.write('\t' + "rm -f dynamicSynthesis")

    def fileCleanUp(self):
        self.generateMakefile()
        # copy the created dynamic synthesis file to the outputs directory inside rundir
        workingPath = os.path.join(self.output_dir, "dynamicSynthesis.cpp")
        filePath = os.path.join(self.curdir, "dynamicSynthesis.cpp")
        shutil.copy(filePath, workingPath)

        # delete the intermediate .txt and .cpp files
        removeIntermediateFileMain = self.curdir + "/dynamicSynthesis.cpp"
        removeIntermediateFileIntermediate = self.curdir + "/dynamicSynthesisSource.cpp"
        os.remove(removeIntermediateFileMain)
        os.remove(removeIntermediateFileIntermediate)

        txt_files_pattern = os.path.join(self.curdir, "*.txt")
        txt_files = glob.glob(txt_files_pattern)
        if txt_files:
            for file in txt_files:
                os.remove(file)
        else:
            pass 

# def main():
#     obj = dynamicEndPointProcessing('spec4agent.cpp')
#     obj.processDynamicTestHarness()
#     obj.fileCleanUp()

# if __name__ == '__main__':
#     main()