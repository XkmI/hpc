__kernel
void
mat_mul(
    __global const float *a,
    __global const float *b,
    __global float *c,
    int width_a,
    int width_b
    )
{
  int ix = get_global_id(0);
  int iy = get_global_id(1);
  
  float value = 0;
  for ( int kx = 0; kx < width_a; ++kx ) {
    float a_elt = a[iy * width_a + kx];
    float b_elt = b[kx * width_b + ix];
    value += a_elt * b_elt;
  }
  
  c[iy * width_b + ix] = value;
}

// Koden Linnea glömde

__kernel
void
dot_prod_mul(
    __global const float *a,
    __global const float *b,
    __global float *c
    )
{
  int ix = get_global_id(0);
  c[ix] = a[ix] * b[ix];
}

__kernel
void
reduction(
  __global float *c,
  __local float *scratch,
  __const int sz,
  __global float *result
  )
{
  int gsz = get_global_size(0);
  int gix = get_global_id(0);
  int lsz = get_local_size(0);
  int lix = get_local_id(0);

  float acc = 0;
  for ( int cix = get_global_id(0); cix < sz; cix += gsz )
    acc += c[cix];

  scratch[lix] = acc;
  barrier(CLK_LOCAL_MEM_FENCE);

  for(int offset = lsz/2; offset > 0; offset /= 2) {
    if ( lix < offset )
      scratch[lix] += scratch[lix+offset];
    barrier(CLK_LOCAL_MEM_FENCE);
  }

  if ( lix == 0 )
    result[get_group_id(0)] = scratch[0];
}