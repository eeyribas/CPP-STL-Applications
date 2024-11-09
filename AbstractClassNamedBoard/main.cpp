#include <QCoreApplication>
#include "boardmodel.h"
#include "boardv1.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BoardModel *board_model = new BoardV1();
    board_model->SetBaudRate(3000000);
    board_model->SetDataLength(10);
    board_model->SetSensorId1(253);
    board_model->SetSensorId2(254);

    board_model->Open();
    if (board_model->IsOpen()) {
        std::vector<unsigned char> read_data = board_model->Read();
        std::cout << "Read Data : ";
        for (uint i = 0; i < read_data.size(); i++)
            std::cout << read_data.at(i) << " ";
        std::cout << std::endl;
    }
    board_model->Close();

    delete board_model;

    return a.exec();
}
