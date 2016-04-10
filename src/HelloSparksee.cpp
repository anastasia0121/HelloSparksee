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

int main(int argc, char *argv[]) 
{
    try 
    {
        const DataManager *dtm = DataManager::get_instanse();

        std::wstring s;
        std::wcin >> s;
        std::wcout << s << std::endl;
        std::wcout << L"work" << std::endl;


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
        //Value old_v, new_v;
        //dtm->remove_node(DRAGON, go.dragon.types.name, old_v.SetString(L"Kondragon0"));
        //dtm->move_node(GNOME, go.gnome.types.name, 
        //        old_v.SetString(L"Untilopulus0"), new_v.SetString(L"NewName"));

        // Export to graphviz
        dtm->export_to_graphviz(); 
    }
    catch (Exception& e) {
        std::cerr << e.Message() << std::endl;
    }
    return 0;
}
