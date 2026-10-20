#include "carcass_model_impl.h"

#include "visitor.h"

CarcassModelImpl::CarcassModelImpl(std::shared_ptr<BaseModelStructure> s) : structure(s) {}
CarcassModelImpl::CarcassModelImpl(const CarcassModelImpl& other) : structure(other.structure->clone()) {}

void CarcassModelImpl::accept(Visitor& visitor) 
{ 
    visitor.visit(*this); 
}

void CarcassModelImpl::transform(const TransformParams& params) 
{ 
    structure->transform(params); 
}

Point CarcassModelImpl::get_center() const
{
    Point c = structure->get_center();
    Point origin = Scene::get_instance().get_center();
    return {c.get_x() + origin.get_x(), c.get_y() + origin.get_y(), c.get_z() + origin.get_z()};
}

std::shared_ptr<ObjectImpl> CarcassModelImpl::clone() const 
{ 
    return std::make_shared<CarcassModelImpl>(*this); 
}

std::shared_ptr<BaseModelStructure> CarcassModelImpl::get_structure() const 
{ 
    return structure; 
}
