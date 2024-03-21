import os
import json
import glob
import pprint
import shutil
import subprocess
from atomic_parser import *
from regex_patterns import *
from dynamicHarnessGenerator import *
from datetime import datetime
from reconfigureMain import *

class dynamicEndPointProcessing:
    def __init__(self, filename): 
        # self.path = path
        self.filename = filename
        self.directory_name = ""
        self.output_dir = ""
        self.curdir = ""
        self.currundir = ""
        self.workingPath = ""
        self.assertionList = list()
        self.location = ""
        self.scriptPath = ""
    
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
    
    def generateMakefile(self, path):
        # makefile_content = """
        # test: clean dynamicSynthesis.cpp
        # \tg++ -std=c++14 -pthread dynamicSynthesis.cpp -o dynamicSynthesis && ./dynamicSynthesis
        # clean:
        # \trm -f dynamicSynthesis
        # """
        makefile = "Makefile"
        makefilePath = os.path.join(path, makefile)
        with open(makefilePath, "w") as makefilehandle:
            makefilehandle.write("test1:\n\t@echo 'running test'\n")
            makefilehandle.write("test: clean dynamicSynthesis.cpp\n")
            makefilehandle.write("\tg++ -std=c++14 -pthread dynamicSynthesis.cpp -o dynamicSynthesis && ./dynamicSynthesis\n")
            makefilehandle.write("clean:\n")
            makefilehandle.write("\trm -f dynamicSynthesis\n")
        makefilehandle.close()

        result = subprocess.run(["make", "test"], capture_output=True, text=True, cwd=path)
        if result.returncode == 0:
            print("Makefile test target executed successfully.")
            print("Output:", result.stdout)
        else:
            print("Error executing Makefile test target:")
            print("Error message:", result.stderr)

    def extract_assertion_source(self, filename):
        f_contents = open(filename, 'r')
        f_contents_body = f_contents.read()
        matches = re.findall(assertion_pat_dyn, f_contents_body, re.MULTILINE)
        for match in matches:
            self.assertionList.append(match)
    
    def fileCleanUp(self):
        # copy the created dynamic synthesis file to the outputs directory inside rundir
        self.workingPath = os.path.join(self.output_dir, "dynamicSynthesis.cpp")
        filePath = os.path.join(self.curdir, "dynamicSynthesis.cpp")
        shutil.copy(filePath, self.workingPath)

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
        self.extract_assertion_source(self.workingPath)
    
    def trimPath(self, path, levels):
        if(levels == 5):
            return os.path.normpath(os.path.join(path, '..', '..',"..","..",".."))
        elif(levels == 4):
            return os.path.normpath(os.path.join(path, '..', '..',"..",".."))

    def cleanMain(self):
        remove_main_function(self.workingPath)
        currentPath = self.workingPath
        targetPath = self.trimPath(currentPath,5)
        targetPath = targetPath + "/scripts/interleavings.txt"
        shutil.copy(targetPath,self.output_dir)
    
    def createInterleavingRuns(self):
        interleavingFilePath = self.output_dir + "/interleavings.txt"
        schedulingList = []
        with open(interleavingFilePath, 'r') as file:
            for line in file:
                schedulingList.append(line.rstrip('\n'))
        for inner_list in schedulingList:
            current_sequence = inner_list
            concatenated_string = ''.join(str(item) for item in inner_list)
            newstring1 = concatenated_string.replace(" ","")
            newstring2 = newstring1.replace(",","")
            newstring3 = newstring2.replace("[","")
            newstring4 = newstring3.replace("]","")
            interleavingName = "sequence:" + str(newstring4)
            self.location = self.currundir + '/output/' + interleavingName
            os.makedirs(self.location, exist_ok=True)
            sourceWithoutMain = self.workingPath
            shutil.copy(sourceWithoutMain,self.location)

            # create main here
            createMain(self.location, current_sequence, self.assertionList)
            self.generateMakefile(self.location)



            


# def main():
#     obj = dynamicEndPointProcessing('spec4agent.cpp')
#     obj.processDynamicTestHarness()
#     obj.fileCleanUp()

# if __name__ == '__main__':
#     main()