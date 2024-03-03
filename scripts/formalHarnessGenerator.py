import os
import json
import pprint
import random
from atomic_parser import *
from regex_patterns import *
from datetime import datetime

class queueGenerator:
    def __init__(self, curdir, rundir, filename, queueSize, interactingPattern): 
        self.curdir = curdir
        self.rundir = rundir
        self.filename = filename
        self.initial_state_map = dict()
        self.directory_name = ""
        self.queueSize = queueSize
        self.interactingPattern = interactingPattern

    def validateInteractingPattern(self, interactingPattern, numberofAgents):
        for index in range(len(interactingPattern)):
            if interactingPattern[index] > numberofAgents:
                print("[SPARC] : Invalid input in interacting pattern:", interactingPattern[index])
                exit(0)
    
    def entityTemplateGenerator(self):
        atomicParser = Parser(self.curdir, self.rundir, self.filename)
        atomicParser.module_extractor()
        atomicParser.displayFunctionTree()
        formalTestFile = "klee_sim.cpp"
        output_formal_file = self.rundir + '/output/'
        debug_log_files_dump = self.rundir + '/debug/'
        file_path = os.path.join(output_formal_file, formalTestFile)
        print("[SPARC] : Formal synthesis directory : ",self.rundir)
        with open(file_path, "w") as file:
            """
            --> Write the header files from the source file to the test harness
            """
            self.directory_name = atomicParser.directory_name
            headerPath = os.path.join(atomicParser.directory_name, "header_contents.txt")
            with open(headerPath, "r") as headerHandle:
                headerContents = headerHandle.read()
                file.write("/*\n")
                file.write("--> Headers from concurrent source file\n")
                file.write("*/\n")
                file.write(headerContents)
                file.write('\n')
                file.write("#define SINGLE_ENTRY_POINT 1\n")
                file.write('\n')
                file.write('using namespace std;\n')
            """
            --> Auto generated entity and class and object instantiations based on SSEL-provided classes and constructs
            """
            file.write('\n')
            file.write("/*\n")
            file.write("--> Entity class object instantiation\n")
            file.write("*/\n")
            for key, value in atomicParser.class_definition.items():
                file.write(value + "* " + key + " = " + "new " + value + ";\n")
            file.write('\n')
            
            """
            --> Auto generated events
            """
            file.write("/*\n")
            file.write("--> Auto generated events\n")
            file.write("*/\n")
            for item in atomicParser.eventlist:
                file.write(item)
                
            """
            --> Auto generated Assertion Variables
            """
            file.write("/*\n")
            file.write("--> Auto generated assertion variables\n")
            file.write("*/\n")
            for item in atomicParser.assertionvariables:
                file.write(item)
            
            """
            --> Auto generated function template for all entities declared in the concurrent source file 
            --> Template of Abstract Syntax Tree of Function Tree:
            {
                key: [ return type,
                       [function arguments],
                       function body,
                       function body file name,
                       processID
                       [atomic block file names],
                       count of atomic blocks,
                       formal process name]
            }
            """
            file.write('\n')
            file.write("/*\n")
            file.write("--> Specification Entity Blocks\n")
            file.write("*/\n")
            file.write('\n')
            for item in atomicParser.functionTree:
                atomicCounter = 1
                file.write("// --> " + atomicParser.functionTree[item][7] + " instance\n")
                file.write(atomicParser.functionTree[item][0] + " " + atomicParser.functionTree[item][7] + "(queue<int> queue_inst){\n")
                file.write("    if(queue_inst.size() == 0){\n")
                file.write("        return;\n")
                file.write("    }\n")
                file.write("    int instruction = queue_inst.front();\n")
                file.write("    switch(instruction){\n")
                """
                --> The below code places the atomic blocks inside the corresponding process instance in the order they
                    were declared in the specification
                """
                for count in range(atomicParser.functionTree[item][6]):
                    file.write("        case " + str(atomicCounter) + ":\n")
                    atomic_file_path = os.path.join(atomicParser.directory_name, atomicParser.functionTree[item][5][count])
                    with open(atomic_file_path, "r") as atomicHandle:
                        atomicContent = atomicHandle.readlines()
                        AtomicElementLineLength = len(atomicContent)
                        linecounter = 0
                        for line in atomicContent:
                            if line in atomicParser.flattenedWaitStatement:
                                for index in range(len(atomicParser.flattenedWaitStatement)):
                                    if atomicParser.flattenedWaitStatement[index] == line:
                                        file.write("            if(" + atomicParser.flattenedFormalWhiletoIf[index] + "){\n")
                                        linecounter = linecounter + 1
                                        if (AtomicElementLineLength == linecounter):
                                            file.write("                queue_inst.pop();\n")
                                        if (AtomicElementLineLength == linecounter):
                                            if atomicCounter != atomicParser.functionTree[item][6]:
                                                file.write("                queue_inst.push(" + str(atomicCounter + 1) + ");\n")
                                        file.write("            }\n")
                                        file.write("            else{\n")
                                        file.write("                // return back to existing instruction {case: " + str(atomicCounter) + "}\n")
                                        file.write("            }\n")
                            else:
                                file.write("                " + line)
                                linecounter = linecounter + 1
                                if (AtomicElementLineLength == linecounter):
                                    file.write('\n')
                                    file.write("                queue_inst.pop();\n")
                                if (AtomicElementLineLength == linecounter):
                                    if atomicCounter != atomicParser.functionTree[item][6]:
                                        file.write("                queue_inst.push(" + str(atomicCounter + 1) + ");\n")
                        atomicCounter = atomicCounter + 1
                file.write("    }\n")  
                file.write("}\n")
                file.write('\n')
                
            """
            --> Main test harness structure generation starts here
            """
            file.write("/*\n")
            file.write("--> Main test harness and Symbolic Test Function\n")
            file.write("*/\n")
            file.write("int main(){\n")
            file.write("    int process_ID;\n")
            file.write("    int common_initial_state = SINGLE_ENTRY_POINT;\n")
            
            """
            --> Declare and establish queues for each entity in the function tree
            """
            for key in atomicParser.functionTree:
                if atomicParser.functionTree[key][6] > 1:
                    common_state_symbolic = key + "_initial_state"
                    common_state = key + "_initial_state" + ";\n"
                    self.initial_state_map[key] = common_state_symbolic
                    file.write("    int " + common_state)
                queue_name = key + "_queue"
                file.write("    queue<int> " + queue_name + ";\n")
                file.write("    " + queue_name + ".push(common_initial_state);\n")
            for key in atomicParser.functionTree:
                file.write("    " + atomicParser.functionTree[key][7] + "(" + key + "_queue);\n")
            
            """
            --> Generate symbolic execution test platform for KLEE Engine
            """
            file.write('\n')
            file.write("/*\n")
            file.write("--> Symbolic execution test platform\n")
            file.write("*/\n")
            # calculate the size of queue based on number of agents (HW or SW) in the specification
            # queue size is number of agents + 2
            #TODO Add limit message to formal validation scalability
            numberofAgents = len(atomicParser.functionTree)
            # If interacting pattern is specified, the populate the queue with the interacting pattern
            # else, populate the queue with random process IDs
            uniqueProcesses = []
            if (len(self.interactingPattern) > 0):
                print("Interacting pattern is specified")
                self.validateInteractingPattern(self.interactingPattern, numberofAgents)
                queueSize = len(self.interactingPattern)
                file.write("    int interactingPattern[" + str(queueSize) + "] = {")
                for index in range(len(self.interactingPattern)):
                    file.write(str(self.interactingPattern[index]))
                    if(index != len(self.interactingPattern) - 1):
                        file.write(", ")
                file.write("};\n")
                file.write("    int schedular_queue_size = " + str(queueSize) + ";\n")
                file.write("    queue<int> scheduler_queue;\n")
                file.write("    for(int i = 0; i<schedular_queue_size; i++)\n")
                file.write("        scheduler_queue.push(interactingPattern[i]);\n")
                file.write("\n");
            
                # Only include processes that are in the interacting pattern
                uniqueProcesses = set(sorted(self.interactingPattern))

                file.write("    while(!scheduler_queue.empty()){\n")
                file.write("        process_ID = scheduler_queue.front();\n")
                file.write("        scheduler_queue.pop();\n")
                firstStatement = True # First statement uses if, the rest use else if
                for processId in uniqueProcesses:
                    for key in atomicParser.functionTree:
                        if(atomicParser.functionTree[key][6] > 1 and atomicParser.functionTree[key][4] == processId):
                            if firstStatement:
                                file.write("        if(process_ID == " + str(atomicParser.functionTree[key][4]) + "){\n")
                                firstStatement = False
                            else:
                                file.write("        else if(process_ID == " + str(atomicParser.functionTree[key][4]) + "){\n")
                            file.write('            klee_make_symbolic(&' + self.initial_state_map[key] + ', sizeof(' + self.initial_state_map[key] + '), "' + self.initial_state_map[key] + '");\n')
                            file.write('            if(' + self.initial_state_map[key] + ' == ' + str(random.randrange(1, atomicParser.functionTree[key][6])) + '){\n')
                            file.write('                ' + key + '_queue.push(' + self.initial_state_map[key] + ');\n')
                            file.write('                ' + atomicParser.functionTree[key][7] + '(' + key + '_queue);\n')
                            file.write('             }\n')
                            file.write('        }\n')
                file.write('    }\n')

            else:
                file.write("    int schedular_queue_size;\n")
                file.write("    int rand_processID;\n")
                file.write('    klee_make_symbolic(&schedular_queue_size, sizeof(schedular_queue_size), "schedular_queue_size");\n')
                
                queueSizeMin = numberofAgents
                if(numberofAgents<=3):
                    queueSizeMin = numberofAgents
                else:
                    queueSizeMin = numberofAgents - 2
                # queueSizeMax = numberofAgents + 2 # unused. Queue Max bound is now passed through a user-input using the configuration file
                file.write("    klee_assume((schedular_queue_size>=" + str(queueSizeMin) + ") & (schedular_queue_size<=" + str(self.queueSize) + "));\n")  
                file.write("    queue<int> scheduler_queue;\n")
                
                file.write("    for(int i = 0; i<schedular_queue_size; i++){\n")
                file.write('        klee_make_symbolic(&rand_processID, sizeof(rand_processID), "rand_processID");\n')
                # rand_pID = random.randint(1,len(atomicParser.functionTree))
                pID_upperBound = len(atomicParser.functionTree) + 1
                file.write("        klee_assume(rand_processID<=" + str(pID_upperBound) + " & rand_processID>0);\n") 
                file.write("        scheduler_queue.push(rand_processID);\n")
                file.write("    }\n")
                file.write("\n")
            
                file.write("    while(!scheduler_queue.empty()){\n")
                file.write("        process_ID = scheduler_queue.front();\n")
                file.write("        scheduler_queue.pop();\n")
                symbolic_loop_counter = 0
                for key in atomicParser.functionTree:
                    if(atomicParser.functionTree[key][6] > 1):
                        if(symbolic_loop_counter == 0):
                            file.write("        if(process_ID == " + str(atomicParser.functionTree[key][4]) + "){\n")
                            symbolic_loop_counter = symbolic_loop_counter + 1
                        else:
                            file.write("        else if(process_ID == " + str(atomicParser.functionTree[key][4]) + "){\n")
                        file.write('            klee_make_symbolic(&' + self.initial_state_map[key] + ', sizeof(' + self.initial_state_map[key] + '), "' + self.initial_state_map[key] + '");\n')
                        file.write('            if(' + self.initial_state_map[key] + ' == ' + str(random.randrange(1, atomicParser.functionTree[key][6])) + '){\n')
                        file.write('                ' + key + '_queue.push(' + self.initial_state_map[key] + ');\n')
                        file.write('                ' + atomicParser.functionTree[key][7] + '(' + key + '_queue);\n')
                        file.write('             }\n')
                        file.write('        }\n')
                file.write('    }\n')
            
            """
            --> Assertion placement in the test harness
            """
            # If interacting pattern is specified, only include processes that are in the interacting pattern
            if len(uniqueProcesses) > 0:
                relevant_assertions = []
                for key in atomicParser.functionTree:
                    if(atomicParser.functionTree[key][4] in uniqueProcesses):
                        relevant_assertions.extend(atomicParser.functionTree[key][8])
                for value in atomicParser.assertionList:
                    matches = re.findall('__assertion__\w+', value)
                    if (all(assertion in relevant_assertions for assertion in matches)):
                        file.write(' ' + str(value) + '\n')
            else:
                for value in atomicParser.assertionList:
                    file.write(' ' + str(value) + '\n')
            file.write('  return 0;\n')
            file.write('}')
            file.close()
 
# def main():
#     obj = queueGenerator('/home/klee/klee_src/examples/v0.1release', 'test_pattern.cpp')
#     obj.entityTemplateGenerator()

# if __name__ == '__main__':
#     main()