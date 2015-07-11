#include "rdpoptions.h"

RdpOptions::RdpOptions()
{
}

QString RdpOptions::host() const
{
    return m_host;
}

void RdpOptions::setHost(const QString &host)
{
    m_host = host;
}

QString RdpOptions::username() const
{
    return m_username;
}

void RdpOptions::setUsername(const QString &username)
{
    m_username = username;
}

QString RdpOptions::password() const
{
    return m_password;
}

void RdpOptions::setPassword(const QString &password)
{
    m_password = password;
}

QSize RdpOptions::resolution() const
{
    return m_resolution;
}

void RdpOptions::setResolution(const QSize &resolution)
{
    m_resolution = resolution;
}

bool RdpOptions::fullscreen() const
{
    return m_fullscreen;
}

void RdpOptions::setFullscreen(bool fullscreen)
{
    m_fullscreen = fullscreen;
}

RdpOptions::Experience RdpOptions::experience() const
{
    return m_experience;
}

void RdpOptions::setExperience(const Experience &experience)
{
    m_experience = experience;
}

bool RdpOptions::bitmapCache() const
{
    return m_bitmapCache;
}

void RdpOptions::setBitmapCache(bool bitmapCache)
{
    m_bitmapCache = bitmapCache;
}

bool RdpOptions::metaKeys() const
{
    return m_metaKeys;
}

void RdpOptions::setMetaKeys(bool metaKeys)
{
    m_metaKeys = metaKeys;
}

bool RdpOptions::useShell() const
{
    return m_useShell;
}

void RdpOptions::setUseShell(bool useShell)
{
    m_useShell = useShell;
}

QString RdpOptions::shell() const
{
    return m_shell;
}

void RdpOptions::setShell(const QString &shell)
{
    m_shell = shell;
}
QString RdpOptions::shellWorkingDir() const
{
    return m_shellWorkingDir;
}

void RdpOptions::setShellWorkingDir(const QString &shellWorkingDir)
{
    m_shellWorkingDir = shellWorkingDir;
}

RdpOptions::Colors RdpOptions::colors() const
{
    return m_colors;
}

void RdpOptions::setColors(const Colors &colors)
{
    m_colors = colors;
}
bool RdpOptions::useAllMonitors() const
{
    return m_useAllMonitors;
}

void RdpOptions::setUseAllMonitors(bool useAllMonitors)
{
    m_useAllMonitors = useAllMonitors;
}
bool RdpOptions::fullscreenBar() const
{
    return m_fullscreenBar;
}

void RdpOptions::setFullscreenBar(bool fullscreenBar)
{
    m_fullscreenBar = fullscreenBar;
}
bool RdpOptions::autoReconnect() const
{
    return m_autoReconnect;
}

void RdpOptions::setAutoReconnect(bool autoReconnect)
{
    m_autoReconnect = autoReconnect;
}
QString RdpOptions::keymap() const
{
    return m_keymap;
}

void RdpOptions::setKeymap(const QString &keymap)
{
    m_keymap = keymap;
}



















