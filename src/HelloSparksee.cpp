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
        // Create a database
        SparkseeConfig cfg;
        Sparksee *sparksee = new Sparksee(cfg);
        Database *db = sparksee->Create(L"HelloSparksee.gdb", L"HelloSparksee");

        // Create a new session of working with database
        Session *sess = db->NewSession();
        Graph *g = sess->GetGraph();

        // Add a node type for the movies , with a unique identifier and two indexed
        // attributes
        Movie movie;
        movie.types.type = g->NewNodeType(L"MOVIE");
        movie.types.id = g->NewAttribute(movie.types.type, L"ID", Long, Unique);
        movie.types.title = g->NewAttribute(movie.types.type, L"TITLE", String, Indexed);
        movie.types.year = g->NewAttribute(movie.types.type, L"YEAR", Integer , Indexed);
        // Add a node type for the people , with a unique identifier and an indexed
        // attribute
        People people;
        people.types.type = g->NewNodeType(L"PEOPLE");
        people.types.id = g->NewAttribute(people.types.type , L"ID", Long, Unique);
        people.types.name = g->NewAttribute(people.types.type , L"NAME", String, Indexed);


        // Add an undirected edge type with an attribute for the cast of a movie
        Cast cast;
        cast.types.type = g->NewEdgeType(L"CAST", false , false);
        cast.types.character = g->NewAttribute(cast.types.type , L"CHARACTER", String, Basic);
        // Add a directed edge type restricted to go from people to 
        // movie for the director of a movie
        Directs directs;
        directs.types.type = g->NewRestrictedEdgeType(L"DIRECTS", people.types.type , movie.types.type, false);

        // =================================================================
        // ADDING NODES
        // Add some MOVIE nodes
        DataManager dtm;
        dtm.g = g;

        movie.values.id = 1;
        movie.values.title = L"Lost in Translation";
        movie.values.year = 2003;
        oid_t mLostInTranslation = dtm.add_node(MOVIE, (void*)(&movie));

        movie.values.id = 2;
        movie.values.title =L"Vicky Cristina Barcelona";
        movie.values.year = 2008;
        oid_t mVickyCB = dtm.add_node(MOVIE, (void*)(&movie));

        movie.values.id = 3;
        movie.values.title = L"Manhattan";
        movie.values.year = 1979;
        oid_t mManhattan = dtm.add_node(MOVIE, (void*)(&movie));

       // Add some PEOPLE nodes
        people.values.id = 1;
        people.values.name = L"Scarlett Johansson";
        oid_t pScarlett = dtm.add_node(PEOPLE, (void*)(&people)); 
        
        people.values.id = 2;
        people.values.name = L"Bill Murray";
        oid_t pBill = dtm.add_node(PEOPLE, (void*)(&people)); 

        people.values.id = 3;
        people.values.name = L"Sofia Coppola";
        oid_t pSofia = dtm.add_node(PEOPLE, (void*)(&people)); 

        people.values.id = 4;
        people.values.name = L"Woody Allen";
        oid_t pWoody = dtm.add_node(PEOPLE, (void*)(&people)); 

        people.values.id = 5;
        people.values.name = L"Penélope Cruz";
        oid_t pPenelope = dtm.add_node(PEOPLE, (void*)(&people)); 

        people.values.id = 6;
        people.values.name = L"Diane Keaton";
        oid_t pDiane = dtm.add_node(PEOPLE, (void*)(&people)); 
        // =============================================================

        // =================================================================
        // ADDING EDGES
        // Add some CAST edges
        // Remember that we are reusing the Value class instance to set the attributes
        cast.values.character = L"Charlotte";
        dtm.add_edge(CAST, (void*)(&cast), mLostInTranslation, pScarlett);

        cast.values.character = L"Bob Harris";
        dtm.add_edge(CAST, (void*)(&cast), mLostInTranslation, pBill);

        cast.values.character = L"Cristina";
        dtm.add_edge(CAST, (void*)(&cast), mVickyCB, pScarlett);

        cast.values.character = L"Maria Elena";
         dtm.add_edge(CAST, (void*)(&cast), mVickyCB , pPenelope);

        cast.values.character = L"Mary";
        dtm.add_edge(CAST, (void*)(&cast), mManhattan, pDiane);

        cast.values.character = L"Isaac";
        dtm.add_edge(CAST, (void*)(&cast), mManhattan, pWoody);

        // Add some DIRECTS edges
        dtm.add_edge(DIRECTS, (void*)(&directs), pSofia, mLostInTranslation);
        dtm.add_edge(DIRECTS, (void*)(&directs), pWoody, mVickyCB);
        dtm.add_edge(DIRECTS, (void*)(&directs), pWoody, mManhattan);
        // =================================================================

        // Export to graphviz
        ExportManager * expMngr = new MyExport();
        //ExportManager* x = static_cast<ExportManager*>(expMngr);
        g->Export(L"test.dot", Graphviz, expMngr);
        delete expMngr; 

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
        Objects *directedByWoody = g->Neighbors(pWoody, directs.types.type, Outgoing);

        // Get the cast of the movies directed by Woody Allen
        Objects *castDirectedByWoody = g->Neighbors(directedByWoody , cast.types.type , Any);
        // Say hello to the people found
        /*ObjectsIterator *it1 = directedByWoody->Iterator();
          while (it1->HasNext())
          {
          oid_t people1Oid = it1->Next();
          g->GetAttribute(people1Oid, peopleNameType, *value);
          std::wcout << L"Hello " << value->GetString() << std::endl;
          }
          delete it1;*/

        // We don't need the directedByWoody collection anymore , so we should delete it
        delete directedByWoody;

        // Get the movies directed by Sofia Coppola
        Objects *directedBySofia = g->Neighbors(pSofia, directs.types.type, Outgoing);
        // Get the cast of the movies directed by Sofia Coppola
        Objects *castDirectedBySofia = g->Neighbors(directedBySofia, cast.types.type, Any);
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
            g->GetAttribute(peopleOid , people.types.name , *value);
            std::wcout << L"Hello " << value->GetString() << std::endl;
        }

        // The ObjectsIterator must be deleted
        delete it;
        // The Objects must be deleted
        delete castFromBoth;

        delete sess;
        delete db;
        delete sparksee;

    }
    catch (sparksee::gdb::Error& e) {
        std::cerr << e.Message() << std::endl;
    }
    return 0;
}
