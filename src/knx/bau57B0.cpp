#include "bau57B0.h"
#include "bits.h"
#include <string.h>
#include <stdio.h>

using namespace std;

Bau57B0::Bau57B0(Platform& platform)
    : BauSystemB(platform),
      _ipParameters(_deviceObj, platform),
      _dlLayer(_deviceObj, _addrTable, _ipParameters, _netLayer, _platform)
{
    _netLayer.dataLinkLayer(_dlLayer);
    _memory.addSaveRestore(&_ipParameters);

    // Set Mask Version in Device Object depending on the BAU
    uint16_t maskVersion;
    popWord(maskVersion, _descriptor);
    _deviceObj.maskVersion(maskVersion);

    // Set which interface objects are available in the device object
    // This differs from BAU to BAU with different medium types.
    // See PID_IO_LIST
    _deviceObj.ifObj(_ifObjs);
}

InterfaceObject* Bau57B0::getInterfaceObject(uint8_t idx)
{
    switch (idx)
    {
        case 0:
            return &_deviceObj;
        case 1:
            return &_addrTable;
        case 2:
            return &_assocTable;
        case 3:
            return &_groupObjTable;
        case 4:
            return &_appProgram;
        case 5: // would be app_program 2
            return nullptr;
        case 6:
            return &_ipParameters;
        default:
            return nullptr;
    }
}

uint8_t* Bau57B0::descriptor()
{
    return _descriptor;
}

DataLinkLayer& Bau57B0::dataLinkLayer()
{
    return _dlLayer;
}