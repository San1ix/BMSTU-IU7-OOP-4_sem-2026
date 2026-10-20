#ifndef OBJ_LOAD_H
#define OBJ_LOAD_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "model.h"
#include "point.h"
#include "edge.h"
#include "exit_code.h"

#define MAX_LINE_LENGTH 256

exit_code_t load_model_from_file(model_t *model, const char *filename);
exit_code_t save_model_to_file(const model_t *model, const char *filename);

#endif