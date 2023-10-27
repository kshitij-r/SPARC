import os
import json
import pprint
from regex_patterns import *
from datetime import datetime

class Parser:
    def __init__(self, curdir, rundir, filename): 
        self.path = curdir
        self.rundir = rundir
        self.filename = filename
        self.tokenMap = dict()
        self.functionTree = dict()
        self.formalFuncID = list()
        self.funcTransformerMap = dict()
        self.directory_name = ""
        self.headers = list()
        self.headerFile = ""
        self.class_definition = dict()
        self.assertionList = list()
        self.eventlist = list()
        self.assertionvariables = list()
        self.waitStatementMap = dict()
        self.flattenedWaitStatement = list()
        self.flattenedWhileStatement = list()
        self.flattenedFormalWhiletoIf = list()
        self.whileStatementMap = dict()
        self.atomicWhileblocks = list()
        self.itemseperatedList = list()
        self.whileStatement = ""
        self.whileCondition = False

    # def file_read(self):
    #     if (not self.filename.endswith('.cpp')) and (not self.filename.endswith('.cc')):
    #         print('Only files ending in .cpp or .cc should be given')
    #         exit(0)
    #     try:
    #         with open(os.path.join(self.path, self.filename), 'r') as file:
    #             f_contents = file.read()
    #     except FileNotFoundError:
    #         print(self.path, self.filename)
    #         print('File not found')
    #         return None
    #     except AttributeError:
    #         print('There is only commented code')
    #     else:
    #         return f_contents

    # def get_current_time_and_date(self):
    #     current_time = datetime.now().strftime("%H:%M:%S")
    #     current_date = datetime.now().strftime("%Y-%m-%d")
    #     return current_date, current_time
    
    def createWorkdir(self):
        """
        This creates a new directory with the name (Test:::currentDate:::currentTime) and all files are dumped in this directory
        """
        # currentDate, currentTime = self.get_current_time_and_date()
        # self.directory_name = "Test:::" + currentDate + ":::" + currentTime
        self.directory_name = self.rundir + "/debug/"
        os.makedirs(self.directory_name, exist_ok=True)
    
    def extract_snippets(self, key, filename):
        agent_body_file = self.directory_name + filename
        f_contents = open(agent_body_file, 'r')
        f_contents_body = f_contents.read()
        f_contents_body = re_dropslash.sub('__', f_contents_body)  
        matches = re.findall(pattern, f_contents_body, re.DOTALL)
        # convert while to if else statements for formal queue
        # for item in matches:
        #     if "while" in item:
        #         self.whileCondition = True
        #         readLine = item.strip()
        #         self.itemseperatedList = readLine.split('\n')
        #         start = "("
        #         end = ")"
        #         start_index = self.itemseperatedList[0].index(start) + len(start)
        #         end_index = self.itemseperatedList[0].index(end, start_index)
        #         self.whileCondition = self.itemseperatedList[0][start_index:end_index]
        #         negationCondition = False
        #         if self.whileStatement.startswith("!"):
        #             negationCondition = True
        #         else:
        #             negationCondition = False
        # print(self.whileStatement, self.whileCondition)
        
        atomicBlockList = []
        atomicBlockCounter = 0
        for i, snippet in enumerate(matches):
            atomicBlockName = "atomicBlock_" + str(i) + "_" + key + ".txt"
            atomicBlockList.append(atomicBlockName)
            atomicBlockCounter = atomicBlockCounter + 1
            file_path = os.path.join(self.directory_name, atomicBlockName)
            with open(file_path, "w") as file:
                file.write(snippet.strip())
        self.functionTree[key].append(atomicBlockList)
        self.functionTree[key].append(atomicBlockCounter)
    
    def extract_class_instance(self, filename):
        f_contents = open(filename, 'r')
        f_contents_body = f_contents.read()
        matches = re.findall(entity_identification_pat, f_contents_body, re.DOTALL)
        for match in matches:
            self.class_definition[match[1]] = match[0]
    
    def extract_events(self, filename):
        f_contents = open(filename, 'r')
        f_contents_body = f_contents.readlines()
        matching_lines = [line for line in f_contents_body if re.search(event_pat, line)]
        for item in matching_lines:
            self.eventlist.append(item)
    
    def extract_assertion_vars(self, filename):
        f_contents = open(filename, 'r')
        f_contents_body = f_contents.readlines()
        matching_lines = [line for line in f_contents_body if re.search(assert_variable, line)]
        for item in matching_lines:
            self.assertionvariables.append(item)
        
    def extract_assertion(self, filename):
        f_contents = open(filename, 'r')
        f_contents_body = f_contents.read()
        matches = re.findall(assertion_pat, f_contents_body, re.MULTILINE)
        for match in matches:
            self.assertionList.append(match)
        
    def generateFormalEntityName(self):
        for key in self.functionTree:
            name = key + "_process"
            self.formalFuncID.append(name)
            self.functionTree[key].append(name)
            """
            --> funcTransformerMap[] contains the mapping of original function names to the transformed
                function name.
            --> funcTransformerMap[] = [transformed name, original parsed name]
            """
            self.funcTransformerMap[key] = name
    
    def extract_headers(self):
        if (not self.filename.endswith('.cpp')) and (not self.filename.endswith('.cc')):
            print('Only files ending in .cpp or .cc should be given')
            exit(0)
        try: 
            with open(os.path.join(self.path, self.filename), 'r') as file:
                f_contents = file.read()
                matches = re.findall(header_pat, f_contents)  # Match lines starting with #include <header> or "header"
                headerFile = "header_contents.txt"
                file_path = os.path.join(self.directory_name, headerFile)
                with open(file_path, "w") as file:
                    for match in matches:
                        headerContent = "#include" + " " + match
                        file.write(headerContent)
                        file.write("\n")
                        self.headers.append(headerContent)
                file.close()
        except FileNotFoundError:
            print(self.path, self.filename)
            print('File not found')
            return None
    
    def extractandParseWaitStatements(self, filename):
        for key, value in self.functionTree.items():
            pre_transformation_match = re.findall(wait_pat, str(value[2]))
            dynamic_wait = ""
            if (len(pre_transformation_match)!=0):
                if key in self.waitStatementMap:
                    self.waitStatementMap[key].append(pre_transformation_match)
                else:
                    self.waitStatementMap[key] = [pre_transformation_match]
                for item in pre_transformation_match:
                    string  = str(item)
                    drop_characters = "();"
                    for char in drop_characters:
                        string = string.replace(char,"")
                    string = string.split("wait__")
                    string.pop(0)
                    negation_pattern = r'!__'
                    if re.search(negation_pattern, string[0]):
                        stripped_string = string[0][1:]
                        dynamic_wait = "while(" + stripped_string + "){};"
                    else:
                        dynamic_wait = "while(!" + string[0] + "){};"
                    if key in self.whileStatementMap:
                        self.whileStatementMap[key].append(dynamic_wait)
                    else:
                        self.whileStatementMap[key] = [dynamic_wait]
        WaitStatementlist = []
        WhileStatementlist = []
        for key, value in self.waitStatementMap.items():
            if isinstance(value, list) and len(value) == 1 and isinstance(value[0], list):
                self.waitStatementMap[key] = value[0]
        
        for val in self.whileStatementMap.values():
            WhileStatementlist.append(val)
        self.flattenedWhileStatement = [item for sublist in WhileStatementlist for item in sublist]
        
        for val in self.waitStatementMap.values():
            WaitStatementlist.append(val)
        self.flattenedWaitStatement = [item for sublist in WaitStatementlist for item in sublist]
        
        for item in self.flattenedWaitStatement:
            matches = re.findall(waitconditionpattern, item)
            self.flattenedFormalWhiletoIf.append(matches)
        self.flattenedFormalWhiletoIf = [item for sublist in self.flattenedFormalWhiletoIf for item in sublist]
        
    def writeWaittoWhileinFile(self):
        sourceFile = "dynamicSynthesisSource.cpp"
        file_path = os.path.join(self.directory_name, sourceFile)
        dynamic_file = open(sourceFile, 'w')
        with open(os.path.join(self.path, self.filename), 'r') as file:
            modified_lines = []
            lines = file.readlines()
            for line in lines:
                for search_value, replace_value in zip(self.flattenedWaitStatement, self.flattenedWhileStatement):
                    if search_value in line:
                        line = line.replace(search_value, replace_value)
                modified_lines.append(line)
            dynamic_file.writelines(modified_lines)
               
    def formalCommentStrip(self):
        for key in self.functionTree:
            updated_value = re.sub(dropslash, '__', self.functionTree[key][2])
            self.functionTree[key][2] = updated_value
    
    def trimfunctionTree(self):
        self.functionTree.pop("main")
    
    def module_extractor(self):
        self.createWorkdir()
        if (not self.filename.endswith('.cpp')) and (not self.filename.endswith('.cc')):
            print('Only files ending in .cpp or .cc should be given')
            exit(0)
        try: 
            with open(os.path.join(self.path, self.filename), 'r') as file:
                f_contents = file.read()
                f_contents = re.sub(threat__start_pat, '' * len(f_contents), f_contents)
                f_contents = re.sub(threat__end_pat, '' * len(f_contents), f_contents)
                for line in f_contents:
                    newfile = None
                    matches = re.findall(FUNC_PATTERN, f_contents, re.DOTALL)
                    processId = 1
                    for match in matches:
                        """
                        --> functionTree format = {function_name: [return type, [argument type and name]], body of function, name of file having function body, processID}
                        """                    
                        return_type, function_name, arguments, function_body = match
                        extractedFunctionBodyName = function_name + "_body.txt"
                        agent_body_dump = self.directory_name + extractedFunctionBodyName
                        newfile = open(agent_body_dump, 'w')
                        if arguments == "":
                            self.functionTree[function_name] = [return_type, [], function_body.strip(), extractedFunctionBodyName, processId]
                            processId = processId + 1
                            newfile.write(function_body.strip())
                            newfile.close()
                        else:
                            self.functionTree[function_name] = [return_type, [arguments.split(',')], function_body.strip(), extractedFunctionBodyName, processId]
                            processId = processId + 1
                            newfile.write(function_body.strip())
                            newfile.close()
            for key in self.functionTree:
                self.extract_snippets(key, self.functionTree[key][3])
            self.extractandParseWaitStatements(self.filename)
            self.writeWaittoWhileinFile()
            self.extract_assertion(self.filename)
            self.trimfunctionTree()
            self.generateFormalEntityName()
            self.extract_headers()
            self.extract_assertion_vars(self.filename)
            self.extract_events(self.filename)
            self.extract_class_instance(self.filename)
            self.formalCommentStrip()
        
        except FileNotFoundError:
            print(self.path, self.filename)
            print('File not found')
            return None
        
    def displayFunctionTree(self):
        file_path = os.path.join(self.directory_name, "functionTree.txt")
        with open(file_path, 'w') as file_name:
            pprint.pprint(self.functionTree, file_name)
            # pprint.pprint(self.functionTree)
            
# def main():
#     obj = Parser('/home/klee/klee_src/examples/SSEL', 'test_pattern.cpp')
#     obj.module_extractor()
#     obj.displayFunctionTree()

# if __name__ == '__main__':
#     main()