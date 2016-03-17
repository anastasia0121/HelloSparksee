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
#include "Wrapper.h"
#include "Type.h"

using namespace sparksee::gdb;
using namespace sparksee::io;

oid_t DataManager::add_node(int16_t type, void *info)
{
    static Value *value = new Value();

    if (g != NULL)
    {
        switch(type)
        {
            case MOVIE: 
                {  
                    Movie *tmp = static_cast<Movie*>(info);
                    oid_t new_node = g->NewNode(tmp->types.type);
                    g->SetAttribute(new_node, tmp->types.id, 
                            value->SetLong(tmp->values.id));
                    g->SetAttribute(new_node, tmp->types.title, 
                            value->SetString(tmp->values.title));
                    g->SetAttribute(new_node, tmp->types.year,
                            value->SetInteger(tmp->values.year));

                    return new_node; 
                }
            case PEOPLE:
                {
                    People *tmp = static_cast<People*>(info);
                    oid_t new_node = g->NewNode(tmp->types.type);
                    g->SetAttribute(new_node, tmp->types.id, 
                            value->SetLong(tmp->values.id));
                    g->SetAttribute(new_node, tmp->types.name, 
                            value->SetString(tmp->values.name));

                    return new_node; 
                }
        }
    }
}

oid_t DataManager::add_edge(int16_t type, void *info, oid_t left, oid_t right)
{
    static Value *value = new Value();

    if (g != NULL)
    {
        switch(type)
        {
            case CAST: 
                {  
                    Cast *tmp = static_cast<Cast*>(info);
                    oid_t new_edge = g->NewEdge(tmp->types.type, left, right);
                    g->SetAttribute(new_edge, tmp->types.character, 
                            value->SetString(tmp->values.character));

                    return new_edge; 
                }
            case DIRECTS:
                {
                    Directs *tmp = static_cast<Directs*>(info);
                    oid_t new_edge = g->NewEdge(tmp->types.type, left, right);

                    return new_edge; 
                }
        }
    }
}
