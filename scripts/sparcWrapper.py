import os
import json
from dynamicSimulation import *
from formalProcessing import *

class sparcProcessConfiguration:
    def __init__(self):
        self.curdir = ""
        self.filename = "config.json"
        self.orgSpecFile = ""
        self.configFile = {}
        self.dynamicValidation = False
        self.formalValidation = False
        self.queueSize = 0
        self.z3 = False
        self.interactingPattern = ""
    
    def printToolInputs(self):
        print("[SPARC] : Tool flags provided by user: \n")
        for key, value in self.configFile.items():
            print(key, ":", value)
    
    def runDynamicValidation(self):
        dynamicobj = dynamicEndPointProcessing(self.orgSpecFile)
        dynamicobj.processDynamicTestHarness()
        dynamicobj.fileCleanUp()
        consolemessage = "[SPARC] : Dynamic synthesis configuration of user-defined configuration file: '" + str(self.orgSpecFile + "' complete " + '\n')
        print(consolemessage)   

    def runFormalValidation(self):
        formalobj = endPointProcessing(self.orgSpecFile, self.queueSize, self.z3, self.interactingPattern)
        formalobj.create_rundir()
        formalobj.processFormalTestHarness()
        consolemessage = "[SPARC] : Formal synthesis configuration of user-defined configuration file: '" + str(self.orgSpecFile + "' complete " + '\n')
        print(consolemessage)  

    def parseConfig(self):
        self.curdir = os.path.abspath(os.path.curdir)
        try:
            f = open("config.json")
            self.configFile = json.load(f)
            for key, value in self.configFile.items():
                if(key == "org_specification_file"):
                    self.orgSpecFile = value
                if(key == "dynamicValidation"):
                    self.dynamicValidation = value
                if(key == "formalValidation"):
                    self.formalValidation = value
                if(key == "queueSize"):
                    self.queueSize = value
                if(key == "z3Solver"):
                    self.z3 = value
                if(key == "interactingPattern"):
                    self.interactingPattern = [int(char) for char in value]
        except FileNotFoundError:
            print(self.curdir, self.filename)
            print('File not found')
        self.printToolInputs()


        if(self.dynamicValidation):
            self.runDynamicValidation()
        
        if(self.formalValidation):
            self.runFormalValidation()

def main():
    obj = sparcProcessConfiguration()
    obj.parseConfig()

if __name__ == '__main__':
    main()