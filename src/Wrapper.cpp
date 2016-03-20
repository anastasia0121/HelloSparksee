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

void DataManager::create_objects(GraphObjects &go)
{
    // Add a node type for the movies , with a unique identifier and two indexed
    // attributes
    go.movie.types.type = g->NewNodeType(L"MOVIE");
    go.movie.types.id = g->NewAttribute(go.movie.types.type, L"ID", Long, Unique);
    go.movie.types.title = g->NewAttribute(go.movie.types.type, L"TITLE", String, Indexed);
    go.movie.types.year = g->NewAttribute(go.movie.types.type, L"YEAR", Integer , Indexed);
    // Add a node type for the people , with a unique identifier and an indexed
    // attribute
    go.people.types.type = g->NewNodeType(L"PEOPLE");
    go.people.types.id = g->NewAttribute(go.people.types.type , L"ID", Long, Unique);
    go.people.types.name = g->NewAttribute(go.people.types.type , L"NAME", String, Indexed);

    // Add an undirected edge type with an attribute for the cast of a movie
    go.cast.types.type = g->NewEdgeType(L"CAST", false , false);
    go.cast.types.character = g->NewAttribute(go.cast.types.type, L"CHARACTER", String, Basic);
    // Add a directed edge type restricted to go from people to 
    // movie for the director of a movie
    go.directs.types.type = g->NewRestrictedEdgeType(L"DIRECTS", 
            go.people.types.type, go.movie.types.type, false);
}

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
