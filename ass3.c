#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <complex.h>
#include <unistd.h>

#define ZEROCHARVAL 48
#define TOLSQ 1e-6
#define ABSSQ(zfl) (crealf(zfl)*crealf(zfl) + cimagf(zfl)*cimagf(zfl))

void newton_iter(const float re_z0, const float im_z0, const char *degree_ptr, char *attr_indices, size_t *n_iter) {
  float realdum, imagdum;
  complex float zDum;
  // Initial guess, initialize iteration counter
  complex float zVal = re_z0 + im_z0*I;
  *n_iter = 0;
    
  // Commence spaghetti
  switch (*degree_ptr) {
    case '1':
    *attr_indices = '0';
    zVal = (complex float) 1.;
    *n_iter = 1;
    break;
    case '2':
    for (;;) {
      realdum = fabsf(crealf(zVal));
      imagdum = fabsf(cimagf(zVal));
      if ((realdum > 1e10) || (imagdum > 1e10)) {
        *attr_indices = '0';
        break;
      }
      if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
        *attr_indices = '0';
        break;
      }
      if (ABSSQ(zVal - 1.) < TOLSQ) {
        *attr_indices = '1';
        break;
      }
      if (ABSSQ(zVal + 1.) < TOLSQ) {
        *attr_indices = '2';
        break;
      }
      zVal = (zVal + 1./zVal)/2.;
      (*n_iter)++;
    }
    break;
  case '3':
    for (;;) {
      realdum = fabsf(crealf(zVal));
      imagdum = fabsf(cimagf(zVal));
      if ((realdum > 1e10) || (imagdum > 1e10)) {
        *attr_indices = '0';
        break;
      }
      if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
        *attr_indices = '0';
        break;
      }
      if (ABSSQ(zVal - 1.) < TOLSQ) {
        *attr_indices = '1';
        break;
      }
      if (ABSSQ(zVal + (0.5 - 0.8660254037844386*I)) < TOLSQ) {
        *attr_indices = '2';
        break;
      }
      if (ABSSQ(zVal + (0.5 + 0.8660254037844386*I)) < TOLSQ) {
        *attr_indices = '3';
        break;
      }
      zVal = (2.*zVal + 1./(zVal*zVal))/3.;
      (*n_iter)++;
    }
    break;
  case '4':
    for (;;) {
      realdum = fabsf(crealf(zVal));
      imagdum = fabsf(cimagf(zVal));
      if ((realdum > 1e10) || (imagdum > 1e10)) {
        *attr_indices = '0';
        break;
      }
      if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
        *attr_indices = '0';
        break;
      }
      if (ABSSQ(zVal - 1.) < TOLSQ) {
        *attr_indices = '1';
        break;
      }
      if (ABSSQ(zVal - I) < TOLSQ) {
        *attr_indices = '2';
        break;
      }
      if (ABSSQ(zVal + 1.) < TOLSQ) {
        *attr_indices = '3';
        break;
      }
      if (ABSSQ(zVal + I) < TOLSQ) {
        *attr_indices = '4';
        break;
      }
      zVal = (3.*zVal + 1./(zVal*zVal*zVal))/4.;
      (*n_iter)++;
    }
    break;
  case '5':
    for (;;) {
      realdum = fabsf(crealf(zVal));
      imagdum = fabsf(cimagf(zVal));
      if ((realdum > 1e10) || (imagdum > 1e10)) {
        *attr_indices = '0';
        break;
      }
      if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
        *attr_indices = '0';
        break;
      }
      if (ABSSQ(zVal - 1.) < TOLSQ) {
        *attr_indices = '1';
        break;
      }
      if (ABSSQ(zVal - (0.309016994374948 + 0.951056516295153*I)) < TOLSQ) {
        *attr_indices = '2';
        break;
      }
      if (ABSSQ(zVal + 0.809016994374947 - 0.587785252292473*I) < TOLSQ) {
        *attr_indices = '3';
        break;
      }
      if (ABSSQ(zVal + 0.809016994374947 + 0.587785252292473*I) < TOLSQ) {
        *attr_indices = '4';
        break;
      }
      if (ABSSQ(zVal - 0.309016994374948 + 0.951056516295153*I) < TOLSQ) {
        *attr_indices = '5';
        break;
      }
      zDum = zVal*zVal;
      zVal = (4.*zVal + 1./(zDum*zDum))/5.;
      (*n_iter)++;
    }
    break;
  case '6':
    for (;;) {
      realdum = fabsf(crealf(zVal));
      imagdum = fabsf(cimagf(zVal));
      if ((realdum > 1e10) || (imagdum > 1e10)) {
        *attr_indices = '0';
        break;
      }
      if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
        *attr_indices = '0';
        break;
      }
      if (ABSSQ(zVal - 1.) < TOLSQ) {
        *attr_indices = '1';
        break;
      }
      if (ABSSQ(zVal - (0.5 + 0.8660254037844386*I)) < TOLSQ) {
        *attr_indices = '2';
        break;
      }
      if (ABSSQ(zVal + 0.5 - 0.8660254037844386*I) < TOLSQ) {
        *attr_indices = '3';
        break;
      }
      if (ABSSQ(zVal + 1.) < TOLSQ) {
        *attr_indices = '4';
        break;
      }
      if (ABSSQ(zVal + 0.5 + 0.8660254037844386*I) < TOLSQ) {
        *attr_indices = '5';
        break;
      }
      if (ABSSQ(zVal - 0.5 + 0.8660254037844386*I) < TOLSQ) {
        *attr_indices = '6';
        break;
      }
      zDum = zVal*zVal;
      zVal = (5.*zVal + 1./(zDum*zDum*zVal))/6.;
      (*n_iter)++;
    }
    break;
  case '7':
    for (;;) {
      realdum = fabsf(crealf(zVal));
      imagdum = fabsf(cimagf(zVal));
      if ((realdum > 1e10) || (imagdum > 1e10)) {
        *attr_indices = '0';
        break;
      }
      if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
        *attr_indices = '0';
        break;
      }
      if (ABSSQ(zVal - 1.) < TOLSQ) {
        *attr_indices = '1';
        break;
      }
      if (ABSSQ(zVal - (0.623489801858734 + 0.781831482468030*I)) < TOLSQ) {
        *attr_indices = '2';
        break;
      }
      if (ABSSQ(zVal + 0.222520933956314 - 0.974927912181824*I) < TOLSQ) {
        *attr_indices = '3';
        break;
      }
      if (ABSSQ(zVal + 0.900968867902419 - 0.433883739117558*I) < TOLSQ) {
        *attr_indices = '4';
        break;
      }
      if (ABSSQ(zVal + 0.900968867902419 + 0.433883739117558*I) < TOLSQ) {
        *attr_indices = '5';
        break;
      }
      if (ABSSQ(zVal + 0.222520933956314 + 0.974927912181824*I) < TOLSQ) {
        *attr_indices = '6';
        break;
      }
      if (ABSSQ(zVal - 0.623489801858734 + 0.781831482468030*I) < TOLSQ) {
        *attr_indices = '7';
        break;
      }
      zDum = zVal*zVal;
      zVal = (6.*zVal + 1./(zDum*zDum*zDum))/7.;
      (*n_iter)++;
    }
    break;
  case '8':
    for (;;) {
      realdum = fabsf(crealf(zVal));
      imagdum = fabsf(cimagf(zVal));
      if ((realdum > 1e10) || (imagdum > 1e10)) {
        *attr_indices = '0';
        break;
      }
      if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
        *attr_indices = '0';
        break;
      }
      if (ABSSQ(zVal - 1.) < TOLSQ) {
        *attr_indices = '1';
        break;
      }
      if (ABSSQ(zVal - (0.707106781186548 + 0.707106781186547*I)) < TOLSQ) {
        *attr_indices = '2';
        break;
      }
      if (ABSSQ(zVal - I) < TOLSQ) {
        *attr_indices = '3';
        break;
      }
      if (ABSSQ(zVal + 0.707106781186548 - 0.707106781186547*I) < TOLSQ) {
        *attr_indices = '4';
        break;
      }
      if (ABSSQ(zVal + 1.) < TOLSQ) {
        *attr_indices = '5';
        break;
      }
      if (ABSSQ(zVal + 0.707106781186548 + 0.707106781186547*I) < TOLSQ) {
        *attr_indices = '6';
        break;
      }
      if (ABSSQ(zVal + I) < TOLSQ) {
        *attr_indices = '7';
        break;
      }
      if (ABSSQ(zVal - 0.707106781186548 + 0.707106781186547*I) < TOLSQ) {
        *attr_indices = '8';
        break;
      }
      zDum = zVal*zVal;
      zVal = (7.*zVal + 1./(zDum*zDum*zDum*zVal))/8.;
      (*n_iter)++;
    }
    break;
  case '9':
    for (;;) {
      realdum = fabsf(crealf(zVal));
      imagdum = fabsf(cimagf(zVal));
      if ((realdum > 1e10) || (imagdum > 1e10)) {
        *attr_indices = '0';
        break;
      }
      if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
        *attr_indices = '0';
        break;
      }
      if (ABSSQ(zVal - 1.) < TOLSQ) {
        *attr_indices = '1';
        break;
      }
      if (ABSSQ(zVal - (0.766044443118978 + 0.642787609686539*I)) < TOLSQ) {
        *attr_indices = '2';
        break;
      }
      if (ABSSQ(zVal - (0.173648177666930 + 0.984807753012208*I)) < TOLSQ) {
        *attr_indices = '3';
        break;
      }
      if (ABSSQ(zVal + 0.500000000000000 - 0.866025403784439*I) < TOLSQ) {
        *attr_indices = '4';
        break;
      }
      if (ABSSQ(zVal + 0.939692620785908 - 0.342020143325669*I) < TOLSQ) {
        *attr_indices = '5';
        break;
      }
      if (ABSSQ(zVal + 0.939692620785908 + 0.342020143325669*I) < TOLSQ) {
        *attr_indices = '6';
        break;
      }
      if (ABSSQ(zVal + 0.500000000000000 + 0.866025403784439*I) < TOLSQ) {
        *attr_indices = '7';
        break;
      }
      if (ABSSQ(zVal - 0.173648177666930 + 0.984807753012208*I) < TOLSQ) {
        *attr_indices = '8';
        break;
      }
      if (ABSSQ(zVal - 0.766044443118978 + 0.642787609686539*I) < TOLSQ) {
        *attr_indices = '9';
        break;
      }
      zDum = zVal*zVal;
      zDum *= zDum;
      zVal = (8.*zVal + 1./(zDum*zDum))/9.;
      (*n_iter)++;
    }
    break;
    // No further cases. Hyyyyyype.

  default:
    fprintf(stderr, "unexpected degree\n");
    exit(1);
  }
}

