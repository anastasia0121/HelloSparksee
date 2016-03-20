#include <stdio.h>
#include "gdb/Sparksee.h"
#include "gdb/Database.h"
#include "gdb/Session.h"
#include "gdb/Graph.h"
#include "gdb/Objects.h"
#include "gdb/ObjectsIterator.h"
#include "gdb/Stream.h"
#include "gdb/Export.h"
#include "MyExport.h"
#include "io/CSVWriter.h"
#include "io/NodeTypeExporter.h"
#include <assert.h>

using namespace sparksee::gdb;
using namespace sparksee::io;

void MyExport::Prepare(Graph * graph) {
    try {
        g = graph;
        type_gnome = g->FindType(L"Gnome");
        gnome_name = g->FindAttribute(type_gnome, L"Name");

        type_mine = g->FindType(L"Mine");
        mine_name = g->FindAttribute(type_mine, L"Name");

        type_ore = g->FindType(L"Ore");
        ore_name = g->FindAttribute(type_ore, L"Name");

        type_dragon = g->FindType(L"Dragon");
        dragon_name = g->FindAttribute(type_dragon, L"Name");

        type_belong = g->FindType(L"Belong");
        type_directs = g->FindType(L"Directs");
        type_mines = g->FindType(L"Mines");
    }
    catch (sparksee::gdb::Error& e) {
        std::cerr << e.Message() << std::endl;
    }
}

void MyExport::Release() {
}

bool_t MyExport::GetGraph(GraphExport& ge) {
    try {
        ge.SetLabel(L"Funny gnomes");
    }
    catch (sparksee::gdb::Error& e) {
        std::cerr << e.Message() << std::endl;
    }
    return true;
}

bool_t MyExport::GetNodeType(type_t nodetype , NodeExport& ne) {
    // default node type export:
    // - PEOPLE in RED nodes
    // - MOVIES in ORANGE nodes
    try 
    {
        if (nodetype == type_mine) 
        {
            ne.SetColorRGB(16711680); // red
        } 
        else
        {
            ne.SetColorRGB(16744192); // ORANGE
        } 
    }
    catch (sparksee::gdb::Error& e) 
    {
        std::cerr << e.Message() << std::endl;
    }
    return true;
}

bool_t MyExport::GetEdgeType(type_t edgetype , EdgeExport& ee) {
    // default edge type export:
    // - CAST in YELLOW lines
    // - DIRECTS in BLUE lines
    try 
    {
        if (edgetype == type_directs) 
        {
            ee.SetColorRGB(16776960); // yellow
        } 
        else
        {
            ee.SetColorRGB(255); // blue
        } 
    }
    catch (sparksee::gdb::Error& e) 
    {
        std::cerr << e.Message() << std::endl;
    }
    return true;
}

bool_t MyExport::GetNode(oid_t nodeOID , NodeExport& ne) {
    // specific node export:
    // - PEOPLE: use the Name attribute as label
    // - MOVIES: use the Title attribute as label
    try {
        int nodetype = g->GetObjectType(nodeOID);
        if (nodetype == type_gnome) 
        {
            g->GetAttribute(nodeOID, gnome_name, v);
        } 
        else if (nodetype == type_mine) 
        {
            g->GetAttribute(nodeOID, mine_name, v);
        } 
        else if (nodetype == type_dragon) 
        {
            g->GetAttribute(nodeOID, dragon_name, v);
        } 
        else if (nodetype == type_ore) 
        {
            g->GetAttribute(nodeOID, ore_name, v);
        } 
        else 
        {
            assert(false);
        }
        std::wstring aux2;
        std::wstringstream aux;
        aux << L"[" << nodeOID << L"]" << v.ToString(aux2);
        ne.SetLabel(aux.str());
    }
    catch (sparksee::gdb::Error& e) {
        std::cerr << e.Message() << std::endl;
    }
    return true;
}

bool_t MyExport::GetEdge(oid_t edgeOID , EdgeExport& ee) {
    // default edge type export is enough
    return false;
}

bool_t MyExport::EnableType(type_t type) {
    // enable all node and edge types
    return true;
}
