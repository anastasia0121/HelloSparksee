#include <iostream> 

#include "gdb/Sparksee.h"
#include "gdb/Database.h"
#include "gdb/Session.h"
#include "gdb/Graph.h"
#include "gdb/Export.h"
#include "gdb/Objects.h"
#include "gdb/ObjectsIterator.h"

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

        dtm->garbage_generate(go);

        Graph *g = dtm->get_graph();

        /*dtm->export_nodes_to_csv(GNOME, L"export/gnome.csv");
        dtm->export_nodes_to_csv(DRAGON, L"export/dragon.csv");
        dtm->export_nodes_to_csv(MINE, L"export/mine.csv");
        dtm->export_nodes_to_csv(ORE, L"export/ore.csv");*/

        /*dtm->import_nodes_from_csv(GNOME, L"export/gnome.csv");
        dtm->import_nodes_from_csv(DRAGON, L"export/dragon.csv");
        dtm->import_nodes_from_csv(MINE, L"export/mine.csv");
        dtm->import_nodes_from_csv(ORE, L"export/ore.csv");*/

        // Export to graphviz
        ExportManager * expMngr = new MyExport();
        //ExportManager* x = static_cast<ExportManager*>(expMngr);
        g->Export(L"test.dot", Graphviz, expMngr);
        delete expMngr; 

        /*
        // =================================================================
        // Queries
        // Get the movies directed by Woody Allen
        // */
        
        Value *value = new Value();

        dtm->remove_node(DRAGON, go.dragon.types.name, value->SetString(L"Kondragon0"));

        delete value;

/*
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
