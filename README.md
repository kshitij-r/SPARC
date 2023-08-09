# SPARK : Specification and Analysis of Hardware-Software Interactions
#### Version: 0.1
#### Release Date: August 09, 2023
<br>

### A Brief Description:
In SPARK, we used a set of existing constructs from C++ and loops, functions, structures, and data types are used to define the constructs. We augmented SPARK with new data types to account for the binary and hexadecimal nature of the data transferred during on-chip transactions. Since SPARK is designed to provide abstraction of system-level communication, the technical details of various bus protocol implementations
are encapsulated into APIs “baked” into the language abstraction. All inter-IP interactions are oblivious to existing bus implementations to enable reusability of SPARK specifications across platforms and interconnect protocols.
<br>

Each agent can be derived from the slave class (slaveconfig.cpp). This will be revised in the future to support more base class agent types<br><br>

## BaseIP Class
BaseIP class includes the following signals:
* A local memory map instance of an IP.
```C++
map<string,int> m_memory_map;
```
* System reset and System Clock
```C++
static bool m_sys_rst, m_sys_clk;
```
* Local IP reset
```C++
bool m_IP_rst;
```
* IP status signal
```C++
bool m_sts_busy;
```
BaseIP class has the following methods:<br>
```C++
void set_busy_sts( bool sts);
```
This method sets the busy status bit (m_sts_busy) of the IP instance.
```C++
read_from_mem(string key); 
```
This methods returns the pointer to the value of the register associated with the "key".
```C++
auto modify_reg_value(string key, int value);
```
This method modifies the register value associated with "key" with the value "value".
```C++
void print_map(map<string, int> const &m);
```
This method prints the memory map associated with the local IP instance.<br><br>

Each master or slave IP inherits from the baseIP class. Certain functions are overwritten in both the master and slave IP class.<br>

## MasterIP Class
This class extends the following classes:
* Memory Module (RAM instance)
```C++
class memory_model
```
* Global Memory Map
```C++
class system_memory_map
```
### MasterIP has the following methods:<br>
* ```C++
  void system_lvl_rst(bool rst);
This method sets the system level reset to true or false. 
* ```C++
  void system_clk(bool clk);
This method sets the system level clock to true or false. 
* ```C++
  void set_busy_sts(bool sts);
This method sets the IP busy status to true or false. 
* ```C++
  int *read_memory_val(int clk, int rst, int start, int offset = 0){
          return memory_model::send_data_from_mem(clk, rst, start, offset = 0);
        }
This method reads the value of a register from the memory map pointed by calculating the address using the base and offset values passed in the arguments. 

* ```C++
    void delete_memory_val(int clk, int rst, int offset, int base = 0){
        memory_model::delete_from_memory(clk, rst, offset, base = 0);
    }
This method deletes the value of the register in the memory map pointed by calculating the address using the base and offset values passed in the arguments.
* ```C++
    void write_memory_val(int clk, int rst, int offset, int value, int base = 0){
        memory_model::write_to_memory(clk, rst, offset, value, base = 0);
    }
This method writes a value of a register to the address pointed by base and offset.

## SlaveIP Class
This class extends the following classes:
* Memory Module (RAM instance)
```C++
class memory_model
```
* Global Memory Map
```C++
class system_memory_map
```
### SlaveIP has the following methods:<br>

This method sets the IP busy status to true or false. 
* ```C++
  void set_busy_sts(bool sts);
This method resets the IP instance or sets the reset value to True or False.
* ```C++
    void reset_ip_instance();
This method checks the IP busy status. 
* ```C++
    bool check_busy_sts();
This method pushes a register value to the ingress FIFO of the IP instance. 
* ```C++
    void ingress_fifo_push(int *value, int offset);
This method pops a register value from the ingress FIFO of the IP instance. 
* ```C++
    int  ingress_fifo_pop(int offset);
This method displays the contents of the ingress FIFO.
* ```C++
  * void display_fifo();

## Memory Module Class
SoC transactions need a memory model to perform read/write operations. SPARK comes with a memory model which enables this. This class extends the following classes:
* BaseIP
```C++
class baseIP
```
* The size of the memory model can be defined in the "memory_model.cpp" file by using the MEMORY_SIZE definition.

### Memory Module has the following methods:<br>
* ```C++
    void print_memory_val();
This method prints the contents of the memory model.
* ```C++
    void delete_from_memory(int clk, int rst, int offset, int base = 0);
This method deletes a value from the memory model pointed by the index using base + offset.
* ```C++
    void write_to_memory(int clk, int rst, int offset, int value, int base);
This method writes a value in the memory model pointed by the index using base + offset.
* ```C++
    int *send_data_from_mem(int clk, int rst, int start, int offset = 0);
This method reads and sends a value in the memory model pointed by the index using base + offset.
* ```C++
    void reset_memory();
This method resets the entire memory model and sets the values to 0.
* ```C++
    bool fetch_sts();
This method reads the fetch status of the memory. Fetch status is used to ensure that the memory is ready to send data when queried.

## Global Memory Map Class
SoC transactions need a memory model to perform read/write operations. SPARK comes with a memory model which enables this. This class extends the following classes:

```C++
class Log
```
The global memory map is an unordered map.
* ```C++
    static unordered_map<string,int> *global_memory_map;
### Global Memory Map has the following methods:<br>
* ```C++
   void display_valid_bits();
This method displays the valid bits of the memory map. If the valid bit is 1, the data is correct, else the data should not be read and is incorrect. 
* ```C++
    bool check_valid_bit(int offset);
This method checks the valid bits of the memory map.
* ```C++
    void print_map(unordered_map<string, int> const &global_memory_map);
This method displays the entire memory map.
* ```C++
    void write_to_system_map(string reg, int value); 
This method writes the value of the register(reg) in the memory map.
* ```C++
    int read_system_map(string key);
This method reads the value of the register(key) in the memory map.
* ```C++
    void update_system_reg_value(string key, int value);
This method updates the value of the register(key) in the memory map.

## Interface Class
Agents modeled in SPARK can interact with each other using interface registers which can be specified using the Interface constructs provided in the language.
For example, if an interface register called "duration is needed", it can be specified in the definition of the agent in the "public" scope, as shown below. The first field in the struct represents the name of the interface register and the second shows its direction as seen from the agent it is specified in.

* ```C++
    interfaceRegisters duration = {"duration","INPUT"};

### Requirements
* This version of SPARK requires C++17 or above to build.
* KLEE is required for formal analysis of specifications generated using SPARK. It can be downloaded by clicking [here](https://klee.github.io/). The Docker version of KLEE should be prefered.