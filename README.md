# SPARC : Specification and Analysis of Hardware-Software Interactions
#### Version: 0.1
#### Release Date: August 09, 2023

### A Brief Description:
In SPARC, we used a set of existing constructs from C++ and loops, functions, structures, and data types are used to define the constructs. We augmented SPARC with new data types to account for the binary and hexadecimal nature of the data transferred during on-chip transactions. Since SPARC is designed to provide abstraction of system-level communication, the technical details of various bus protocol implementations
are encapsulated into APIs “baked” into the language abstraction. All inter-IP interactions are oblivious to existing bus implementations to enable reusability of SPARC specifications across platforms and interconnect protocols.
<br>

![Feature Set of an SSEL Agent](Documentation/figures/TechCon%202023%20SSEL/features.png)
Each agent/entity can be derived from the **slave class [slaveconfig.cpp]**. This will be revised in the future to support more base class agent types.

### Requirements
1. This version of SPARC requires C++17 or above to build.
2. KLEE is required for formal analysis of specifications generated using SPARC. It can be downloaded by clicking [here](https://klee.github.io/). The Docker version of KLEE should be prefered.
### SPARC Setup Guide
Once the KLEE setup has been completed, the following sequence of steps need to be followed: <br>
1. Attach your shell to the KLEE Docker container. 
2. Enter the following directory and make clone this repository.
```C++
cd /home/klee/klee_src/examples
``` 
3. Clone the SPARC repository at this location.
### SPARC Synthesis Guide
SPARC supports two modes of specification synthesis: (1) Dynamic synthesis, (2) Formal synthesis.
#### Dynamic synthesis
Once the system specification is complete, follow the below steps:
1. To generate the synthesis harness using SPARC:
```C++
make dynamicHarness
``` 
This generates a test harness file (dynamicSimulation.cpp) in the working directory.

2. To synthesize the generated test harness:
```C++
make synthesis_dynamic
``` 

#### Formal synthesis
SPARC uses a concurrent-tonon-concurrent program transformation to generate the test harness for formal analysis. The flow is shown in the figure below.
![Program Analysis Flow](Documentation/figures/TechCon%202023%20SSEL/harness.png)

Once the system specification is complete, follow the below steps:
1. To generate the synthesis harness using SPARC:
```C++
make formalHarness
``` 
This generates a test harness file (formalSynthesisHarness.cpp) in the working directory.

2. To synthesize the generated test harness:
```C++
make synthesis_formal
``` 
### Agent Specification Template
Agents in SPARC can be specified in isolation using the following template:

1. Extend the agent class from the slaveIP class. The template for agent definition is as follows:

```C++
class AGENT_NAME : public slaveIP{
    // First, declare all interface registers for this agent
    public:
        interfaceRegisters name_of_reg = {"name_of_reg","direction of interface register (INPUT/OUTPUT)"};
        interfaceRegisters reg2 = {"reg1","OUTPUT"};
   
    // Second, specify all functionalities of the agent inside individual functions. Note that the return type of these functions should be void.  
    public:
        void function1();
        void function2();
        void function3();
    
    // Third, any local/private variables or functions for the agent should be declared private and end with an _. 
    private:
        bool variable1_ = false;
        bool variable2_ = false;
};

// Here, all the function body can be specified. This can also be done in the function declaration above.
``` 
More documentation on each of the SPARC constructs and features can be found [here](/Documentation/). For a video walkthough, please click [here](https://drive.google.com/file/d/1FouqvEBRwxMwFEAk99wn_y9iO8KQwEN0/view?usp=sharing).

For further information or any issues related to this repository, please send an email to Kshitij Raj at kshitijraj@ufl.edu




