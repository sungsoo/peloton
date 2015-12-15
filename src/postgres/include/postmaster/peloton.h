/*-------------------------------------------------------------------------
 *
 * peloton.h
 * file description
 *
 * Copyright(c) 2015, CMU
 *
 * /peloton/src/backend/bridge/peloton.h
 *
 *-------------------------------------------------------------------------
 */

#ifndef PELOTON_H
#define PELOTON_H

#include "backend/common/types.h"
#include "backend/bridge/ddl/bootstrap.h"
#include "backend/planner/abstract_plan.h"
#include "backend/bridge/dml/mapper/dml_utils.h"

#include "libpq/libpq-be.h"
#include "nodes/execnodes.h"
#include "utils/memutils.h"
#include "tcop/dest.h"

//===--------------------------------------------------------------------===//
// GUC Variables
//===--------------------------------------------------------------------===//

/* Possible values for peloton_logging_mode GUC */
typedef enum LoggingType
{
  LOGGING_TYPE_INVALID, /* No logging */

  LOGGING_TYPE_ARIES,   /* Aries */
  LOGGING_TYPE_PELOTON  /* Peloton */
} LoggingType;

extern LoggingType peloton_logging_mode;

/* Possible values for peloton_caching_mode GUC */
typedef enum CachingType
{
  CACHING_OFF,   /* Off */
  CACHING_ON   /* On */
} CachingType;

// Caching mode
extern CachingType peloton_caching_mode;

// Cache size for tile cache
extern int peloton_tile_cache_size;

// Enable query compilation module ?
extern bool peloton_enable_query_compilation;

//===--------------------------------------------------------------------===//
// Peloton_Status     Sent by the peloton to share the status with backend.
//===--------------------------------------------------------------------===//

typedef struct peloton_status {
  peloton::Result m_result;
  List *m_result_slots;

  // number of tuples processed
  uint32_t m_processed;

  peloton_status(){
    m_processed = 0;
    m_result = peloton::RESULT_SUCCESS;
    m_result_slots = nullptr;
  }

} peloton_status;

extern bool logging_on;

//===--------------------------------------------------------------------===//
// Functions called from postmaster
//===--------------------------------------------------------------------===//

extern bool IsPelotonQuery(List *relationOids);

//===--------------------------------------------------------------------===//
// Functions called from postgres, utility, and execMain
//===--------------------------------------------------------------------===//

extern void peloton_bootstrap();

extern void peloton_ddl(Node *parsetree);

extern void peloton_dml(PlanState *planstate,
                        bool sendTuples,
                        DestReceiver *dest,
                        TupleDesc tuple_desc,
                        const char *prepStmtName);

#endif   /* PELOTON_H */

