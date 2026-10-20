#include "cmd_manager.h"

static model_t model;

exit_code_t perform_cmd(request_t &request)
{
    exit_code_t rc = RC_OK;

    switch(request.cmd)
    {
        case LOAD_MODEL:
            rc = load_model_from_file(&model, request.filename);
            if (rc == RC_OK)
                rc = update_model_center(&model);
            break;
            
        case SAVE_MODEL:
            rc = save_model_to_file(&model, request.filename);
            break;
            
        case DRAW_MODEL:
            rc = draw_model(&model, request.scene, request.draw_params);
            break;
            
        case MOVE_MODEL:
            rc = move_model(&model, request.transformation);
            break;
            
        case ROTATE_MODEL:
            rc = rotate_model(&model, request.transformation);
            break;
            
        case SCALE_MODEL:
            rc = scale_model(&model, request.transformation);
            break;
            
        case SET_CENTER:
            set_model_center(&model, &request.center);
            break;
            
        case UPDATE_CENTER:
            rc = update_model_center(&model);
            break;
            
        case CLEAN_MODEL:
            free_model(&model);
            break;
            
        case CHECK_MODEL:
            rc = is_loaded(&model) ? RC_OK : RC_FAIL_MODEL_NOT_LOADED;
            break;
            
        default:
            rc = RC_FAIL_UNKNOWN_CMD;
            break;
    }

    return rc;
}