#include "carcass_model.h"

CarcassModel::CarcassModel(std::shared_ptr<CarcassModelImpl> i) : VisibleObj(i) {}
std::shared_ptr<BaseObj> CarcassModel::clone() const 
{ 
    return std::make_shared<CarcassModel>(std::dynamic_pointer_cast<CarcassModelImpl>(impl->clone())); 
}
