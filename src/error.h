#ifndef ERROR_H
#define ERROR_H

typedef enum {
	CN_ERR_OK, CN_ERR_LAYNUM, CN_ERR_INPNUM, CN_ERR_OUTNUM,
	CN_ERR_NOMEM, CN_ERR_NEURONNUM, CN_ERR_OUTBOUND,
	CN_ERR_BUILT, CN_ERR_OPENFILE,
	/* This element must be the last.
	 * For every new error code, don't forget to update
	 * msg[] on error.c */
	_CN_ERROR_NUM_
} CN_ERROR_T;

void set_error (CN_ERROR_T error);
CN_ERROR_T get_current_error (void);
char *get_error_msg (void);

#endif /* ERROR_H */
