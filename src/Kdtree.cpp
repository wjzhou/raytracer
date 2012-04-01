#include <iostream>
#include <memory>
#include <new>
#include "common.hpp"
struct KdNode_base_hook
{
  Vec3f kdpos;
  short plane;
};

class KdNode;
struct KdNearestNodes {
  int max;
  int found;
  int got_heap;
  Vec3f pos;
  float *dist2;
  const KdNode **index;
};

//*** photon
struct Photon: public KdNode_base_hook{
  Vec3f indir;
  Color power;
};
typedef Photon KdNode;

//<template class KdNode>
class KdTree
{
public:
  KdTree(size_t max_nodes);
  void store(KdNode& kdNode);
  void balance(void);
  void locate(void);
  void irradiance_estimate(
    float irrad[3],                // returned irradiance
    const float pos[3],            // surface position
    const float normal[3],         // surface normal at pos
    const float max_dist,          // max distance to look for photons
    const int nphotons ) const;    // number of photons to use

  void locate_photons(
    NearestPhotons *const np,      // np is used to locate the photons
    const int index ) const;       // call with index = 1
  
private:
  Vec3f bbox_min;
  Vec3f bbox_max;
  void balance_segment(
    KdNode **pbal,
    KdNode **porg,
    const int index,
    const int start,
    const int end );

  void median_split(
    KdNode **p,
    const int start,
    const int end,
    const int median,
    const int axis );
  KdNode* nodes;
  size_t stored_nodes;
  size_t max_nodes;
  size_t half_stored_photons;
  int prev_scale;
};

KdTree::KdTree(const int a_max_nodes)
{
  stored_nodes = 0;
  prev_scale = 1;
  max_nodes = a_max_nodes;

  nodes = new (nothrow) KdNode[max_nodes+1];

  if (nodes == NULL) {
    std::cerr<<"Out of memory initializing photon map\n");
    std::exit(7);
  }

  bbox_min[0] = bbox_min[1] = bbox_min[2] = 1e8f;
  bbox_max[0] = bbox_max[1] = bbox_max[2] = -1e8f;
}


KdTree :: ~KdTree()
{
  delete[] nodes;
}

void irradiance_estimate(
  Vec3f irrad,                // returned irradiance
  const Vec3f pos,            // surface position
  const Vec3f normal,         // surface normal at pos
  const float max_dist,          // max distance to look for photons
  const int nphotons ) const     // number of photons to use
//**********************************************
{
  irrad[0] = irrad[1] = irrad[2] = 0.0;

  KdNearestNodes np; //the origin is nearest photon
  np.dist2 = (float*)alloca( sizeof(float)*(nphotons+1) );
  np.index = (const Photon**)alloca( sizeof(Photon*)*(nphotons+1) );

  np.pos[0] = pos[0]; np.pos[1] = pos[1]; np.pos[2] = pos[2];
  np.max = nphotons;
  np.found = 0;
  np.got_heap = 0;
  np.dist2[0] = max_dist*max_dist;

  // locate the nearest photons
  locate_nodes( &np, 1 );

  // if less than 8 photons return
  if (np.found<8)
    return;

  Vec3f pdir;

  // sum irradiance from all photons
  for (int i=1; i<=np.found; i++) {
    const Photon *p = np.index[i];
    // the photon_dir call and following if can be omitted (for speed)
    // if the scene does not have any thin surfaces
    //    photon_dir( pdir, p );
    pdir=p->indir;
    if ( (pdir[0]*normal[0]+pdir[1]*normal[1]+pdir[2]*normal[2]) < 0.0f ) {
      irrad[0] += p->power[0];
      irrad[1] += p->power[1];
      irrad[2] += p->power[2];
    }
  }

  const float tmp=(1.0f/M_PI)/(np.dist2[0]);	// estimate of density

  irrad[0] *= tmp;
  irrad[1] *= tmp;
  irrad[2] *= tmp;
}

