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
