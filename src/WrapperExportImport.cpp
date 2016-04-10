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

void DataManager::export_to_graphviz() const
{
    ExportManager * expMngr = new MyExport();
    g->Export(L"test.dot", Graphviz, expMngr);
    delete expMngr; 
}

void DataManager::export_nodes_to_csv(int16_t type, const std::wstring &file_name) const
{
    if (g != NULL)
    {
        // Type of node to export
        type_t exportType;
        // All attributes of type to export
        AttributeList attrs;

        switch(type)
        {
            case GNOME: 
                {  
                    // Export all GNOMEs to csv
                    exportType = g->FindType(L"Gnome");
                    // Export attributes of GNOME
                    attrs.Add(g->FindAttribute(exportType, L"Id"));
                    attrs.Add(g->FindAttribute(exportType, L"Name"));
                    attrs.Add(g->FindAttribute(exportType, L"Age"));
                    attrs.Add(g->FindAttribute(exportType, L"Strength"));
                    attrs.Add(g->FindAttribute(exportType, L"Intelligence"));
                    attrs.Add(g->FindAttribute(exportType, L"Charisma"));
                    attrs.Add(g->FindAttribute(exportType, L"Skills"));
                    break;
                }
            case MINE:
                {
                    // Export all MINEs to csv
                    exportType = g->FindType(L"Mine");  
                    // Export attributes of MINE
                    attrs.Add(g->FindAttribute(exportType, L"Id"));
                    attrs.Add(g->FindAttribute(exportType, L"Name")); 
                    break;
                }
            case DRAGON: 
                {
                    // Export all DRAGONSs to csv
                    exportType = g->FindType(L"Dragon");
                    // Export attributes of DRAGON 
                    attrs.Add(g->FindAttribute(exportType, L"Id"));
                    attrs.Add(g->FindAttribute(exportType, L"Name"));
                    attrs.Add(g->FindAttribute(exportType, L"Color"));
                    attrs.Add(g->FindAttribute(exportType, L"Cost"));
                    attrs.Add(g->FindAttribute(exportType, L"Size"));
                    attrs.Add(g->FindAttribute(exportType, L"Age"));
                    attrs.Add(g->FindAttribute(exportType, L"Strength"));
                    attrs.Add(g->FindAttribute(exportType, L"Charisma"));
                    attrs.Add(g->FindAttribute(exportType, L"Skills"));
                    break;
                }  
            case ORE:
                {   
                    // Export all OREs to csv
                    exportType = g->FindType(L"Ore");  
                    // Export attributes of ORE 
                    attrs.Add(g->FindAttribute(exportType, L"Id"));
                    attrs.Add(g->FindAttribute(exportType, L"Name"));
                    break; 
                }
        }

        // configure CSV writer
        CSVWriter csv;
        csv.SetSeparator(L"|");
        csv.SetAutoQuotes(true);
        csv.Open(file_name);

        NodeTypeExporter nte(csv, *g, exportType, attrs);
        nte.Run();
        csv.Close();
    }
}

