#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <getopt.h>
#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>

int
main(int argc, char* argv[])
{
  cl_int error;

  cl_platform_id platform_id;
  cl_uint nmb_platforms;
  if ( clGetPlatformIDs(1, &platform_id, &nmb_platforms) != CL_SUCCESS ) {
    fprintf(stderr, "cannot get platform\n" );
    return 1;
  }

  cl_device_id device_id;
  cl_uint nmb_devices;
  if ( clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &nmb_devices) != CL_SUCCESS ) {
    fprintf(stderr, "cannot get device\n" );
    return 1;
  }

  cl_context context;
  cl_context_properties properties[] =
  {
    CL_CONTEXT_PLATFORM,
    (cl_context_properties) platform_id,
    0
  };
  context = clCreateContext(properties, 1, &device_id, NULL, NULL, &error);
  if ( error != CL_SUCCESS ) {
    fprintf(stderr, "cannot create context\n");
    return 1;
  }

  cl_command_queue command_queue;
  command_queue = clCreateCommandQueueWithProperties(context, device_id, NULL, &error);
  if ( error != CL_SUCCESS ) {
    fprintf(stderr, "cannot create command queue\n");
    return 1;
  }

  char *opencl_program_src;
  {
    FILE *clfp = fopen("./fcn.cl", "r");
    if ( clfp == NULL ) {
      fprintf(stderr, "could not load cl source code\n");
      return 1;
    }
    fseek(clfp, 0, SEEK_END);
    int clfsz = ftell(clfp);
    fseek(clfp, 0, SEEK_SET);
    opencl_program_src = (char*) malloc((clfsz+1)*sizeof(char));
    fread(opencl_program_src, sizeof(char), clfsz, clfp);
    opencl_program_src[clfsz] = 0;
    fclose(clfp);
  }

  cl_program program;
  size_t src_len = strlen(opencl_program_src);
  program = clCreateProgramWithSource(
                context, 1, (const char **) &opencl_program_src, (const size_t*) &src_len, &error);
  if ( error != CL_SUCCESS ) {
    fprintf(stderr, "cannot create program\n");
    return 1;
  }

  free(opencl_program_src);
  
  error = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if ( error != CL_SUCCESS ) {
    fprintf(stderr, "cannot build program. log:\n");
      
    size_t log_size = 0;
    clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

    char *log = malloc(log_size*sizeof(char));
    if ( log == NULL ) {
      fprintf(stderr, "could not allocate memory\n");
      return 1;
    }

    clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

    fprintf(stderr, "%s\n", log );

    free(log);

    return 1;
  }
  
  cl_kernel kernel_diff = clCreateKernel(program, "diffusion", &error);
  if ( error != CL_SUCCESS ) {
    fprintf(stderr, "cannot create kernel_diff\n");
    return 1;
  }

  size_t n_steps;
  float diff_const;
  int c;

  while((c = getopt(argc, argv, "n:d:")) !=-1){
    switch(c){
      case 'n':
        n_steps = atoi(optarg);
        break;
      case 'd':
        diff_const = atof(optarg);
        break;
      case '?':
        fprintf(stderr, "Invalid argumentn");
        exit(1);
      default:
        abort();
    }
  }

  // Commence Gnocchi
  float* h1;
  size_t width, height;
  {
    // FILE* initfile = fopen("init","r");
    // FILE* initfile = fopen("/home/hpc2022/diffusion_opencl/test_data/init_100_100","r");
    // FILE* initfile = fopen("/home/hpc2022/diffusion_opencl/test_data/init_10000_10000","r");
    // FILE* initfile = fopen("/home/hpc2022/diffusion_opencl/test_data/init_10000_1000","r");
    // FILE* initfile = fopen("/home/hpc2022/diffusion_opencl/test_data/init_100000_100","r");
    // FILE* initfile = fopen("init_100000_100_smol","r");
    // FILE* initfile = fopen("init_100000_100_lorge","r");
    FILE* initfile = fopen("init_jltest","r");
    if (initfile == NULL) {
      perror("error:");
      exit(1);
    }

    fseek(initfile,0,SEEK_END);
    // const size_t initfilesize = ftell(initfile)/sizeof(char) + 1;
    const size_t initfilesize = ftell(initfile)/sizeof(char);
    fseek(initfile,0,SEEK_SET);

    char* initfileStr = (char*) malloc(initfilesize*sizeof(char));
    fread(initfileStr, sizeof(char), initfilesize, initfile);

    fclose(initfile);

    // initfileStr[initfilesize] = '\0';

    //printf ("Splitting string \"%s\" into tokens:\n",initfileStr);
    char* tok; const char whitespace[3] = " \n";
    height = strtoul(strtok(initfileStr, whitespace),NULL,10) + 2lu;
    width = strtoul(strtok(NULL, whitespace),NULL,10) + 2lu;
    //printf("Vi har %zu rader och %zu kolumner\n", nRows, nCols);

    // Mallocation & initialisation of our h1 matrix
    // Could 1000% be parallelised, but nah.
    h1 = malloc(width*height*sizeof(float));
    size_t ix;
    for (ix = 0; ix < width*height; ix++) {
      h1[ix] = 0.f;
    }

    // Misstänker att det finns nåt mindre ass sätt att göra detta på, men detta får duga tillsvidare.
    // Dumping of file init into matrix h1 (with zero-padding).
    size_t jx;
    size_t kx;
    while ((tok = strtok(NULL, whitespace)) != NULL) {
      // printf("Token is: %s\n",tok);
      ix = strtoul(tok, NULL, 10);
      jx = strtoul(strtok(NULL, whitespace), NULL, 10);
      h1[(ix+1)*width + (jx+1)] = strtof(strtok(NULL, whitespace), NULL);
      //printf("Hello, (%zu,%zu) : %f\n", ix, jx, h1[(ix+1)*(nCols+2) + (jx+1)]);
      kx++;
    }

    //printf("Element (1,3) är nu %f\n", h1[2*(nCols+2)+4]);

    free(initfileStr);
  }
  // End Gnocchi
  // printf("läsning klar\n");

  cl_mem input_buffer_h1, input_buffer_h2;
  input_buffer_h1 = clCreateBuffer(context, CL_MEM_READ_WRITE,
                       width*height * sizeof(float), NULL, &error);
  if ( error != CL_SUCCESS ) {
    fprintf(stderr, "cannot create buffer h1\n");
    return 1;
  }
  input_buffer_h2 = clCreateBuffer(context, CL_MEM_READ_WRITE,
                       width*height * sizeof(float), NULL, &error);
  if ( error != CL_SUCCESS ) {
    fprintf(stderr, "cannot create buffer h2\n");
    return 1;
  }

  if ( clEnqueueWriteBuffer(command_queue,
           input_buffer_h1, CL_TRUE, 0, width*height * sizeof(float), h1, 0, NULL, NULL)
       != CL_SUCCESS ) {
    fprintf(stderr, "cannot enqueue write of buffer h1\n");
    return 1;
  }
  if ( clEnqueueWriteBuffer(command_queue,
           input_buffer_h2, CL_TRUE, 0, width*height * sizeof(float), h1, 0, NULL, NULL)
       != CL_SUCCESS ) {
    fprintf(stderr, "cannot enqueue write of buffer h2\n");
    return 1;
  }

  clSetKernelArg(kernel_diff, 2, sizeof(float), &diff_const);
   
  const size_t global_sz[2] = {height - 2lu, width - 2lu}; //excluding the borders !!!!!
  const size_t local_sz[2] = {10lu, 10lu};
  cl_mem temp;
  for(size_t ix = 0; ix < n_steps; ix++){
    clSetKernelArg(kernel_diff, 0, sizeof(cl_mem), &input_buffer_h1);
    clSetKernelArg(kernel_diff, 1, sizeof(cl_mem), &input_buffer_h2);
    if ( clEnqueueNDRangeKernel(command_queue, kernel_diff,
             2, NULL, (const size_t *) &global_sz, (const size_t *) &local_sz, 0, NULL, NULL)
         != CL_SUCCESS ) {
      fprintf(stderr, "cannot enqueue kernel_diff\n");
      return 1;
    }
    temp = input_buffer_h1;
    input_buffer_h1 = input_buffer_h2;
    input_buffer_h2 = temp;
  }

  // Reuse h1 as output
  float *output = malloc(width*height * sizeof(float));
  if ( clEnqueueReadBuffer(command_queue,
           input_buffer_h1, CL_TRUE, 0, width*height * sizeof(float), output, 0, NULL, NULL)
       != CL_SUCCESS ) {
    fprintf(stderr, "cannot enqueue read of buffer c\n");
    return 1;
  }

  if ( clFinish(command_queue) != CL_SUCCESS ) {
    fprintf(stderr, "cannot finish queue\n");
    return 1;
  }

  double mean = 0.;
  // float mean = 0.;
  for(size_t ix = 1; ix < height-1; ix++){
    for(size_t jx = 1; jx < width-1; jx++){
      mean += (double) output[ix*width + jx] / (double) ((width-2lu)*(height-2lu)); 
      // mean += output[ix*width + jx] / ((width-2lu)*(height-2lu)); 
    }
  }
  // Snabbare men sämre precision:
  //mean /= (double) ((width-2lu)*(height-2lu));

  double abs_diff_mean = 0.;
  // float abs_diff_mean = 0.;
  for(size_t ix = 1; ix < height-1; ix++){
    for(size_t jx = 1; jx < width-1; jx++){
      abs_diff_mean += fabs((double)output[ix*width + jx] - mean) / (double) ((width-2lu)*(height-2lu)); 
      // abs_diff_mean += fabs(output[ix*width + jx] - mean) / ((width-2lu)*(height-2lu)); 
    }
  }
  // Snabbare men sämre precision:
  //abs_diff_mean /= (double) ((width-2lu)*(height-2lu));

  free(h1);

  clReleaseMemObject(input_buffer_h1);
  clReleaseMemObject(input_buffer_h2);

  clReleaseProgram(program);
  clReleaseKernel(kernel_diff);

  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);

  printf("%f\n", mean);
  printf("%f\n", abs_diff_mean);

  return 0;
}
