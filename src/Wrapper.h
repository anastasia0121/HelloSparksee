#ifndef __IFMO_DISTRIBUTED_CLASS_WRAPPER__H
#define __IFMO_DISTRIBUTED_CLASS_WRAPPER__H

#include <iostream> 

#include "gdb/Sparksee.h"
#include "gdb/Database.h"
#include "gdb/Session.h"
#include "gdb/Graph.h"
#include "gdb/Export.h"
#include "gdb/Objects.h"
#include "gdb/ObjectsIterator.h"
#include "io/CSVWriter.h"
#include "io/NodeTypeExporter.h"

#include "MyExport.h"
#include "Type.h"

using namespace sparksee::gdb;
using namespace sparksee::io;

class DataManager
{
public:
    Graph * get_graph() const
    {
        return g;
    }

    //create all objects (after called this method
    //graph can add object tis type)
    void create_objects(GraphObjects &go) const;

    static const DataManager * get_instanse();
   
    //add node to database
    //type - type of object (see Type.h)
    //info - struct which contain type and attributes of object
    oid_t add_node(int16_t type, void *info) const;
 
    //see add node
    oid_t add_edge(int16_t type, void *info, oid_t left, oid_t right) const;
   
    ~DataManager();
            
    //May be we should forbid move constructor and operator
    //like copy constructor and iterator
    DataManager (const DataManager &) = delete;
    DataManager & operator = (const DataManager &) = delete;

private:
     DataManager();
  
private:
     Sparksee * sparksee;
     Database *db;
     Session * sess;
     Graph *g;
};
#endif // __IFMO_DISTRIBUTED_CLASS_WRAPPER__H
