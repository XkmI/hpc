__kernel
void
diffusion(
    __global const float *old,
    __global float *new,
    int diff_const,
    )
{
  int ix = get_global_id(0) + 1;
  int jx = get_global_id(1) + 1; 
  float sum4 =  old[ix * width + jx - 1] + old[ix * width + jx + 1] + old[(ix - 1) * width + jx] + old[(ix + 1) * width + jx]
  new[ix * width + jx] = old[ix * width + jx] + diff_const * (sum4 / 4 - old[ix * width + jx])
}

// // Koden Linnea glömde
// 
// __kernel
// void
// dot_prod_mul(
//     __global const float *a,
//     __global const float *b,
//     __global float *c
//     )
// {
//   int ix = get_global_id(0);
//   c[ix] = a[ix] * b[ix];
// }
// 
// __kernel
// void
// reduction(
//   __global float *c,
//   __local float *scratch,
//   __const int sz,
//   __global float *result
//   )
// {
//   int gsz = get_global_size(0);
//   int gix = get_global_id(0);
//   int lsz = get_local_size(0);
//   int lix = get_local_id(0);
// 
//   float acc = 0;
//   for ( int cix = get_global_id(0); cix < sz; cix += gsz )
//     acc += c[cix];
// 
//   scratch[lix] = acc;
//   barrier(CLK_LOCAL_MEM_FENCE);
// 
//   for(int offset = lsz/2; offset > 0; offset /= 2) {
//     if ( lix < offset )
//       scratch[lix] += scratch[lix+offset];
//     barrier(CLK_LOCAL_MEM_FENCE);
//   }
// 
//   if ( lix == 0 )
//     result[get_group_id(0)] = scratch[0];
// }
