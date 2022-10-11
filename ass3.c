#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <complex.h>

typedef struct {
  int val;
  char pad[60]; // cacheline - sizeof(int)
} int_padded;

typedef struct {
  complex double z_val;
  char **attractors;
  size_t **convergences;
  int ib;
  int istep;
  size_t length;
  int tx;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_compute_t;

typedef struct {
  char **attractors;
  size_t **convergences;
  size_t length;
  size_t n_threads;
  FILE* fz;
  FILE* fi;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_write_t;

int
main_thrd_compute(
  void *args
  )
{
  const thrd_info_t *thrd_info = (thrd_info_t*) args;
  const float **v = thrd_info->v;
  float **w = thrd_info->w;
  const int ib = thrd_info->ib;
  const int istep = thrd_info->istep;
  const int length = thrd_info->length;
  const int tx = thrd_info->tx;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  for ( int ix = ib; ix < length; ix += istep ) {
    const float *vix = v[ix];
    // We allocate the rows of the result before computing, and free them in another thread.
    float *wix = (float*) malloc(length*sizeof(float));
    
    for ( int jx = 0; jx < length; ++jx )
      wix[jx] = sqrtf(vix[jx]);
    
     mtx_lock(mtx);
     w[ix] = wix;
     status[tx].val = ix + istep;
     mtx_unlock(mtx);
     cnd_signal(cnd);

     // In order to illustrate thrd_sleep and to force more synchronization
     // points, we sleep after each line for one micro seconds.
     thrd_sleep(&(struct timespec){.tv_sec=0, .tv_nsec=1000}, NULL);
   }

  return 0;
}

int
main_thrd_write(
  void *args
  )
{
  const thrd_info_write_t *thrd_info = (thrd_info_write_t*) args;
  char **attractors= thrd_info->attractors;
  size_t **convergences = thrd_info->convergences;
  size_t length = thrd_info->length;
  size_t n_threads = thrd_info->n_threads;
  FILE* fz = thrd_info->fz;
  FILE* fi = thrd_info->fi;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  char* rgbs[10] = {
    "0   0   0   ",
    "255 140 0   ",
    "255 216 0   ",
    "216 255 0   ",
    "124 255 0   ",
    "137 0   255 ",
    "255 0   135 ",
    "255 0   12  ",
    "107 0   255 ",
    "0   244 255 "
  }

  // We do not increment ix in this loop, but in the inner one.
  for ( int ix = 0, ibnd; ix < length; ) {

    // If no new lines are available, we wait.
    for ( mtx_lock(mtx); ; ) {
      // We extract the minimum of all status variables.
      ibnd = length;
      for ( int tx = 0; tx < nthrds; ++tx )
        if ( ibnd > status[tx].val )
          ibnd = status[tx].val;
 
      if ( ibnd <= ix )
        // We rely on spurious wake-ups, which in practice happen, but are not
        // guaranteed.
        cnd_wait(cnd,mtx);
      else {
        mtx_unlock(mtx);
        break;
      }

      // Instead of employing a conditional variable, we could also invoke
      // thrd_yield or thrd_sleep in order to yield to other threads or grant a
      // specified time to the computation threads.
    }

    fprintf(stderr, "writing until %i\n", ibnd);

    // We do not initialize ix in this loop, but in the outer one.
    for ( ; ix < ibnd; ++ix ) {
      for(size_t jx = 0; jx < length; jx++) {
          
      }

      // We free the component of w, since it will never be used again.
      free(w[ix]);
    }
  }

  return 0;
}

int
main(int argc, char* argv[])
{

  size_t length = 21;
  size_t n_threads = 1;
  char degree = "1";
  
  while ((c = getopt (argc, argv, "tl:")) != -1)
    switch (c)
      {
      case 'l':
        length = strtol(optarg,NULL,10);
        break;
      case 't':
        n_threads = strtol(optarg,NULL,10);
        break;
      case '?':
        degree = optopt[0]; 
        return 1;
      default:
        abort ();
  }

  float **v = (float**) malloc(length*sizeof(float*));
  float **w = (float**) malloc(length*sizeof(float*));
  float *ventries = (float*) malloc(length*length*sizeof(float));
  // The entries of w will be allocated in the computation threads are freed in
  // the check thread.

  for ( int ix = 0, jx = 0; ix < length; ++ix, jx += length )
    v[ix] = ventries + jx;

  for ( int ix = 0; ix < length*length; ++ix )
    ventries[ix] = ix;

  const int nthrds = 8;
  thrd_t thrds[nthrds];
  thrd_info_t thrds_info[nthrds];

  thrd_t thrd_check;
  thrd_info_check_t thrd_info_check;
    
  mtx_t mtx;
  mtx_init(&mtx, mtx_plain);

  cnd_t cnd;
  cnd_init(&cnd);

  int_padded status[nthrds];

  for ( int tx = 0; tx < nthrds; ++tx ) {
    thrds_info[tx].v = (const float**) v;
    thrds_info[tx].w = w;
    thrds_info[tx].ib = tx;
    thrds_info[tx].istep = nthrds;
    thrds_info[tx].length = length;
    thrds_info[tx].tx = tx;
    thrds_info[tx].mtx = &mtx;
    thrds_info[tx].cnd = &cnd;
    thrds_info[tx].status = status;
    status[tx].val = -1;

    int r = thrd_create(thrds+tx, main_thrd, (void*) (thrds_info+tx));
    if ( r != thrd_success ) {
      fprintf(stderr, "failed to create thread\n");
      exit(1);
    }
    thrd_detach(thrds[tx]);
  }

  {
    thrd_info_check.v = (const float**) v;
    thrd_info_check.w = w;
    thrd_info_check.length = length;
    thrd_info_check.nthrds = nthrds;
    thrd_info_check.mtx = &mtx;
    thrd_info_check.cnd = &cnd;
    // It is important that we have initialize status in the previous for-loop,
    // since it will be consumed by the check threads.
    thrd_info_check.status = status;

    int r = thrd_create(&thrd_check, main_thrd_check, (void*) (&thrd_info_check));
    if ( r != thrd_success ) {
      fprintf(stderr, "failed to create thread\n");
      exit(1);
    }
  }

  {
    int r;
    thrd_join(thrd_check, &r);
  }

  free(ventries);
  free(v);
  free(w);

  mtx_destroy(&mtx);
  cnd_destroy(&cnd);

  return 0;
}
