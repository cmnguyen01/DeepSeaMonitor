#ifndef TABLEBUILDER_H
#define TABLEBUILDER_H

#include <QTableWidget>


class TableBuilder
{
public:
    TableBuilder();
    static void buildTable(QTableWidget * table, QString deviceName);
};

#endif // TABLEBUILDER_H
