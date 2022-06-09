#ifndef cleaner_common_h
#define cleaner_common_h

/* Header files required by Max and Pd ****************************************/
#include "ext.h"
#include "z_dsp.h"
#include "ext_obex.h"


/* The global variables *******************************************************/
#define MINIMUM_THRESHOLD 0.0
#define DEFAULT_THRESHOLD 0.5
#define MAXIMUM_THRESHOLD 1.0

#define MINIMUM_ATTENUATION 0.0
#define DEFAULT_ATTENUATION 0.1
#define MAXIMUM_ATTENUATION 1.0

/* The object structure *******************************************************/
typedef struct _cleaner {
    t_pxobject obj;

    double fs;
    
    double threshold_value;
    double attenuation_value;

    int threshold_connected;
    int attenuation_connected;
} t_cleaner;

/* The arguments/inlets/outlets/vectors indexes *******************************/
enum ARGUMENTS { A_THRESHOLD, A_ATTENUATION };
enum INLETS { I_INPUT, I_THRESHOLD, I_ATTENUATION, NUM_INLETS };
enum OUTLETS { O_OUTPUT, NUM_OUTLETS };
enum DSP { PERFORM, OBJECT,
           INPUT1, THRESHOLD, ATTENUATION, OUTPUT1,
           VECTOR_SIZE, NEXT };

/* The class pointer **********************************************************/
static t_class *cleaner_class;

/* Function prototypes ********************************************************/
void *cleaner_common_new(t_cleaner *x, short argc, t_atom *argv);
void cleaner_free(t_cleaner *x);

void cleaner_dsp(t_cleaner *x, t_object *dsp64,
                   short *count,
                   double samplerate,
                   long maxvectorsize,
                   long flags);
void cleaner_perform(t_cleaner *x, t_object *dsp64,
                       double **ins, long numins,
                       double **outs, long numouts,
                       long vectorsize,
                       long flags,
                       void *userparams);

/******************************************************************************/

#endif /* cleaner_common_h */
