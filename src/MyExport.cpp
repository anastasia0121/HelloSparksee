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
        peopleTypeId = g->FindType(L"PEOPLE");
        nameAttrId = g->FindAttribute(peopleTypeId , L"NAME");
        moviesTypeId = g->FindType(L"MOVIE");
        titleAttrId = g->FindAttribute(moviesTypeId , L"TITLE");
        castTypeId = g->FindType(L"CAST");
        directsTypeId = g->FindType(L"DIRECTS");
    }
    catch (sparksee::gdb::Error& e) {
        std::cerr << e.Message() << std::endl;
    }
}

void MyExport::Release() {
}

bool_t MyExport::GetGraph(GraphExport& ge) {
    try {
        ge.SetLabel(L"Hollywood");
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
    try {
        if (nodetype == peopleTypeId) {
            ne.SetColorRGB(16711680); // red
        } else if (nodetype == moviesTypeId) {
            ne.SetColorRGB(16744192); // ORANGE
        } else {
            assert(false);
        }
    }
    catch (sparksee::gdb::Error& e) {
        std::cerr << e.Message() << std::endl;
    }
    return true;
}

bool_t MyExport::GetEdgeType(type_t edgetype , EdgeExport& ee) {
    // default edge type export:
    // - CAST in YELLOW lines
    // - DIRECTS in BLUE lines
    try {
        if (edgetype == castTypeId) {
            ee.SetColorRGB(16776960); // yellow
        } else if (edgetype == directsTypeId) {
            ee.SetColorRGB(255); // blue
        } else {
            assert(false);
        }
    }
    catch (sparksee::gdb::Error& e) {
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
        if (nodetype == peopleTypeId) {
            g->GetAttribute(nodeOID , nameAttrId , v);
        } else if (nodetype == moviesTypeId) {
            g->GetAttribute(nodeOID , titleAttrId , v);
        } else {
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