void KdTree :: locate_nodes(
  KdNearestNodes *const np,
  const int index ) const
{
  const KdNode *p = &nodes[index];
  float dist1;

  if (index<half_stored_photons) {
    dist1 = np->pos[ p->plane ] - p->kdpos[ p->plane ];

    if (dist1>0.0) { // if dist1 is positive search right plane
      locate_photons( np, 2*index+1 );
      if ( dist1*dist1 < np->dist2[0] )
        locate_photons( np, 2*index );
    } else {         // dist1 is negative search left first
      locate_photons( np, 2*index );
      if ( dist1*dist1 < np->dist2[0] )
        locate_photons( np, 2*index+1 );
    }
  }

  // compute squared distance between current photon and np->pos

  dist1 = p->kdpos[0] - np->pos[0];
  float dist2 = dist1*dist1;
  dist1 = p->kdpos[1] - np->pos[1];
  dist2 += dist1*dist1;
  dist1 = p->kdpos[2] - np->pos[2];
  dist2 += dist1*dist1;
  
  if ( dist2 < np->dist2[0] ) {
    // we found a photon :) Insert it in the candidate list

    if ( np->found < np->max ) {
      // heap is not full; use array
      np->found++;
      np->dist2[np->found] = dist2;
      np->index[np->found] = p;
    } else {
      int j,parent;

      if (np->got_heap==0) { // Do we need to build the heap?
        // Build heap
        float dst2;
        const KdNode *phot;
        int half_found = np->found>>1;
        for ( int k=half_found; k>=1; k--) {
          parent=k;
          phot = np->index[k];
          dst2 = np->dist2[k];
          while ( parent <= half_found ) {
            j = parent+parent;
            if (j<np->found && np->dist2[j]<np->dist2[j+1])
              j++;
            if (dst2>=np->dist2[j])
              break;
            np->dist2[parent] = np->dist2[j];
            np->index[parent] = np->index[j];
            parent=j;
          }
          np->dist2[parent] = dst2;
          np->index[parent] = phot;
        }
        np->got_heap = 1;
      }

      // insert new photon into max heap
      // delete largest element, insert new and reorder the heap

      parent=1;
      j = 2;
      while ( j <= np->found ) {
        if ( j < np->found && np->dist2[j] < np->dist2[j+1] )
          j++;
        if ( dist2 > np->dist2[j] )
          break;
        np->dist2[parent] = np->dist2[j];
        np->index[parent] = np->index[j];
        parent = j;
        j += j;
      }
      np->index[parent] = p;
      np->dist2[parent] = dist2;

      np->dist2[0] = np->dist2[1];
    }
  }
}



void KdTree :: store(
  const Vec3f power,
  const Vec3f pos,
  const Vec3f dir)
//***************************
{
  if (stored_photons>=max_photons)
    return;

  stored_photons++;
  KdNode *const node = &nodes[stored_photons];

  for (int i=0; i<3; i++) {
    node->kdpos[i] = pos[i];

    if (pos[i] < bbox_min[i])
      bbox_min[i] = pos[i];
    if (pos[i] > bbox_max[i])
      bbox_max[i] = pos[i];
    
    node->power[i] = power[i];
    node->indir[i]=dir[i];
  }
}

void scale_photon_power(KdTree* tree, const float scale )
//********************************************************
{
  for (int i=tree->prev_scale; i<=tree->stored_photons; i++) {
    tree->nodes[i].power *= scale;
  }
  prev_scale = stored_photons;
}

//<template class Node>
void KdTree::store(KdNode& node)
{
  assert(stored_nodes<max_nodes); //too many photons
  kdPhotons[++stored_nodes]=node;
  for (int i=0; i<3; i++) {
    if(node.kdpos[i]<bbox_min[i])
      bbox_min[i]=node.kdpos[i];
    if(node.kdpos[i]>bbox_max[i])
      bbox_max[i]=node.kdpos[i];
  }
}

