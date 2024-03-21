from atomic_parser import *
from regex_patterns import *

def remove_main_function(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    start_index = None
    end_index = None
    in_main_function = False

    for i, line in enumerate(lines):
        if 'int main' in line or 'void main' in line:
            start_index = i
            in_main_function = True
        elif in_main_function and '{' in line:
            # Assuming opening bracket of main function is on the same line
            start_index = None
        elif in_main_function and '}' in line:
            end_index = i
            break

    if start_index is not None and end_index is not None:
        del lines[start_index:end_index+1]

        with open(file_path, 'w') as file:
            file.writelines(lines)
        # print("Main function removed successfully.")
    else:
        print("Main function not found.")

def createMain(path, listPattern, assertionList):
    assertion = assertionList
    agentMap = {
        1: "userInputDriver",
        2: "dcPowerSupplyDriver",
        3: "userInterfaceDriver",
        4: "swDriver",
        5: "dcMotorDriver",
        6: "tempMonitorDriver",
        7: "rpmMonitorDriver"
    }
    currentPath = path
    sequence = listPattern
    filtered_list = [x for x in sequence if x != '[' and x != ' ' and x != ']' and x != ',']
    fileToOpen = currentPath + "/dynamicSynthesis.cpp"
    try:
        with open(fileToOpen, 'a') as file:
            firstEntry = True
            file.write("\n")
            file.write("// Scheduling harness\n")
            file.write("int main(){\n")
            file.write("    queue<int> scheduling_queue;\n")
            file.write("    int process_ID;\n")
            for item in filtered_list:
                string = "    scheduling_queue.push(" + str(item) + ");\n"
                file.write(string)
            file.write("    while(!scheduling_queue.empty()){\n")
            file.write("        process_ID = scheduling_queue.front();\n")
            file.write("        scheduling_queue.pop();\n")
            for item in filtered_list:
                if(firstEntry):
                    file.write("        if(process_ID == " + str(item) + "){\n")
                    threadToSchedule = "            " + str(agentMap[int(item)]) + "();\n"
                    file.write(threadToSchedule)
                    file.write("            }\n")
                    firstEntry = False
                else:
                    file.write("        else if(process_ID == " + str(item) + "){\n")
                    threadToSchedule = "            " + str(agentMap[int(item)]) + "();\n"
                    file.write(threadToSchedule)
                    file.write("            }\n")
            file.write("    }\n")

            # Place assertions in the main function
            """
            --> Assertion placement in the test harness
            """
            file.write("/*\n")
            file.write("--> Assertions\n")
            file.write("*/\n")
            for value in assertion:
                file.write(' ' + str(value) + '\n')
            file.write("    return 0;\n")
            file.write("}")
            file.close()
    except Exception as e:
        print("Error:", e)
