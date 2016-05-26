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
#include "Timer.h"

using namespace sparksee::gdb;
using namespace sparksee::io;

#define GARBAGE 0
#define EXPORT 1
#define IMPORT 0 

#define TASK1 0
#define TASK2 0
#define TASK3 0 
#define TASK3M 1

int main(int argc, char *argv[]) 
{
    try 
    {
        setlocale(LC_ALL,"");
        const DataManager *dtm = DataManager::get_instanse();

        GraphObjects go;
        dtm->create_objects(go);

#if GARBAGE
        dtm->get_session().Begin();
        dtm->garbage_generate(go);
        dtm->get_session().Commit();
#endif
#if EXPORT
        dtm->export_all();
#endif
#if IMPORT
        dtm->import_all();
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
        dtm->search(go.dragon.types.name, L"Лщтвкфпщт0");
#endif
#if TASK3
        Value v;
        oid_t node = dtm->search(go.mine.types.name, v.SetString(L"Arhopolis1"));
        
        uint64_t rate = timer::init_rate();
        uint64_t t1 = timer::rdtsc();
        dtm->bfs(node, L"Ore" , 30); 
        uint64_t t2 = timer::rdtsc();

        std::wcout << timer::to_msec(t2 - t1, rate) << std::endl;

        dtm->dfs(node, L"Ore" , 30); 
        dtm->context(node, L"Ore" , 30); 
#endif
#if TASK3M
        Value v;
        Value old_v, new_v;
        dtm->get_session().Begin();
        uint64_t rate = timer::init_rate();
        uint64_t t1 = timer::rdtsc();
        dtm->search(go.gnome.types.name, v.SetString(L"Untilopulus1"));
        //1
        //dtm->regexp_search(go.gnome.types.name, v.SetString(L"Un"));
        //2
        //oid_t node = dtm->search(go.mine.types.name, v.SetString(L"Arhopolis1"));
        //Objects * objs = dtm->get_graph().Neighbors(node, go.belong.types.type, Any); 
        //3
        //dtm->remove_node(GNOME, go.gnome.types.name, old_v.SetString(L"Untilopulus1"));
        //4
        //dtm->change_node(go.gnome.types.name, 
        //        old_v.SetString(L"Untilopulus2"), new_v.SetString(L"NewName"));
        //5
        //dtm->change_node(go.gnome.types.name, 
        //        old_v.SetString(L"Unt"), new_v.SetString(L"NewName"));
        uint64_t t2 = timer::rdtsc();

        //delete it;
        //delete objs;
        dtm->get_session().Commit();

        std::wcout << timer::to_msec(t2 - t1, rate) << std::endl;
#endif

        // Export to graphviz
        // dtm->export_to_graphviz(); 
    }
    catch (Exception& e)
    {
        std::cerr << e.Message() << std::endl;
    }
    return 0;
}
