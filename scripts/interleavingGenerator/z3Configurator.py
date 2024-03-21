import os
import json

class z3configurator:
    def __init__(self):
        self.curdir = ""
        self.filename = "constraint.json"
        self.configFile = {}
        self.length = 0
        self.numAgents = 0;
        self.agentID = []
        self.order = []
        self.clause = {}
    
    def parseConfig(self):
        self.curdir = os.path.abspath(os.path.curdir)
        try:
            f = open("constraint.json")
            self.configFile = json.load(f)
            for key, value in self.configFile.items():
                if(key == "count"):
                    self.length = value
                if(key == "num_agents"):
                    self.numAgents = value
                if(key == "agentIDs"):
                    self.agentID = value
                if(key == "clause"):
                    self.order = value
            for index, sublist in enumerate(self.order):
                key = 'clause{}'.format(index + 1)
                self.clause[key] = sublist
        except FileNotFoundError:
            print(self.curdir, self.filename)
            print('File not found')
    
    def createZ3configurator(self):
        configFile = "z3Gen.py"
        configFilePath = os.path.join(self.curdir, configFile)
        with open(configFile, "w") as handle:
            handle.write("from z3 import *\n")
            handle.write("\n")
            handle.write("def interleaving_with_constraints(number_list):\n")
            handle.write("# Create Z3 solver\n")
            handle.write("  solver = Solver()\n")
            handle.write("\n")
            handle.write("  # Create variables for each number in the list\n")
            handle.write('  numbers = [Int(f"num{i}") for i in range(len(number_list))]\n')
            handle.write("\n")
            handle.write("  # Add constraints to ensure each number is selected from the list\n")
            handle.write("  for i, number in enumerate(numbers):\n")
            handle.write("      solver.add(Or([number == n for n in number_list]))\n")
            handle.write("\n")
            for key, value in self.clause.items():
                commentString = "   # Adding a constraint for " + str(key) + "\n"
                handle.write(   commentString)
                firstobject = "  " + str(key) + "_low = number_list.index(" + str(value[0]) + ")\n"
                handle.write(firstobject)
                secondobject = "  " + str(key) + "_high = number_list.index(" + str(value[1]) + ")\n"
                handle.write(secondobject)
                solverString = "  solver.add(numbers[" + str(key) + "_low] < numbers[" + str(key) + "_high])\n"
                handle.write(solverString)
                handle.write("\n")
            handle.write("  # Initialize counter for generated numbers\n")
            handle.write("  count = 0\n")
            handle.write("\n")
            handle.write("# Check if the constraints are satisfiable\n")
            strcheck = "  while solver.check() == sat and count < " + str(self.length) + ":\n"
            handle.write(strcheck)
            handle.write("      # Get the satisfying model\n")
            handle.write("      model = solver.model()\n")
            handle.write("      # Extract the selected numbers from the model\n")
            handle.write("      selected_numbers = [model.evaluate(number).as_long() for number in numbers]\n")
            handle.write("      yield selected_numbers\n")
            handle.write("      # Increment counter\n")
            handle.write("      count += 1\n")
            handle.write("      # Add a new constraint to exclude the current solution\n")
            handle.write("      solver.add(Or([numbers[i] != selected_numbers[i] for i in range(len(number_list))]))\n")
            handle.write("\n")
            handle.write("# ID of interacting agents from configuration file\n")
            agentlist = "number_list = " + str(self.agentID) + "\n" 
            handle.write(agentlist)
            handle.write("\n")
            genStringComment = "# Generate and write " + str(self.length) + " interleavings to interleavings.txt\n"
            handle.write(genStringComment)
            handle.write('interleavingFile = "interleavings.txt"\n')
            handle.write("file = os.path.join(interleavingFile)\n")
            handle.write('with open(file, "w") as handle: \n')
            handle.write("  for number in interleaving_with_constraints(number_list):\n")
            handle.write('      sequence = str(number) + "\\n"')
            handle.write("\n")
            handle.write("      handle.write(sequence)\n")

def main():
    obj = z3configurator()
    obj.parseConfig()
    obj.createZ3configurator()

if __name__ == '__main__':
    main()