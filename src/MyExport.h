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
      type_t peopleTypeId;
      attr_t nameAttrId;
      type_t moviesTypeId;
      attr_t titleAttrId;
      type_t castTypeId;
      type_t directsTypeId;
      Value v;
   public:
      MyExport()
         : g(NULL), peopleTypeId(Type::InvalidType), nameAttrId(Attribute::InvalidAttribute), 
         moviesTypeId(Type::InvalidType), titleAttrId(Attribute::InvalidAttribute), 
         castTypeId(Type::InvalidType), directsTypeId(Type::InvalidType) {};

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
