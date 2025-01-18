#include <stdlib.h>

/* Don't forget to:
 *
 *    srand(time(NULL));
 *
 * Before call this function!
 */
float frand (float min, float max)
{
	float diff;

	diff = max - min;

	return ((float) rand() / (float) (RAND_MAX/diff)) + min;
}
