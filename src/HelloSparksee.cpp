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

#include "Type.h"
#include "MyExport.h"
#include "Wrapper.h"

using namespace sparksee::gdb;
using namespace sparksee::io;


int main(int argc, char *argv[]) 
{
    try 
    {
        const DataManager *dtm = DataManager::get_instanse();
        GraphObjects go;

        dtm->create_objects(go);

        //Gnome
        go.gnome.values.id = 1;
        go.gnome.values.name = L"Untilopulus0";
        go.gnome.values.age = 2003;
        go.gnome.values.str = 2003;
        go.gnome.values.intel = 2003;
        go.gnome.values.cha = 2003;
        go.gnome.values.skill = L"Brilliant";
        oid_t gnome0 = dtm->add_node(GNOME, (void*)(&go.gnome));

        go.gnome.values.id = 2;
        go.gnome.values.name = L"Untilopulus1";
        oid_t gnome1 = dtm->add_node(GNOME, (void*)(&go.gnome));

        go.gnome.values.id = 3;
        go.gnome.values.name = L"Untilopulus2";
        oid_t gnome2 = dtm->add_node(GNOME, (void*)(&go.gnome));

        //Mine
        go.mine.values.id = 1;
        go.mine.values.name = L"Arhopolis";
        oid_t mine0 = dtm->add_node(MINE, (void*)(&go.mine)); 

        //Dragon
        go.dragon.values.id = 1;
        go.dragon.values.name = L"Kondragon0";
        go.dragon.values.age = 2003;
        go.dragon.values.color = 2003;
        go.dragon.values.size = 2003;
        go.dragon.values.cost = 2003;
        go.dragon.values.str = 2003;
        go.dragon.values.cha = 2003;
        go.dragon.values.skill = L"Brilliant";
        oid_t dragon0 = dtm->add_node(DRAGON, (void*)(&go.dragon));

        //Ore
        go.ore.values.id = 1;
        go.ore.values.name = L"Gira0";
        oid_t ore0 = dtm->add_node(ORE, (void*)(&go.ore)); 

        go.ore.values.id = 2;
        go.ore.values.name = L"Gira1";
        oid_t ore1 = dtm->add_node(ORE, (void*)(&go.ore)); 

        //Belong
        go.belong.values.prof = L"Miner";
        dtm->add_edge(BELONG, (void*)(&go.belong), gnome0, mine0);

        dtm->add_edge(BELONG, (void*)(&go.belong), gnome1, mine0);

        go.belong.values.prof = L"Ruler";
        dtm->add_edge(BELONG, (void*)(&go.belong), gnome2, mine0);

        //Directs
        dtm->add_edge(DIRECTS, (void*)(&go.directs), gnome2, mine0);

        //Mines
        dtm->add_edge(MINES, (void*)(&go.mines), ore0, mine0);
        dtm->add_edge(MINES, (void*)(&go.mines), ore1, mine0);
        // =================================================================
        Graph *g = dtm->get_graph();

        // Export to graphviz
        ExportManager * expMngr = new MyExport();
        //ExportManager* x = static_cast<ExportManager*>(expMngr);
        g->Export(L"test.dot", Graphviz, expMngr);
        delete expMngr; 
        
/*
        // Export PEOPLE to csv
        type_t peopleTypeId = g->FindType(L"PEOPLE");
        attr_t idAttrId = g->FindAttribute(peopleTypeId , L"ID");
        attr_t nameAttrId = g->FindAttribute(peopleTypeId , L"NAME");
        // configure CSV writer
        CSVWriter csv;
        csv.SetSeparator(L"|");
        csv.SetAutoQuotes(true);
        csv.Open(L"people.csv");
        // export PEOPLE node type: Name and Age attributes
        AttributeList attrs;
        attrs.Add(idAttrId);
        attrs.Add(nameAttrId);
        NodeTypeExporter nte(csv, *g, peopleTypeId, attrs);
        nte.Run();
        csv.Close();

        // =================================================================
        // Queries
        // Get the movies directed by Woody Allen
        Objects *directedByWoody = g->Neighbors(pWoody, go.directs.types.type, Outgoing);

        // Get the cast of the movies directed by Woody Allen
        Objects *castDirectedByWoody = g->Neighbors(directedByWoody , go.cast.types.type , Any);
        // Say hello to the people found
        //        ObjectsIterator *it1 = directedByWoody->Iterator();
        //          while (it1->HasNext())
        //          {
        //          oid_t people1Oid = it1->Next();
        //          g->GetAttribute(people1Oid, peopleNameType, *value);
        //          std::wcout << L"Hello " << value->GetString() << std::endl;
        //          }
        //          delete it1;

        // We don't need the directedByWoody collection anymore , so we should delete it
        delete directedByWoody;

        // Get the movies directed by Sofia Coppola
        Objects *directedBySofia = g->Neighbors(pSofia, go.directs.types.type, Outgoing);
        // Get the cast of the movies directed by Sofia Coppola
        Objects *castDirectedBySofia = g->Neighbors(directedBySofia, go.cast.types.type, Any);
        // We don't need the directedBySofia collection anymore , so we should delete it
        delete directedBySofia;

        // We want to know the people that acted in movies directed by Woody AND in movies directed by Sofia.
        Objects *castFromBoth = Objects::CombineIntersection(castDirectedByWoody, castDirectedBySofia);
        // We don't need the other collections anymore
        delete castDirectedByWoody;
        delete castDirectedBySofia;

        // Say hello to the people found
        ObjectsIterator *it = castFromBoth->Iterator();
        Value * value = new Value();
        while (it->HasNext())
        {
            oid_t peopleOid = it->Next();
            g->GetAttribute(peopleOid , go.people.types.name , *value);
            std::wcout << L"Hello " << value->GetString() << std::endl;
        }

        delete value;

        // The ObjectsIterator must be deleted
        delete it;
        // The Objects must be deleted
        delete castFromBoth;
        */
    }
    catch (sparksee::gdb::Error& e) {
        std::cerr << e.Message() << std::endl;
    }
    return 0;
}
