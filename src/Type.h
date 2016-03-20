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

struct Gnome
{
    struct types
    {
        type_t type;
        attr_t id;
        attr_t name;
        attr_t age;
        attr_t str;
        attr_t intel;
        attr_t cha;
        attr_t skill;
    } types;

    struct values
    {
        long id;
        std::wstring name;
        int age;
        int str;
        int intel;
        int cha;
        std::wstring skill;
    } values;
};

struct Dragon
{
    struct types
    {
        type_t type;
        attr_t id;
        attr_t name;
        attr_t color;
        attr_t cost;
        attr_t size;
        attr_t age;
        attr_t str;
        attr_t cha;
        attr_t skill;
    } types;

    struct values
    {
        long id;
        std::wstring name;
        long color;
        int cost;
        int size;
        int age;
        int str;
        int intel;
        int cha;
        std::wstring skill;
    } values;
};

struct Mine
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

struct Ore
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

struct Belong
{
    struct types
    {
        type_t type;
        attr_t prof;
    } types;

    struct values
    {
        std::wstring prof;
    }values;
};

struct Directs
{
    struct types
    {
        type_t type;
    } types;
};

struct Mines
{
    struct types
    {
        type_t type;
    } types;
};

enum {
    GNOME,
    MINE,
    DRAGON,
    ORE,
    DIRECTS,
    BELONG,
    MINES
};

struct GraphObjects
{
    struct Gnome gnome;
    struct Mine mine;
    struct Dragon dragon;
    struct Ore ore;
    struct Belong belong;
    struct Directs directs;
    struct Mines mines;
};

#endif // __IFMO_DISTRIBUTED_CLASS_TYPES__H
