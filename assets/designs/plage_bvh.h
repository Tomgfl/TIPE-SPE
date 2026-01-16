#ifndef PLAGE_H 
#define PLAGE_H 

#include "options.h"
#include "utiles.h"
#include "vector.h"
#include "sdf.h"
#include "objets.h"
#include "bvh.h"

BVHNode* BVH_eau( );
BVHNode* BVH_Feuilles( );
BVHNode* BVH_sable( );
BVHNode* BVH_socle( );
BVHNode* BVH_SolPlage( );
BVHNode* BVH_TranzatPied( );
BVHNode* BVH_TranzatSupport( );
BVHNode* BVH_Tronc( );
BVHNode* BVH_Plage();
#endif