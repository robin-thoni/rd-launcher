#ifndef RDPOPTIONSHELPER_H
#define RDPOPTIONSHELPER_H

#include "rdpoptions.h"

class RdpOptionsHelper
{
public:
    static void save(const RdpOptions& opt);

    static RdpOptions load(QString group);

    static QList<RdpOptions> loadAll();

    static QString getDefaultName();
};

#endif // RDPOPTIONSHELPER_H