typedef struct {
  int val;
  char pad[60]; // cacheline - sizeof(int)
} int_padded;

typedef struct {
  char **attractors;
  size_t **convergences;
  char degree;
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
  size_t nthrds;
  FILE* fa;
  FILE* fc;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_write_t;

int
main_thrd_compute(
  void *args
  )
{
  const thrd_info_compute_t *thrd_info = (thrd_info_compute_t*) args;
  char **attractors = thrd_info->attractors;
  size_t **convergences = thrd_info->convergences;
  char degree = thrd_info->degree;
  const int ib = thrd_info->ib;
  const int istep = thrd_info->istep;
  const int length = thrd_info->length;
  const int tx = thrd_info->tx;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  for ( int ix = ib; ix < length; ix += istep ) {
    // We allocate the rows of the result before computing, and free them in another thread.
    char *attractor = (char*) malloc(length*sizeof(char));
    size_t *convergence = (size_t*) malloc(length*sizeof(size_t));
    attractors[ix] = (char*) malloc(length*sizeof(char));
    convergences[ix] = (size_t*) malloc(length*sizeof(size_t));
    
    for ( int jx = 0; jx < length; ++jx ) {
      newton_iter(-2 + 4/((const float) length - 1)*ix,  2 - 4/((const float) length - 1)*jx, (const char*) &degree, &attractor[jx], &convergence[jx]);
      //fprintf(stderr, "attractor %s\n", attractor);
    }
    
    mtx_lock(mtx);
    fprintf(stderr, "attractor %s\n", attractor);
    attractors[ix] = attractor;
    fprintf(stderr, "attractors[ix] %s\n", attractors[ix]);
    convergences[ix] = convergence;
    status[tx].val = ix + istep;
    mtx_unlock(mtx);
    cnd_signal(cnd);

    // In order to illustrate thrd_sleep and to force more synchronization
    // points, we sleep after each line for one micro second.
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
  size_t nthrds= thrd_info->nthrds;
  FILE* fa = thrd_info->fa;
  FILE* fc = thrd_info->fc;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  char attractor_rgb[length*12];
  char convergence_grey[length*12];
  size_t conv_capped;

  char greys[100*12] = {'\0'};
  for(size_t kx = 0; kx < 100; ++kx){
    sprintf(&greys[kx*12], "%-4ld%-4ld%-4ld", kx, kx, kx);
  }

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
  };

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
    //fprintf(stderr, "1 writing until %i\n", ibnd);
      for(size_t jx = 0; jx < length; jx++) {
        //fprintf(stderr, "2 writing until %i\n", ibnd);
        conv_capped = convergences[ix][jx] > 99 ? 99 : convergences[ix][jx];
        //fprintf(stderr, "attractor_rgb[12*(jx-1)] %c\n", attractor_rgb[12*(jx-1)]);
        //fprintf(stderr, "attractors[ix][jx]%c\n", attractors[ix][jx]);
        memcpy(&attractor_rgb[12*jx], rgbs[attractors[ix][jx]], 12);
        //fprintf(stderr, "4 writing until %i\n", ibnd);
        memcpy(&convergence_grey[12*jx], &greys[12*(int) conv_capped], 12);
        //fprintf(stderr, "5 writing until %i\n", ibnd);
      }
      fprintf(stderr, "attractor_rgb %s\n", attractor_rgb);
      fwrite(&attractor_rgb, sizeof(char), 12*length+1, fa);
      fwrite(&convergence_grey, sizeof(char), 12*length+1, fc);

      // We free the component of w, since it will never be used again.
      free(attractors[ix]);
      free(convergences[ix]);
    }
  }

  return 0;
}

