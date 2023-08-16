
## Interface Class
Agents modeled in SPARC can interact with each other using interface registers which can be specified using the Interface constructs provided in the language.
For example, if an interface register called "duration is needed", it can be specified in the definition of the agent in the "public" scope, as shown below. The first field in the struct represents the name of the interface register and the second shows its direction as seen from the agent it is specified in.

* ```C++
    interfaceRegisters duration = {"duration","INPUT"};

