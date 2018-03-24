///////////////////////////////////////////////////////////
//  SimpleValue.cpp
//  Definition of the class SimpleValue
//  Created on:      20-Mar-2018 18:47:29
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "mbed-client/m2minterfacefactory.h"
#include "mbed-client/m2mresource.h"
#include "SimpleValue.h"

SimpleValue::SimpleValue()
  :value(0.0)
{
  valueObject = M2MInterfaceFactory::create_object("3202");
  M2MObjectInstance* valueInstance = valueObject->create_object_instance();

  M2MResource* valueResource = valueInstance->create_dynamic_resource("5600",
    "AnalogIn", M2MResourceInstance::FLOAT, true);

  valueResource->set_operation(M2MBase::GET_ALLOWED);
  valueResource->set_value((uint8_t*)"0", 1);
}

void SimpleValue::setValue(float value)
{
  //TODO
}

M2MObject* SimpleValue::GetObject()
{
  return valueObject;
}
