#ifndef __IFMO_DISTRIBUTED_CLASS_MY_EXPORT__H
#define __IFMO_DISTRIBUTED_CLASS_MY_EXPORT__H

#include <stdio.h>
#include "gdb/Sparksee.h"
#include "gdb/Database.h"
#include "gdb/Session.h"
#include "gdb/Graph.h"
#include "gdb/Objects.h"
#include "gdb/ObjectsIterator.h"
#include "gdb/Stream.h"
#include "gdb/Export.h"
#include "io/CSVWriter.h"
#include "io/NodeTypeExporter.h"
#include <assert.h>

using namespace sparksee::gdb;
using namespace sparksee::io;

class MyExport : public ExportManager {
   private:
      Graph * g;

      type_t type_gnome;
      attr_t gnome_name;

      type_t type_mine;
      attr_t mine_name;

      type_t type_ore;
      attr_t ore_name;

      type_t type_dragon;
      attr_t dragon_name;

      type_t type_belong;
      type_t type_directs;
      type_t type_mines;

      Value v;
   public:
      MyExport()
         : g(NULL), 
         type_gnome(Type::InvalidType), gnome_name(Attribute::InvalidAttribute), 
         type_mine(Type::InvalidType), mine_name(Attribute::InvalidAttribute), 
         type_ore(Type::InvalidType), ore_name(Attribute::InvalidAttribute), 
         type_dragon(Type::InvalidType), dragon_name(Attribute::InvalidAttribute), 
         type_belong(Type::InvalidType), 
         type_directs(Type::InvalidType),
         type_mines(Type::InvalidType) {};

      virtual void Prepare(Graph * graph);

      virtual void Release();

      virtual bool_t GetGraph(GraphExport& ge);

      virtual bool_t GetNodeType(type_t nodetype , NodeExport& ne);

      virtual bool_t GetEdgeType(type_t edgetype , EdgeExport& ee);

      virtual bool_t GetNode(oid_t nodeOID , NodeExport& ne);

      virtual bool_t GetEdge(oid_t edgeOID , EdgeExport& ee);

      virtual bool_t EnableType(type_t type);
};
#endif // __IFMO_DISTRIBUTED_CLASS_MY_EXPORT__H
