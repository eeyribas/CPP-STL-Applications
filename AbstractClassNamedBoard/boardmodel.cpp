#include "boardmodel.h"

BoardModel::~BoardModel() {   }

void BoardModel::SetPortName(std::string value) {    port_name = value;  }
std::string BoardModel::GetPortName() {  return port_name;   }
void BoardModel::SetBaudRate(int value) {    baud_rate = value;  }
int BoardModel::GetBaudRate() {  return baud_rate;   }
void BoardModel::SetDataLength(uint value) {  data_length = value;    }
uint BoardModel::GetDataLength() {    return data_length; }
void BoardModel::SetSensorId1(unsigned char id) {  sensor_id_1 = id; }
unsigned char BoardModel::GetSensorId1() { return sensor_id_1; }
void BoardModel::SetSensorId2(unsigned char id) {  sensor_id_2 = id;  }
unsigned char BoardModel::GetSensorId2() { return sensor_id_2; }
