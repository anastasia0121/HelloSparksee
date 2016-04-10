#include <iostream> 

#include "gdb/Sparksee.h"
#include "gdb/Database.h"
#include "gdb/Session.h"
#include "gdb/Graph.h"
#include "gdb/Export.h"
#include "gdb/Objects.h"
#include "gdb/ObjectsIterator.h"
#include "gdb/Exception.h"

#include "Type.h"
#include "MyExport.h"
#include "Wrapper.h"

using namespace sparksee::gdb;
using namespace sparksee::io;

#define GARBAGE 0
#define EXPORT 0
#define IMPORT 1

#define TASK1 0
#define TASK2 1

int main(int argc, char *argv[]) 
{
    try 
    {
        setlocale(LC_ALL,"");
        const DataManager *dtm = DataManager::get_instanse();

        GraphObjects go;
        dtm->create_objects(go);

#if GARBAGE
        dtm->garbage_generate(go);
#else
#if EXPORT
        dtm->export_all();
#endif
#if IMPORT
        dtm->import_all();
#endif
#endif
        
#if TASK1
        Value old_v, new_v;
        dtm->remove_node(DRAGON, go.dragon.types.name, old_v.SetString(L"Kondragon0"));
        dtm->change_node(go.gnome.types.name, 
                old_v.SetString(L"Untilopulus0"), new_v.SetString(L"NewName"));
#endif
#if TASK2
        Value v;
        dtm->regexp_search(go.dragon.types.name, v.SetString(L"Ko"));
#endif

        // Export to graphviz
        dtm->export_to_graphviz(); 
    }
    catch (Exception& e) {
        std::cerr << e.Message() << std::endl;
    }
    return 0;
}
