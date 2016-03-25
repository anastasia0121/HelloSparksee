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

DataManager::DataManager()
{
    // Create a database
    SparkseeConfig cfg;
    sparksee = new Sparksee(cfg);
    db = sparksee->Create(L"HelloSparksee.gdb", L"HelloSparksee");

    // Create a new session of working with database
    sess = db->NewSession();
    g = sess->GetGraph();
}

DataManager::~DataManager()
{
    delete g;
    delete sess;
    delete db;
    delete sparksee;
}


const DataManager * DataManager::get_instanse()
{
    static DataManager dm; //only linux after c++11
    return &dm;
}

void DataManager::create_objects(GraphObjects &go) const
{
    //Gnome
    go.gnome.types.type  = g->NewNodeType(L"Gnome");
    go.gnome.types.id    = g->NewAttribute(go.gnome.types.type, L"Id",        Long,    Unique);
    go.gnome.types.name  = g->NewAttribute(go.gnome.types.type, L"Name",      String,  Indexed);
    go.gnome.types.age   = g->NewAttribute(go.gnome.types.type, L"Age",       Integer, Indexed);
    go.gnome.types.str   = g->NewAttribute(go.gnome.types.type, L"Strenght",  Integer, Indexed);
    go.gnome.types.intel = g->NewAttribute(go.gnome.types.type, L"Intelligence", Integer, Indexed);
    go.gnome.types.cha   = g->NewAttribute(go.gnome.types.type, L"Character", Integer, Indexed);
    go.gnome.types.skill = g->NewAttribute(go.gnome.types.type, L"Skills",    String,  Indexed);

    //Mine
    go.mine.types.type = g->NewNodeType(L"Mine");
    go.mine.types.id   = g->NewAttribute(go.mine.types.type , L"Id",   Long,   Unique);
    go.mine.types.name = g->NewAttribute(go.mine.types.type , L"Name", String, Indexed);
    
    //Dragon
    go.dragon.types.type  = g->NewNodeType(L"Dragon");
    go.dragon.types.id    = g->NewAttribute(go.dragon.types.type, L"Id",        Long,    Unique);
    go.dragon.types.name  = g->NewAttribute(go.dragon.types.type, L"Name",      String,  Indexed);
    go.dragon.types.color = g->NewAttribute(go.dragon.types.type, L"Color",     Integer, Indexed);
    go.dragon.types.cost  = g->NewAttribute(go.dragon.types.type, L"Cost",      Integer, Indexed);
    go.dragon.types.size  = g->NewAttribute(go.dragon.types.type, L"Size",      Integer, Indexed);
    go.dragon.types.age   = g->NewAttribute(go.dragon.types.type, L"Age",       Integer, Indexed);
    go.dragon.types.str   = g->NewAttribute(go.dragon.types.type, L"Strenght",  Integer, Indexed);
    go.dragon.types.cha   = g->NewAttribute(go.dragon.types.type, L"Character", Integer, Indexed);
    go.dragon.types.skill = g->NewAttribute(go.dragon.types.type, L"Skills",    String,  Indexed);

    //Ore
    go.ore.types.type = g->NewNodeType(L"Ore");
    go.ore.types.id   = g->NewAttribute(go.ore.types.type , L"Id",   Long,   Unique);
    go.ore.types.name = g->NewAttribute(go.ore.types.type , L"Name", String, Indexed);

    //Belong 
    go.belong.types.type = g->NewEdgeType(L"Belong", false , false); //not ore TODO
    go.belong.types.prof = g->NewAttribute(go.belong.types.type, L"Profession", String, Basic);

    //Directs
    go.directs.types.type = g->NewRestrictedEdgeType(L"DIRECTS", 
            go.gnome.types.type, go.mine.types.type, false);

    //Mines
    go.mines.types.type = g->NewRestrictedEdgeType(L"MINES", 
            go.ore.types.type, go.mine.types.type, false);
}

oid_t DataManager::add_node(int16_t type, void *info) const
{
    static Value *value = new Value();

    if (g != NULL)
    {
        switch(type)
        {
            case GNOME: 
                {  
                    Gnome *tmp = static_cast<Gnome*>(info);
                    oid_t new_node = g->NewNode(tmp->types.type);

                    g->SetAttribute(new_node, tmp->types.id, 
                            value->SetLong(tmp->values.id));
                    g->SetAttribute(new_node, tmp->types.name, 
                            value->SetString(tmp->values.name));
                    g->SetAttribute(new_node, tmp->types.age,
                            value->SetInteger(tmp->values.age));
                    g->SetAttribute(new_node, tmp->types.str,
                            value->SetInteger(tmp->values.str));
                    g->SetAttribute(new_node, tmp->types.intel,
                            value->SetInteger(tmp->values.intel));
                    g->SetAttribute(new_node, tmp->types.cha,
                            value->SetInteger(tmp->values.cha));
                    g->SetAttribute(new_node, tmp->types.skill, 
                            value->SetString(tmp->values.skill));

                    return new_node; 
                }
            case MINE:
                {
                    Mine *tmp = static_cast<Mine*>(info);
                    oid_t new_node = g->NewNode(tmp->types.type);

                    g->SetAttribute(new_node, tmp->types.id, 
                            value->SetLong(tmp->values.id));
                    g->SetAttribute(new_node, tmp->types.name, 
                            value->SetString(tmp->values.name));

                    return new_node; 
                }
            case DRAGON: 
                {  
                    Dragon *tmp = static_cast<Dragon*>(info);
                    oid_t new_node = g->NewNode(tmp->types.type);

                    g->SetAttribute(new_node, tmp->types.id, 
                            value->SetLong(tmp->values.id));
                    g->SetAttribute(new_node, tmp->types.name, 
                            value->SetString(tmp->values.name));
                    g->SetAttribute(new_node, tmp->types.age,
                            value->SetInteger(tmp->values.age));
                    g->SetAttribute(new_node, tmp->types.color,
                            value->SetInteger(tmp->values.color));
                    g->SetAttribute(new_node, tmp->types.cost,
                            value->SetInteger(tmp->values.cost));
                    g->SetAttribute(new_node, tmp->types.size,
                            value->SetInteger(tmp->values.size));
                    g->SetAttribute(new_node, tmp->types.str,
                            value->SetInteger(tmp->values.str));
                    g->SetAttribute(new_node, tmp->types.cha,
                            value->SetInteger(tmp->values.cha));
                    g->SetAttribute(new_node, tmp->types.skill, 
                            value->SetString(tmp->values.skill));

                    return new_node; 
                }
            case ORE:
                {
                    Ore *tmp = static_cast<Ore*>(info);
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

oid_t DataManager::add_edge(int16_t type, void *info, oid_t left, oid_t right) const
{
    static Value *value = new Value();

    if (g != NULL)
    {
        switch(type)
        {
            case BELONG: 
                {  
                    Belong *tmp = static_cast<Belong*>(info);
                    oid_t new_edge = g->NewEdge(tmp->types.type, left, right);
                    g->SetAttribute(new_edge, tmp->types.prof, 
                            value->SetString(tmp->values.prof));

                    return new_edge; 
                }
            case DIRECTS:
                {
                    Directs *tmp = static_cast<Directs*>(info);
                    oid_t new_edge = g->NewEdge(tmp->types.type, left, right);

                    return new_edge; 
                }
            case MINES: 
                {  
                    Mines *tmp = static_cast<Mines*>(info);
                    oid_t new_edge = g->NewEdge(tmp->types.type, left, right);

                    return new_edge; 
                }
        }
    }
}
