/* Header files required by Max ***********************************************/
#include "ext.h"
#include "ext_obex.h"
#include "buffer.h"

/* The class pointer **********************************************************/
static t_class *bed_class;

/* The object structure *******************************************************/
typedef struct _bed {
    t_object obj;

    t_symbol *b_name;
    t_buffer *buffer;
} t_bed;

/* Function prototypes ********************************************************/
void *bed_new(t_symbol *s, short argc, t_atom *argv);
void bed_free(t_bed *x);

int bed_attach_buffer(t_bed *x);
void bed_info(t_bed *x);
void bed_bufname(t_bed *x, t_symbol *name);

/* The initialization routine *************************************************/
int C74_EXPORT main()
{
    /* Initialize the class */
    bed_class = class_new("bed",
                          (method)bed_new,
                          (method)bed_free,
                          (long)sizeof(t_bed), 0, A_GIMME, 0);

    /* Bind the object-specific methods */
    class_addmethod(bed_class, (method)bed_info, "info", 0);
    class_addmethod(bed_class, (method)bed_bufname, "name", A_SYM, 0);

    /* Register the class with Max */
    class_register(CLASS_BOX, bed_class);

    /* Print message to Max window */
    object_post(NULL, "bed • External was loaded");

    /* Return with no error */
    return 0;
}

/* The new and free instance routines *****************************************/
void *bed_new(t_symbol *s, short argc, t_atom *argv)
{
    /* Instantiate a new object */
    t_bed *x = (t_bed *)object_alloc(bed_class);

    /* Parse passed argument */
    atom_arg_getsym(&x->b_name, 0, argc, argv);

    /* Print message to Max window */
    post("bed • Object was created");

    /* Return a pointer to the new object */
    return x;
}

void bed_free(t_bed *x)
{
    /* Print message to Max window */
    post("bed • Object was deleted");
}

/* The object-specific methods ************************************************/
int bed_attach_buffer(t_bed *x)
{
    t_object *o;
    o = x->b_name->s_thing;

    if (o == NULL) {
        post("\"%s\" is not a valid buffer", x->b_name->s_name);
        return 0;
    }

    if (ob_sym(o) == gensym("buffer~")) {
        x->buffer = (t_buffer *)o;
        return 1;
    } else {
        return 0;
    }
}

void bed_info(t_bed *x)
{
    if (!bed_attach_buffer(x)) {
        return;
    }

    t_buffer *b;
    b = x->buffer;

    post("buffer name: %s", b->b_name->s_name);
    post("frame count: %d", b->b_frames);
    post("channel count: %d", b->b_nchans);
    post("validity: %d", b->b_valid);
    post("in-use status: %d", b->b_inuse);
}

void bed_bufname(t_bed *x, t_symbol *name)
{
    x->b_name = name;
}

/******************************************************************************/
