#ifndef RDPOPTIONS_H
#define RDPOPTIONS_H

#include <QString>
#include <QSize>

class RdpOptions
{
public:
    RdpOptions();

    enum Colors
    {
        HighColor_15 = 15,
        HighColor_16 = 16,
        TrueColor = 24,
        HighestQuality = 32
    };

    enum Experience
    {
        Modem,
        LowSpeed,
        Satellite,
        HighSpeed,
        WAN,
        LAN,
        Detect
    };

    QString host() const;
    void setHost(const QString &host);

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    QSize resolution() const;
    void setResolution(const QSize &resolution);

    bool fullscreen() const;
    void setFullscreen(bool fullscreen);

    Experience experience() const;
    void setExperience(const Experience &experience);

    bool bitmapCache() const;
    void setBitmapCache(bool bitmapCache);

    bool metaKeys() const;
    void setMetaKeys(bool metaKeys);

    bool useShell() const;
    void setUseShell(bool useShell);

    QString shell() const;
    void setShell(const QString &shell);

    QString shellWorkingDir() const;
    void setShellWorkingDir(const QString &shellWorkingDir);

    Colors colors() const;
    void setColors(const Colors &colors);

    bool useAllMonitors() const;
    void setUseAllMonitors(bool useAllMonitors);

    bool fullscreenBar() const;
    void setFullscreenBar(bool fullscreenBar);

    bool autoReconnect() const;
    void setAutoReconnect(bool autoReconnect);

    QString keymap() const;
    void setKeymap(const QString &keymap);

private:
    QString m_host;

    QString m_username;

    QString m_password;

    bool m_fullscreen;

    QSize m_resolution;

    bool m_useAllMonitors;

    Colors m_colors;

    bool m_fullscreenBar;

    bool m_metaKeys;

    bool m_useShell;

    QString m_shell;

    QString m_shellWorkingDir;

    Experience m_experience;

    bool m_bitmapCache;

    bool m_autoReconnect;

    QString m_keymap;
};

#endif // RDPOPTIONS_H
