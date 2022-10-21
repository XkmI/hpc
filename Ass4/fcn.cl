__kernel
void
diffusion(
    __global const float *old,
    __global float *new,
    float diff_const
    )
{
  int ix = get_global_id(0) + 1;
  int jx = get_global_id(1) + 1; 
  int width = get_global_size(1) + 2;
  float sum4 =  old[ix * width + jx - 1] + old[ix * width + jx + 1] + old[(ix - 1) * width + jx] + old[(ix + 1) * width + jx];
  new[ix * width + jx] = old[ix * width + jx] + diff_const * (sum4 / 4 - old[ix * width + jx]);
}
