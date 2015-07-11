#include "rdesktoplauncher.h"
#include <QStringList>
#include <QProcess>
#include <QDebug>

RDesktopLauncher::RDesktopLauncher()
{
}

void RDesktopLauncher::start(RdpOptions options)
{
    QStringList args;
    args.append("-u");
    args.append(options.username());
    args.append("-p");
    args.append(options.password());
    args.append("-a");
    args.append(QString("%1").arg((int)options.colors()));
    if (!options.fullscreen())
    {
        args.append("-g");
        QSize reso = options.resolution();
        args.append(QString("%1x%2").arg(reso.width()).arg(reso.height()));
    }
    else
    {
        args.append("-f");
    }
    if (options.bitmapCache())
    {
        args.append("-P");
    }
    if (!options.metaKeys())
    {
        args.append("-K");
    }
    if (options.useShell())
    {
        args.append("-s");
        args.append(options.shell());
        args.append("-c");
        args.append(options.shellWorkingDir());
    }

    args.append("-k");
    args.append(options.keymap());

    args.append("-r");
    args.append("clipboard:PRIMARYCLIPBOARD");

    args.append(options.host());

    QProcess::startDetached("rdesktop", args);
}
