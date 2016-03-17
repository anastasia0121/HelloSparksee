#ifndef __IFMO_DISTRIBUTED_CLASS_TYPES__H
#define __IFMO_DISTRIBUTED_CLASS_TYPES__H
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

#include "MyExport.h"

struct Movie
{
    struct types
    {
        type_t type;
        attr_t id;
        attr_t title;
        attr_t year;
    } types;

    struct values
    {
        long id;
        std::wstring title;
        int year;
    } values;
};

struct People
{
    struct types
    {
        type_t type;
        attr_t id;
        attr_t name;
    } types;

    struct values
    {
        long id;
        std::wstring name;
    }values;
};

struct Cast
{
    struct types
    {
        type_t type;
        attr_t character;
    } types;

    struct values
    {
        std::wstring character;
    }values;
};

struct Directs
{
    struct types
    {
        type_t type;
    } types;
};

enum {
    MOVIE,
    PEOPLE,
    CAST,
    DIRECTS
};

#endif // __IFMO_DISTRIBUTED_CLASS_TYPES__H
