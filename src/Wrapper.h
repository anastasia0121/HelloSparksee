#ifndef __CLASS_WRAPPER__H
#define __CLASS_WRAPPER__H

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

    // Export to graphviz
    void export_to_graphviz() const;

    //create all objects (after called this method
    //graph can add object tis type)
    void create_objects(GraphObjects &go) const;

    static const DataManager * get_instanse();
   
    //add node to database
    //type - type of object (see Type.h)
    //info - struct which contain type and attributes of object
    oid_t add_node(int16_t type, void *info) const;
 
    void remove_node(int16_t type, attr_t attr, Value &value) const;

    void change_node(attr_t attr, Value &old_v,
            Value &new_v) const;

    //see add node
    oid_t add_edge(int16_t type, void *info, oid_t left, oid_t right) const;
    
    void garbage_generate(GraphObjects &go) const;

    void regexp_search(attr_t attr, Value &v) const;
    
    // Export all nodes of given "type" to csv file named "file_name"
    void export_nodes_to_csv(int16_t type, const std::wstring &file_name) const;
    
    // Export all edges of given "type" to csv file named "file_name"
    void export_edges_to_csv(int16_t type, int16_t type_tail, int16_t type_head, const std::wstring &file_name) const;

    // Import all nodes of given "type" from csv file named "file_name"
    void import_nodes_from_csv(int16_t type, const std::wstring &file_name) const;

    // Import all edges of given "type" from csv file named "file_name"
    void import_edges_from_csv(int16_t type, int16_t type_tail, int16_t type_head, const std::wstring &file_name) const;

    void export_all() const;
    void import_all() const;

    ~DataManager();
            
    //May be we should forbid move constructor and operator
    //like copy constructor and iterator
    DataManager (const DataManager &) = delete;
    DataManager & operator = (const DataManager &) = delete;

    void switch_keyboard_layout(std::wstring &src, std::wstring &dst) const;
//private:

private:
     DataManager();
  
private:
     Sparksee * sparksee;
     Database *db;
     Session * sess;
     Graph *g;
};
#endif // __CLASS_WRAPPER__H