int
main(int argc, char* argv[])
{

  size_t length = 21;
  int nthrds = 1;
  char degree = '2';
  /* int c;
  
  while ((c = getopt (argc, argv, "tl:")) != -1)
    switch (c)
      {
      case 'l':
        length = strtol(optarg,NULL,10);
        break;
      case 't':
        nthrds = strtol(optarg,NULL,10);
        break;
      case '?':
        degree = optopt; 
        return 1;
      default:
        abort ();
  } */

  char **attractors = (char**) malloc(length*sizeof(char*));
  size_t **convergences = (size_t**) malloc(length*sizeof(size_t*));
  // The entries of w will be allocated in the computation threads are freed in
  // the check thread.

  thrd_t thrds[nthrds];
  thrd_info_compute_t thrds_info_compute[nthrds];

  thrd_t thrd_write;
  thrd_info_write_t thrd_info_write;
    
  mtx_t mtx;
  mtx_init(&mtx, mtx_plain);

  cnd_t cnd;
  cnd_init(&cnd);

  int_padded status[nthrds];

  for ( int tx = 0; tx < nthrds; ++tx ) {
    thrds_info_compute[tx].attractors = attractors;
    thrds_info_compute[tx].convergences = convergences;
    thrds_info_compute[tx].degree = degree;
    thrds_info_compute[tx].ib = tx;
    thrds_info_compute[tx].istep = nthrds;
    thrds_info_compute[tx].length = length;
    thrds_info_compute[tx].tx = tx;
    thrds_info_compute[tx].mtx = &mtx;
    thrds_info_compute[tx].cnd = &cnd;
    thrds_info_compute[tx].status = status;
    status[tx].val = -1;

    int r = thrd_create(thrds+tx, main_thrd_compute, (void*) (thrds_info_compute+tx));
    if ( r != thrd_success ) {
      fprintf(stderr, "failed to create thread\n");
      exit(1);
    }
    thrd_detach(thrds[tx]);
  }

  {
    FILE* fa = fopen("newton_attractors_xd.ppm","w");
    FILE* fc = fopen("newton_convergence_xd.ppm","w");
    fprintf(fa, "P3\n%ld %ld\n255", length, length);
    fprintf(fc, "P3\n%ld %ld\n100", length, length);

    thrd_info_write.attractors = attractors;
    thrd_info_write.convergences = convergences;
    thrd_info_write.length = length;
    thrd_info_write.nthrds = nthrds;
    thrd_info_write.fa = fa;
    thrd_info_write.fc = fc;
    thrd_info_write.mtx = &mtx;
    thrd_info_write.cnd = &cnd;
    // It is important that we have initialize status in the previous for-loop,
    // since it will be consumed by the check threads.
    thrd_info_write.status = status;

    int r = thrd_create(&thrd_write, main_thrd_write, (void*) (&thrd_info_write));
    if ( r != thrd_success ) {
      fprintf(stderr, "failed to create thread\n");
      exit(1);
    }

  fclose(fa);
  fclose(fc);
  }

  {
    int r;
    thrd_join(thrd_write, &r);
  }

  //free(attractors);
  //free(convergences);

  mtx_destroy(&mtx);
  cnd_destroy(&cnd);

  return 0;
}
