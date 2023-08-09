#ifndef MAP_HEADER_H
#define MAP_HEADER_H
#include <map>
#include <list>
#include <set>
#include <string>
#define PATHSOURCESIZE 5
#define ENTITYCOUNT 3
using namespace std;

static multimap<string, int> *interfaceRegMap;
static multimap<string, int> *sourceIDMap;
static multimap<string, string> *integrationMap;
static multimap<string, string> *p2pmap;
static list<string> *commitEntityList;
static list<string> *systemList;
static list<string> *uniqueSystemList;
static list<string> *specEntityList;
static set<string> *p2pToSet;
static set<string> *sysToSet;
static set<string> *vacuousPoint;
static list<int> *countInterfaceRegister;
// extern map<string, int> interfaceRegMap;
// extern map<string, int> sourceIDMap;

struct  interfaceRegisters{
                string name;
                string direction;
                int value;
                bool commitLocalMap;
                array<int, PATHSOURCESIZE> pathSource;
                int pathCount;
            };
#endif /* MAP_HEADER_H */

// int main() {
//     return 0;
// }
