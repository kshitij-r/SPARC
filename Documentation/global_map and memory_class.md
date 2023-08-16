### Memory Module Class
SoC transactions need a memory model to perform read/write operations. SPARK comes with a memory model which enables this. This class extends the following classes:
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