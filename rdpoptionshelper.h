#ifndef RDPOPTIONSHELPER_H
#define RDPOPTIONSHELPER_H

#include "rdpoptions.h"

class RdpOptionsHelper
{
public:
    static void save(const RdpOptions& opt);

    static RdpOptions load(QString group);

    static void remove(const RdpOptions& opt);

    static QList<RdpOptions> loadAll();

    static QString getDefaultName();

    static QString getGroupName(const RdpOptions& opt);
};

#endif // RDPOPTIONSHELPER_H
