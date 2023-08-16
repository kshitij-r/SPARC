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
