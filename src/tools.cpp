// Copyright 2020, the Aether Development Team (see doc/dev_team.md for members)
// Full license can be found in License.md

#include "../include/aether.h"

// -----------------------------------------------------------------------------
// Translate an fvec into a vector
// -----------------------------------------------------------------------------

std::vector<float> make_vector_from_fvec(fvec in_fvec) {

  int64_t nPts = in_fvec.n_elem;
  std::vector<float> out_vector(nPts);
  for (int64_t iPt = 0; iPt < nPts; iPt++)
    out_vector[iPt] = in_fvec(iPt);
  return out_vector;
}

// -----------------------------------------------------------------------------
// Translate a vector into an fvec
// -----------------------------------------------------------------------------

fvec make_fvec_from_vector(std::vector<float> in_vector) {

  int64_t nPts = in_vector.size();
  fvec out_fvec(nPts);
  for (int64_t iPt = 0; iPt < nPts; iPt++)
    out_fvec(iPt) = in_vector[iPt];
  return out_fvec;
}

// -----------------------------------------------------------------------------
// Make a vector of fcubes
// -----------------------------------------------------------------------------

std::vector<fcube> make_cube_vector(int64_t nLons,
				    int64_t nLats,
				    int64_t nAlts,
				    int64_t nComps) {
  std::vector<fcube> vec;
  fcube one_component(nLons, nLats, nAlts);
  one_component.zeros();
  for (int64_t iComp = 0; iComp < nComps; iComp++)
    vec.push_back(one_component);
  return vec;
}

// -----------------------------------------------------------------------------
// Dot product
// This assumes a 3-component vector of fcubes:
// -----------------------------------------------------------------------------

fcube dot_product(std::vector<fcube> vec1,
		  std::vector<fcube> vec2) {
  // create the dot product:
  fcube dot = vec1[0];
  dot.zeros();
  for (int64_t iComp = 0; iComp < 3; iComp++)
    dot = dot + vec1[iComp] % vec2[iComp];
  return dot;  
}

// -----------------------------------------------------------------------------
// Cross product
// This assumes a 3-component vector of fcubes:
// -----------------------------------------------------------------------------

std::vector<fcube> cross_product(std::vector<fcube> vec1,
				 std::vector<fcube> vec2) {
  std::vector<fcube> cross;
  // East:
  cross.push_back(vec1[1] % vec2[2] - vec1[2] % vec2[1]);
  // North:
  cross.push_back(-(vec1[0] % vec2[2] - vec1[2] % vec2[0]));
  // Vertical:
  cross.push_back(vec1[0] % vec2[1] - vec1[1] % vec2[0]);
  return cross;  
}
