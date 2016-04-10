#include <iostream> 

#include "gdb/Sparksee.h"
#include "gdb/Database.h"
#include "gdb/Session.h"
#include "gdb/Graph.h"
#include "gdb/Export.h"
#include "gdb/Objects.h"
#include "gdb/ObjectsIterator.h"
#include "io/CSVWriter.h"
#include "io/CSVReader.h"
#include "io/NodeTypeExporter.h"
#include "io/NodeTypeLoader.h"
#include "io/EdgeTypeExporter.h"
#include "io/EdgeTypeLoader.h"

#include <array>
#include <cstdlib>
#include <stdlib.h>

#include "MyExport.h"
#include "Wrapper.h"
#include "Type.h"

using namespace sparksee::gdb;
using namespace sparksee::io;

DataManager::DataManager()
{
    // Create a database
    SparkseeConfig cfg;
    cfg.SetRecoveryEnabled(true);
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
    go.gnome.types.str   = g->NewAttribute(go.gnome.types.type, L"Strength",  Integer, Indexed);
    go.gnome.types.intel = g->NewAttribute(go.gnome.types.type, L"Intelligence", Integer, Indexed);
    go.gnome.types.cha   = g->NewAttribute(go.gnome.types.type, L"Charisma",  Integer, Indexed);
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
    go.dragon.types.str   = g->NewAttribute(go.dragon.types.type, L"Strength",  Integer, Indexed);
    go.dragon.types.cha   = g->NewAttribute(go.dragon.types.type, L"Charisma",  Integer, Indexed);
    go.dragon.types.skill = g->NewAttribute(go.dragon.types.type, L"Skills",    String,  Indexed);

    //Ore
    go.ore.types.type = g->NewNodeType(L"Ore");
    go.ore.types.id   = g->NewAttribute(go.ore.types.type , L"Id",   Long,   Unique);
    go.ore.types.name = g->NewAttribute(go.ore.types.type , L"Name", String, Indexed);

    //Belong 
    go.belong.types.type = g->NewEdgeType(L"Belong", false , false); //not ore TODO
    go.belong.types.prof = g->NewAttribute(go.belong.types.type, L"Profession", String, Basic);

    //Mines
    go.mines.types.type = g->NewRestrictedEdgeType(L"Mines", 
            go.mine.types.type, go.ore.types.type, false);
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
            case MINES: 
                {  
                    Mines *tmp = static_cast<Mines*>(info);
                    oid_t new_edge = g->NewEdge(tmp->types.type, left, right);

                    return new_edge; 
                }
        }
    }
}

void DataManager::remove_node(int16_t type, attr_t attr, Value &value) const
{
    Objects * node = g->Select(attr, Equal, value);

    //    ObjectsIterator *it = node->Iterator();

    //    while (it->HasNext())
    {
        switch(type)
        {
            case GNOME:
            case DRAGON:
                {
                    type_t belong_type = g->FindType(L"Belong");  
                    Objects *edges_belongs = g->Explode(node, 
                            belong_type, Any);
                    g->Drop(edges_belongs);
                    delete edges_belongs;

                    break;
                }
            case ORE:
                {
                    type_t mines_type = g->FindType(L"Mines");  
                    Objects *edges_mines = g->Explode(node, 
                            mines_type, Any);
                    g->Drop(edges_mines);
                    delete edges_mines;

                    break;
                }
            case MINE:
                {
                    type_t belong_type = g->FindType(L"Belong");  
                    Objects *edges_belongs = g->Explode(node, 
                            belong_type, Any);
                    g->Drop(edges_belongs);
                    delete edges_belongs;

                    type_t mines_type = g->FindType(L"Mines");  
                    Objects *edges_mines = g->Explode(node, 
                            mines_type, Any);
                    g->Drop(edges_mines);
                    delete edges_mines;

                    break;
                }

        }
    }
    //    delete it;
    g->Drop(node);
    delete node;
}

void DataManager::change_node(attr_t attr, 
        Value &old_v, Value &new_v) const
{
    Objects * objs = g->Select(attr, Equal, old_v);
    ObjectsIterator *it = objs->Iterator();

    while (it->HasNext())
    {
        oid_t node = it->Next();
        g->SetAttribute(node, attr, new_v);
    }

    delete it;
    delete objs;
}

void DataManager::regexp_search(attr_t attr, Value &v) const
{
    Objects * objs = g->Select(attr, RegExp, v);
    ObjectsIterator *it = objs->Iterator();

    while (it->HasNext())
    {
        oid_t node = it->Next();
        g->GetAttribute(node, attr, v);
        std::wcout << L"I find " << v.GetString() << std::endl;
    }

    delete it;
    delete objs;
}

void DataManager::garbage_generate(GraphObjects &go) const
{
    const size_t gnome_count = 20;
    const size_t mine_count = 1;
    const size_t dragon_count = 2;
    const size_t ore_count = 1;

    std::array<oid_t, mine_count> mine;

    for (int i = 0; i < mine_count; ++i)
    {
        //Mine
        go.mine.values.id = i;
        go.mine.values.name = L"Arhopolis";
        mine[i] = add_node(MINE, (void*)(&go.mine)); 
    }

    for (int i = 0; i < gnome_count; ++i)
    {
        //Gnome
        go.gnome.values.id = i;
        go.gnome.values.name = (L"Untilopulus" + std::to_wstring(i));
        go.gnome.values.age = 2003;
        go.gnome.values.str = 2003;
        go.gnome.values.intel = 2003;
        go.gnome.values.cha = 2003;
        go.gnome.values.skill = L"Brilliant";
        oid_t gnome = add_node(GNOME, (void*)(&go.gnome));
        //Belong
        go.belong.values.prof = L"Miner";
        add_edge(BELONG, (void*)(&go.belong), gnome, mine[0]);
    }

    for (int i = 0; i < dragon_count; ++i)
    {
        //Dragon
        go.dragon.values.id = i;
        go.dragon.values.name = (L"Kondragon" + std::to_wstring(i));
        go.dragon.values.age = 2003;
        go.dragon.values.color = 2003;
        go.dragon.values.size = 2003;
        go.dragon.values.cost = 2003;
        go.dragon.values.str = 2003;
        go.dragon.values.cha = 2003;
        go.dragon.values.skill = L"Brilliant";
        oid_t dragon = add_node(DRAGON, (void*)(&go.dragon));
        //Belong
        go.belong.values.prof = L"Dragon";
        add_edge(BELONG, (void*)(&go.belong), dragon, mine[0]);
    }

    for (int i = 0; i < ore_count; ++i)
    {
        //Ore
        go.ore.values.id = i;
        go.ore.values.name = L"Gira0";
        oid_t ore = add_node(ORE, (void*)(&go.ore)); 
        //Mines
        add_edge(MINES, (void*)(&go.mines), mine[0], ore);
    }
}
