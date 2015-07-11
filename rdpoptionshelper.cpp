#include <QSettings>
#include "rdpoptionshelper.h"
#include <QList>
#include <QStringList>

void RdpOptionsHelper::save(const RdpOptions &opt)
{
    QString group;
    if (opt.host().isEmpty())
        group = RdpOptionsHelper::getDefaultName();
    else if (opt.username().isEmpty())
        group = opt.host();
    else
        group = opt.username() + "@" + opt.host();
    QSettings set(QSettings::UserScope, "RdpOptions");
    set.beginGroup(group);
    set.setValue("host", opt.host());
    set.setValue("username", opt.username());
    set.setValue("password", QByteArray(opt.password().toStdString().c_str()).toBase64());
    set.setValue("fullscreen", opt.fullscreen());
    set.setValue("resolution", opt.resolution());
    set.setValue("useAllMonitors", opt.useAllMonitors());
    set.setValue("colors", opt.colors());
    set.setValue("fullscreenBar", opt.fullscreenBar());
    set.setValue("metaKeys", opt.metaKeys());
    set.setValue("useShell", opt.useShell());
    set.setValue("shell", opt.shell());
    set.setValue("shellWorkingDir", opt.shellWorkingDir());
    set.setValue("experience", opt.experience());
    set.setValue("bitmapCache", opt.bitmapCache());
    set.setValue("autoReconnect", opt.autoReconnect());
    set.setValue("keymap", opt.keymap());
    set.endGroup();
}

RdpOptions RdpOptionsHelper::load(QString group)
{
    if (group.isEmpty())
        group = getDefaultName();
    QSettings set(QSettings::UserScope, "RdpOptions");
    set.beginGroup(group);
    RdpOptions opt;
    opt.setHost(set.value("host", "").toString());
    opt.setUsername(set.value("username", "").toString());
    opt.setPassword(QByteArray::fromBase64(set.value("password", "").toByteArray()));
    opt.setFullscreen(set.value("fullscreen", true).toBool());
    opt.setResolution(set.value("resolution", QSize(0, 0)).toSize());
    opt.setUseAllMonitors(set.value("useAllMonitors", false).toBool());
    opt.setColors((RdpOptions::Colors)set.value("colors", RdpOptions::HighestQuality).toInt());
    opt.setFullscreenBar(set.value("fullscreenBar", true).toBool());
    opt.setMetaKeys(set.value("metaKeys", true).toBool());
    opt.setUseShell(set.value("useShell", false).toBool());
    opt.setShell(set.value("shell", "").toString());
    opt.setShellWorkingDir(set.value("shellWorkingDir", "").toString());
    opt.setExperience((RdpOptions::Experience)set.value("experience", RdpOptions::Detect).toInt());
    opt.setBitmapCache(set.value("bitmapCache", true).toBool());
    opt.setAutoReconnect(set.value("autoReconnect", true).toBool());
    opt.setKeymap(set.value("keymap", "en_US").toString());
    set.endGroup();
    return opt;
}

QList<RdpOptions> RdpOptionsHelper::loadAll()
{
    QSettings set(QSettings::UserScope, "RdpOptions");
    QList<RdpOptions> opts;
    opts.append(load(getDefaultName()));
    QStringList groups = set.childGroups();
    for (int i = 0; i < groups.size(); ++i)
    {
        QString group = groups.at(i);
        if (group != getDefaultName())
            opts.append(load(groups.at(i)));
    }
    return opts;
}

QString RdpOptionsHelper::getDefaultName()
{
    return "__Default__";
}
