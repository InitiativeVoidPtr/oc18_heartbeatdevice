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
{
  valueObject = M2MInterfaceFactory::create_object("3314");
  M2MObjectInstance* valueInstance = valueObject->create_object_instance();

  valueResource = valueInstance->create_dynamic_resource("5527",
    "AnalogValues", M2MResourceInstance::STRING, true);

  valueResource->set_operation(M2MBase::GET_ALLOWED);
  valueResource->set_value((uint8_t*)"0", 1);
}

void SimpleValue::setValue(uint8_t* value, uint8_t size)
{
  valueResource->set_value(value, size);
}

M2MObject* SimpleValue::GetObject()
{
  return valueObject;
}