void KdTree::balance(void)
{
  if(stored_nodes>1) {
    Kdnode **pa1 = new (Kdnode*)[stored_nodes+1];
    Kdnode **pa2 = new (Kdnode*)[stored_nodes+1];

    for(int i=0; i<stored_nodes; i++ )
      pa2[i]=&nodes[i];

    balance_segment(pa1, pa2, 1, 1, stored_nodes);
    delete[] pa2;

    int d, j=1, foo=1;
    KdNode tmpNode = nodes[j];

    for (int i=1; i<=stored_nodes; i++) {
      d=pa1[j]-nodes;
      pa1[j] = NULL;
      if (d != foo)
        nodes[j] = nodes[d];
      else {
        nodes[j] = tmpNode;

        if (i<stored_nodes) {
          for (;foo<=stored_nodes; foo++)
            if (pa1[foo] != NULL)
              break;
          tmpNode = nodes[foo];
          j = foo;
        }
        continue;
      }
      j = d;
    }
    delete[] pa1;
  }
  half_stored_nodes = stored_nodes/2-1;
}

  
static inline void swap(KdNode*& a, KdNode*& b)
{
  KdNode* tmp=a;
  a=b;
  b=tmp;
}

void Photon_map :: median_split(
  KdNode **p,
  const int start,               // start of photon block in array
  const int end,                 // end of photon block in array
  const int median,              // desired median number
  const int axis )               // axis to split along
//*****************************************************************
{
  int left = start;
  int right = end;

  while ( right > left ) {
    const float v = p[right]->kdpos[axis];
    int i=left-1;
    int j=right;
    for (;;) {
      while ( p[++i]->kdpos[axis] < v )
        ;
      while ( p[--j]->kdpos[axis] > v && j>left )
        ;
      if ( i >= j )
        break;
      swap(p,i,j);
    }

    swap(p,i,right);
    if ( i >= median )
      right=i-1;
    if ( i <= median )
      left=i+1;
  }
}

  
// See "Realistic image synthesis using Photon Mapping" chapter 6
// for an explanation of this function
//****************************
void KdTree :: balance_segment(
  KdNode **pbal,
  KdNode **porg,
  const int index,
  const int start,
  const int end )
//****************************
{
  //--------------------
  // compute new median
  //--------------------

  int median=1;
  while ((4*median) <= (end-start+1))
    median += median;

  if ((3*median) <= (end-start+1)) {
    median += median;
    median += start-1;
  } else	
    median = end-median+1;

  //--------------------------
  // find axis to split along
  //--------------------------

  int axis=2;
  if ((bbox_max[0]-bbox_min[0])>(bbox_max[1]-bbox_min[1]) &&
      (bbox_max[0]-bbox_min[0])>(bbox_max[2]-bbox_min[2]))
    axis=0;
  else if ((bbox_max[1]-bbox_min[1])>(bbox_max[2]-bbox_min[2]))
    axis=1;

  //------------------------------------------
  // partition photon block around the median
  //------------------------------------------

  median_split( porg, start, end, median, axis );

  pbal[ index ] = porg[ median ];
  pbal[ index ]->plane = axis;

  //----------------------------------------------
  // recursively balance the left and right block
  //----------------------------------------------

  if ( median > start ) {
    // balance left segment
    if ( start < median-1 ) {
      const float tmp=bbox_max[axis];
      bbox_max[axis] = pbal[index]->kdpos[axis];
      balance_segment( pbal, porg, 2*index, start, median-1 );
      bbox_max[axis] = tmp;
    } else {
      pbal[ 2*index ] = porg[start];
    }
  }

  if ( median < end ) {
    // balance right segment
    if ( median+1 < end ) {
      const float tmp = bbox_min[axis];		
      bbox_min[axis] = pbal[index]->kdpos[axis];
      balance_segment( pbal, porg, 2*index+1, median+1, end );
      bbox_min[axis] = tmp;
    } else {
      pbal[ 2*index+1 ] = porg[end];
    }
  }	
}
