#include <stdio.h>
#include <stddef.h>
#include <string.h>
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
  int diff_const;
  int c;

  while((c = getopt(argc, argv, "n:d:")) !=-1){
    switch(c){
      case 'n':
        n_steps = atoi(optarg);
        break;
      case 'd':
        diff_const = atoi(optarg)
        break;
      case '?':
        fprintf(stderr, "Invalid argumentn");
        exit(1)
      default:
        abort();
    }
  }

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
           input_buffer_h1, CL_TRUE, 0, width*height * sizeof(float), a, 0, NULL, NULL)
       != CL_SUCCESS ) {
    fprintf(stderr, "cannot enqueue write of buffer h1\n");
    return 1;
  }
  if ( clEnqueueWriteBuffer(command_queue,
           input_buffer_h2, CL_TRUE, 0, width*height * sizeof(float), b, 0, NULL, NULL)
       != CL_SUCCESS ) {
    fprintf(stderr, "cannot enqueue write of buffer h2\n");
    return 1;
  }

  clSetKernelArg(kernel_diff, 0, sizeof(cl_mem), &input_buffer_h1);
  clSetKernelArg(kernel_diff, 1, sizeof(cl_mem), &input_buffer_h2);
    
  const size_t global_sz[] = {height - 1, width - 1}; //excluding the borders !!!!!
  const size_t local_sz[] = {10, 10};
  cl_mem temp;
  for(ix = 0; ix < nsteps; ix++){
    if ( clEnqueueNDRangeKernel(command_queue, kernel_diff,
             2, NULL, (const size_t *) &global_sz, &local_sz, 0, NULL, NULL)
         != CL_SUCCESS ) {
      fprintf(stderr, "cannot enqueue kernel_diff\n");
      return 1;
    }
    temp = input_buffer_h1;
    input_buffer_h1 = input_buffer_h2;
    input_buffer_h2 = temp;
  }

  // size_t local_redsz = 32;
  // size_t nredgps = 
  // const cl_int sz_clint = (clint) (height - 1) * (width - 1);
  // clSetKernelArg(kernel_diff, 0, sizeof(cl_mem), &input_buffer_h1);
  // clSetKernelArg(kernel_diff, 1, sizeof(cl_mem), &input_buffer_h1);
  // clSetKernelArg(kernel_diff, 2, sizeof(cl_mem), &input_buffer_h1);
  // clSetKernelArg(kernel_diff, 3, sizeof(cl_mem), &input_buffer_h1);

  
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

  free(h1);
  free(h2);

  double mean = 0;
  for(size_t ix = 1; ix < height-1; ix++){
    for(size_t jx = 1; jx width-1; jx++){
      mean += output[ix*width + jx] /(double) (width*height); 
    }
  }

  double abs_diff_mean = 0;
  for(size_t ix = 1; ix < height-1; ix++){
    for(size_t jx = 1; jx width-1; jx++){
      abs_diff_mean += fabs((output[ix*width + jx] - mean) /(double) (width*height)); 
    }
  }

  free(output);

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