void DataManager::export_edges_to_csv(int16_t type, int16_t type_tail, int16_t type_head, const std::wstring &file_name) const
{
    if (g != NULL)
    {
        // Type of edge to export
        type_t exportType;
        // All attributes of type to export
        AttributeList attrs;
        
        // configure CSV writer
        CSVWriter csv;
        csv.SetSeparator(L"|");
        csv.SetAutoQuotes(true);
        csv.Open(file_name);
        
        switch(type)
        {
            case BELONG: 
                {
                    exportType = g->FindType(L"Belong");
                    attrs.Add(g->FindAttribute(exportType, L"Profession"));

                    // If tail is a GNOME or a DRAGON
                    switch(type_tail)
                    {
                        case GNOME: 
                            {
                                // 2 - head position in .csv file
                                // 1 - tail position in .csv file
                                EdgeTypeExporter ete(csv, *g, exportType, attrs, 2, 1, 
                                        g->FindAttribute(g->FindType(L"Mine"), L"Id"), 
                                            g->FindAttribute(g->FindType(L"Gnome"), L"Id"));
                                ete.Run();
                                break;
                            }
                        case DRAGON:
                            {
                                // 2 - head position in .csv file
                                // 1 - tail position in .csv file
                                EdgeTypeExporter ete(csv, *g, exportType, attrs, 2, 1, 
                                        g->FindAttribute(g->FindType(L"Mine"), L"Id"), 
                                            g->FindAttribute(g->FindType(L"Dragon"), L"Id"));
                                ete.Run();
                                break;
                            }
                    }
                    break;
                }
            case MINES: 
                {
                    // Export all DRAGONSs to csv
                    exportType = g->FindType(L"Mines");

                    // 2 - head position in .csv file
                    // 1 - tail position in .csv file
                    EdgeTypeExporter ete(csv, *g, exportType, attrs, 2, 1, g->FindAttribute(g->FindType(L"Ore"), L"Id"), 
                                g->FindAttribute(g->FindType(L"Mine"), L"Id"));
                    ete.Run();
                    break;
                }
        }

        csv.Close();
    }
}

void DataManager::import_nodes_from_csv(int16_t type, const std::wstring &file_name) const
{
    if (g != NULL)
    {
        // Type of node to export
        type_t importType;
        // All attributes of type to export
        AttributeList attrs;
        // Positions of attributes in csv file (number of columns)
        Int32List attrPos;

        switch(type)
        {
            case GNOME: 
                {  
                    // Export all GNOMEs from csv
                    importType = g->FindType(L"Gnome");
                    // Export attributes of GNOME
                    attrs.Add(g->FindAttribute(importType, L"Id"));
                    attrs.Add(g->FindAttribute(importType, L"Name"));
                    attrs.Add(g->FindAttribute(importType, L"Age"));
                    attrs.Add(g->FindAttribute(importType, L"Strength"));
                    attrs.Add(g->FindAttribute(importType, L"Intelligence"));
                    attrs.Add(g->FindAttribute(importType, L"Charisma"));
                    attrs.Add(g->FindAttribute(importType, L"Skills"));

                    for (int i = 0; i < 7; ++i)
                    {
                        attrPos.Add(i);
                    }                    

                    break;
                }
            case MINE:
                {
                    // Import all MINEs from csv
                    importType = g->FindType(L"Mine");  
                    // Import attributes of MINE
                    attrs.Add(g->FindAttribute(importType, L"Id"));
                    attrs.Add(g->FindAttribute(importType, L"Name")); 

                    for (int i = 0; i < 2; ++i)
                    {
                        attrPos.Add(i);
                    }

                    break;
                }
            case DRAGON: 
                {
                    // Import all DRAGONSs from csv
                    importType = g->FindType(L"Dragon");
                    // Import attributes of DRAGON 
                    attrs.Add(g->FindAttribute(importType, L"Id"));
                    attrs.Add(g->FindAttribute(importType, L"Name"));
                    attrs.Add(g->FindAttribute(importType, L"Color"));
                    attrs.Add(g->FindAttribute(importType, L"Cost"));
                    attrs.Add(g->FindAttribute(importType, L"Size"));
                    attrs.Add(g->FindAttribute(importType, L"Age"));
                    attrs.Add(g->FindAttribute(importType, L"Strength"));
                    attrs.Add(g->FindAttribute(importType, L"Charisma"));
                    attrs.Add(g->FindAttribute(importType, L"Skills"));

                    for (int i = 0; i < 9; ++i)
                    {
                        attrPos.Add(i);
                    }

                    break;
                }  
            case ORE:
                {   
                    // Import all OREs from csv
                    importType = g->FindType(L"Ore");  
                    // Import attributes of ORE 
                    attrs.Add(g->FindAttribute(importType, L"Id"));
                    attrs.Add(g->FindAttribute(importType, L"Name"));

                    for (int i = 0; i < 2; ++i)
                    {
                        attrPos.Add(i);
                    }

                    break; 
                }
        }

        // configure CSV writer
        CSVReader csv;
        csv.SetSeparator(L"|");
        csv.SetStartLine(0);
        csv.Open(file_name);

        // import node type
        NodeTypeLoader ntl(csv, *g, importType, attrs, attrPos);
        ntl.SetLogError(file_name + L".log");
        ntl.Run();
        csv.Close();
    }
}

