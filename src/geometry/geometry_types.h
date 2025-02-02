/*
 * Copyright Redis Ltd. 2016 - present
 * Licensed under your choice of the Redis Source Available License 2.0 (RSALv2) or
 * the Server Side Public License v1 (SSPLv1).
 */

#pragma once

typedef void* GEOMETRY; // TODO: GEOMETRY Not uppercase
#define GEO_VARIANTS(X) X(Cartesian) X(Geographic)
#define GEO_VARIANT_NAMES(X) X(Cartesian,FLAT) X(Geographic,SPHERICAL)
typedef enum {
  GEOMETRY_LIB_TYPE_NONE = 0,
  GEOMETRY_LIB_TYPE_BOOST_GEOMETRY = 1,
  GEOMETRY_LIB_TYPE_S2 = 2,
  GEOMETRY_LIB_TYPE__NUM,
} GEOMETRY_LIB_TYPE; // TODO: GEOMETRY Not uppercase

typedef enum {
  GEOMETRY_FORMAT_NONE = 0,
  GEOMETRY_FORMAT_WKT = 1,
  GEOMETRY_FORMAT_GEOJSON = 2,
} GEOMETRY_FORMAT; // TODO: GEOMETRY Not uppercase

typedef enum {
#define X(variant) \
  GEOMETRY_COORDS_##variant,
GEO_VARIANTS(X)
#undef X
  GEOMETRY_COORDS__NUM,
} GEOMETRY_COORDS;

typedef enum QueryType {
  CONTAINS,
  WITHIN,
} QueryType;


static inline const char *GeometryCoordsToName(GEOMETRY_COORDS coords) {
#define X(variant,name) \
  case GEOMETRY_COORDS_##variant: return #name;
  switch(coords) {
    GEO_VARIANT_NAMES(X)
    default: return "UNKNOWN";
  }
#undef X
}
