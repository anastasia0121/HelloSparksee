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
        void create_objects(GraphObjects &go);

        //add to database
        oid_t add_node(int16_t type, void *info);
      
        oid_t add_edge(int16_t type, void *info, oid_t left, oid_t right);

        Graph *g;
};
#endif // __IFMO_DISTRIBUTED_CLASS_WRAPPER__H