void DataManager::import_edges_from_csv(int16_t type, int16_t type_tail, int16_t type_head, const std::wstring &file_name) const
{
    if (g != NULL)
    {
        // Type of edge to export
        type_t importType;
        // All attributes of type to export
        AttributeList attrs;
        
        // configure CSV writer
        CSVReader csv;
        csv.SetSeparator(L"|");
        csv.SetStartLine(0);
        csv.Open(file_name);
        
        switch(type)
        {
            case BELONG: 
                {
                    importType = g->FindType(L"Belong");
                    attrs.Add(g->FindAttribute(importType, L"Profession"));

                    // If tail is a GNOME or a DRAGON
                    switch(type_tail)
                    {
                        case GNOME: 
                            {
                                Int32List prof_pos;
                                prof_pos.Add(0);
                                // 2 - head position in .csv file
                                // 1 - tail position in .csv file
                                EdgeTypeLoader ete(csv, *g, importType, attrs, prof_pos, 2, 1, 
                                        g->FindAttribute(g->FindType(L"Mine"), L"Id"), 
                                            g->FindAttribute(g->FindType(L"Gnome"), L"Id"));
                                ete.Run();
                                break;
                            }
                        case DRAGON:
                            {
                                Int32List prof_pos;
                                prof_pos.Add(0);
                                // 2 - head position in .csv file
                                // 1 - tail position in .csv file
                                EdgeTypeLoader ete(csv, *g, importType, attrs, prof_pos, 2, 1, 
                                        g->FindAttribute(g->FindType(L"Mine"), L"Id"), 
                                            g->FindAttribute(g->FindType(L"Dragon"), L"Id"));
                                ete.Run();
                                break;
                            }
                    }
                    break;
                }
            case MINES: 
                {
                    // Export all DRAGONSs to csv
                    importType = g->FindType(L"Mines");

                    Int32List attrs_pos;
                    // 2 - head position in .csv file
                    // 1 - tail position in .csv file
                    EdgeTypeLoader ete(csv, *g, importType, attrs, attrs_pos, 2, 1, g->FindAttribute(g->FindType(L"Ore"), L"Id"), 
                                g->FindAttribute(g->FindType(L"Mine"), L"Id"));
                    ete.Run();
                    break;
                }
        }

        csv.Close();
    }
}

void DataManager::import_all() const
{
    // IMPORT NODES FROM CSV
    import_nodes_from_csv(GNOME, L"export/gnome.csv");
    import_nodes_from_csv(DRAGON, L"export/dragon.csv");
    import_nodes_from_csv(MINE, L"export/mine.csv");
    import_nodes_from_csv(ORE, L"export/ore.csv");

    // IMPORT EDGES FROM CSV
    import_edges_from_csv(BELONG, GNOME, MINE, L"export/belong_gnome.csv");
    import_edges_from_csv(BELONG, DRAGON, MINE, L"export/belong_dragon.csv");
    import_edges_from_csv(MINES, GNOME, MINE, L"export/mines.csv");
}

void DataManager::export_all() const
{
    // EXPORT NODES TO CSV
    export_nodes_to_csv(GNOME, L"export/gnome.csv");
    export_nodes_to_csv(DRAGON, L"export/dragon.csv");
    export_nodes_to_csv(MINE, L"export/mine.csv");
    export_nodes_to_csv(ORE, L"export/ore.csv");
    // EXPORT EDGES TO CSV
    export_edges_to_csv(BELONG, GNOME, MINE, L"export/belong_gnome.csv");
    export_edges_to_csv(BELONG, DRAGON, MINE, L"export/belong_dragon.csv");
    export_edges_to_csv(MINES, GNOME, MINE, L"export/mines.csv");
}
