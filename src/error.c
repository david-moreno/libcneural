#include "error.h"

static int __cn_current_error__ = CN_ERR_OK;

static char *msg[_CN_ERROR_NUM_] = {
	"All is fine here dude",
	"The number of layers is lower than the minimum",
	"The number of inputs is lower than the minimum",
	"The number of outputs is lower than the minimum",
	"Insufficient memory",
	"The number of neurons is lower than the minimum",
	"The given index is out of bounds",
	"The network is already built",
	"The file cannot be opened"
};

void set_error (CN_ERROR_T error)
{
	__cn_current_error__ = error;
}

CN_ERROR_T get_current_error (void)
{
	return __cn_current_error__;
}

char *get_error_msg (void)
{
	return msg[__cn_current_error__];
}
